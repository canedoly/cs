#include "visuals.h"
#include "../../include/render.h"
#include "../menu/menu.h"
#include "../../include/tf2.h"
#include "../projectile_aim/projectile_aim.h"
#include <deque>
#include "../seed_prediction/seed_prediction.h"
#include "../crithack/crithack.h"

static std::string m_vote_target = "temp";
static std::string m_vote_caller = "temp";

void c_visuals::draw_indicators( ) {
	if ( !ctx->m_local_player || !ctx->m_local_player->is_alive( ) || !ctx->m_local_weapon )
		return;

	if ( ctx->m_engine_vgui->is_game_ui_visible( ) )
		return;

	auto indicator_amount = 0;

	if ( config->m_exploits.m_doubletap_indicator )
		indicator_amount++;

#ifndef JW_RELEASE_BUILD
	if ( config->m_seed_pred.m_draw_indicator )
		indicator_amount++;
#endif

	auto height_to_deduct = ( indicator_amount * ( ctx->m_tahoma_narrow.m_tall + 20 ) ) * 0.5f;

	ctx->m_surface->draw_set_alpha( 0.7f ); {
		auto y_offset = ctx->m_screen_height * 0.5f - height_to_deduct;

		if ( config->m_exploits.m_doubletap_indicator ) {
			int ticks = config->m_hvh.m_fakelag && ctx->m_charged_ticks <= 0 ? ctx->m_client_state->m_choked_commands : ctx->m_charged_ticks;

			render->outlined_text( 37, y_offset, e_string_align::ALIGN_DEFAULT, ctx->m_tahoma_narrow.m_font, color( 255, 255, 255 ), "ticks: %i (%.2fs)", ticks, TICKS_TO_TIME( ctx->m_charged_ticks ) );
			y_offset += ctx->m_tahoma_narrow.m_tall;

			render->filled_rect( 35, y_offset, 125, 10, config->m_colors.m_ui_background );
			float max_ticks = 22.f;

			if (ctx->m_local_player->m_player_class() == CLASS_SCOUT)
				max_ticks = 21.f;

			if (config->m_misc.m_reduce_input_delay)
				max_ticks = 20.f;

			render->gradient_rect( 35, y_offset, math::remap_val_clamped( ticks, 0.0f, max_ticks, 0.0f, 125.0f ), 10, config->m_colors.m_ui_foreground, config->m_colors.m_ui_accent, true );
			render->outlined_rect( 35, y_offset, 125, 10, config->m_colors.m_ui_outline );
			y_offset += 20;
		}

		/*if (config->m_exploits.m_crithack_indicator && ctx->m_local_weapon->get_slot() <= 2) {
			con_var* crits_enabled = ctx->m_cvar->find_var( "tf_weapon_criticals" );

			if ( !crits_enabled->get_int( ) || ctx->m_local_player->m_player_class( ) == CLASS_SPY && ctx->m_local_weapon->get_slot( ) > 0 || ctx->m_local_player->m_player_class( ) == CLASS_SNIPER && ctx->m_local_weapon->get_slot( ) == 0 || ctx->m_local_weapon->get_weapon_id( ) == TF_WEAPON_LUNCHBOX || tf2::is_non_aimable( ctx->m_local_weapon ) ) {
				render->outlined_text( ctx->m_screen_width * 0.5f, ctx->m_screen_height * 0.5f + 50, e_string_align::ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, color( 255, 255, 255 ), "crits disabled" );
			}

			else {
				if ( ctx->m_local_weapon->get_slot( ) != e_weapon_slots::SLOT_MELEE ) {
					if ( crithack->m_official_crit_dmg >= crithack->m_crit_cost && crithack->m_bucket_crits > 0 )
						render->outlined_text( ctx->m_screen_width * 0.5f, ctx->m_screen_height * 0.5f + 50, e_string_align::ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, color( 100, 255, 100 ), "crit ready" );
					else
						render->outlined_text( ctx->m_screen_width * 0.5f, ctx->m_screen_height * 0.5f + 50, e_string_align::ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, color( 255, 100, 100 ), "crit not ready" );

					render->outlined_text( ctx->m_screen_width * 0.5f, ctx->m_screen_height * 0.5f + 50 + ctx->m_tahoma_narrow.m_tall, e_string_align::ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, color( 255, 255, 255 ), "%i / %i potential crits", crithack->m_bucket_crits, crithack->m_bucket_crits_max );
				}
				else render->outlined_text( ctx->m_screen_width * 0.5f, ctx->m_screen_height * 0.5f + 50, e_string_align::ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, color( 255, 255, 255 ), "%i / %i potential crits", crithack->m_bucket_crits, crithack->m_bucket_crits_max );

				if ( ctx->m_local_weapon->get_slot( ) != e_weapon_slots::SLOT_MELEE && crithack->m_official_crit_dmg < crithack->m_crit_cost )
					render->outlined_text( ctx->m_screen_width * 0.5f, ctx->m_screen_height * 0.5f + 50 + ctx->m_tahoma_narrow.m_tall * 2, e_string_align::ALIGN_CENTER, ctx->m_tahoma_narrow.m_font, color( 255, 255, 255 ), "deal %i damage", crithack->m_official_crit_dmg < 0 ? -crithack->m_official_crit_dmg : crithack->m_official_crit_dmg );
			}
		}*/

// MAYBE USE THE INDICATOR STYLE ????????
		if ( config->m_misc.m_vote_revealer && m_vote_in_progress ) {
			render->outlined_text( 37, y_offset, e_string_align::ALIGN_DEFAULT, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, "Kick called on %s by %s", m_vote_target.c_str( ), m_vote_caller.c_str( ) );
			render->outlined_text( 37, y_offset + 12, e_string_align::ALIGN_DEFAULT, ctx->m_tahoma_narrow.m_font, config->m_colors.m_ui_text, "Yes = %i  |  No = %i", m_vote_yes, m_vote_no );
		}
	} ctx->m_surface->draw_set_alpha( 1.0f );
}

