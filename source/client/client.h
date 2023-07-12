#pragma once
#include "hooks/hooks.h"
#include "features/menu/menu.h"
#include "features/game_events/game_events.h"
#include "features/models/models.h"
#include "features/outlines/outlines.h"
#include "features/visuals/visuals.h"

class c_client {
public:
	void attach( ) {

		while ( !GetModuleHandleA( "mss32.dll" ) || !GetModuleHandleA( "materialsystem.dll" ) || !GetModuleHandleA( "shaderapidx9.dll" ) )
			std::this_thread::sleep_for( std::chrono::milliseconds( 175 ) );

		// --- steam interfaces ---
		ctx->m_steam_client = util::get_interface< i_steam_client* >( "steamclient.dll", "SteamClient017" );
		auto steam_pipe = ctx->m_steam_client->create_steam_pipe( );
		auto steam_user = ctx->m_steam_client->connect_to_global_user( steam_pipe );
		ctx->m_steam_user = ctx->m_steam_client->get_steam_user( steam_user, steam_pipe, "SteamUser017" );

		menu->load_config( );

		// --- interfaces ---
		ctx->m_client = util::get_interface< i_base_client_dll* >( "client.dll", "VClient017" );
		ctx->m_client_mode = **util::find_signature< i_client_mode***, 2u >( "client.dll", "8B 0D ? ? ? ? 8B 02 D9 05" );
		ctx->m_client_state = *util::find_signature< c_client_state**, 1u >( "engine.dll", "68 ? ? ? ? E8 ? ? ? ? 83 C4 08 5F 5E 5B 5D C3" );
		ctx->m_cvar = util::get_interface< i_cvar* >( "vstdlib.dll", "VEngineCvar004" );
		ctx->m_debug_overlay = util::get_interface< iv_debug_overlay* >( "engine.dll", "VDebugOverlay003" );
		ctx->m_engine_client = util::get_interface< iv_engine_client* >( "engine.dll", "VEngineClient013" );
		ctx->m_engine_trace = util::get_interface< i_engine_trace* >( "engine.dll", "EngineTraceClient003" );
		ctx->m_engine_vgui = util::get_interface< i_engine_vgui* >( "engine.dll", "VEngineVGui002" );
		ctx->m_entity_list = util::get_interface< i_client_entity_list* >( "client.dll", "VClientEntityList003" );
		ctx->m_game_event = util::get_interface< c_game_event_manager* >( "engine.dll", "GAMEEVENTSMANAGER002" );
		ctx->m_game_movement = util::get_interface< c_game_movement* >( "client.dll", "GameMovement001" );
		ctx->m_globals = *util::find_signature< c_global_vars_base**, 8u >( "engine.dll", "A1 ? ? ? ? 8B 11 68" );
		ctx->m_input = **util::find_signature< i_input***, 2u >( "client.dll", "8B 0D ? ? ? ? 56 8B 01 FF 50 24 8B 45 FC" );
		ctx->m_model_info = util::get_interface< iv_model_info* >( "engine.dll", "VModelInfoClient006" );
		ctx->m_move_helper = **util::find_signature< i_move_helper***, 2u >( "client.dll", "8B 0D ? ? ? ? 8B 01 FF 50 28 56 8B C8" );
		ctx->m_physics = util::get_interface< i_physics* >( "vphysics.dll", "VPhysics031" );
		ctx->m_physics_collision = util::get_interface< i_physics_collision* >( "vphysics.dll", "VPhysicsCollision007" );
		ctx->m_physics_surface_props = util::get_interface< i_physics_surface_props* >( "vphysics.dll", "VPhysicsSurfaceProps001" );
		ctx->m_prediction = util::get_interface< c_prediction* >( "client.dll", "VClientPrediction001" );
		ctx->m_random_seed = *util::find_signature< int32_t**, 2u >( "client.dll", "C7 05 ? ? ? ? ? ? ? ? 5D C3 8B 40 34" );
		ctx->m_render_view = util::get_interface< iv_render_view* >( "engine.dll", "VEngineRenderView014" );
		ctx->m_studio_render = util::get_interface< i_studio_render* >( "studiorender.dll", "VStudioRender025" );
		ctx->m_surface = util::get_interface< i_surface* >( "vguimatsurface.dll", "VGUI_Surface030" );
		ctx->m_panel = util::get_interface< c_panel* >( "vgui2.dll", "VGUI_Panel009" );
		ctx->m_model_renderer = util::get_interface<iv_model_renderer*>("engine.dll", "VEngineModel016");
		ctx->m_material_system = util::get_interface<iv_material_system*>("materialsystem.dll", "VMaterialSystem081");
		ctx->m_view_render = **util::find_signature<i_view_render***, 2u>( "client.dll", "8B 0D ? ? ? ? 8B 01 FF 50 ? 8B 06 8D 4D ? 51 8B CE" );

		// --- other signatures ---
		ctx->m_anim_state_update = util::find_signature< DWORD >( "client.dll", "55 8B EC 81 EC ? ? ? ? 53 57 8B F9 8B 9F ? ? ? ? 89 5D E0 85 DB 0F 84" );
		ctx->m_update_client_side_animations = util::find_signature< DWORD >( "client.dll", "55 8B EC 83 EC 0C 56 57 8B F1 E8 ? ? ? ? 8B F8 85 FF 74 10 8B 17 8B CF 8B 92 ? ? ? ? FF D2" );

		// --- fonts ---
		render->reload_fonts( );

		// --- materials ---
		models->init_materials( );
		outlines->init_materials( );

		// --- hooks ---
		MH_Initialize( ); {
			hooks::add_to_crit_bucket::init( );
			hooks::anim_state_update::init( );
			hooks::build_transformations::init( );
			hooks::calc_is_attack_critical::init( );
			hooks::calc_viewmodel_view::init( );
			hooks::chat_printf::init( );
			hooks::check_for_sequence_change::init( );
			hooks::check_simple_material::init( );
			hooks::cl_check_for_pure_server_whitelist::init();
			hooks::cl_move::init( );
			hooks::cl_read_packets::init( );
			hooks::cl_send_move::init( );
			hooks::client_think::init( );
			hooks::create_move::init( );
			hooks::create_tf_gibs::init( );
			hooks::create_tf_ragdoll::init( );
			hooks::dispatch_user_message::init( );
			hooks::do_post_screen_space_effects::init( );
			hooks::draw_model_execute::init( );
			hooks::draw_static_props::init( );
			hooks::fire_bullet::init( );
			hooks::forced_material_override::init( );
			hooks::frame_stage_notify::init( );
			hooks::fx_fire_bullets::init( );
			hooks::get_shoot_sound::init( );
			hooks::get_tracer_type::init( );
			hooks::get_user_cmd::init( );
			hooks::in_cond::init( );
			hooks::interpolate::init( );
			hooks::interpolate_server_entities::init();
			hooks::is_pve_mode_active::init( );
			hooks::level_init::init( );
			hooks::level_shutdown::init( );
			hooks::lock_cursor::init( );
			hooks::material_uncache::init( );
			hooks::notification_queue_add::init( );
			hooks::on_screen_size_changed::init( );
			hooks::override_view::init( );
			hooks::paint::init( );
			hooks::paint_traverse::init( );
			hooks::physics_simulate::init( );
			hooks::render_view::init( );
			hooks::run_command::init( );
			hooks::s_start_dynamic_sound::init( );
			hooks::send_datagram::init( );
			hooks::send_net_message::init( );
			hooks::set_alpha_modulation::init( );
			hooks::set_color_modulation::init( );
			hooks::setup_bones::init( );
			hooks::should_draw_viewmodel::init( );
			hooks::update_client_side_animations::init( );
			hooks::use_item_confirm::init( );
			hooks::wnd_proc::init( );
			//hooks::write_user_cmd::init( );
		} MH_EnableHook( MH_ALL_HOOKS );

		// --- events ---
		game_events->init( );
		//ctx->m_cvar->find_var( "rate" )->set_value( 786432 ); // we do a little trolling and fix the dombletap
		ctx->m_cvar->find_var( "r_drawtracers_firstperson" )->set_value( 1 );

		// -- cheater list ---
		util::download_cheater_list( ); // this might take a while on slow connections
	}

	void detach( ) {
		menu->reset( );
		ctx->m_game_event->remove_listener( game_events );
		MH_DisableHook( MH_ALL_HOOKS );
		MH_Uninitialize( );
		models->remove_materials( );
		outlines->remove_materials( );
		render->delete_textures( );
	}

	bool m_unauthorized = false;
};

inline c_client* client = new c_client;
