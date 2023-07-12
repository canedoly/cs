#include "misc.h"
#include "../hitscan/hitscan.h"
#include "../../hooks/hooks.h"

void c_misc::run( c_user_cmd* cmd ) {
	if ( !ctx->m_local_player || !ctx->m_local_player->is_alive( ) || !ctx->m_local_weapon )
		return;

	if ( config->m_misc.m_taunt_slide )
		taunt_slide( ctx->m_local_player, cmd );

	if (!ctx->m_local_player->is_taunting())
	{
		if (config->m_misc.m_bunnyhop)
			bunnyhop(ctx->m_local_player, cmd);

		if (config->m_misc.m_auto_strafer)
			auto_strafer(cmd);

		if (config->m_misc.m_fast_stop && !ctx->m_running_shift)
			fast_stop(cmd);
	}
}

void c_misc::anti_aim( c_user_cmd* cmd, bool* send_packet ) {
	if ( !ctx->m_local_player || !ctx->m_local_player->is_alive( ) || !ctx->m_local_weapon )
		return;

	if ( ctx->m_running_shift || ctx->m_shift)
		return;

	auto old_angles = cmd->m_view_angles;

	c_base_player* best_player = hitscan->closest_to_crosshair;
	static bool side = false;
	bool found_local = false;
	if (best_player)
	{
		vector left, right, forward;
		math::angle_vectors(ctx->m_engine_client->get_view_angles() - vector(0.0f, 90.0f, 0.0f), &left);
		math::angle_vectors(ctx->m_engine_client->get_view_angles() + vector(0.0f, 90.0f, 0.0f), &right);

		left = ctx->m_local_player->get_world_space_center() + left * 65;
		right = ctx->m_local_player->get_world_space_center() + right * 65;

		if (tf2::is_visible(best_player, ctx->m_local_player, best_player->get_world_space_center(), left, MASK_SHOT | CONTENTS_GRATE))
		{
			side = false;
			found_local = true;
		}

		if (tf2::is_visible(best_player, ctx->m_local_player, best_player->get_world_space_center(), right, MASK_SHOT | CONTENTS_GRATE))
		{
			side = true;
			found_local = true;
		}
	}

	static int pitch_swap_delay = 0;
	static int real_swap_delay = 0;
	static int fake_swap_delay = 0;

	if (config->m_hvh.m_pitch.m_enabled)
	{
		static float pitch = 69.f;
		static bool swap = false;
		if (config->m_hvh.m_pitch.m_jitter)
		{
			if (pitch_swap_delay-- <= 0)
			{
				swap = !swap;
				pitch = swap ? config->m_hvh.m_pitch.m_min_angle : config->m_hvh.m_pitch.m_max_angle;
				pitch_swap_delay = config->m_hvh.m_pitch.m_jitter_max;
			}
		}
		else
		{
			pitch = config->m_hvh.m_pitch.m_pitch_angle;
		}
		
		cmd->m_view_angles.m_x = pitch;
	}

	ctx->m_real_angles.m_x = ctx->m_fake_angles.m_x = cmd->m_view_angles.m_x;

	static int angle_multiplier = -1;

	float fake_yaw = cmd->m_view_angles.m_y;
	float real_yaw = cmd->m_view_angles.m_y;

	if (!config->m_hvh.m_fakelag && ( !config->m_hvh.m_fake_yaw.m_enabled || !config->m_hvh.m_real_yaw.m_enabled ) || ctx->m_unchoke_del > 1 ) {
		if (ctx->m_choke_tick)
			ctx->m_choke_tick = false;

		else
			ctx->m_choke_tick = true;

		*send_packet = ctx->m_choke_tick;
	}

	if (config->m_hvh.m_fake_yaw.m_enabled && *send_packet == true)
	{
		fake_yaw += !side ? 90.f : -90.f;

		if (config->m_hvh.m_fake_yaw.m_jitter)
		{
			if (fake_swap_delay-- <= 0)
			{
				static int current_angle_index = 0;
				std::vector<float> angles = {};

				for (int n = 1; n <= config->m_hvh.m_fake_yaw.m_jitter_max + 1; n++)
				{
					angles.emplace_back((config->m_hvh.m_fake_yaw.m_min_angle / n) * 10);
					angles.emplace_back((config->m_hvh.m_fake_yaw.m_max_angle / n) * 10);
				}

				if (static_cast<size_t>(current_angle_index++) >= angles.size() - 1u)
					current_angle_index = 0;

				fake_yaw += angles[current_angle_index];
				fake_swap_delay = 3; // yessir
			}
		}

		if (config->m_hvh.m_fake_yaw.m_anti_logic)
		{
			fake_yaw += ctx->m_globals->m_current_time * 630.f;
			while (fake_yaw > 180.f)
				fake_yaw -= 360.f;

			while (fake_yaw < -180.f)
				fake_yaw += 360.f;
		}

		cmd->m_view_angles.m_y += fake_yaw;
		ctx->m_fake_angles = cmd->m_view_angles;
	}

	if (config->m_hvh.m_real_yaw.m_enabled && *send_packet == false)
	{
		if (config->m_hvh.m_real_yaw.m_edge)
		{
			real_yaw -= side ? -90.f : 90.f;
		}
		else if (config->m_hvh.m_real_yaw.m_anti_logic)
		{
			if (real_swap_delay-- <= 0)
			{
				if (side)
					angle_multiplier = 1.f;
				else
					angle_multiplier = -1.f;

				real_swap_delay = 8; // yessir
			}
		}

		cmd->m_view_angles.m_y += std::clamp(real_yaw, -180.f, 180.f);
		ctx->m_real_angles = cmd->m_view_angles;
		
		if (!ctx->m_local_player->is_taunting())
			leg_jitter(cmd);
	}

	if ( ( ctx->m_local_weapon->get_weapon_id( ) == TF_WEAPON_PIPEBOMBLAUNCHER || ctx->m_local_weapon->get_weapon_id( ) == TF_WEAPON_COMPOUND_BOW ) && ctx->m_local_weapon->m_charge_begin_time( ) > 0.0f )
		cmd->m_view_angles = old_angles;

	else if ( cmd->m_buttons & IN_ATTACK && ctx->m_local_weapon->can_shoot( ) )
		cmd->m_view_angles = old_angles;
}