void c_visuals::trace_projectile_path( ) {
	if ( !ctx->m_local_player || !ctx->m_local_player->is_alive( ) || !ctx->m_local_weapon || !config->m_projectile_aim.m_projectile_path_any_angle )
		return;

	if ( ctx->m_engine_vgui->is_game_ui_visible( ) )
		return;

	projectile_info_t info = { };

	if ( !projectile_sim->get_info( ctx->m_local_player, ctx->m_local_weapon, ctx->m_engine_client->get_view_angles( ), info ) )
		return;

	if (config->m_automations.m_charge_max > 0 && ctx->m_local_weapon->get_slot() == 1 && ctx->m_local_player->m_player_class() == CLASS_DEMOMAN) {
		//modify speed based on custom charge max
		float get_max_charge = config->m_automations.m_charge_max / 27.0f;
		if (ctx->m_local_weapon->m_item_definition_index() == Demoman_s_TheQuickiebombLauncher)
			get_max_charge = config->m_automations.m_charge_max / 70.0f;

		float diff = 15;
		if (ctx->m_local_weapon->m_item_definition_index() == Demoman_s_TheQuickiebombLauncher)
			diff = 5;

		float new_speed = math::remap_val_clamped(get_max_charge-TICKS_TO_TIME(diff), 0.0f, tf2::attrib_hook_float(4.0f, "stickybomb_charge_rate", ctx->m_local_weapon), 900.0f, 2400.0f);
		info.m_speed = new_speed;
	}

	if ( !projectile_sim->init( info ) )
		return;

	for ( int n = 0; n < TIME_TO_TICKS( 10.0f ); n++ ) {
		auto old_position = projectile_sim->get_origin( );
		projectile_sim->run_tick( );
		auto new_position = projectile_sim->get_origin( );

		static auto render_line = util::find_signature< void( __cdecl* )( const vector&, const vector&, color, bool ) >( "engine.dll", "55 8B EC 81 EC ? ? ? ? 56 E8 ? ? ? ? 8B 0D ? ? ? ? 8B 01 FF 90 ? ? ? ? 8B F0 85 F6" );
		render_line( old_position, new_position, color( 235, 235, 235, 175 ), false );

		ray_t ray = { };
		ray.init( old_position, new_position, vector( -4.5f, -4.5f, -4.5f ), vector( 4.5f, 4.5f, 4.5f ) );

		c_trace_filter_hitscan filter = { };
		filter.m_skip = ctx->m_local_player;

		trace_t trace = { };
		ctx->m_engine_trace->trace_ray( ray, MASK_SHOT, &filter, &trace );

		if ( trace.did_hit( ) ) {
			ctx->m_projectile_camera_position = new_position;
			auto angles = vector( );
			math::vector_angles( trace.m_plane.m_normal, angles );

			static auto render_box = util::find_signature< void( __cdecl* )( const vector&, const vector&, const vector&, const vector&, color, bool, bool ) >( "engine.dll", "55 8B EC 51 8B 45 ? 8B C8 FF 75" );
			render_box( new_position, angles, vector( -1.0f, -4.5f, -4.5f ), vector( 1.0f, 4.5f, 4.5f ), color( 195, 35, 35, 200 ), false, false );

			static auto render_wireframe_box = util::find_signature< void( __cdecl* )( const vector&, const vector&, const vector&, const vector&, color, bool ) >( "engine.dll", "55 8B EC 81 EC ? ? ? ? 56 E8 ? ? ? ? 8B 0D ? ? ? ? 8B 01 FF 90 ? ? ? ? 8B F0 89 75 ? 85 F6 74 ? 8B 06 8B CE FF 50 ? A1" );
			render_wireframe_box( new_position, angles, vector( -1.0f, -4.5f, -4.5f ), vector( 1.0f, 4.5f, 4.5f ), color( 235, 65, 65, 235 ), false );

			break;
		}
	}

}

