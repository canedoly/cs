#include "hitscan.h"
#include "../visuals/visuals.h"
#include "../seed_prediction/seed_prediction.h"
#include "../cheat_detection/cheat_detection.h"

std::vector< c_hitscan::target_t > c_hitscan::get_best_targets() {
	std::vector< target_t > m_targets = { };

	for ( const auto& aimbot_entity : ctx->aimbot_entities ) {
		const auto& entity = aimbot_entity->as< c_base_player >( );
		if ( !entity || entity->is_dormant( ) || entity == ctx->m_local_player )
			continue;

		if ( entity->is_player( ) && ( entity->is_invulnerable( ) || entity->is_bonked( ) || entity->is_ghost( ) ) )
			continue;

		if ( !entity->is_enemy( ) )
			continue;

		if ( !( entity->is_player( ) && entity->as< c_base_player >( )->is_alive( ) ) && !entity->is_building( ) )
			continue;

		if (entity->is_cloaked() && config->m_aimbot_global.m_ignore_cloaked)
			continue;

		if ( entity->is_player( ) && entity->is_player_on_friend_list( ) && config->m_aimbot_global.m_ignore_friends )
			continue;

		target_t target;
		target.m_entity = entity;
		target.m_fov = math::calculate_fov( ctx->m_engine_client->get_view_angles( ), math::calculate_angle( ctx->m_local_player->get_shoot_position( ), entity->get_world_space_center( ) ) );
		target.m_distance = ctx->m_local_player->m_origin( ).dist_to( entity->m_origin( ) );

		if ( target.m_fov > config->m_aimbot_global.m_aim_fov )
			continue;

		target.m_priority = 2;
		m_targets.emplace_back( target );
	}

	if (config->m_aimbot.m_aim_stickies)
	{
		for (auto& projectile : ctx->projectiles)
		{
			const auto& entity = projectile->as< c_base_player >();
			if (!entity || entity->is_dormant() || entity == ctx->m_local_player)
				continue;

			if (projectile->m_pipebomb_type() != TYPE_STICKY)
				continue;

			const auto& thrower = ctx->m_entity_list->get_client_entity_from_handle(projectile->m_thrower())->as<c_base_player>();
			if (thrower && !thrower->is_enemy())
				continue;

			target_t target;
			target.m_entity = entity;
			target.m_fov = math::calculate_fov(ctx->m_engine_client->get_view_angles(), math::calculate_angle(ctx->m_local_player->get_shoot_position(), entity->get_world_space_center()));
			target.m_distance = ctx->m_local_player->m_origin().dist_to(entity->m_origin());

			if (target.m_fov > config->m_aimbot_global.m_aim_fov)
				continue;

			target.m_priority = 1;
			m_targets.emplace_back(target);
		}
	}

	std::sort( m_targets.begin( ), m_targets.end( ), [ ]( const target_t& a, const target_t& b ) {
		return a.m_fov < b.m_fov;
	} );

	std::sort( m_targets.begin( ), m_targets.end( ), [ ]( const target_t& a, const target_t& b ) {
		return a.m_priority < b.m_priority;
	} );

	if ( !m_targets.empty( ) )
		hitscan->closest_to_crosshair = m_targets.front( ).m_entity->as< c_base_player >( );

	return m_targets;
}

std::vector< vector > c_hitscan::generate_points_for_hitbox( c_base_player* player, int hitbox, matrix_3x4* backtrack_matrix, model_t* model ) {
	if ( !model )
		return { };

	studiohdr_t* hdr = ctx->m_model_info->get_studio_model( model );

	if ( !hdr )
		return { };

	if ( !backtrack_matrix )
		return { };

	mstudiohitboxset_t* set = hdr->hitbox_set( 0 );
	if ( !set )
		return { };

	mstudiobbox_t* box = set->hitbox( hitbox );
	if ( !box )
		return { };

	vector min = box->bbmin;
	vector max = box->bbmax;

	float scale = 0.5f;
	switch ( player->m_player_class( ) ) {
	case CLASS_HEAVY:
		scale = config->m_aimbot.m_heavy_mp / 100.f;
		break;
	case CLASS_SCOUT:
		scale = config->m_aimbot.m_scout_mp / 100.f;
		break;
	case CLASS_SNIPER:
		if ( hitbox != HITBOX_HEAD )
			scale = config->m_aimbot.m_sniper_mp / 100.f;
		break;
	default:
		return { player->get_hitbox_position_from_matrix( hitbox, backtrack_matrix, model ) };
		break;
	}

	const std::vector< vector > untransformed_points = {
		vector( ( min.m_x * -scale ), ( min.m_y * -scale ), ( min.m_z + max.m_z ) * 0.5f ),
		vector( ( min.m_x * scale ), ( min.m_y * scale ), ( min.m_z + max.m_z ) * 0.5f ),
		vector( ( min.m_x + max.m_x ) * 0.5f, ( min.m_y + max.m_y ) * 0.5f, ( max.m_z + min.m_z ) * 0.5f )
	};

	std::vector< vector > points = { };
	for ( const vector& point : untransformed_points ) {
		vector transformed = math::vector_transform( point, backtrack_matrix[ box->bone ] );
		// most likely fixes points clipping thru walls
		if ( !tf2::is_visible( player, NULL, player->get_world_space_center( ), transformed, MASK_SHOT | CONTENTS_GRATE ) )
			continue; // it does

		//ctx->m_debug_overlay->add_box_overlay(transformed, { -2,-2,-2 }, { 2,2,2 }, {}, 255, 255, 255, 255, TICK_INTERVAL * 2);
		//ctx->m_debug_overlay->add_text_overlay(transformed, TICK_INTERVAL * 2, "%i", hitbox);
		points.emplace_back( transformed );
	}

	return points;
}

