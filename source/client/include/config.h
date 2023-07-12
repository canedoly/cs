#pragma once
#include "util.h"

class c_key_bind {
public:
	c_key_bind( uint16_t key ) {
		m_key = key;
	}

	bool is_held( ) {
		return ( m_key && GetAsyncKeyState( m_key ) && util::is_window_in_focus( ) );
	}

	uint16_t m_key = 0u;
};

enum e_models_materials { NONE, FLAT, SHADED, FRESNEL };
class c_config {
public:
	struct {
		bool m_enabled = true;
		c_key_bind m_aim_key = c_key_bind( VK_XBUTTON2 );
		bool m_ignore_friends = true;
		bool m_ignore_cloaked = false;
		int m_aim_fov = 60;
	} m_aimbot_global;

	struct {
		bool m_enabled = true;
		bool m_delayshot = true;
		int m_delayshot_percent = 30;
		bool m_auto_scope = true;
		bool m_aim_stickies = true;
		bool m_tap_fire = true;
		int m_tap_fire_distance = 1000;
		bool m_baim_on_lethal = true;
		float m_heavy_mp = 65.f;
		float m_scout_mp = 55.f;
		float m_sniper_mp = 66.f;
		bool m_require_key = false;
		bool m_safe_point = false;
		bool m_force_last_tick = false;
		bool m_backtrack = true;
		int m_max_targets = 4;
	} m_aimbot;

	struct {
		bool m_enabled = true;
		bool m_draw_indicator = true;
		bool m_extreme_prediction = false;
	} m_seed_pred;

	struct {
		bool m_enabled = true;
		bool m_auto_shoot = true;
		int m_target_sorting = 0; // 0 = fov // 1 = dist
		bool m_optimized_prediction = false;
		bool m_turn_prediction = true;
		float m_sample_time = 0.1f; // sample time for turn data in seconds, lower = quicker reactions / higher = more stable
		float m_hitchance = 25.0f;
		float m_max_simulation_time = 3.0f;
		bool m_draw_prediction_path = true;
		bool m_draw_projectile_path = true;
		bool m_projectile_path_any_angle = false;
	} m_projectile_aim;

	struct {
		bool m_enabled = true;
		bool m_auto_detonate = true;
		int m_auto_detonate_distance = 90;
		int m_charge_max = 0;
		bool m_auto_vaccinator = true;
		bool m_auto_vacc_pop = true;
		int m_auto_vaccinator_projectile_threat = 2;
		int m_auto_vaccinator_player_threat = 1;
		int m_auto_vaccinator_projectile_prediction = 3;
		int m_auto_vac_switch_delay = 120;
	} m_automations;

	struct {
		bool m_enable = true;
		bool m_require_aimkey = true;
		bool m_if_backstable = true;
		bool m_smack_friedly_buildings = true;
		bool m_smack_friends = true;
	} m_melee_aim;

	struct {
		bool m_players_enabled = true;
		bool m_buildings_enabled = true;
		bool m_projectiles_enabled = true;
		bool m_world_enabled = true;
		//bool m_misc_enabled = true;

		// --- players ---
		bool m_player_name = true;
		bool m_player_box = true;
		bool m_player_health = true;
		bool m_player_weapon = true;
		bool m_player_flags = true;
		bool m_player_enemy = false;
		bool m_player_team_color = false;
		int m_far_esp_fade_t = 10;
		bool m_player_arrows = true;
		float m_arrows_screen_distance = 0.2f;
		int m_arrows_screen_shape = 0;
		bool m_arrows_esp = true;

		// --- buildings ---
		bool m_building_name = true;
		bool m_building_box = true;
		bool m_building_health = true;
		bool m_building_flags = true;
		bool m_building_enemy = false;

		// --- projectiles ---
		bool m_projectile_name = true;
		bool m_projectile_box = true;
		bool m_projectile_distance = true;
		bool m_projectile_flags = true;
		bool m_projectile_enemy = true;
		bool m_predict_stickies = true;