void c_visuals::visualize_stickies_path( ) {
	if ( !ctx->m_local_player || !config->m_esp.m_predict_stickies || ctx->m_engine_vgui->is_game_ui_visible( ) )
		return;

	if ( ctx->m_engine_vgui->is_game_ui_visible( ) )
		return;

	for ( const auto& entity : ctx->projectiles ) {
		if ( !entity || !entity->is_projectile( ) || !entity->get_model( ) || entity->get_client_class( )->m_class_id != class_id_t::CTFGrenadePipebombProjectile )
			continue;

		projectile_info_t m_projectile_info;
		vector angle, startscr, endscr;
		m_projectile_info.m_speed = entity->estimate_abs_velocity( ).length_2d( );
		if ( entity->estimate_abs_velocity( ).length( ) <= 1.f )
			continue;

		const float g = 800;

		math::vector_angles( entity->estimate_abs_velocity( ), angle );

		vector alongDir = entity->estimate_abs_velocity( );
		alongDir.normalize_in_place( );

		vector start = entity->m_origin( ), end = entity->m_origin( );

		float alongVel = sqrt( entity->estimate_abs_velocity( ).m_x * entity->estimate_abs_velocity( ).m_x + entity->estimate_abs_velocity( ).m_y * entity->estimate_abs_velocity( ).m_y );

		for ( auto t = 0.0f; t < 5.0f; t += TICK_INTERVAL ) {
			float along = alongVel * t;
			float height = entity->estimate_abs_velocity( ).m_z * t - 0.5f * g * t * t;

			start = end;
			end.m_x = entity->m_origin( ).m_x + alongDir.m_x * along;
			end.m_y = entity->m_origin( ).m_y + alongDir.m_y * along;
			end.m_z = entity->m_origin( ).m_z + height;

			tf2::world_to_screen( start, startscr );
			tf2::world_to_screen( end, endscr );
			render->line( startscr.m_x, startscr.m_y, endscr.m_x, endscr.m_y, config->m_colors.m_ui_accent );

			if ( !tf2::is_visible( entity, NULL, start, end, MASK_SHOT ) ) {
				ctx->m_debug_overlay->add_box_overlay( end, entity->m_mins( ), entity->m_maxs( ), vector( ), config->m_colors.m_ui_accent.m_r, config->m_colors.m_ui_accent.m_g, config->m_colors.m_ui_accent.m_b, 100, 0.03f );
				break;
			}
		}
	}
}

void c_visuals::draw_hitboxes( c_base_player* player, const model_t* model, matrix_3x4* bones, const color& colorface, const color& coloredge, float time ) {
	if ( !model || !player || !bones )
		return;

	if ( ctx->m_engine_vgui->is_game_ui_visible( ) )
		return;

	const studiohdr_t* hdr = ctx->m_model_info->get_studio_model( model );
	const mstudiohitboxset_t* set = hdr->hitbox_set( player->m_hitbox_set( ) );

	for ( int i = 0; i < set->numhitboxes; ++i ) {
		const mstudiobbox_t* bbox = set->hitbox( i );
		if ( !bbox )
			continue;

		matrix_3x4 rotMatrix;
		math::angle_matrix( bbox->angle, rotMatrix );

		matrix_3x4 matrix;
		math::concat_transforms( bones[ bbox->bone ], rotMatrix, matrix );

		auto bbox_angle = vector( );
		math::matrix_angles( matrix, bbox_angle );

		auto matrix_origin = vector( );
		math::get_matrix_origin( matrix, matrix_origin );

		ctx->m_debug_overlay->add_box_overlay_2( matrix_origin, bbox->bbmin, bbox->bbmax, bbox_angle, colorface, coloredge, time );
	}
}

