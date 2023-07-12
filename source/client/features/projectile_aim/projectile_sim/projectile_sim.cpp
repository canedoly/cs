#include "projectile_sim.h"

i_physics_environment* environment = nullptr;
c_physics_object* object = nullptr;

bool c_projectile_sim::init( const projectile_info_t& info ) {
	if ( !environment )
		environment = ctx->m_physics->create_environment( );

	if ( !object ) {
		auto collide = ctx->m_physics_collision->bbox_to_collide( vector( -2.0f, -2.0f, -2.0f ), vector( 2.0f, 2.0f, 2.0f ) );
		auto params = g_phys_default_object_params;

		params.m_damping = 0.0f;
		params.m_rot_damping = 0.0f;
		params.m_inertia = 0.0f;
		params.m_rot_inertia_limit = 0.0f;
		params.m_enable_collisions = false;

		object = reinterpret_cast< c_physics_object* >( environment->create_poly_object( collide, 0, info.m_position, info.m_angle, &params ) );
		object->wake( );
	}

	if ( !environment || !object )
		return false;

	auto forward = vector( ), up = vector( );
	math::angle_vectors( info.m_angle, &forward, nullptr, &up );

	auto velocity = forward * info.m_speed, angular_velocity = vector( );

	switch ( info.m_type ) {
		case TF_PROJECTILE_PIPEBOMB:
		case TF_PROJECTILE_PIPEBOMB_REMOTE:
		case TF_PROJECTILE_PIPEBOMB_PRACTICE:
		case TF_PROJECTILE_CANNONBALL: {
			velocity += ( up * 200.0f );
			angular_velocity = vector( 600.0f, -1200.0f, 0.0f );
			break;
		}

		default: break;
	}

	if ( info.m_no_spin )
		angular_velocity.set( 0.0f, 0.0f, 0.0f );

	object->set_position( info.m_position, info.m_angle, true );
	object->set_velocity( &velocity, &angular_velocity );

	auto drag = 0.0f;
	auto drag_basis = vector( ), angular_drag_basis = vector( );

	switch ( info.m_type ) {
		case TF_PROJECTILE_PIPEBOMB: {
			drag = 1.0f;
			drag_basis = vector( 0.003902f, 0.009962f, 0.009962f );
			angular_drag_basis = vector( 0.003618f, 0.001514f, 0.001514f );
			break;
		}

		case TF_PROJECTILE_PIPEBOMB_REMOTE:
		case TF_PROJECTILE_PIPEBOMB_PRACTICE: {
			drag = 1.0f;
			drag_basis = vector( 0.007491f, 0.007491f, 0.007306f );
			angular_drag_basis = vector( 0.002777f, 0.002842f, 0.002812f );
			break;
		}

		case TF_PROJECTILE_CANNONBALL: {
			drag = 1.0f;
			drag_basis = vector( 0.020971f, 0.019420f, 0.020971f );
			angular_drag_basis = vector( 0.012997f, 0.013496f, 0.013714f );
			break;
		}

		default: break;
	}

	object->set_drag_coefficient( &drag, &drag );

	object->m_drag_basis = drag_basis;
	object->m_angular_drag_basis = angular_drag_basis;

	auto max_velocity = 1000000.0f;
	auto max_angular_velocity = 1000000.0f;

	switch ( info.m_type ) {
		case TF_PROJECTILE_PIPEBOMB:
		case TF_PROJECTILE_PIPEBOMB_REMOTE:
		case TF_PROJECTILE_PIPEBOMB_PRACTICE:
		case TF_PROJECTILE_CANNONBALL: {
			max_velocity = k_max_velocity;
			max_angular_velocity = k_max_angular_velocity;
			break;
		}

		default: break;
	}

	physics_performanceparams_t params;
	params.defaults( );

	params.m_max_velocity = max_velocity;
	params.m_max_angular_velocity = max_angular_velocity;

	environment->set_performance_settings( &params );
	environment->set_air_density( 2.0f );

	static auto sv_gravity = ctx->m_cvar->find_var( "sv_gravity" );

	if ( drag )
		environment->set_gravity( vector( 0.0f, 0.0f, -( 800.0f * info.m_gravity_modifier ) ) );
	else
		environment->set_gravity( vector( 0.0f, 0.0f, -( sv_gravity->get_float( ) * info.m_gravity_modifier ) ) );

	environment->reset_simulation_clock( );

	return true;
}

