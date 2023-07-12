#pragma once
#include "config.h"
#include "entities.h"

#define TICK_INTERVAL		( ctx->m_globals->m_interval_per_tick )
#define TIME_TO_TICKS( dt )	( static_cast< int >( 0.5f + static_cast< float >( dt ) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )	( TICK_INTERVAL * ( t ) )

struct font_t {
	const char* m_name = "";
	int m_tall = 0, m_weight = 0, m_flags = 0;
	DWORD m_font = 0x0;
};

class c_ctx {
public:
	// --- interfaces ---
	i_base_client_dll* m_client = nullptr;
	i_client_mode* m_client_mode = nullptr;
	c_client_state* m_client_state = nullptr;
	i_cvar* m_cvar = nullptr;
	iv_debug_overlay* m_debug_overlay = nullptr;
	iv_engine_client* m_engine_client = nullptr;
	i_engine_trace* m_engine_trace = nullptr;
	i_engine_vgui* m_engine_vgui = nullptr;
	i_client_entity_list* m_entity_list = nullptr;
	c_game_event_manager* m_game_event = nullptr;
	c_game_movement* m_game_movement = nullptr;
	c_global_vars_base* m_globals = nullptr;
	i_input* m_input = nullptr;
	iv_model_info* m_model_info = nullptr;
	iv_model_renderer* m_model_renderer = nullptr;
	iv_material_system* m_material_system = nullptr;
	i_move_helper* m_move_helper = nullptr;
	i_physics* m_physics = nullptr;
	i_physics_collision* m_physics_collision = nullptr;
	i_physics_surface_props* m_physics_surface_props = nullptr;
	c_prediction* m_prediction = nullptr;
	int32_t* m_random_seed = nullptr;
	iv_render_view* m_render_view = nullptr;
	i_steam_client* m_steam_client = nullptr;
	i_steam_user* m_steam_user = nullptr;
	i_studio_render* m_studio_render = nullptr;
	i_surface* m_surface = nullptr;
	c_panel* m_panel = nullptr;
	i_view_render* m_view_render = nullptr;

	// --- entities ---
	c_base_player* m_local_player = nullptr;
	c_base_combat_weapon* m_local_weapon = nullptr;
	c_player_resource* m_player_resource = nullptr;

	std::vector< c_base_player* > players = { };
	std::vector< c_base_object* > buildings = { };
	std::vector< c_base_entity* > aimbot_entities = { };
	std::vector< c_base_entity* > healthpacks = { };
	std::vector< c_base_entity* > ammopacks = { };
	std::vector< c_base_entity* > projectiles = { };

	//will finish later
	/*std::vector<c_base_entity*> objectives = { };
	std::vector<c_base_entity*>	bombs = { };
	std::vector<c_base_entity*>	npc = { };*/

	// -- fonts ---
	font_t m_tahoma_narrow = { "Tahoma", 12, 0 };
	font_t m_tahoma_wide = { "Tahoma", 12, 600 };
	font_t m_tahoma_big = { "Tahoma", 18, 500 };
	font_t m_tahoma_bold = { "Tahoma Bold", 12, 800 };
	font_t m_verdana_narrow = { "Verdana", 12, 0 };
	font_t m_small_fonts = { "Small Fonts", 8, 0 };
	font_t m_small_fonts_medium = { "Small Fonts", 10, 0 };

	// --- dt ---
	bool m_is_recharging = false, m_shift = false, m_running_shift = false, m_warping = false;
	float m_dt_recharge_wait = 0.f;
	int m_charged_ticks = 0, m_wait_ticks = 24;
	int m_shifted_ticks = 24;
	std::function< void( float, bool ) > m_cl_move_call;

	// --- other ---
	int m_screen_width = 0, m_screen_height = 0;
	view_matrix m_world_to_projection = { };
	void* m_aimbot_target_info = nullptr;
	bool* m_send_packet = nullptr;
	bool m_perfect_silent = false;;
	std::map<c_base_player*, int> m_far_esp_t = { };
	int m_fps = 0;
	c_user_cmd* m_current_user_cmd = nullptr;
	bool was_in_attack = false;
	bool finished_last_shot = false;
	vector m_punch_angle = {};
	bool m_update_anims = false;
	DWORD m_update_client_side_animations = 0x0, m_anim_state_update = 0x0;
	bool m_choking = false;
	bool m_drawing_static_props = false;
	bool m_sniper_dot_is_local = false;
	int m_last_ammo = 0;
	clc_move m_current_move = { };
	vector m_projectile_camera_position = { };
	bool m_drawing_projectile_camera = false;

	// --- antiaim ---
	bool m_switch_yaw = false, m_choke_tick = false;
	int m_unchoke_del = 0, m_jit_del = 0;
	vector m_fake_angles = { }, m_real_angles = { }, m_actual_angles = { };
	matrix_3x4* m_fake_matrix = { };

	// --- auth ---
	std::string m_user_name = "";

	// --- viewmodel aimbot ---
	vector m_aimbot_angles = {};
	int m_aimbot_delay = 0;
	bool m_running_prediction = false;
};

inline c_ctx* ctx = new c_ctx;