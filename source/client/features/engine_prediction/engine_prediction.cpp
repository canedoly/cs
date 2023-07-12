#include "engine_prediction.h"


void c_engine_prediction::start(c_user_cmd* cmd) {
	if (!ctx->m_local_player || !ctx->m_local_player->is_alive() || ctx->m_warping || ctx->m_running_shift)
		return;

	ctx->m_running_prediction = true;
	static auto update_buttons = reinterpret_cast<void(__thiscall*)(c_base_player*, int)>(util::find_signature<void*>("client.dll", "55 8B EC 8B 81 ? ? ? ? 8B D0"));
	static auto pred_player = reinterpret_cast<c_base_player*>(util::find_signature<void*, 0x2>("client.dll", "55 8B EC 8B 81 ? ? ? ? 8B D0"));
	static auto reset_instance_counter = reinterpret_cast<void(__cdecl*)()>(util::find_signature<void*>("client.dll", "68 ? ? ? ? 6A ? 68 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 83 C4 ? C3"));

	reset_instance_counter();
	ctx->m_local_player->m_current_command() = cmd;
	*ctx->m_random_seed = md5_pseudo_random(cmd->m_command_number) & std::numeric_limits< int >::max();
	pred_player = ctx->m_local_player;

	m_old_current_time = ctx->m_globals->m_current_time;
	m_old_frame_time = ctx->m_globals->m_frame_time;
	m_old_tick_count = ctx->m_globals->m_tick_count;

	const int old_tick_base = ctx->m_local_player->m_tick_base();
	const bool old_in_prediction = ctx->m_prediction->m_in_prediction;
	const bool old_first_time_predicted = ctx->m_prediction->m_first_time_predicted;

	ctx->m_globals->m_current_time = TICKS_TO_TIME(get_tick_base(ctx->m_local_player, cmd));
	ctx->m_globals->m_frame_time = (ctx->m_prediction->m_engine_paused ? 0.0f : TICK_INTERVAL);

	// iirc u dont need to set this
	ctx->m_globals->m_tick_count = get_tick_base(ctx->m_local_player, cmd);

	ctx->m_prediction->m_in_prediction = true;
	ctx->m_prediction->m_first_time_predicted = false;

	ctx->m_game_movement->start_track_prediction_errors(ctx->m_local_player);

	if (cmd->m_weapon_select != 0)
		if (const auto& weapon = ctx->m_entity_list->get_client_entity(cmd->m_weapon_select)->as<c_base_combat_weapon>())
			ctx->m_local_player->select_item(weapon->get_name(), cmd->m_weapon_subtype);

	update_buttons(ctx->m_local_player, cmd->m_buttons);
	ctx->m_prediction->set_local_view_angles(cmd->m_view_angles);

	int think_tick = ctx->m_local_player->m_next_think_tick();

	if (ctx->m_local_player->physics_run_tick(0))
		ctx->m_local_player->pre_think();

	if (think_tick > 0 && think_tick <= ctx->m_globals->m_tick_count)
	{
		ctx->m_local_player->set_next_think(-1, 0);
		ctx->m_local_player->think();
	}

	// most likely setup move causing angle change
	ctx->m_prediction->setup_move(ctx->m_local_player, cmd, ctx->m_move_helper, &m_move_data);
	ctx->m_game_movement->process_movement(ctx->m_local_player, &m_move_data);
	ctx->m_prediction->finish_move(ctx->m_local_player, cmd, &m_move_data);

	ctx->m_local_player->post_think();

	ctx->m_game_movement->finish_track_prediction_errors(ctx->m_local_player);

	ctx->m_local_player->m_tick_base() = old_tick_base;

	ctx->m_prediction->m_in_prediction = old_in_prediction;
	ctx->m_prediction->m_first_time_predicted = old_first_time_predicted;
}

void c_engine_prediction::end(c_user_cmd* cmd) {
	if (!ctx->m_local_player || !ctx->m_local_player->is_alive() || ctx->m_warping || ctx->m_running_shift)
		return;

	static auto pred_player = reinterpret_cast<c_base_player*>(util::find_signature<void*, 0x2>("client.dll", "55 8B EC 8B 81 ? ? ? ? 8B D0"));

	ctx->m_globals->m_current_time = m_old_current_time;
	ctx->m_globals->m_frame_time = m_old_frame_time;
	ctx->m_globals->m_tick_count = m_old_tick_count;

	ctx->m_local_player->m_current_command() = nullptr;
	*ctx->m_random_seed = -1;
	pred_player = NULL;
	ctx->m_running_prediction = false;
}

int c_engine_prediction::get_tick_base( c_base_player* local_player, c_user_cmd* cmd ) {
	static int tick = 0;
	static c_user_cmd* last_cmd = nullptr;

	if ( cmd ) {
		if ( !last_cmd || last_cmd->m_has_been_predicted )
			tick = local_player->m_tick_base( );

		else tick++;
		last_cmd = cmd;
	}

	return tick;
}