void c_misc::leg_jitter( c_user_cmd* cmd ) {
	static bool pos = false;
	if ( cmd->m_forward_move == 0.f && cmd->m_side_move == 0.f && ctx->m_local_player->m_velocity( ).length_2d( ) < 10.f )
	{
		if ( ctx->m_local_player->m_ducked( ) )
		{
			const float yaw = DEG_TO_RAD( fmodf( ctx->m_globals->m_current_time * 360.f * 1.95f, 360.f ) );
			const float velDir = yaw;
			const float wishAng = atan2f( -cmd->m_side_move, cmd->m_forward_move );
			const float delta = math::angle_diff_rad( velDir, wishAng );
			const float moveDir = delta < 0.0f ? velDir : velDir;
			cmd->m_forward_move = cosf( moveDir ) * 3.75f;
			cmd->m_side_move = -sinf( moveDir ) * 3.75f;
			pos = !pos;
		}
		else
		{
			const float yaw = DEG_TO_RAD( fmodf( ctx->m_globals->m_current_time * 360.f * 1.95f, 360.f ) );
			const float velDir = yaw;
			const float wishAng = atan2f( -cmd->m_side_move, cmd->m_forward_move );
			const float delta = math::angle_diff_rad( velDir, wishAng );
			const float moveDir = delta < 0.0f ? velDir : velDir;
			cmd->m_forward_move = cosf( moveDir ) * 1.25f;
			cmd->m_side_move = -sinf( moveDir ) * 1.25f;
			pos = !pos;
		}
	}
}