shot_info_t c_hitscan::handle_hvh_classes( target_t target ) {
	shot_info_t info{ };

	auto player = target.m_entity->as< c_base_player >( );

	std::vector< int > hitboxes = { 5, 4, 3, 2, 1 };

	if ( config->m_aimbot.m_safe_point || player->m_player_class( ) == CLASS_SCOUT )
		hitboxes = { 1, 2 };

	// if no fake latency and if it is on and is lower than 120ms then do original model
	if ( !config->m_exploits.m_fake_latency || ( config->m_exploits.m_fake_latency && config->m_exploits.m_fake_latency_amount < 120 ) ) {

		// lets ensure the player is not shifting currently
		// simtime has to go up, has to be higher than old simtime and cannot be the same
		if (player->m_simulation_time() > player->m_old_simulation_time())
		{
			matrix_3x4 matrix[128];
			player->setup_bones(matrix, 128, 0x7FF00, ctx->m_globals->m_current_time);

			for (auto& hitbox : hitboxes) {
				std::vector< vector > points = generate_points_for_hitbox(player, hitbox, matrix, player->get_model());
				for (auto& point : points) {
					if (tf2::is_visible(ctx->m_local_player, player, ctx->m_local_player->get_shoot_position(), point, MASK_SHOT | CONTENTS_GRATE)) {
						info.m_choked_packets = -1; // no backtrack
						info.m_entity = player;
						info.m_found = true;
						info.m_pos = point;
						info.m_sim_time = player->m_simulation_time();
					}
				}
			}
		}
	}

	if ( info.m_found )
		return info;

	if ( config->m_exploits.m_fake_latency || config->m_exploits.m_backtrack ) {
		if (backtrack->m_records[player->entindex()].size() > 0)
		{
			for (size_t i = 0; i < backtrack->m_records[player->entindex()].size(); i++) {
				auto& rec = backtrack->m_records[player->entindex()][i];
				
				if (!backtrack->is_tick_valid(rec.m_simulation_time))
					continue;

				for (auto& hitbox : hitboxes) {
					vector pos = player->get_hitbox_position_from_matrix(hitbox, rec.m_bones, rec.m_model);
					if (tf2::is_visible(ctx->m_local_player, player, ctx->m_local_player->get_shoot_position(), pos, MASK_SHOT | CONTENTS_GRATE)) {
						info.m_choked_packets = rec.m_choked_packets;
						info.m_entity = player;
						info.m_found = true;
						info.m_pos = pos;
						info.m_sim_time = rec.m_simulation_time;
						info.record = rec;
						return info;
					}
				}
			}
		}
	}

	return info;
}

