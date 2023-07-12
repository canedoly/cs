#pragma once
#include "render.h"

namespace tf2 {

	inline void update_w2s_matrix( ) {
		c_view_setup view = { };

		if ( ctx->m_client->get_player_view( view ) ) {
			static view_matrix world_to_view = { }, view_to_projection = { }, world_to_pixels = { };
			ctx->m_render_view->get_matrices_for_view( view, &world_to_view, &view_to_projection, &ctx->m_world_to_projection, &world_to_pixels );
		}
	}

	inline bool world_to_screen( const vector& origin, vector& screen ) {
		const auto& world_to_projection = ctx->m_world_to_projection.as_3x4( );
		auto w = world_to_projection[ 3 ][ 0 ] * origin[ 0 ] + world_to_projection[ 3 ][ 1 ] * origin[ 1 ] + world_to_projection[ 3 ][ 2 ] * origin[ 2 ] + world_to_projection[ 3 ][ 3 ];
		screen.m_z = 0.0f;

		if ( w > 0.001f ) {
			auto inverse_w = ( 1.0f / w );
			screen.m_x = ( static_cast< float >( ctx->m_screen_width ) * 0.5f ) + ( 0.5f * ( ( world_to_projection[ 0 ][ 0 ] * origin[ 0 ] + world_to_projection[ 0 ][ 1 ] * origin[ 1 ] + world_to_projection[ 0 ][ 2 ] * origin[ 2 ] + world_to_projection[ 0 ][ 3 ] ) * inverse_w ) * static_cast< float >( ctx->m_screen_width ) + 0.5f );
			screen.m_y = ( static_cast< float >( ctx->m_screen_height ) * 0.5f ) - ( 0.5f * ( ( world_to_projection[ 1 ][ 0 ] * origin[ 0 ] + world_to_projection[ 1 ][ 1 ] * origin[ 1 ] + world_to_projection[ 1 ][ 2 ] * origin[ 2 ] + world_to_projection[ 1 ][ 3 ] ) * inverse_w ) * static_cast< float >( ctx->m_screen_height ) + 0.5f );
			return true;
		}

		return false;
	}

	inline color get_health_color( int health, int max_health ) {
		int hp = std::max( 0, std::min( health, max_health ) );
		int r = std::min( ( ( 510 * ( max_health - hp ) ) / max_health ) + 130, 255 );
		int g = std::min( ( ( 510 * hp ) / max_health ), 255 );
		return color( r, g, 40, 180 );
	}

	inline void get_projectile_fire_setup( c_base_player* player, const vector& view_angles, vector offset, vector* position_out ) {
		static auto flip_viewmodels = ctx->m_cvar->find_var( "cl_flipviewmodels" );
		if ( flip_viewmodels && flip_viewmodels->get_bool( ) )
			offset.m_y *= -1.0f;

		auto forward = vector( ), right = vector( ), up = vector( );
		math::angle_vectors( view_angles, &forward, &right, &up );

		*position_out = player->get_shoot_position( ) + ( forward * offset.m_x ) + ( right * offset.m_y ) + ( up * offset.m_z );
	}

	inline void get_projectile_fire_setup( c_base_player* player, const vector& view_angles, vector offset, vector& position_out, vector& angle_out, bool pipes ) {
		static auto flip_viewmodels = ctx->m_cvar->find_var( "cl_flipviewmodels" );
		if ( flip_viewmodels && flip_viewmodels->get_bool( ) )
			offset.m_y *= -1.0f;

		auto forward = vector( ), right = vector( ), up = vector( );
		math::angle_vectors( view_angles, &forward, &right, &up );

		position_out = player->get_shoot_position( ) + ( forward * offset.m_x ) + ( right * offset.m_y ) + ( up * offset.m_z );

		if ( pipes ) {
			angle_out = view_angles;
		}

		else {
			auto end_position = position_out + ( forward * 2000.0f );
			math::vector_angles( end_position - position_out, angle_out );
		}
	}

	inline float attrib_hook_float( float base_value, const char* search_string, c_base_entity* entity, void* buffer = nullptr, bool is_global_const_string = false ) {
		typedef float( __cdecl* attrib_hook_float_fn )( float, const char*, c_base_entity*, void*, bool );
		static auto fn = util::find_signature< attrib_hook_float_fn >( "client.dll", "55 8B EC 83 EC 0C 8B 0D ? ? ? ? 53 56 57 33 F6 33 FF 89 75 F4 89 7D F8 8B 41 08 85 C0 74 38" );
		return fn( base_value, search_string, entity, buffer, is_global_const_string );
	}

