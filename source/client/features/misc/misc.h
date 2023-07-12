#pragma once
#include "../../include/tf2.h"
#include <functional>

class c_misc {
public:
	void run( c_user_cmd* cmd );
	void handle_dt( c_user_cmd* cmd, bool* send_packet );
	void velocity_handler( c_user_cmd* cmd );
	void fake_lag( c_user_cmd* cmd, int max_ticks, bool* send_packet );
	bool handle_warp(float extra_sample, bool final_tick, std::function<void(float, bool)> f);
	void auto_warp(c_user_cmd* cmd);
	void handle_weapon_sway();
	void fix_local_animations();
	void anti_backstab(c_user_cmd* cmd);
	void anti_aim( c_user_cmd* cmd, bool* send_packet );
	void scout_jump( c_user_cmd* cmd );
	void shoot_sticky_at_charge( c_user_cmd* cmd );

	struct globals_backup {
		int m_cl_frame_time;
		int m_frame_time;
		int m_current_time;
		int m_tick_count;

		inline void copy( ) {
			//m_cl_frame_time = ctx->m_client_state->m_frame_time;
			//m_frame_time = ctx->m_globals->m_frame_time;
			m_current_time = ctx->m_globals->m_current_time;
			//m_tick_count = ctx->m_globals->m_tick_count;
		}

		inline void restore( ) {
			//ctx->m_client_state->m_frame_time = m_cl_frame_time;
			//ctx->m_globals->m_frame_time = m_frame_time;
			ctx->m_globals->m_current_time = m_current_time;
			//ctx->m_globals->m_tick_count = m_tick_count;
		}
	};
	globals_backup state = { };

	void fix_input_delay( bool final_tick );
	bool should_read_packets( );
private:
	void taunt_slide( c_base_player* player, c_user_cmd* cmd );
	void bunnyhop( c_base_player* player, c_user_cmd* cmd );
	void auto_strafer( c_user_cmd* cmd );
	void fast_stop( c_user_cmd* cmd );
	void leg_jitter( c_user_cmd* cmd );
};

inline c_misc* misc = new c_misc;