shot_info_t c_hitscan::handle_headshot_weapons(target_t target) {
	shot_info_t info{ };

	if ( ctx->m_local_weapon->get_weapon_id( ) == TF_WEAPON_SMG )
		return handle_other( target );

	auto player = target.m_entity->as<c_base_player>( );

	std::vector< int > hitboxes = {
		HITBOX_HEAD
	};

	if ( ( player->m_health( ) < 50 || ctx->m_local_weapon->m_charge_damage( ) >= player->m_health( ) ) && config->m_aimbot.m_baim_on_lethal )
		hitboxes = { HITBOX_NECK };

	// if no fake latency and if it is on and is lower than 120ms then do original model
	if ( !config->m_exploits.m_fake_latency || ( config->m_exploits.m_fake_latency && config->m_exploits.m_fake_latency_amount < 120 ) ) {
		matrix_3x4 matrix[ 128 ];
		player->setup_bones( matrix, 128, 0x7FF00, ctx->m_globals->m_current_time );

		for ( auto& hitbox : hitboxes ) {
			if ( hitbox == 0 ) {
				vector pos = player->get_hitbox_position_from_matrix(hitbox, matrix, player->get_model( ) );
				if ( tf2::is_visible( ctx->m_local_player, player, ctx->m_local_player->get_shoot_position( ), pos, MASK_SHOT | CONTENTS_GRATE ) ) {
					info.m_choked_packets = -1; // no backtrack
					info.m_entity = player;
					info.m_found = true;
					info.m_pos = pos;
					info.m_sim_time = player->m_simulation_time( );
					info.m_require_scope = true;
					info.m_headshot = true;
					return info;
				}
			}

			else {
				std::vector< vector > points = generate_points_for_hitbox( player, hitbox, matrix, player->get_model( ) );
				for ( auto& point : points ) {
					if ( tf2::is_visible( ctx->m_local_player, player, ctx->m_local_player->get_shoot_position( ), point, MASK_SHOT | CONTENTS_GRATE ) ) {
						info.m_choked_packets = -1; // no backtrack
						info.m_entity = player;
						info.m_found = true;
						info.m_pos = point;
						info.m_sim_time = player->m_simulation_time( );
						return info;
					}
				}
			}
		}
	}

	if ( config->m_exploits.m_fake_latency || config->m_exploits.m_backtrack ) {
		if (backtrack->m_records[player->entindex()].size() > 2)
		{
			for (size_t i = 2; i < backtrack->m_records[player->entindex()].size(); i++) {
				auto& rec = backtrack->m_records[player->entindex()][i];
				if (!backtrack->is_tick_valid(rec.m_simulation_time))
					continue;

				for (auto& hitbox : hitboxes) {
					vector pos = player->get_hitbox_position_from_matrix(hitbox, rec.m_bones, rec.m_model);
					if (tf2::is_visible(ctx->m_local_player, player, ctx->m_local_player->get_shoot_position(), pos, MASK_SHOT | CONTENTS_GRATE)) {
						info.m_choked_packets = rec.m_choked_packets;
						info.m_entity = player;
						info.m_found = true;
						info.m_pos = pos;
						info.m_sim_time = rec.m_simulation_time;
						info.record = rec;
						return info;
					}
				}
			}
		}
	}

	return info;
}

shot_info_t c_hitscan::handle_other( target_t target ) {
	shot_info_t info{ };

	auto player = target.m_entity->as< c_base_player >( );
	std::vector< int > hitboxes = { HITBOX_NECK, HITBOX_PELVIS };

	// if no fake latency and if it is on and is lower than 120ms then do original model
	if ( !config->m_exploits.m_fake_latency || ( config->m_exploits.m_fake_latency && config->m_exploits.m_fake_latency_amount < 120 ) ) {
		matrix_3x4 matrix[ 128 ];
		player->setup_bones( matrix, 128, 0x100, ctx->m_globals->m_current_time );

		for ( auto& hitbox : hitboxes ) {
			vector pos = player->get_hitbox_position_from_matrix(hitbox, matrix, player->get_model( ) );
			if ( tf2::is_visible( ctx->m_local_player, player, ctx->m_local_player->get_shoot_position( ), pos, MASK_SHOT | CONTENTS_GRATE ) ) {
				info.m_choked_packets = -1; // no backtrack
				info.m_entity = player;
				info.m_found = true;
				info.m_pos = pos;
				info.m_sim_time = player->m_simulation_time( );

				return info;
			}
		}
	}

	if ( config->m_exploits.m_fake_latency || config->m_exploits.m_backtrack ) {
		if (backtrack->m_records[player->entindex()].size() > 2)
		{
			for (size_t i = 2; i < backtrack->m_records[player->entindex()].size(); i++) {
				auto& rec = backtrack->m_records[player->entindex()][i];
				if (!backtrack->is_tick_valid(rec.m_simulation_time))
					continue;

				for (auto& hitbox : hitboxes) {
					vector pos = player->get_hitbox_position_from_matrix(hitbox, rec.m_bones, rec.m_model);
					if (tf2::is_visible(ctx->m_local_player, player, ctx->m_local_player->get_shoot_position(), pos, MASK_SHOT | CONTENTS_GRATE)) {
						info.m_choked_packets = rec.m_choked_packets;
						info.m_entity = player;
						info.m_found = true;
						info.m_pos = pos;
						info.m_sim_time = rec.m_simulation_time;
						info.record = rec;
						return info;
					}
				}
			}
		}
	}

	return info;
}