		// --- world ---
		bool m_world_name = true;
		bool m_world_box = true;
		bool m_world_distance = true;
	} m_esp;

	struct {
		bool m_enabled = true;
		int m_rendering_order = 0;

		// --- players ---
		bool m_player_models = true;
		bool m_player_two_models = true;
		bool m_player_ignorez = true;
		bool m_player_enemy_only = false;
		bool m_player_overlay = false;
		bool m_player_overlay_occluded = false;
		bool m_player_overlay_unoccluded = false;
		float m_player_alpha = 1.0f;
		float m_player_alpha_occluded = 1.0f;
		float m_player_alpha_unoccluded = 1.0f;
		bool m_player_attachments = true;
		int m_player_model = FLAT;
		int m_player_model_occluded = FLAT;
		int m_player_model_unoccluded = FLAT;

		bool m_backtrack_models = true;
		bool m_backtrack_last_only = true;
		e_models_materials m_backtrack_model = FLAT;

		// --- buildings ---
		bool m_building_models = true;
		bool m_building_two_models = true;
		bool m_building_ignorez = true;
		bool m_building_enemy_only = false;
		bool m_building_overlay = false;
		bool m_building_overlay_occluded = false;
		bool m_building_overlay_unoccluded = false;
		float m_building_alpha = 1.0f;
		float m_building_alpha_occluded = 1.0f;
		float m_building_alpha_unoccluded = 1.0f;
		int m_building_model = FLAT;
		int m_building_model_occluded = FLAT;
		int m_building_model_unoccluded = FLAT;

		// --- world ---
		bool m_world_models = true;
		bool m_world_two_models = true;
		bool m_world_ignorez = true;
		bool m_world_overlay = false;
		bool m_world_overlay_occluded = false;
		bool m_world_overlay_unoccluded = false;
		float m_world_alpha = 1.0f;
		float m_world_alpha_occluded = 1.0f;
		float m_world_alpha_unoccluded = 1.0f;
		int m_world_model = FLAT;
		int m_world_model_occluded = FLAT;
		int m_world_model_unoccluded = FLAT;

		// --- projectiles ---
		bool m_projectile_models = true;
		bool m_projectile_two_models = true;
		bool m_projectile_ignorez = true;
		bool m_projectile_enemy_only = false;
		bool m_projectile_overlay = false;
		bool m_projectile_overlay_occluded = false;
		bool m_projectile_overlay_unoccluded = false;
		float m_projectile_alpha = 1.0f;
		float m_projectile_alpha_occluded = 1.0f;
		float m_projectile_alpha_unoccluded = 1.0f;
		int m_projectile_model = FLAT;
		int m_projectile_model_occluded = FLAT;
		int m_projectile_model_unoccluded = FLAT;
	} m_models;

	struct {
		bool m_enabled = true;
		bool m_blur_outline = true;
		bool m_stencil_outline = true;
		int m_blur_scale = 5;
		int m_stencil_scale = 1;

		// --- players ---
		bool m_player_outlines = true;
		bool m_player_enemy_only = false;
		float m_player_alpha = 1.0f;

		// --- buildings ---
		bool m_building_outlines = true;
		bool m_building_enemy_only = false;
		float m_building_alpha = 1.0f;

		// --- world ---
		bool m_world_outlines = true;
		float m_world_alpha = 1.0f;

		// --- projectiles ---
		bool m_projectile_outlines = true;
		bool m_projectile_enemy_only = false;
		float m_projectile_alpha = 1.0f;

	} m_outlines;

	struct {
		int m_bullet_tracers = 1;
		bool m_mvm_giant_sounds = true;
		bool m_sniper_sightlines = true;
		int m_zoomed_field_of_view = 90;
		int m_field_of_view = 120;
		bool m_thirdperson = false;
		bool m_remove_recoil = false;
		int m_viewmodel_x = 0, m_viewmodel_y = 0, m_viewmodel_z = 0, m_viewmodel_roll = 0, m_viewmodel_fov = 68;
		bool m_viewmodel_sway = false;
		int m_viewmodel_sway_val = 0;
		bool m_remove_scope = true;
		bool m_visualize_aimbot = true;
		bool m_remove_zoom = true;
		float m_aspect_ratio = 0.f;
		float m_prop_alpha = 0.7f;
		c_key_bind m_thirdperson_key = c_key_bind( 'Z' );

