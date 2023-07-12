#include "melee.h"
#include "../visuals/visuals.h"

bool c_melee::can_backstab(const vector& source, const vector& destination, vector wsc_delta) {
	wsc_delta.m_z = 0;
	wsc_delta.normalize_in_place();

	auto source_forward = vector();
	math::angle_vectors(source, &source_forward);

	source_forward.m_z = 0;
	source_forward.normalize_in_place();

	auto destination_forward = vector();
	math::angle_vectors(destination, &destination_forward);

	destination_forward.m_z = 0;
	destination_forward.normalize_in_place();

	if (wsc_delta.dot_product(source_forward) <= 0.5f)
		return false;

	if (wsc_delta.dot_product(destination_forward) <= 0.01f)
		return false;

	if (source_forward.dot_product(destination_forward) <= -0.3f)
		return false;

	return true;
}

void c_melee::run(c_user_cmd* cmd)
{
	if (!ctx->m_local_player || !ctx->m_local_player->is_alive() || !ctx->m_local_weapon || !config->m_aimbot_global.m_enabled || !config->m_melee_aim.m_enable || ( config->m_melee_aim.m_require_aimkey && !config->m_aimbot_global.m_aim_key.is_held( ) ) )
		return;

	if (ctx->m_local_weapon->get_slot() != 2)
		return;

	if (ctx->m_local_player->is_cloaked())
		return;

	float best_distance = 80.f;

	std::vector<c_target> possible_targets = {};

	for (const auto& entity : ctx->aimbot_entities) {
		const auto& player = entity->as<c_base_player>();
		if (!player || player == ctx->m_local_player || player->is_dormant() )
			continue;

		if (player->is_player() && !player->is_alive())
			continue;

		if (player->is_player() && (player->is_invulnerable() ||
			player->is_bonked() ||
			player->is_ghost() ||
			(player->is_player_on_friend_list() && config->m_aimbot_global.m_ignore_friends && ctx->m_local_weapon->m_item_definition_index() != Soldier_t_TheDisciplinaryAction)))
			continue;

		// predict swing
		float dst = (ctx->m_local_player->get_world_space_center() + ctx->m_local_player->m_velocity() * TICKS_TO_TIME(4)).dist_to(player->get_world_space_center());
		if (ctx->m_local_player->m_player_class() == CLASS_SPY) // do not do it on spy
			dst = ctx->m_local_player->get_world_space_center().dist_to(player->get_world_space_center());

		c_target target = {};

		if (player->is_player())
		{
			// we dont backtrack friends
			if (ctx->m_local_weapon->m_item_definition_index() == Soldier_t_TheDisciplinaryAction)
			{
				if (!player->is_enemy() && config->m_melee_aim.m_smack_friends && dst <= best_distance)
				{
					target.m_dst = dst;
					target.m_player = player;
					target.m_record = {};
					target.m_priority = 1;
					possible_targets.emplace_back(target);
					continue;
				}
			}

			if (backtrack->m_records[player->entindex()].size() > 2)
			{
				for (size_t i = 2; i < backtrack->m_records[player->entindex()].size(); i++)
				{
					auto& record = backtrack->m_records[player->entindex()][i];
					if (!backtrack->is_tick_valid(record.m_simulation_time))
						continue;

					dst = ctx->m_local_player->get_world_space_center().dist_to(record.m_world_space_center);
					if (ctx->m_local_player->m_player_class() != CLASS_SPY)
						dst = (ctx->m_local_player->get_world_space_center() + ctx->m_local_player->m_velocity() * TICKS_TO_TIME(4)).dist_to(record.m_world_space_center);

					if (dst <= best_distance)
					{
						vector angle_to = math::calculate_angle(ctx->m_local_player->get_shoot_position(), record.m_world_space_center);
						if (config->m_melee_aim.m_if_backstable && ctx->m_local_player->m_player_class() == CLASS_SPY &&
							!can_backstab(angle_to, player->m_eye_angles(), record.m_world_space_center - ctx->m_local_player->get_world_space_center())) {
							target = {};
							continue;
						}

						target.m_dst = dst;
						target.m_player = player;
						target.m_record = record;
						target.m_priority = 1;
						possible_targets.emplace_back(target);
					}
				}
			}
		}
		else
		{
			if (dst > best_distance)
				continue;

			if (!config->m_melee_aim.m_smack_friedly_buildings)
				if (!player->is_enemy())
					continue;

			if (ctx->m_local_player->m_player_class() != CLASS_ENGINEER)
				continue;

			const auto& builder = ctx->m_entity_list->get_client_entity_from_handle(player->as<c_base_object>()->m_builder())->as<c_base_player>();
			if (!builder)
				continue;
			
			target.m_dst = dst;
			target.m_player = player;
			target.m_record = {};
			target.m_priority = builder->is_local_player() ? 2 : 1;
			possible_targets.emplace_back(target);
		}
	}

	std::sort(possible_targets.begin(), possible_targets.end(), [](const c_target& a, c_target& b) {

		if (a.m_priority != b.m_priority)
			return a.m_priority > b.m_priority;

		return a.m_dst < b.m_dst;
	});

	if (possible_targets.empty())
		return;

	c_target target = possible_targets.front();

	if (target.m_player)
	{
		vector angle = math::calculate_angle(ctx->m_local_player->get_shoot_position(), target.m_record.m_simulation_time > 0.f ? target.m_record.m_world_space_center : target.m_player->get_world_space_center());
		math::clamp_angle(angle);

		// duck when above player // idk if this is a good idea
		if (!(ctx->m_local_player->m_flags() & FL_ONGROUND) && ctx->m_local_player->m_origin().m_z - target.m_record.m_origin.m_z > 45.f)
			cmd->m_buttons |= IN_DUCK;

		cmd->m_view_angles = angle;
		cmd->m_buttons |= IN_ATTACK;

		ctx->m_aimbot_angles = cmd->m_view_angles;
		ctx->m_aimbot_delay = 148;

		if (ctx->m_local_weapon->is_attacking(cmd))
		{
			// gotta make sure g
			if (target.m_record.m_simulation_time > 0.f)
			{
				target.m_player->m_eye_angles() = target.m_record.m_angles;
				target.m_player->m_mins() = target.m_record.m_mins;
				target.m_player->m_maxs() = target.m_record.m_maxs;
				//target.m_player->m_origin() = target.m_record.m_origin;
				target.m_player->m_velocity() = target.m_record.m_velocity;
				target.m_player->m_cycle() = target.m_record.m_cycle;

				visuals->draw_hitboxes(target.m_player, target.m_record.m_model, target.m_record.m_bones, color(255, 255, 255, 10), color(255, 255, 255), ctx->m_engine_client->get_net_channel_info()->get_latency(1));
				cmd->m_tick_count = TIME_TO_TICKS(target.m_record.m_simulation_time + tf2::get_lerp_time());
			}
			else
			{
				if (target.m_player->is_player())
				{
					matrix_3x4 boner[128] = {};
					target.m_player->setup_bones(boner, 128, 0x100, ctx->m_globals->m_current_time);
					visuals->draw_hitboxes(target.m_player, target.m_player->get_model(), boner, color(255, 255, 255, 10), color(255, 255, 255), ctx->m_engine_client->get_net_channel_info()->get_latency(1));
					cmd->m_tick_count = TIME_TO_TICKS(target.m_player->m_simulation_time() + tf2::get_lerp_time());
				}
			}
		}
	}
}