shot_info_t c_hitscan::handle_buildings( target_t target ) {
	shot_info_t info{ };
	info.m_found = false;
	auto player = target.m_entity->as< c_base_player >( );

	vector pos = player->get_world_space_center( );
	if ( tf2::is_visible( ctx->m_local_player, player, ctx->m_local_player->get_shoot_position( ), pos, MASK_SHOT | CONTENTS_GRATE ) ) {
		info.m_entity = player;
		info.m_found = true;
		info.m_pos = pos;
		return info;
	}

	return info;
}

void c_hitscan::handle_tap_fire( shot_info_t info, c_user_cmd* cmd ) {
	if ( config->m_aimbot.m_tap_fire && !( config->m_seed_pred.m_enabled ) ) {
		float last_shot = ( ctx->m_local_player->m_tick_base( ) * ctx->m_globals->m_interval_per_tick ) - ctx->m_local_weapon->m_last_fire_time( );

		if ( ctx->m_local_player->m_player_class( ) == CLASS_HEAVY && ctx->m_local_player->m_origin( ).dist_to( info.m_pos ) > config->m_aimbot.m_tap_fire_distance ) {
			if ( last_shot <= 0.25f )
				cmd->m_buttons &= ~IN_ATTACK;
		}

		else if ( ( ctx->m_local_weapon->m_item_definition_index( ) == Spy_m_FestiveAmbassador || ctx->m_local_weapon->m_item_definition_index( ) == Spy_m_TheAmbassador ) && info.m_entity->as< c_base_player >( )->m_health( ) > 50 ) {
			if ( last_shot <= 0.990f )
				cmd->m_buttons &= ~IN_ATTACK;
		}

		if ( ctx->m_local_player->m_player_class( ) == CLASS_SNIPER && ctx->m_local_weapon->get_slot( ) == 0 ) {
			if ( info.m_headshot ) {
				if ( !ctx->m_local_weapon->can_fire_critical_shot( true ) )
					cmd->m_buttons &= ~IN_ATTACK;

				if ( info.m_entity->as< c_base_player >( )->m_health( ) > 150 ) {
					float damage = math::remap_val_clamped( ctx->m_local_weapon->m_charge_damage( ), 0.0f, 150.0f, 0.0f, 450.0f );
					if ( !( damage >= info.m_entity->as< c_base_player >( )->m_health( ) || damage == 450 ) )
						cmd->m_buttons &= ~IN_ATTACK;
				}
			}

			else {
				float damage = ctx->m_local_weapon->m_charge_damage( );
				if ( !( damage >= info.m_entity->as< c_base_player >( )->m_health() || damage == 150.f ) )
					cmd->m_buttons &= ~IN_ATTACK;
			}
		}
	}
}