	inline bool is_visible( c_base_entity* skip, c_base_entity* target, vector from, vector to, unsigned int mask ) {
		c_game_trace trace;
		c_trace_filter_hitscan filter;
		filter.m_skip = skip;
		ray_t ray;
		ray.init( from, to );
		ctx->m_engine_trace->trace_ray( ray, mask, &filter, &trace );

		return ( ( trace.m_ent && trace.m_ent == target ) || trace.m_fraction > 0.99f );
	}

	inline bool is_visible( c_base_entity* skip, c_base_entity* target, vector from, vector to, unsigned int mask, vector mins, vector maxs ) {
		c_game_trace trace;
		c_trace_filter_hitscan filter;
		filter.m_skip = skip;
		ray_t ray;
		ray.init( from, to, mins, maxs );
		ctx->m_engine_trace->trace_ray( ray, mask, &filter, &trace );

		return ( ( trace.m_ent && trace.m_ent == target ) || trace.m_fraction > 0.99f );
	}

	inline float get_lerp_time( ) {
		static auto cl_interp = ctx->m_cvar->find_var( "cl_interp" );
		static auto cl_interp_ratio = ctx->m_cvar->find_var( "cl_interp_ratio" );
		static auto cl_updaterate = ctx->m_cvar->find_var( "cl_updaterate" );
		static auto min_ud_rate = ctx->m_cvar->find_var( "sv_minupdaterate" );
		static auto max_ud_rate = ctx->m_cvar->find_var( "sv_maxupdaterate" );
		static auto c_min_ratio = ctx->m_cvar->find_var( "sv_client_min_interp_ratio" );
		static auto c_max_ratio = ctx->m_cvar->find_var( "sv_client_max_interp_ratio" );

		int ud_rate = cl_updaterate->get_int( );

		if ( min_ud_rate && max_ud_rate )
			ud_rate = max_ud_rate->get_int( );

		float ratio = cl_interp_ratio->get_float( );

		if ( ratio == 0 )
			ratio = 1.f;

		float lerp = cl_interp->get_float( );

		if ( c_min_ratio && c_max_ratio && c_min_ratio->get_float( ) != 1 )
			ratio = std::clamp( ratio, c_min_ratio->get_float( ), c_max_ratio->get_float( ) );

		return std::max( lerp, ( ratio / ud_rate ) );
	}

	inline void fix_movement( c_user_cmd* cmd, vector old_angles ) {
		auto forward = vector( ), right = vector( ), up = vector( );
		math::angle_vectors( old_angles, &forward, &right, &up );

		forward.m_z = right.m_z = up.m_x = up.m_y = 0.0f;

		forward.normalize_in_place( );
		right.normalize_in_place( );
		up.normalize_in_place( );

		auto old_forward = vector( ), old_right = vector( ), old_up = vector( );
		math::angle_vectors( cmd->m_view_angles, &old_forward, &old_right, &old_up );

		old_forward.m_z = old_right.m_z = old_up.m_x = old_up.m_y = 0.0f;

		old_forward.normalize_in_place( );
		old_right.normalize_in_place( );
		old_up.normalize_in_place( );

		const float pitch_forward = forward.m_x * cmd->m_forward_move;
		const float yaw_forward = forward.m_y * cmd->m_forward_move;
		const float pitch_side = right.m_x * cmd->m_side_move;
		const float yaw_side = right.m_y * cmd->m_side_move;
		const float roll_up = up.m_z * cmd->m_up_move;

		const float x = old_forward.m_x * pitch_side + old_forward.m_y * yaw_side + old_forward.m_x * pitch_forward + old_forward.m_y * yaw_forward + old_forward.m_z * roll_up;
		const float y = old_right.m_x * pitch_side + old_right.m_y * yaw_side + old_right.m_x * pitch_forward + old_right.m_y * yaw_forward + old_right.m_z * roll_up;
		const float z = old_up.m_x * yaw_side + old_up.m_y * pitch_side + old_up.m_x * yaw_forward + old_up.m_y * pitch_forward + old_up.m_z * roll_up;

		cmd->m_forward_move = std::clamp( x, -450.f, 450.f );
		cmd->m_side_move = std::clamp( y, -450.f, 450.f );
		cmd->m_up_move = std::clamp( z, -450.f, 450.f );
	}

