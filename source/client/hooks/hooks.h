#pragma once
#include "minhook/minhook.h"
#include "../include/tf2.h"

namespace hooks {
	namespace add_to_crit_bucket {
		typedef void( __fastcall* fn )( c_base_combat_weapon*, void*, float );
		inline fn original_function;
		void __fastcall function( c_base_combat_weapon* this_, void* edx, float damage );
		void init( );
	}

	namespace anim_state_update {
		typedef void( __fastcall* fn )( void*, void*, float, float );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, float yaw, float pitch );
		void init( );
	}

	namespace build_transformations {
		typedef void( __fastcall* fn )( void*, void*, void*, vector*, void*, matrix_3x4&, int, void* );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, void* hdr, vector* pos, void* q, matrix_3x4& camera_transform, int bone_mask, void* bone_computed );
		void init( );
	}

	namespace calc_is_attack_critical {
		typedef void( __fastcall* fn )( c_base_combat_weapon*, void* );
		inline fn original_function;
		void __fastcall function( c_base_combat_weapon* this_, void* edx );
		void init( );
	}

	namespace calc_viewmodel_view {
		using fn = void( __fastcall* )( void*, void*, c_base_player*, const vector&, vector& );
		inline fn original_function = nullptr;
		void __fastcall function( void*, void*, c_base_player*, const vector&, vector& );
		void init( );
	}

	namespace chat_printf {
		typedef void( __cdecl* fn )( void*, int, int, const char*, ... );
		inline fn original_function;
		void __cdecl function( void* ecx, int index, int filter, const char* fmt, ... );
		void init( );
	}

	namespace check_for_sequence_change {
		typedef void( __fastcall* fn )( void*, void*, void*, int, bool, bool );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, void* hdr, int current, bool force_new, bool interpolate );
		void init( );
	}

	namespace check_simple_material {
		typedef bool( __cdecl* fn )( i_material* );
		inline fn original_function;
		bool __cdecl function( i_material* material );
		void init( );
	}

	namespace cl_check_for_pure_server_whitelist {
		typedef void( __cdecl* fn )( int );
		inline fn original_function;
		void __cdecl function( int files );
		void init( );
	}

	namespace cl_move {
		typedef void( __cdecl* fn )( float, bool );
		inline fn original_function = nullptr;
		void __cdecl function( float accumulated_extra_samples, bool final_tick );
		void init( );
	};

	namespace cl_read_packets {
		typedef void( __cdecl* fn )( bool );
		inline fn original_function = nullptr;
		void __cdecl function( bool final_tick );
		void init( );
	}

	namespace cl_send_move {
		typedef void( __fastcall* fn )( void*, void* );
		inline fn original_function = nullptr;
		void __fastcall function( void* ecx, void* edx );
		void init( );
	}

	namespace client_think {
		typedef void( __fastcall* fn )( void*, void* );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx );
		void init( );
	}

	namespace create_move {
		typedef bool( __fastcall* fn )( void*, void*, float, c_user_cmd* );
		inline fn original_function;
		bool __fastcall function( void* ecx, void* edx, float input_sample_time, c_user_cmd* cmd );
		void init( );
	}

	namespace create_tf_gibs {
		typedef void( __fastcall* fn )( c_tf_ragdoll*, void*, bool, bool );
		inline fn original_function;
		void __fastcall function( c_tf_ragdoll* this_, void* ecx, bool destroy_ragdoll, bool current_position );
		void init( );
	}

	namespace create_tf_ragdoll {
		typedef void( __fastcall* fn )( c_tf_ragdoll*, void* );
		inline fn original_function;
		void __fastcall function( c_tf_ragdoll* this_, void* edx );
		void init( );
	}

	namespace dispatch_user_message {
		typedef bool( __fastcall* fn )( void*, void*, int msg_type, bf_read& msg_data );
		inline fn original_function;
		bool __fastcall function( void*, void*, int msg_type, bf_read& msg_data );
		void init( );
	}

	namespace do_post_screen_space_effects {
		typedef bool( __fastcall* fn )( void*, void*, const c_view_setup* );
		inline fn original_function;
		bool __fastcall function( void* ecx, void* edx, const c_view_setup* view );
		void init( );
	}

	namespace draw_model_execute {
		typedef void( __fastcall* fn )( void*, void*, const draw_model_state_t&, const model_render_info_t&, matrix_3x4* );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, const draw_model_state_t&, const model_render_info_t&, matrix_3x4* );
		void init( );
	}

	namespace draw_static_props {
		typedef void( __fastcall* fn )( void*, void*, void**, int, bool, bool );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, void** props, int count, bool shadow_depth, bool draw_vcollide_wireframe );
		void init( );
	}

	namespace fire_bullet {
		typedef void( __fastcall* fn )( c_base_player*, void*, c_base_combat_weapon*, const fire_bullets_info_t&, bool, int, int );
		inline fn original_function;
		void __fastcall function( c_base_player* this_, void* edx, c_base_combat_weapon* weapon, fire_bullets_info_t& info, bool do_effects, int damage_type, int custom_damage_type );
		void init( );
	}

	namespace forced_material_override {
		typedef void( __fastcall* fn )( void*, void*, i_material*, int );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, i_material* mat, int override_type );
		void init( );
	}

	namespace frame_stage_notify {
		typedef void( __fastcall* fn )( void*, void*, client_frame_stage_t );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, client_frame_stage_t stage );
		void init( );
	}

	namespace fx_fire_bullets {
		typedef void ( __cdecl* fn )( c_base_combat_weapon* wpn, int player, const vector& origin, const vector& angles, int weapon, int mode, int seed, float flSpread, float damage /* = -1.0f */, bool critical /* = false*/ );
		inline fn original_function;
		void __cdecl function( c_base_combat_weapon* wpn, int player, const vector& origin, const vector& angles, int weapon, int mode, int seed, float flSpread, float damage /* = -1.0f */, bool critical /* = false*/ );
		void init( );
	}

	namespace get_shoot_sound {
		typedef const char*( __fastcall* fn )( void*, void*, int );
		inline fn original_function;
		const char* __fastcall function( void* ecx, void* edx, int );
		void init( );
	}

	namespace get_tracer_type {
		typedef const char* ( __fastcall* fn )( void*, void* );
		inline fn original_function;
		const char* __fastcall function( void* ecx, void* edx );
		void init( );
	}

	namespace get_user_cmd {
		typedef c_user_cmd* ( __fastcall* fn )( void*, void*, int );
		inline fn original_function;
		c_user_cmd* __fastcall function( void* ecx, void* edx, int sequence_number );
		void init( );
	}

	namespace in_cond {
		typedef bool( __fastcall* fn )( void*, void*, e_tf_cond );
		inline fn original_function;
		bool __fastcall function( void* ecx, void* edx, e_tf_cond id );
		void init( );
	}

	namespace interpolate {
		typedef bool( __fastcall* fn )( c_base_entity*, void*, float );
		inline fn original_function = nullptr;
		bool __fastcall function( c_base_entity* ecx, void* edx, float current_time );
		void init( );
	}

	namespace interpolate_server_entities {
		typedef void( __cdecl* fn )( );
		inline fn original_function;
		void __cdecl function( );
		void init( );
	}

	namespace is_pve_mode_active {
		typedef bool( __fastcall* fn )( void*, void* );
		inline fn original_function;
		bool __fastcall function( void* ecx, void* edx );
		void init( );
	}

	namespace level_init {
		typedef void( __fastcall* fn )( void*, void* );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx );
		void init( );
	}

	namespace level_shutdown {
		typedef void( __fastcall* fn )( void*, void* );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx );
		void init( );
	}

	namespace lock_cursor {
		typedef void( __fastcall* fn )( void*, void* );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx );
		void init( );
	}

	namespace material_uncache {
		typedef void( __fastcall* fn )( i_material*, void*, bool );
		inline fn original_function;
		void __fastcall function( i_material* ecx, void* edx, bool preserve_vars );
		void init( );
	}

	namespace notification_queue_add {
		typedef int( __cdecl* fn )( void* );
		inline fn original_function;
		void __cdecl function( void* notif );
		void init( );
	}

	namespace on_remove_entity {
		typedef void( __fastcall* fn )( void*, void*, c_base_entity*, unsigned int );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, c_base_entity* ent, unsigned int unk );
		void init( );
	}

	namespace on_screen_size_changed {
		typedef void( __fastcall* fn )( void*, void*, int, int );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, int old_width, int old_height );
		void init( );
	}

	namespace override_view {
		typedef void( __fastcall* fn )( void*, void*, c_view_setup* );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, c_view_setup* setup );
		void init( );
	}

	namespace paint {
		typedef void( __fastcall* fn )( void*, void*, paint_mode_t );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, paint_mode_t mode );
		void init( );
	}

	namespace paint_traverse {
		typedef void( __fastcall* fn )( void*, void*, unsigned int, bool, bool );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, unsigned int vgui_panel, bool force_repaint, bool allow_force );
		void init( );
	}

	namespace physics_simulate {
		using fn = void( __fastcall* )( void*, void* );
		inline fn original_function = nullptr;
		void __fastcall function( void*, void* );
		void init( );
	}

	namespace render_view {
		using fn = void( __fastcall* ) ( void*, void*, const c_view_setup&, int, int );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, const c_view_setup& view, int clear_flags, int what_to_draw );
		void init( );
	}

	namespace run_command {
		typedef void( __fastcall* fn )( void*, void*, c_base_player*, c_user_cmd*, i_move_helper* );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, c_base_player* player, c_user_cmd* ucmd, i_move_helper* move_helper );
		void init( );
	}

	namespace s_start_dynamic_sound {
		typedef void( __cdecl* fn )( start_sound_params_t& );
		inline fn original_function;
		void __cdecl function( start_sound_params_t& params );
		void init( );
	};

	namespace send_datagram {
		typedef int( __fastcall* fn )( void*, void*, bf_write* );
		inline fn original_function;
		int __fastcall function( void*, void*, bf_write* );
		void init( );
	}

	namespace send_net_message {
		typedef bool( __fastcall* fn )( void*, void*, i_net_message*, bool, bool );
		inline fn original_function;
		bool __fastcall function( void*, void*, i_net_message*, bool, bool );
		void init( );
	}

	namespace set_alpha_modulation {
		typedef void( __fastcall* fn )( void*, void*, float );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, float alpha );
		void init( );
	}

	namespace set_color_modulation {
		typedef void( __fastcall* fn )( void*, void*, float const* );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx, float const* color );
		void init( );
	}

	namespace setup_bones {
		typedef bool( __fastcall* fn )( void*, void*, matrix_3x4*, int, int, float );
		inline fn original_function;
		bool __fastcall function( void* ecx, void* edx, matrix_3x4* bone_to_world, int max_bones, int bone_mask, float current_time );
		void init( );
	}

	namespace should_draw_viewmodel {
		typedef bool( __fastcall* fn )( void* ecx, void* edx );
		inline fn original_function;
		bool __fastcall function( void* ecx, void* edx );
		void init( );
	}

	namespace update_client_side_animations {
		typedef void( __fastcall* fn )( void*, void* );
		inline fn original_function;
		void __fastcall function( void* ecx, void* edx );
		void init( );
	}

	namespace use_item_confirm {
		typedef void( __cdecl* fn )( bool, void* );
		inline fn original_function;
		void __cdecl function( bool unkn, DWORD* context );
		void init( );
	}

	namespace wnd_proc {
		inline HWND game_hwnd;
		inline WNDPROC original_wndproc;

		typedef LRESULT( __thiscall* fn )( HWND, UINT, WPARAM, LPARAM );
		inline fn original_function;
		LRESULT CALLBACK function( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
		void init( );
	}

	namespace write_user_cmd {
		typedef void(  __cdecl* fn )( bf_write*, c_user_cmd*, c_user_cmd* );
		inline fn original_function;
		void __cdecl function( bf_write* buf, c_user_cmd* from, c_user_cmd* to );
		void init( );
	}
}