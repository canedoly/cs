#pragma once
#include "../../include/ctx.h"

class c_engine_prediction {
public:
	void start( c_user_cmd* cmd );
	void end( c_user_cmd* cmd );
	int get_tick_base(c_base_player* local_player, c_user_cmd* cmd);

private:
	c_move_data m_move_data = { };
	float m_old_current_time = 0.0f, m_old_frame_time = 0.0f;
	int m_old_tick_count = 0;
	
};

inline c_engine_prediction* engine_prediction = new c_engine_prediction;