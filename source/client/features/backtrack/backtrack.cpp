#include "backtrack.h"
#include <algorithm>

bool c_backtrack::is_tick_valid(float simulation_time)
{
	// https://github.com/sr2echa/TF2-Source-Code/blob/c61d9750613a088617fa183a56708becfd38b81a/tf2_src/game/server/player_lagcompensation.cpp#L382

	float correct = 0.f;
	correct += ctx->m_engine_client->get_net_channel_info()->get_latency(0);
	correct += ctx->m_engine_client->get_net_channel_info()->get_latency(1);
	correct += tf2::get_lerp_time();
	correct = std::clamp(correct, 0.f, 1.f);

	float target_time = simulation_time + tf2::get_lerp_time() * (config->m_exploits.m_fake_latency ? 4 : 1); // there we go
	float delta_time = correct - (TICKS_TO_TIME(ctx->m_globals->m_tick_count) - target_time);
	return std::fabs(delta_time) < 0.2f - TICKS_TO_TIME(1);
}

void c_backtrack::save_lag_comp()
{
	ctx->m_local_player = ctx->m_entity_list->get_client_entity(ctx->m_engine_client->get_local_player())->as< c_base_player >();

	if (!ctx->m_local_player || !ctx->m_local_weapon || tf2::is_non_aimable(ctx->m_local_weapon) || tf2::is_projectile_weapon(ctx->m_local_weapon))
		return;

	for (const auto& player : ctx->players )
	{
		if (!player->is_alive() || player->is_dormant() || player->m_team_num() == ctx->m_local_player->m_team_num() || !player->is_player())
		{
			m_records[ player->entindex( ) ].clear( );
			continue;
		}

		// https://github.com/sr2echa/TF2-Source-Code/blob/c61d9750613a088617fa183a56708becfd38b81a/tf2_src/game/server/player_lagcompensation.cpp#L288
		if (!m_records[ player->entindex( ) ].empty() && m_records[ player->entindex( ) ].front().m_simulation_time >= player->m_simulation_time())
			continue;

		/*
			Layer 11 Gotta update from latest tick and simtime has to go up not stay the same nor go down (simtime goes down when u shift)
		*/
		if (player->m_simulation_time() < player->m_old_simulation_time())
			continue;

		const float old = *reinterpret_cast<float*>((player + 0x6C) + 0x4);
		const float diff = player->m_simulation_time() - old;
		int ticks = TIME_TO_TICKS(diff);
		ticks = std::clamp(ticks, 0, 22);

		backtrack_record_t record{};
		record.m_maxs = player->m_maxs();
		record.m_mins = player->m_mins();
		record.m_angles = player->m_eye_angles();
		record.m_choked_packets = ticks;
		record.m_is_fake_lagging = ticks >= 7;
		record.m_cycle = player->m_cycle();
		record.m_origin = player->m_origin();
		record.m_velocity = player->m_velocity();
		record.m_world_space_center = player->get_world_space_center();
		record.m_simulation_time = player->m_simulation_time();
		record.m_model = player->get_model();
		player->setup_bones(record.m_bones, 128, 0x7FF00, player->m_simulation_time());

		const float velocity_per_tick = player->m_velocity().length_2d() * ctx->m_globals->m_interval_per_tick;
		if (player->m_velocity().length_2d() > 140.f)
		{
			int ticks_required = std::clamp((int)std::ceilf(64.f / velocity_per_tick), 0, 22);

			record.m_is_breaking_lagcomp = ticks >= ticks_required;
			if (record.m_is_breaking_lagcomp )
			{
				m_records[ player->entindex( ) ].clear();
				continue;
			}
		}

		m_records[player->entindex()].emplace_front(record);
		// erase all invalid records
		if (!config->m_exploits.m_fake_latency)
		{
			while (m_records[player->entindex()].size() > static_cast<size_t>(TIME_TO_TICKS(0.2f)))
				m_records[player->entindex()].pop_back();
		}
		else
		{
			if (!m_records[player->entindex()].empty() && m_records[player->entindex()].size() > 67)
			{
				if (auto invalid = std::find_if(std::cbegin(m_records[player->entindex()]), std::cend(m_records[player->entindex()]), [](const backtrack_record_t& rec) { 
					return !backtrack->is_tick_valid(rec.m_simulation_time) || rec.m_is_breaking_lagcomp;
				}); 
					invalid != std::cend(m_records[player->entindex()]))
					m_records[player->entindex()].erase(invalid, std::cend(m_records[player->entindex()]));
					// awesome codenz init mate
			}
		}
	}
}

void c_backtrack::update_sequences()
{
	static int last_incoming = 0;

	c_net_channel* netchan = (c_net_channel*)ctx->m_client_state->m_net_channel;
	if (netchan)
	{
		if (netchan->m_in_sequence_nr != last_incoming)
		{
			last_incoming = netchan->m_in_sequence_nr;

			seq sequence{};
			sequence.m_reliable = netchan->m_in_reliable_state;
			sequence.m_sequence = netchan->m_in_sequence_nr;
			sequence.m_servertime = ctx->m_globals->m_current_time;
			sequences.push_front(sequence);
		}

		if (sequences.size() > 2048)
			sequences.pop_back();
	}
}

void c_backtrack::add_latency(void* netchan, float latency)
{
	for (auto& seq : sequences)
	{
		if (ctx->m_globals->m_current_time - seq.m_servertime >= latency)
		{
			((c_net_channel*)netchan)->m_in_reliable_state = seq.m_reliable;
			((c_net_channel*)netchan)->m_in_sequence_nr = seq.m_sequence;
			break;
		}
	}
}

c_backtrack::backtrack_record_t c_backtrack::best_last_tick(int ent_idx)
{
	if (tf2::is_projectile_weapon(ctx->m_local_weapon) || m_records[ent_idx].empty() || m_records[ent_idx].size() < 2)
		return {};

	for (size_t i = m_records[ent_idx].size() - 1; i > 0; i--)
		if (is_tick_valid(m_records[ent_idx][i].m_simulation_time))
			return m_records[ent_idx][i];

	return {};
}

c_backtrack::backtrack_record_t c_backtrack::best_first_tick(int ent_idx)
{
	if (tf2::is_projectile_weapon(ctx->m_local_weapon) || m_records[ent_idx].empty() || m_records[ent_idx].size() < 2)
		return {};

	for (size_t i = 2; i < m_records[ent_idx].size(); i++)
		if (is_tick_valid(m_records[ent_idx][i].m_simulation_time))
			return m_records[ent_idx][i];

	return {};
}