void c_misc::handle_dt(c_user_cmd* cmd, bool* send_packet) {
	if (!ctx->m_local_player || !ctx->m_local_weapon || (!(ctx->m_local_player->m_flags() & FL_ONGROUND) && !config->m_exploits.m_doubletap_in_air))
		return;

	if (!tf2::is_allowed_to_dt(ctx->m_local_weapon))
		return;

	if (ctx->m_warping)
	{
		cmd->m_buttons &= ~(IN_ATTACK);
		return;
	}

	if (!ctx->m_shift && !ctx->m_running_shift) {
		static c_base_combat_weapon* old_weapon = nullptr;

		if (old_weapon != ctx->m_local_weapon) {
			ctx->m_wait_ticks = 24;
			old_weapon = ctx->m_local_weapon;
		}

		if (!ctx->m_local_weapon->can_shoot() && ctx->m_shifted_ticks <= 0)
			ctx->m_wait_ticks = 24;

		if (ctx->m_local_player->m_player_class() == CLASS_HEAVY) {
			if (ctx->m_local_weapon->get_slot() == SLOT_PRIMARY && ctx->m_local_weapon->m_minigun_state() != AC_STATE_SPINNING)
				ctx->m_wait_ticks = 24;
		}
	}

	if (ctx->m_wait_ticks > 0)
		return;

	if (cmd->m_buttons & IN_ATTACK && ctx->m_local_weapon->can_shoot())
	{
		auto allowed_ticks = config->m_misc.m_reduce_input_delay ? 20 : (ctx->m_local_weapon->m_item_definition_index() == Scout_m_ForceANature ||
			ctx->m_local_weapon->m_item_definition_index() == Scout_m_FestiveForceANature) ? 21 : 22;

		if (ctx->m_charged_ticks >= allowed_ticks)
		{
			*send_packet = false;
			ctx->m_shift = true;
		}
	}
}

void c_misc::bunnyhop( c_base_player* player, c_user_cmd* cmd ) {
	static bool jump_state = false;

	if ( cmd->m_buttons & IN_JUMP ) {
		if ( !jump_state && !( player->m_flags( ) & FL_ONGROUND ) )
			cmd->m_buttons &= ~IN_JUMP;

		else if ( jump_state )
			jump_state = false;
	}

	else if ( !jump_state )
		jump_state = true;
}

void c_misc::velocity_handler( c_user_cmd* cmd ) {
	if (!config->m_aimbot.m_delayshot)
		return;

	auto angles = vector( ), forward = vector( );
	if ( ctx->m_local_player && ctx->m_running_shift && !ctx->m_warping ) {
		if ( ctx->m_charged_ticks > ( config->m_misc.m_reduce_input_delay ? 6 : 14 ) ) {
			math::vector_angles( ctx->m_local_player->m_velocity( ), angles );
			angles.m_y = cmd->m_view_angles.m_y - angles.m_y;
			math::angle_vectors( angles, &forward );
			forward *= ctx->m_local_player->m_velocity( ).length( );

			cmd->m_forward_move = -forward.m_x * ( config->m_misc.m_reduce_input_delay ? 2.f : 1.f );
			cmd->m_side_move = -forward.m_y * ( config->m_misc.m_reduce_input_delay ? 2.f : 1.f );
		}
		else if (ctx->m_charged_ticks > ( config->m_misc.m_reduce_input_delay ? 1 : 3 ) )
		{
			cmd->m_forward_move = cmd->m_side_move = 0.0f;
			cmd->m_buttons &= ~(IN_FORWARD | IN_BACK | IN_MOVELEFT | IN_MOVERIGHT);
		}
	}
}

