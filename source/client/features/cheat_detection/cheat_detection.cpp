#include "cheat_detection.h"
#include <fstream>
#include "../../include/ctx.h"
#include "../../include/tf2.h"

void c_cheat_detection::scan_players() {
	
	if (!ctx->m_local_player || !ctx->m_local_weapon)
		return;

	for (const auto& player : ctx->players)
	{
		if (!player || !player->is_player() || player->is_dormant())
			continue;

		player_info_t info{};
		ctx->m_engine_client->get_player_info( player->entindex( ), &info);
		if (info.m_friends_id <= 0)
			continue;

		// do not init the same suspect twice mah guy
		if (m_suspects[ player->entindex( ) ].m_friends_id > 0)
			continue;

		if (!m_suspects[ player->entindex() ].m_detected_thru_list && tf2::is_a_cheater_unoptimized(info.m_friends_id))
		{
			m_suspects[player->entindex()].m_friends_id = info.m_friends_id;
			m_suspects[player->entindex()].m_marked = true;
			m_suspects[player->entindex()].m_detected_thru_list = true;
			continue;
		}

		if (m_suspects[player->entindex()].m_marked || m_suspects[player->entindex()].m_detected_thru_list)
			continue;

		m_suspects[ player->entindex( ) ] = c_suspect(info.m_friends_id, 5, 25, false, false, 1000, 1000, player, info.m_name, player->m_origin(), player->m_velocity());
	}

	for (size_t i = 0; i < m_suspects.size(); i++)
	{
		auto& suspect = m_suspects[i];
		if (suspect.m_dumped || suspect.m_friends_id <= 0 || suspect.m_marked)
			continue;

		if (!suspect.m_player)
			continue;

		// fakelag detection
		if (suspect.m_fakelag_strikes <= 0)
		{
			suspect.m_marked = true;
		}

		if (suspect.m_fakelag_strikes > 0 && suspect.m_next_fakelag-- <= 0)
		{
			const float old = *reinterpret_cast<float*>((suspect.m_player + 0x6C) + 0x4);
			const float diff = suspect.m_player->m_simulation_time() - old;
			int ticks = std::clamp(TIME_TO_TICKS(diff), 0, 22);

			if (ticks >= 12)
				suspect.m_fakelag_strikes--;

			suspect.m_next_fakelag = 4000;
		}

		if (suspect.m_strikes <= 0)
			suspect.m_marked = true;

		// antiaim detection
		if (suspect.m_player->m_eye_angles().m_x >= 90.f || suspect.m_player->m_eye_angles().m_x <= -90.f)
		{
			if (suspect.m_player->m_eye_angles().m_x >= 90.f)
				suspect.m_player->m_eye_angles().m_x = -89.f;

			if (suspect.m_player->m_eye_angles().m_x <= -90.f)
				suspect.m_player->m_eye_angles().m_x = 89.f;

			suspect.m_marked = true;
		}

		// marked for dump
		if (suspect.m_marked)
			drop_to_file(suspect);
	}
}

void c_cheat_detection::drop_to_file(c_suspect suspect) {
	std::ofstream output("players.txt", std::ios_base::app); // app allows to push to file
	output << std::to_string(suspect.m_friends_id).c_str() << std::endl;
	output.close();

	// actually mark him
	//tf2::m_cheat_ids.emplace_back(suspect.m_friends_id);
	suspect.m_dumped = true;
}
