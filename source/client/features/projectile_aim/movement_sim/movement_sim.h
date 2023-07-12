#pragma once
#include "../../../include/tf2.h"
#include <deque>

class c_movement_sim {
public:
	std::map< c_base_player*, std::deque< vector > > m_directions = { };
	std::map< c_base_player*, bool > m_ground_state = { };
	bool init( c_base_player* player );
	void restore( );
	vector run_tick( );
	void fill_directions( );
	void draw_path( );

private:
	std::vector< vector > m_positions = { };
	c_base_player* m_player = nullptr;
	c_move_data m_move_data = { };
	bool m_old_in_prediction = false, m_old_first_time_predicted = false;
	float m_old_frame_time = 0.0f, m_turn_speed = 0.0f, m_old_forward_move = 0.0f, m_old_side_move = 0.0f, m_time_stamp = 0.0f;
	inline const vector& get_origin( ) { return m_move_data.m_abs_origin; }
	void setup_move_data( c_base_player *player, c_move_data* move_data );
	void compute_turn_speed( c_base_player* player, c_move_data* move_data );
};

inline c_movement_sim* movement_sim = new c_movement_sim;