#pragma once
#include "movement_sim/movement_sim.h"
#include "projectile_sim/projectile_sim.h"

class c_projectile_aim {
public:
	void run( c_user_cmd* cmd );
	void draw_path( );

private:
	projectile_info_t m_projectile_info = { };
	std::vector< vector > m_positions = { };
	float m_time = 0.0f, m_time_stamp = 0.0f;
	vector m_angle = vector( );
	c_base_entity* m_target = nullptr;
	bool find_ideal_target( c_base_player* player );
	std::vector< vector > get_aim_positions( c_base_combat_weapon* weapon );
	void handle_player_aim( c_base_player* player, c_base_combat_weapon* weapon, c_user_cmd* cmd );
	void handle_building_aim( c_base_player* player, c_base_combat_weapon* weapon, c_user_cmd* cmd );
	float get_latency( );
	bool is_pipe( c_base_combat_weapon* weapon );
	bool is_rocket( c_base_combat_weapon* weapon );
	float solve_projectile_speed(c_base_combat_weapon* weapon, const vector& a, const vector& b);
	bool solve_projectile( c_base_combat_weapon* weapon, const vector& a, const vector& b );
	void solve_pipe_aim( c_base_combat_weapon* weapon );
	bool trace_projectile_path( c_base_player* player, c_base_combat_weapon* weapon, vector pos );
	void aim( c_base_combat_weapon* weapon, c_user_cmd* cmd );
};

inline c_projectile_aim* projectile_aim = new c_projectile_aim;