void c_visuals::draw_server_hitboxes( ) {
	static int old_tick = ctx->m_globals->m_tick_count;
	if ( old_tick == ctx->m_globals->m_tick_count )
		return;
	old_tick = ctx->m_globals->m_tick_count;

	if ( ctx->m_input->cam_is_third_person( ) ) {
		static auto get_server_animating = reinterpret_cast< void* ( * )( int ) >( util::find_signature< uintptr_t >( "server.dll", "55 8B EC 8B 55 ? 85 D2 7E ? A1" ) );
		static auto draw_server_hitboxes = reinterpret_cast< void( __thiscall* )( void*, float, bool ) >( util::find_signature< uintptr_t >( "server.dll", "55 8B EC 83 EC ? 57 8B F9 80 BF ? ? ? ? ? 0F 85 ? ? ? ? 83 BF ? ? ? ? ? 75 ? E8 ? ? ? ? 85 C0 74 ? 8B CF E8 ? ? ? ? 8B 97" ) );

		if ( ctx->m_local_player && ctx->m_local_player->is_alive( ) ) {
			void* server_animating = get_server_animating( ctx->m_local_player->entindex( ) );
			if ( server_animating )
				draw_server_hitboxes( server_animating, ctx->m_globals->m_interval_per_tick, true );
		}
	}
}

/*

	i hate chat vote revealers
	clutters the chat too much

*/

void c_visuals::vote_revealer_register_event( c_game_event* event ) {
	if ( !config->m_misc.m_vote_revealer )
		return;

	if ( fnv::hash( event->get_name( ) ) != fnv::hash( "vote_cast" ) )
		return;

	( event->get_int( "vote_option" ) == 0 ) ? m_vote_yes++ : m_vote_no++;
}

void c_visuals::vote_revealer_register_message( int message, bf_read& data ) {
	if ( !config->m_misc.m_vote_revealer || !ctx->m_local_player )
		return;

	if ( message == VoteStart ) {
		int team = data.ReadByte( );
		int vote_id = data.ReadLong( );
		int caller = data.ReadByte( );
		char reason[ 64 ], name[ 64 ];
		data.ReadString( reason, 64 );
		data.ReadString( name, 64 );
		auto target = static_cast< uint8_t >( data.ReadByte( ) );
		target >>= 1;

		if ( team == ctx->m_local_player->m_team_num( ) )
			return;

		m_vote_in_progress = true;
		m_vote_no = 1;
		m_vote_yes = 1;

		player_info_t caller_info, target_info;
		bool info = false;
		info = ctx->m_engine_client->get_player_info( caller, &caller_info ) && ctx->m_engine_client->get_player_info( target, &target_info );

		//ctx->m_cvar->console_printf( "Team: %i  Target: %i  %s\n", team, target, target_info.m_name ); // this is correct
		//ctx->m_cvar->console_printf( "Team: %i  caller: %i  %s\n", team, caller, caller_info.m_name );

		m_vote_caller = caller_info.m_name;
		m_vote_target = target_info.m_name;
	}

	else m_vote_in_progress = false;
}

void c_visuals::draw_camera_outline( ) {
	if ( ctx->m_engine_vgui->is_game_ui_visible( ) )
		return;

	if ( ctx->m_local_weapon && ( ctx->m_local_weapon->get_weapon_id( ) == TF_WEAPON_PIPEBOMBLAUNCHER || ctx->m_local_weapon->get_weapon_id( ) == TF_WEAPON_SYRINGEGUN_MEDIC ) && config->m_projectile_aim.m_projectile_path_any_angle && config->m_visuals.m_projectile_camera && !ctx->m_projectile_camera_position.is_zero( ) ) {
		render->outlined_rect( visuals->camera_position.m_x,
							   visuals->camera_position.m_y,
							   visuals->camera_position.m_w,
							   visuals->camera_position.m_h,
							   config->m_colors.m_ui_accent );

		render->outlined_rect( visuals->camera_position.m_x - 1,
							   visuals->camera_position.m_y - 1,
							   visuals->camera_position.m_w + 2,
							   visuals->camera_position.m_h + 2,
							   config->m_colors.m_ui_background );
	}
}