void c_misc::auto_strafer( c_user_cmd* cmd ) {
	static bool was_jumping = false;
	bool is_jumping = cmd->m_buttons & IN_JUMP;

	if ( !ctx->m_local_player || !ctx->m_local_player->is_alive( ) || ctx->m_local_player->m_water_level( ) > 1 )
		return;

	if ( ctx->m_local_player->m_move_type( ) == MOVETYPE_NOCLIP
		 || ctx->m_local_player->m_move_type( ) == MOVETYPE_LADDER
		 || ctx->m_local_player->m_move_type( ) == MOVETYPE_OBSERVER )
	{
		return;
	}

	if ( !( ctx->m_local_player->m_flags( ) & FL_ONGROUND ) && ( !is_jumping || was_jumping ) ) {
		if ( ctx->m_local_player->m_flags( ) & ( 1 << 11 ) )
			return;

		const float speed = ctx->m_local_player->m_velocity( ).length_2d( );
		auto& velocity = ctx->m_local_player->m_velocity( );

		if ( speed < 2.0f )
			return;

		const auto compute_perfect_delta = [ ]( float speed ) noexcept {
			static auto air_acceleration = ctx->m_cvar->find_var( "sv_airaccelerate" );

			if ( !air_acceleration )
				return 0.0f;

			const auto term = 25.f / air_acceleration->get_float( ) / powf( ctx->m_local_player->m_max_speed( ), 2.0f ) / speed;

			if ( term < 1.0f && term > -1.0f )
				return acosf( term );

			return 0.f;
		};

		if ( const auto delta = compute_perfect_delta( speed ) ) {
			const auto yaw = DEG_TO_RAD( ctx->m_engine_client->get_view_angles().m_y);
			const auto velocity_direction = atan2f( velocity.m_y, velocity.m_x ) - yaw;
			const auto wish_angle = atan2f( -cmd->m_side_move, cmd->m_forward_move );
			const auto delta_ = math::angle_diff_rad( velocity_direction, wish_angle );
			const auto move_direction = delta_ < 0.0f ? velocity_direction + delta : velocity_direction - delta;

			cmd->m_forward_move = cosf( move_direction ) * 450.f;
			cmd->m_side_move = -sinf( move_direction ) * 450.f;
		}
	}

	was_jumping = is_jumping;
}

void c_misc::fast_stop( c_user_cmd* cmd ) {
	if ( cmd->m_buttons & ( IN_FORWARD | IN_BACK | IN_MOVELEFT | IN_MOVERIGHT ) )
		return;

	if ( !ctx->m_local_player || !ctx->m_local_player->is_alive( ) )
		return;

	if ( ctx->m_local_player->m_flags( ) & FL_ONGROUND ) {
		const auto speed = ctx->m_local_player->m_velocity( ).length( );
		if ( speed > 20.f ) {
			vector direction;
			math::vector_angles(ctx->m_local_player->m_velocity(), direction);
			direction.m_y = cmd->m_view_angles.m_y - direction.m_y;
			vector forward;
			math::angle_vectors(direction, &forward);

			vector negated_direction = forward * speed;

			cmd->m_forward_move = -negated_direction.m_x;
			cmd->m_side_move = -negated_direction.m_y;
		}
	}
}

void c_misc::taunt_slide( c_base_player* player, c_user_cmd* cmd ) {
	if ( player->m_player_cond( ) & TFCond_Taunting ) {
		float forward = 0.0f, side = 0.0f;

		if ( cmd->m_buttons & IN_FORWARD )
			forward += 450.f;

		if ( cmd->m_buttons & IN_BACK ) {
			side -= 450.f;
			cmd->m_view_angles.m_z = -90.f;
		}

		if ( cmd->m_buttons & IN_MOVELEFT )
			side -= 450.f;

		if ( cmd->m_buttons & IN_MOVERIGHT )
			side += 450.f;

		if ( ( !( cmd->m_buttons & IN_FORWARD ) && !( cmd->m_buttons & IN_BACK ) && !( cmd->m_buttons & IN_MOVELEFT ) && !( cmd->m_buttons & IN_MOVERIGHT ) ) ) {
			forward -= 450.f;
			cmd->m_view_angles.m_x = 90.f;
		}

		cmd->m_forward_move = forward;
		cmd->m_side_move = side;
		cmd->m_view_angles.m_y = ctx->m_engine_client->get_view_angles().m_y;
	}
}