		// --- ragdolls ---
		bool m_ragdolls_enabled = true;
		bool m_ragdolls_enemy_only = true;
		int m_ragdoll_type = 0; // 0 - default, 1 - gold, 2 - ice
		bool m_ragdoll_burning = false;
		bool m_ragdoll_electrocuted = false;
		bool m_ragdoll_dissolving = false;
		bool m_ragdoll_become_ash = false;

		bool m_projectile_camera = false;
		int m_projectile_camera_forward = 85;
		int m_projectile_camera_right = 0;
		int m_projectile_camera_up = 100;
		int m_projectile_camera_fov = 80;
	} m_visuals;

	struct {
		bool m_bunnyhop = true;
		bool m_auto_strafer = true;
		bool m_fast_stop = true;
		bool m_scout_jump = true;
		bool m_taunt_slide = true;
		bool m_avoid_push = true;
		bool m_skip_welcome = true;
		bool m_vote_revealer = true;
		bool m_reduce_input_delay = false;
		bool m_chat_player_connects = false;
		bool m_chat_player_disconnects = false;
		bool m_chat_player_class_changes = false;
		bool m_chat_player_name_changes = false;
		bool m_chat_vote_casts = false;
		c_key_bind m_scout_jump_key = c_key_bind( 'X' );
	} m_misc;

	struct {
		bool m_fakelag = false;
		bool m_fakelag_no_dt = true;
		int m_max_ticks = 22;
		int m_max_unchoke_del = 0;
		bool m_break_lag_comp = true;

		struct {
			bool m_enabled = false;
			int m_max_angle = 180;
			int m_min_angle = -180;
			bool m_jitter = true;
			int m_jitter_max = 100;
			int m_pitch_angle = 271;
		} m_pitch;

		struct {
			bool m_enabled = false;
			bool m_anti_logic = true;
			bool m_edge = true;
		} m_real_yaw;

		struct {
			bool m_enabled = false;
			bool m_anti_logic = false;
			bool m_jitter = true;
			int m_max_angle = 180;
			int m_min_angle = -180;
			int m_jitter_max = 4;
		} m_fake_yaw;
	} m_hvh;

	struct {
		bool m_crithack = true;
		bool m_crithack_indicator = true;
		bool m_doubletap = true;
		bool m_doubletap_indicator = true;
		bool m_warp = true;
		bool m_doubletap_in_air = true;
		bool m_no_choke = false;
		int m_warp_speed = 3;
		bool m_dynamic_warp_ticks = false;
		bool m_auto_warp = true;
		int m_auto_warp_scale = 30;
		bool m_fake_latency = false;
		int m_fake_latency_amount = 200;
		bool m_backtrack = false;
		
		c_key_bind m_crithack_key = c_key_bind( 'Q' );
		c_key_bind m_doubletap_recharge_key = c_key_bind( 'R' );
		c_key_bind m_tickbase_warp_key = c_key_bind( VK_LSHIFT );
		c_key_bind m_auto_warp_key = c_key_bind( 'F' );
	} m_exploits;

	struct {
		color m_ui_outline = color( 15, 15, 15 );
		color m_ui_background = color( 30, 30, 30 );
		color m_ui_foreground = color( 45, 45, 45 );
		color m_ui_accent = color( 195, 65, 65 );
		color m_ui_text = color( 255, 255, 255 );
	} m_colors;

	struct {
		bool m_skull_background = false;
	} m_menu;

	struct {
		c_key_bind m_detach_key = c_key_bind( VK_F11 );
	} m_settings;
};

inline c_config* config = new c_config;