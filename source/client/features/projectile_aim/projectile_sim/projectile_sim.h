#pragma once
#include "../../../include/tf2.h"

struct projectile_info_t {
	projectile_type_t m_type = { };
	vector m_position = vector( ), m_angle = vector( );
	float m_speed = 0.0f, m_gravity_modifier = 0.0f;
	bool m_no_spin = false;
};

class c_projectile_sim {
public:
	bool init( const projectile_info_t& info );
	bool get_info( c_base_player* player, c_base_combat_weapon* weapon, const vector& angles, projectile_info_t& info );
	void run_tick( );
	vector get_origin( );
};

inline c_projectile_sim* projectile_sim = new c_projectile_sim;