void c_misc::fake_lag( c_user_cmd* cmd, int maxticks, bool* send_packet ) {
	if ( ctx->m_shift || ctx->m_running_shift || !config->m_hvh.m_fakelag || ctx->m_is_recharging ) {
		ctx->m_choking = false;
		return;
	}

	if (!ctx->m_local_player || !ctx->m_local_player->is_alive() || ctx->m_local_player->is_taunting( ) )
	{
		ctx->m_choking = false;
		return;
	}

	if ( ctx->m_local_weapon->is_attacking( cmd )  ) {
		*send_packet = true;
		ctx->m_choking = false;
		return;
	}
	// good job cardinal, localplr = 0x000000C5
	float velocity_per_tick = ctx->m_local_player->m_velocity( ).length_2d( ) * ctx->m_globals->m_interval_per_tick;
	if ( velocity_per_tick <= 0.f )
		velocity_per_tick = 1.f;

	int lag_comp_required = std::clamp( ( int )ceilf( 64.f / velocity_per_tick ), 0, 22 );
	int min_ticks = config->m_hvh.m_break_lag_comp ? ( lag_comp_required > maxticks ? maxticks : lag_comp_required ) : maxticks;

	if ( ctx->m_charged_ticks > 2 )
		min_ticks = 0;

	if ( ctx->m_client_state->m_choked_commands >= min_ticks ) {
		*send_packet = true;
		ctx->m_choking = false;
	}
	else {
		*send_packet = false;
		ctx->m_choking = true;
	}
}

bool c_misc::handle_warp( float extra_sample, bool final_tick, std::function< void( float, bool ) > f ) {
	if ( !config->m_exploits.m_warp )
		return false;

	int ticks_per_call = config->m_exploits.m_warp_speed;

	if ( config->m_exploits.m_dynamic_warp_ticks ) {
		float velocity_per_tick = ctx->m_local_player->m_velocity().length_2d() * ctx->m_globals->m_interval_per_tick;
		if (velocity_per_tick <= 0.f)
			velocity_per_tick = 1.f;

		int lag_comp_required = std::clamp((int)ceilf(64.f / velocity_per_tick), 0, 22);
		ticks_per_call = lag_comp_required / 2;
	}

	if ( config->m_exploits.m_tickbase_warp_key.is_held( ) && ctx->m_charged_ticks >= ticks_per_call ) {
		for ( int i = 0; i < ticks_per_call; i++ ) {
			f( extra_sample, final_tick ); // cl_move call
			ctx->m_charged_ticks--;
			ctx->m_shifted_ticks++;
			ctx->m_warping = true;

			ctx->m_dt_recharge_wait = ctx->m_globals->m_current_time + 0.2f;
			*ctx->m_send_packet = ( i == ticks_per_call - 1 );
		}
		ctx->m_warping = false;
	}

	return false;
}

void c_misc::auto_warp( c_user_cmd* cmd ) {
	if ( !ctx->m_local_player || !ctx->m_local_player->is_alive( ) || !ctx->m_local_weapon || config->m_hvh.m_fakelag || ctx->m_charged_ticks <= 0 )
		return;

	if ( !config->m_exploits.m_auto_warp || !config->m_exploits.m_auto_warp_key.is_held( ) )
		return;

	std::vector< std::pair< float, c_base_player* > > targets;

	for ( const auto& player : ctx->players ) {
		if ( !player || !player->is_player( ) || !player->is_alive( ) || !player->is_enemy( ) || player->is_invulnerable( ) || player->is_dormant( ) || player->is_ghost( ) )
			continue;

		auto fov = math::calculate_fov( ctx->m_engine_client->get_view_angles( ), math::calculate_angle( ctx->m_local_player->get_world_space_center( ), player->get_world_space_center( ) ) );

		if ( fov > 90.f )
			continue;

		targets.emplace_back( std::pair< float, c_base_player* >( fov, player ) );
	}

	std::sort( targets.begin( ), targets.end( ), [ ]( const std::pair< float, c_base_player* >& a, const std::pair< float, c_base_player* >& b ) {
		return a.first > b.first;
	} );

	while ( targets.size( ) > static_cast< size_t >( config->m_aimbot.m_max_targets ) )
		targets.pop_back( );

	bool side = true;
	bool can_see_player = false;
	vector left, right, forward;
	math::angle_vectors( ctx->m_engine_client->get_view_angles( ) - vector( 0.0f, 90.0f, 0.0f ), &left );
	math::angle_vectors( ctx->m_engine_client->get_view_angles( ) + vector( 0.0f, 90.0f, 0.0f ), &right );

	left = ctx->m_local_player->get_world_space_center( ) + left * config->m_exploits.m_auto_warp_scale;
	right = ctx->m_local_player->get_world_space_center( ) + right * config->m_exploits.m_auto_warp_scale;

	for ( auto& target : targets ) {
		if (tf2::is_visible( target.second, ctx->m_local_player, target.second->get_world_space_center( ), left, MASK_SHOT | CONTENTS_GRATE ) ) {
			side = false;
			can_see_player = true;
		}

		else if ( tf2::is_visible( target.second, ctx->m_local_player, target.second->get_world_space_center( ), right, MASK_SHOT | CONTENTS_GRATE ) ) {
			side = true;
			can_see_player = true;
		}

		if ( can_see_player )
			break;
	}

	if ( can_see_player && !(cmd->m_buttons & IN_ATTACK )) {
		cmd->m_side_move = ( side ? -450 : 450 );

		if ( ctx->m_local_player->m_velocity( ).length( ) > 100.f ) {
			ctx->m_shift = true;
		}
	}
}