bool c_projectile_sim::get_info( c_base_player* player, c_base_combat_weapon* weapon, const vector& angles, projectile_info_t& info ) {
	if ( !player || !weapon )
		return false;

	auto current_time = static_cast< float >( player->m_tick_base( ) ) * TICK_INTERVAL;
	auto ducking = player->m_flags( ) & FL_DUCKING;

	auto position = vector( );
	auto angle = vector( );

	switch ( weapon->m_item_definition_index( ) ) {
		case Soldier_s_TheRighteousBison:
		case Engi_m_ThePomson6000:
			tf2::get_projectile_fire_setup( player, angles, vector( 0.f, 0.f, 0.f ), position, angle, false );
			info = { TF_PROJECTILE_ENERGY_RING, position, angle, 1200.0f, 0.0f, true };
			return true;
	}

	switch ( weapon->get_weapon_id( ) ) {
		case TF_WEAPON_ROCKETLAUNCHER: {
			if ( weapon->m_item_definition_index( ) == Soldier_m_TheOriginal )
				//												this offset is still wrong, its still vertically offset on the original (afaik)
				tf2::get_projectile_fire_setup( player, angles, vector( 0.f, 0.f, 0.f ), position, angle, false );
			else
				tf2::get_projectile_fire_setup( player, angles, vector( 23.5f, 12.0f, ducking ? 8.0f : -3.0f ), position, angle, false );

			info = { TF_PROJECTILE_ROCKET, position, angle, 1100.0f, 0.0f, true };
			return true;
		}

		case TF_WEAPON_ROCKETLAUNCHER_DIRECTHIT: {
			tf2::get_projectile_fire_setup( player, angles, vector( 23.5f, 12.0f, ducking ? 8.0f : -3.0f ), position, angle, false );
			info = { TF_PROJECTILE_ROCKET, position, angle, 1980.0f, 0.0f, true };
			return true;
		}

		case TF_WEAPON_GRENADELAUNCHER: {
			tf2::get_projectile_fire_setup( player, angles, vector( 16.0f, 8.0f, -6.0f ), position, angle, true );

			auto is_loch_n_load = weapon->m_item_definition_index( ) == Demoman_m_TheLochnLoad;
			auto speed = is_loch_n_load ? 1490.0f : 1200.0f;

			info = { TF_PROJECTILE_PIPEBOMB, position, angle, speed, 1.0f, true };
			return true;
		}

		case TF_WEAPON_PIPEBOMBLAUNCHER: {
			tf2::get_projectile_fire_setup( player, angles, vector( 16.0f, 8.0f, -6.0f ), position, angle, true);

			auto charge_begin_time = weapon->m_charge_begin_time( );
			auto charge = current_time - charge_begin_time;
			auto speed = math::remap_val_clamped( charge, 0.0f, tf2::attrib_hook_float( 4.0f, "stickybomb_charge_rate", weapon ), 900.0f, 2400.0f );

			if ( charge_begin_time <= 0.0f ) {
				speed = 900.0f;
			}

			info = { TF_PROJECTILE_PIPEBOMB_REMOTE, position, angle, speed, 1.0f, true }; // why is this 1.0f
			return true;
		}

		case TF_WEAPON_CANNON: {
			tf2::get_projectile_fire_setup( player, angles, vector( 16.0f, 8.0f, -6.0f ), position, angle, true );
			info = { TF_PROJECTILE_CANNONBALL, position, angle, 1454.0f, 1.0f, true };
			return true;
		}

		case TF_WEAPON_FLAREGUN: {
			tf2::get_projectile_fire_setup( player, angles, vector( 23.5f, 12.0f, ducking ? 8.0f : -3.0f ), position, angle, false);
			info = { TF_PROJECTILE_FLARE, position, angle, 2000.0f, 0.3f, true };
			return true;
		}

		case TF_WEAPON_FLAREGUN_REVENGE: {
			tf2::get_projectile_fire_setup( player, angles, vector( 23.5f, 12.0f, ducking ? 8.0f : -3.0f ), position, angle, false );
			info = { TF_PROJECTILE_FLARE, position, angle, 3000.0f, 0.45f, true };
			return true;
		}

		case TF_WEAPON_COMPOUND_BOW: {
			tf2::get_projectile_fire_setup( player, angles, vector( 23.5f, 8.0f, -3.0f ), position, angle, false );

			auto charge_begin_time = weapon->m_charge_begin_time( );
			auto charge = current_time - charge_begin_time;
			auto speed = math::remap_val_clamped( charge, 0.0f, 1.0f, 1800.0f, 2600.0f );
			auto gravity_mod = math::remap_val_clamped( charge, 0.0f, 1.0f, 0.5f, 0.1f );

			if ( charge_begin_time <= 0.0f ) {
				speed = 1800.0f;
				gravity_mod = 0.5f;
			}

			info = { TF_PROJECTILE_ARROW, position, angle, speed, gravity_mod, true };
			return true;
		}

		case TF_WEAPON_CROSSBOW: {
			tf2::get_projectile_fire_setup( player, angles, vector( 23.5f, 8.0f, -3.0f ), position, angle, false );
			info = { TF_PROJECTILE_HEALING_BOLT, position, angle, 2400.0f, 0.2f, true };
			return true;
		}

		case TF_WEAPON_SHOTGUN_BUILDING_RESCUE: {
			tf2::get_projectile_fire_setup( player, angles, vector( 23.5f, 8.0f, -3.0f ), position, angle, false );
			info = { TF_PROJECTILE_BUILDING_REPAIR_BOLT, position, angle, 2400.0f, 0.2f, true };
			return true;
		}

		case TF_WEAPON_FLAME_BALL: {
			//												probably wrong
			tf2::get_projectile_fire_setup( player, angles, vector( 0.0f, 12.0f, 0.0f ), position, angle, false );
			info = { TF_PROJECTILE_BALLOFFIRE, position, angle, 3000.0f, 0.0f, true };
			return true;
		}
		
		case TF_WEAPON_SYRINGEGUN_MEDIC: {
			// wrong
			tf2::get_projectile_fire_setup(player, angles, vector(23.5f, 4.0f, -6.0f), position, angle, false);
			info = { TF_PROJECTILE_SYRINGE, position, angle, 1000.f, 0.2f, true };
			return true;
		}

		default: return false;
	}
}

void c_projectile_sim::run_tick( ) {
	if ( !environment )
		return;

	environment->simulate( TICK_INTERVAL );
}

vector c_projectile_sim::get_origin( ) {
	if ( !object )
		return vector( );

	auto out = vector( );
	object->get_position( &out, nullptr );

	return out;
}