void c_hitscan::run( c_user_cmd* cmd ) {
	if ( !config->m_aimbot_global.m_enabled || !config->m_aimbot.m_enabled )
		return;

	if ( !ctx->m_local_player || !ctx->m_local_player->is_alive( ) || !ctx->m_local_weapon )
		return;

	if ( tf2::is_projectile_weapon( ctx->m_local_weapon ) || tf2::is_non_aimable( ctx->m_local_weapon ) || ctx->m_local_weapon->get_slot( ) == 2 )
		return;

	if ( config->m_aimbot.m_require_key && !config->m_aimbot_global.m_aim_key.is_held( ) )
		return;

	auto targets = get_best_targets();
	if ( targets.empty( ) )
		return;

	const bool is_key_held = config->m_aimbot_global.m_aim_key.is_held();

	vector old_angles = cmd->m_view_angles;
	static c_base_player* old_target = { };
	shot_info_t info;
	static bool has_shot_at_target = false;

	for ( auto& best_target : targets ) {
		if ( !best_target.m_entity->is_player( ) )
			info = handle_buildings( best_target );
		else {
			switch ( ctx->m_local_player->m_player_class( ) ) {
				case CLASS_ENGINEER: {
					info = handle_other( best_target );
					break;
				}

				case CLASS_SOLDIER:
				case CLASS_PYRO: {
					if ( ctx->m_local_weapon->get_weapon_id( ) != TF_WEAPON_SHOTGUN_PYRO && ctx->m_local_weapon->get_weapon_id( ) != TF_WEAPON_SHOTGUN_SOLDIER )
						return;

					info = handle_other( best_target );
					break;
				}

				case CLASS_SPY:
				case CLASS_SNIPER: {
					info = handle_headshot_weapons( best_target );
					break;
				}

				case CLASS_SCOUT:
				case CLASS_HEAVY: {
					info = handle_hvh_classes( best_target );
					break;
				}
			}
		}

		if ( info.m_found )
			break;
	}

	if ( info.m_found && info.m_entity ) {
		if ( old_target != info.m_entity->as< c_base_player >( ) ) {
			old_target = info.m_entity->as< c_base_player >( );
			has_shot_at_target = false;
		}

		const float old = *reinterpret_cast< float* >( ( info.m_entity->as< c_base_player >( ) + 0x6C ) + 0x4 );
		const float diff = info.m_entity->as< c_base_player >( )->m_simulation_time( ) - old;
		int ticks = TIME_TO_TICKS( diff );
		ticks = std::clamp( ticks, 0, 22 );

		// fakelag fix
		if (info.m_entity->is_player() && ticks > 6 && info.m_entity->as<c_base_player>()->m_velocity().length() > 178.f)
			return;

		bool result = false;
		if ( ctx->m_shifted_ticks < 19 && ctx->m_charged_ticks > 5 && info.m_entity->is_player( ) ) {
			int ticks = std::floor( 10 * ( config->m_aimbot.m_delayshot_percent / 100.f ) );
			const vector extrapolated = ctx->m_local_player->get_shoot_position( ) + ( ctx->m_local_player->m_velocity( ) * -TICKS_TO_TIME( ticks ) );
			//const vector extrapolated2 = ctx->m_local_player->get_shoot_position( ) + ( ctx->m_local_player->m_velocity( ) * TICKS_TO_TIME( ticks ) );

			result = tf2::is_visible( ctx->m_local_player, info.m_entity, extrapolated, info.m_pos, MASK_SHOT | CONTENTS_GRATE ); //&&
			//tf2::is_visible(ctx->m_local_player, info.m_entity, extrapolated2, info.m_pos, MASK_SHOT | CONTENTS_GRATE);

			if ( !has_shot_at_target ) {
				if ( ctx->m_shift || ctx->m_running_shift )
					result = true;

				if ( !result )
					return;
			}
		}

		if ( is_key_held ) {
			if ( ctx->m_local_player->m_player_class( ) == CLASS_SNIPER && info.m_require_scope && !ctx->m_local_player->is_zoomed( ) && config->m_aimbot.m_auto_scope ) {
				cmd->m_buttons |= IN_ATTACK2;
				return;
			}

			cmd->m_buttons |= IN_ATTACK;
		}

		handle_tap_fire( info, cmd );

		vector angle = math::calculate_angle( ctx->m_local_player->get_shoot_position( ), info.m_pos );
		math::clamp_angle(angle);

		if (cmd->m_buttons & IN_ATTACK) {
			cmd->m_view_angles = angle;

			if ( ctx->m_local_weapon->can_shoot( ) ) {

				ctx->m_aimbot_angles = cmd->m_view_angles;
				ctx->m_aimbot_delay = 250;

				if ( !info.m_entity->is_building( ) ) {
					auto record = info.record;

					if ( !record.m_model ) {
						matrix_3x4* boner = nullptr;
						info.m_entity->as< c_base_player >( )->setup_bones( boner, 128, 0x100, ctx->m_globals->m_current_time );
						visuals->draw_hitboxes( info.m_entity->as< c_base_player>( ), info.m_entity->as< c_base_player >( )->get_model( ), boner, color( 255, 255, 255, 10 ), color( 255, 255, 255 ), 0.2f );
					}

					else
					{
						visuals->draw_hitboxes(info.m_entity->as< c_base_player >(), record.m_model, record.m_bones, color(255, 255, 255, 10), color(255, 255, 255), 0.2f);

						// apparently we need to backup this to the recorded position
						info.m_entity->as< c_base_player >( )->m_eye_angles() = record.m_angles;
						info.m_entity->as< c_base_player >( )->m_mins() = record.m_mins;
						info.m_entity->as< c_base_player >( )->m_maxs() = record.m_maxs;
						//info.m_entity->as< c_base_player >( )->m_origin() = record.m_origin; // can cause issues (visually)
						info.m_entity->as< c_base_player >( )->m_velocity() = record.m_velocity;
						info.m_entity->as< c_base_player >( )->m_cycle() = record.m_cycle;
					}

					cmd->m_tick_count = TIME_TO_TICKS(info.m_sim_time + tf2::get_lerp_time());
				}

				has_shot_at_target = true;
			}
		}
	}
}