void c_misc::handle_weapon_sway( ) {
	static auto cl_wpn_sway_interp = ctx->m_cvar->find_var( "cl_wpn_sway_interp" );
	static auto cl_wpn_sway_scale = ctx->m_cvar->find_var( "cl_wpn_sway_scale" );

	if ( cl_wpn_sway_interp && cl_wpn_sway_scale ) {
		static const float old_sway_interp = cl_wpn_sway_interp->get_float( );
		static const float old_sway_scale = cl_wpn_sway_scale->get_float( );

		if (config->m_visuals.m_viewmodel_sway) {
			cl_wpn_sway_interp->set_value(0.1f);
			cl_wpn_sway_scale->set_value(config->m_visuals.m_viewmodel_sway_val);
		}

		else {
			cl_wpn_sway_interp->set_value( old_sway_interp );
			cl_wpn_sway_scale->set_value( old_sway_scale );
		}
	}
}

void c_misc::fix_local_animations( ) {
	auto local = ctx->m_local_player;
	if ( !local || !local->is_alive( ) )
		return;

	if ( local->m_force_taunt_cam( ) ) {
		if ( config->m_hvh.m_real_yaw.m_enabled )
			ctx->m_prediction->set_local_view_angles( ctx->m_real_angles );
		else
			ctx->m_prediction->set_local_view_angles( ctx->m_fake_angles );

		// replace with fake chams
		//bool old_m_client_side_animations = local->m_client_side_animations( );
		
		//int choked = ctx->m_client_state->m_choked_commands;
		//if ( choked > 1 ) {
		//	local->m_client_side_animations( ) = false;
		//	local->m_eye_angles() = ctx->m_fake_angles;
		//}

	//	else {
		//	local->m_client_side_animations( ) = true;
		//}
		local->m_client_side_animations( ) = true;
	}
}

void c_misc::anti_backstab( c_user_cmd* cmd ) {
	if ( !ctx->m_local_player || !ctx->m_local_player->is_alive( ) || !ctx->m_local_weapon || ( cmd->m_buttons & IN_ATTACK && ctx->m_local_weapon->can_shoot( ) ) || ctx->m_running_shift )
		return;

	float best_distance = 110.f;
	c_base_player* best_spy = nullptr;

	for ( const auto& player : ctx->players ) {
		if ( !player || !player->is_player( ) || !player->is_alive( ) || player->is_dormant( ) || player->m_player_class( ) != CLASS_SPY || !player->is_enemy( ) )
			continue;

		float dst = player->m_origin( ).dist_to( ctx->m_local_player->m_origin( ) );
		if ( dst > 135.f )
			continue;

		if ( dst < best_distance ) {
			best_distance = dst;
			best_spy = player;
		}
	}

	if ( best_spy ) {
		vector angle = math::calculate_angle( ctx->m_local_player->get_shoot_position( ), best_spy->get_world_space_center( ) );
		if (math::calculate_fov(ctx->m_engine_client->get_view_angles(), angle) > 35.f)
		{
			if (!config->m_hvh.m_fakelag)
				*ctx->m_send_packet = ctx->m_client_state->m_choked_commands >= 2;
			
			if (*ctx->m_send_packet)
				cmd->m_view_angles.m_y = angle.m_y;
		}
	}
}