	inline bool is_projectile_weapon( c_base_combat_weapon* weapon ) {
		if ( !weapon )
			return false;

		switch ( weapon->m_item_definition_index( ) ) {
			case Soldier_s_TheRighteousBison:
			case Engi_m_ThePomson6000: return true;
		}

		switch ( weapon->get_weapon_id( ) ) {
			case TF_WEAPON_CANNON:
			case TF_WEAPON_COMPOUND_BOW:
			case TF_WEAPON_CROSSBOW:
			case TF_WEAPON_FLAMETHROWER:
			case TF_WEAPON_FLAME_BALL:
			case TF_WEAPON_FLAREGUN:
			case TF_WEAPON_DRG_POMSON:
			case TF_WEAPON_GRENADELAUNCHER:
			case TF_WEAPON_NAILGUN:
			case TF_WEAPON_PIPEBOMBLAUNCHER:
			case TF_WEAPON_STICKY_BALL_LAUNCHER:
			case TF_WEAPON_ROCKETLAUNCHER:
			case TF_WEAPON_ROCKETLAUNCHER_DIRECTHIT:
			case TF_WEAPON_JAR:
			case TF_WEAPON_JAR_MILK: 
			case TF_WEAPON_SYRINGEGUN_MEDIC: return true;
			default: return false;
		}
	}

	inline bool is_non_aimable( c_base_combat_weapon* weapon ) {
		switch ( weapon->m_item_definition_index( ) ) {
			case Soldier_s_TheBuffBanner:
			case Soldier_s_FestiveBuffBanner:
			case Soldier_s_TheBattalionsBackup:
			case Soldier_s_TheConcheror: return true;
			default: {
				switch ( weapon->get_weapon_id( ) ) {
					case TF_WEAPON_MEDIGUN:
					case TF_WEAPON_PDA:
					case TF_WEAPON_PDA_ENGINEER_BUILD:
					case TF_WEAPON_PDA_ENGINEER_DESTROY:
					case TF_WEAPON_PDA_SPY:
					case TF_WEAPON_PDA_SPY_BUILD:
					case TF_WEAPON_BUILDER:
					case TF_WEAPON_GRAPPLINGHOOK: return true;
					default: return false;
				}
				break;
			}
		}
	}

	inline bool is_allowed_to_dt( c_base_combat_weapon* weapon ) {
		if ( is_non_aimable( weapon ) )
			return false;

		switch ( weapon->get_weapon_id( ) )
		{
		case TF_WEAPON_COMPOUND_BOW:
		case TF_WEAPON_PIPEBOMBLAUNCHER:
		case TF_WEAPON_CROSSBOW:
		case TF_WEAPON_JAR:
		case TF_WEAPON_JAR_MILK:
		case TF_WEAPON_STICKY_BALL_LAUNCHER:
		case TF_WEAPON_DRG_POMSON:
		case TF_WEAPON_FLAREGUN:
		case TF_WEAPON_FLAMETHROWER:
		case TF_WEAPON_CANNON:
		{
			return false;
			break;
		}
		}

		return true;
	}

	inline double plat_float_time( ) {
		typedef double( __cdecl* plat_float_time_fn )( );
		static auto function = reinterpret_cast< plat_float_time_fn >( GetProcAddress( GetModuleHandleA( "tier0.dll" ), "Plat_FloatTime" ) );
		return function( );
	}

	inline void random_seed( int seed ) {
		typedef void( __cdecl* random_seed_fn )( int );
		static auto function = reinterpret_cast< random_seed_fn >( GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "RandomSeed" ) );
		return function( seed );
	}

	inline int random_int( int min, int max ) {
		typedef int( __cdecl* random_int_fn )( int, int );
		static auto function = reinterpret_cast< random_int_fn >( GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "RandomInt" ) );
		return function( min, max );
	}

	inline float random_float( float min, float max ) {
		typedef float( __cdecl* random_float_fn )( float, float );
		static auto function = reinterpret_cast< random_float_fn >( GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "RandomFloat" ) );
		return function( min, max );
	}

	inline const char* get_player_class( int class_id ) {
		switch ( class_id ) {
			case CLASS_SCOUT: { return "Scout"; }
			case CLASS_SOLDIER: { return "Soldier"; }
			case CLASS_PYRO: { return "Pyro"; }
			case CLASS_DEMOMAN: { return "Demoman"; }
			case CLASS_HEAVY: { return "Heavy"; }
			case CLASS_ENGINEER: { return "Engineer"; }
			case CLASS_MEDIC: { return "Medic"; }
			case CLASS_SNIPER: { return "Sniper"; }
			case CLASS_SPY: { return "Spy"; }
			default: return "";
		}

		return "";
	}

	bool is_a_cheater_unoptimized(int friendsid);
}