void c_misc::scout_jump( c_user_cmd* cmd ) {
	static bool shot = false;
	if ( !ctx->m_local_player || !ctx->m_local_player->is_alive( ) || !ctx->m_local_weapon || ctx->m_local_player->m_water_level( ) > 1 )
		return;

	if ( ctx->m_local_player->m_move_type( ) == MOVETYPE_NOCLIP || ctx->m_local_player->m_move_type( ) == MOVETYPE_LADDER || ctx->m_local_player->m_move_type( ) == MOVETYPE_OBSERVER )
		return;

	if ( util::is_window_in_focus( ) && ( GetAsyncKeyState( config->m_misc.m_scout_jump_key.m_key ) & 1 ) && !ctx->m_surface->is_cursor_visible( ) )
	{
		if ( ctx->m_local_player && ctx->m_local_player->is_alive( ) && !ctx->m_local_player->is_dormant( ) && ctx->m_local_player->m_player_class( ) == CLASS_SCOUT && ctx->m_local_player->is_on_ground( ) )
		{
			if ( ctx->m_local_weapon->m_item_definition_index( ) == Scout_m_ForceANature || ctx->m_local_weapon->m_item_definition_index( ) == Scout_m_FestiveForceANature )
			{
				vector angle = { 37.f, cmd->m_view_angles.m_y, 0.0f };
				if ( !shot )
				{
					cmd->m_buttons |= IN_JUMP;
					cmd->m_buttons |= IN_ATTACK;
					shot = true;
				}
				shot = false;

				tf2::fix_movement( cmd, angle );
				cmd->m_view_angles = angle;
			}
		}
	}
}

void c_misc::fix_input_delay( bool final_tick ) {
	if ( ctx->m_client_state->m_net_channel && ctx->m_client_state->m_net_channel->is_loopback( ) )
		return;

	if ( !ctx->m_engine_client->is_in_game( ) )
		return;

	globals_backup backup{ };

	backup.copy( );
	{
		hooks::cl_read_packets::original_function( final_tick );

		//state.copy( );
	}
	backup.restore( );
}

bool c_misc::should_read_packets( ) {
	if ( !ctx->m_client_state->m_net_channel || ctx->m_client_state->m_net_channel->is_loopback( ) )
		return true;

	if ( !ctx->m_engine_client->is_in_game( ) )
		return true;

	//state.restore( );
	return false;
}

void c_misc::shoot_sticky_at_charge(c_user_cmd* cmd) {
	if (!ctx->m_local_player || 
		!ctx->m_local_weapon || 
		!(ctx->m_local_player->m_player_class() == CLASS_DEMOMAN && ctx->m_local_weapon->get_slot() == 1) || 
		config->m_aimbot_global.m_enabled && config->m_projectile_aim.m_enabled && config->m_aimbot_global.m_aim_key.is_held() || 
		config->m_automations.m_charge_max == 0 ||
		!(cmd->m_buttons & IN_ATTACK) 
		) 
		return;

	float get_current_charge = ctx->m_globals->m_current_time - ctx->m_local_weapon->m_charge_begin_time(); // ever heard of remap_val_clamped
	float get_max_charge = config->m_automations.m_charge_max / 27.0f;
	float get_latency = ctx->m_engine_client->get_net_channel_info()->get_latency(0);

	if (ctx->m_local_weapon->m_item_definition_index() == Demoman_s_TheQuickiebombLauncher)
		get_max_charge = config->m_automations.m_charge_max / 70.0f;

	if (get_current_charge > 5.0f)
		return;

	if (get_current_charge >= get_max_charge)
		cmd->m_buttons &= ~IN_ATTACK;
}