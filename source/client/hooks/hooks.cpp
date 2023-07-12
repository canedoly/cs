#include "hooks.h"
#include "../features/automations/automations.h"
#include "../features/seed_prediction/seed_prediction.h"
#include "../features/crithack/crithack.h"
#include "../features/engine_prediction/engine_prediction.h"
#include "../features/esp/esp.h"
#include "../features/hitscan/hitscan.h"
#include "../features/misc/misc.h"
#include "../features/projectile_aim/projectile_aim.h"
#include "../features/menu/menu.h"
#include "../features/visuals/visuals.h"
#include "../features/backtrack/backtrack.h"
#include "../features/melee/melee.h"
#include "../features/models/models.h"
#include "../features/cheat_detection/cheat_detection.h"
#include "../features/outlines/outlines.h"

void __fastcall hooks::add_to_crit_bucket::function(c_base_combat_weapon* this_, void* edx, float damage) {
	if (this_ == ctx->m_local_weapon && !crithack->m_is_going_through_crit_cmds)
		if (ctx->finished_last_shot) //easy fix for non-melee.
			return original_function(this_, edx, damage);
}

void hooks::add_to_crit_bucket::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC A1 ? ? ? ? F3 0F 10 81 ? ? ? ? F3 0F 10 48 ? 0F 2F C8 76 1D F3 0F 58 45 ? 0F 2F C8 F3 0F 11 81 ? ? ? ? 77 03 0F 28 C1 F3 0F 11 81 ? ? ? ?");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::anim_state_update::function(void* ecx, void* edx, float yaw, float pitch) {
	const auto& anim_state = reinterpret_cast<c_tf_player_anim_state*>(ecx);

	if (!anim_state)
		return original_function(ecx, edx, yaw, pitch);

	const auto& player = anim_state->get_base_player();

	if (!player)
		return original_function(ecx, edx, yaw, pitch);

	if (ctx->m_update_anims)
		return original_function(ecx, edx, yaw, pitch);
}

void hooks::anim_state_update::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 81 EC ? ? ? ? 53 57 8B F9 8B 9F ? ? ? ? 89 5D E0 85 DB 0F 84");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::build_transformations::function(void* ecx, void* edx, void* hdr, vector* pos, void* q, matrix_3x4& camera_transform, int bone_mask, void* bone_computed) {
	static auto addr1 = util::find_signature< uintptr_t >("client.dll", "8B 46 ? 83 C4 ? F6 04 B8 ? 0F 84");
	static auto addr2 = util::find_signature< uintptr_t >("client.dll", "8B 46 ? 8B 14 B8 83 FA ? 75 ? 8B 83 ? ? ? ? 03 45 ? 50 8D 85");
	if (reinterpret_cast<uintptr_t>(_ReturnAddress()) == addr1)
		*reinterpret_cast<uintptr_t*>(_AddressOfReturnAddress()) = addr2;

	original_function(ecx, edx, hdr, pos, q, camera_transform, bone_mask, bone_computed);
}

void hooks::build_transformations::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 81 EC ? ? ? ? 53 8B D9 8B 0D ? ? ? ? 56 33 F6 89 75 ? 89 75 ? 8B 41 ? 89 75 ? 89 75 ? 57 85 C0");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::calc_is_attack_critical::function(c_base_combat_weapon* this_, void* edx) {
	if (!ctx->m_local_player || !ctx->m_local_weapon || ctx->m_local_weapon != this_)
		return original_function(this_, edx);

	original_function(this_, edx);

}

void hooks::calc_is_attack_critical::init() {
	auto target = util::find_signature< fn >("client.dll", "53 57 6A ? 68 ? ? ? ? 68 ? ? ? ? 6A ? 8B F9 E8 ? ? ? ? 50 E8 ? ? ? ? 8B D8 83 C4 ? 85 DB 0F 84");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::calc_viewmodel_view::function(void* ecx, void* edx, c_base_player* owner, const vector& eyes, vector& angles) {
	auto weapon = owner->get_active_weapon();

	if (ctx->m_local_player && ctx->m_local_player->m_force_taunt_cam())
		return;

	if (weapon) {
		if (config->m_visuals.m_visualize_aimbot && !ctx->m_aimbot_angles.is_zero() && ctx->m_aimbot_delay-- > 0) {
			angles = ctx->m_aimbot_angles;
		}

		auto forward = vector(), right = vector(), up = vector();
		math::angle_vectors(angles, &forward, &right, &up);

		if (weapon->get_weapon_id() == TF_WEAPON_COMPOUND_BOW)
			right *= -1.0f;

		auto new_eye_pos = eyes + (
			(right * config->m_visuals.m_viewmodel_x) +
			(forward * config->m_visuals.m_viewmodel_y) +
			(up * config->m_visuals.m_viewmodel_z)
			);

		angles.m_z += config->m_visuals.m_viewmodel_roll;
		return original_function(ecx, edx, owner, new_eye_pos, angles);
	}

	original_function(ecx, edx, owner, eyes, angles);
}

void hooks::calc_viewmodel_view::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 83 EC 70 8B 55 0C 53 8B 5D 08 89 4D FC 8B 02 89 45 E8 8B 42 04 89 45 EC 8B 42 08 89 45 F0 56 57");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

static std::string local({ '\x7', '9', '5', '3', '2', 'F', 'F' });
static std::string friends({ '\x7', '0', '0', 'C', '8', 'F', 'F' });
static std::string cheater({ '\x7', 'F', 'F', '3', '2', '3', '2' });
void __cdecl hooks::chat_printf::function(void* ecx, int index, int filter, const char* fmt, ...) {
	va_list vlist;
	char buffer[4096];
	va_start(vlist, fmt);
	vsnprintf_s(buffer, sizeof(buffer), fmt, vlist);
	va_end(vlist);

	if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n')
	{
		buffer[strlen(buffer) - 1] = 0;
	}
	char* buf = buffer;
	while (*buf && (*buf == '\n' || *buf == '\r' || *buf == '\x1A'))
	{
		buf++;
	}
	if (!*buf) { return; }

	std::string msg = buf, name = {};

	player_info_t info{};
	if (!ctx->m_engine_client->get_player_info(index, &info))
	{
		return original_function(ecx, index, filter, "%s", msg.c_str());
	}

	name = info.m_name;
	if (msg.find(name) == std::string::npos)
	{
		return original_function(ecx, index, filter, "%s", msg.c_str());
	}

	if (index) {
		std::string color, tag;
		bool set = false;

		if (index == ctx->m_engine_client->get_local_player()) {
			color = local;
			tag = "|Local|";
			set = true;
		}

		else if (ctx->m_entity_list->get_client_entity(index) &&
			ctx->m_entity_list->get_client_entity(index)->as<c_base_player>()->is_player_on_friend_list()) {
			color = friends;
			tag = "|Friend|";
			set = true;
		}

		if (set) {
			msg = color + tag + " \x3" + msg;
			if (auto offset = msg.find(name)) {
				msg = msg.replace(offset + name.length(), 0, "\x1");
			}
		}
	}

	original_function(ecx, index, filter, "%s", msg.c_str());
}

void hooks::chat_printf::init() {
	auto target = util::get_virtual< fn >(ctx->m_client_mode->m_chat_element, 19u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::check_for_sequence_change::function(void* ecx, void* edx, void* hdr, int current, bool force_new, bool interpolate) {
	return original_function(ecx, edx, hdr, current, force_new, false);
}

void hooks::check_for_sequence_change::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 53 8B 5D 08 57 8B F9 85 DB 0F 84 ? ? ? ? 83 7F 0C 00 75 05 E8 ? ? ? ? 6B 4F 0C 2C 0F 57 C0 56 8B 37 83 C6 D4 03 F1 F3 0F 10 4E ? 0F 2E C8 9F F6 C4 44 7B 62 8B 45 0C");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

bool __cdecl hooks::check_simple_material::function(i_material* material) {
	return true;
}

void hooks::check_simple_material::init() {
	auto target = util::find_signature< fn >("engine.dll", "55 8B EC 56 8B 75 08 85 F6 75 05 32 C0 5E 5D C3 8B 06 8B CE 57 FF 90 ? ? ? ? 6A 10 8B F8 68 ? ? ? ? 57 E8 ? ? ? ? 83 C4");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __cdecl hooks::cl_check_for_pure_server_whitelist::function(int files) {
	return;
}

void hooks::cl_check_for_pure_server_whitelist::init() {
	auto target = util::find_signature< fn >("engine.dll", "55 8B EC 83 3D ? ? ? ? ? 7E 5E 80 3D ? ? ? ? ? 75");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

/*

	Ideally we would like to rebuild PhysicsSimulate from C_BasePlayer and pair it with this
	We would need to bypass this check
	if (m_nSimulationTick == gpGlobals->tickcount)
		return;

	to get the game to simulate our player while shifting ticks

*/

void __cdecl hooks::cl_move::function(float accumulated_extra_samples, bool final_tick) {
	ctx->m_cl_move_call = original_function;
	if (config->m_misc.m_reduce_input_delay)
		misc->fix_input_delay(final_tick);

	if (!ctx->m_local_player)
		return original_function(accumulated_extra_samples, final_tick);

	if (!ctx->m_local_player->is_alive() || !ctx->m_local_weapon)
		return original_function(accumulated_extra_samples, final_tick);

	static bool allowed_to_charge = false;
	if (config->m_exploits.m_doubletap_recharge_key.is_held())
		allowed_to_charge = true;

	auto allowed_ticks = config->m_misc.m_reduce_input_delay ? 20 : (ctx->m_local_weapon->m_item_definition_index() == Scout_m_ForceANature ||
		ctx->m_local_weapon->m_item_definition_index() == Scout_m_FestiveForceANature) ? 21 : 22;

	if (allowed_to_charge)
		allowed_to_charge = ctx->m_charged_ticks < allowed_ticks;

	if (allowed_to_charge)
	{
		if (ctx->m_charged_ticks < allowed_ticks)
		{
			ctx->m_is_recharging = true;
			ctx->m_shifted_ticks--;
			ctx->m_charged_ticks++;
			ctx->m_wait_ticks = 24;
			return;
		}
	}

	ctx->m_is_recharging = false;

	original_function(accumulated_extra_samples, final_tick);
	misc->handle_warp(accumulated_extra_samples, final_tick, original_function);

	if (ctx->m_warping)
		return;

	if (ctx->m_wait_ticks > 0)
	{
		ctx->m_wait_ticks--;
		return;
	}

	if (ctx->m_shift && ctx->m_charged_ticks > 0 && config->m_exploits.m_doubletap)
	{
		ctx->m_running_shift = true;
		while (ctx->m_charged_ticks > 0)
		{
			original_function(accumulated_extra_samples, final_tick);
			ctx->m_charged_ticks--;
			ctx->m_shifted_ticks++;
		}
		ctx->m_running_shift = false;
		ctx->m_shift = false;
	}
}

void hooks::cl_move::init() {
	auto target = util::find_signature< fn >("engine.dll", "55 8B EC 83 EC ? 83 3D ? ? ? ? 02 0F 8C ? ? 00 00 E8 ? ? ? 00 84 C0");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __cdecl hooks::cl_read_packets::function(bool final_tick) {
	if (!config->m_misc.m_reduce_input_delay) {
		return original_function(final_tick);
	}

	if (misc->should_read_packets())
		original_function(final_tick);
}

void hooks::cl_read_packets::init() {
	auto target = util::find_signature< fn >("engine.dll", "55 8B EC 83 EC 34 8B 0D ? ? ? ?");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::cl_send_move::function(void* ecx, void* edx) {
	if (!ctx->m_client_state || !ctx->m_client_state->m_net_channel)
		return original_function(ecx, edx);

	byte data[4000];

	const int choked = ctx->m_client_state->m_net_channel->m_choked_packets;
	//ctx->m_cvar->console_color_printf( { 0, 255, 255, 255 }, "before change: %i\n", choked );
	const int next_command_num = ctx->m_client_state->m_last_out_going_command + choked + 1;

	clc_move move_message;
	move_message.m_data_out.start_writing(data, sizeof(data));

	move_message.m_new_commands = 1 + choked;
	move_message.m_new_commands = std::clamp(move_message.m_new_commands, 0, MAX_NEW_COMMANDS);

	const int extra_commands = choked + 1 - move_message.m_new_commands;
	const int backup_commands = std::max(2, extra_commands);
	move_message.m_backup_commands = std::clamp(backup_commands, 0, MAX_BACKUP_COMMANDS);

	const int num_commands = move_message.m_new_commands + move_message.m_backup_commands;

	auto from = -1;
	auto ok = true;

	for (auto to = next_command_num - num_commands + 1; to <= next_command_num; to++) {
		const bool is_new_command = to >= next_command_num - move_message.m_new_commands + 1;
		ok = ok && ctx->m_client->write_usercmd_delta_to_buffer(&move_message.m_data_out, from, to, is_new_command);
		from = to;
	}

	if (ok) {
		if (extra_commands > 0)
			ctx->m_client_state->m_net_channel->m_choked_packets -= extra_commands;

		ctx->m_current_move = move_message;

		typedef bool(__thiscall* send_net_message_fn)(void*, i_net_message*, bool, bool);
		util::get_virtual< send_net_message_fn >(ctx->m_client_state->m_net_channel, 37u)(ctx->m_client_state->m_net_channel, &move_message, false, false);
	}
}

void hooks::cl_send_move::init() {
	auto target = util::find_signature< fn >("engine.dll", "55 8B EC 81 EC ? ? ? ? A1 ? ? ? ? 8D");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::client_think::function(void* ecx, void* edx) {
	const auto ent = reinterpret_cast<c_base_entity*>(reinterpret_cast<uintptr_t>(ecx) - 12);
	if (!ent)
		return original_function(ecx, edx);

	const auto owner = ctx->m_entity_list->get_client_entity_from_handle(ent->m_owner_entity())->as< c_base_entity >();
	if (!owner)
		return;

	ctx->m_sniper_dot_is_local = (owner == ctx->m_local_player);
	original_function(ecx, edx);

	auto m_laser_beam_effect = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(ecx) + 1360);

	if (m_laser_beam_effect && !ctx->m_sniper_dot_is_local) {
		static auto set_control_point = util::find_signature< void(__thiscall*)(void*, int, const vector&) >("client.dll", "55 8B EC 53 8B 5D ? 57 8B F9 83 BF");
		set_control_point(m_laser_beam_effect, 2, owner->m_team_num() == TF_TEAM_RED ? vector(215.0f, 60.0f, 60.0f) : vector(0.0f, 200.0f, 255.0f));
	}
}

void hooks::client_think::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 83 EC ? 53 56 8B F1 8B 0D ? ? ? ? 57 E8");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

bool __fastcall hooks::create_move::function(void* ecx, void* edx, float input_sample_time, c_user_cmd* cmd) {
	if (!cmd || !cmd->m_command_number)
		return original_function(ecx, edx, input_sample_time, cmd);

	if (original_function(ecx, edx, input_sample_time, cmd))
		ctx->m_engine_client->set_view_angles(cmd->m_view_angles);

	uint32_t _bp; __asm mov _bp, ebp;
	bool* send_packet = reinterpret_cast<bool*>(***reinterpret_cast<uint32_t***>(_bp) - 0x1);
	ctx->m_send_packet = send_packet;
	ctx->m_current_user_cmd = cmd;
	//ctx->m_update_anims = true;

	auto old_angles = cmd->m_view_angles;

	if (config->m_misc.m_reduce_input_delay)
		ctx->m_prediction->update(ctx->m_client_state->m_delta_tick,
			ctx->m_client_state->m_delta_tick > 0,
			ctx->m_client_state->m_last_command_ack,
			ctx->m_client_state->m_last_out_going_command + ctx->m_client_state->m_choked_commands);

	crithack->run(cmd);
	misc->run(cmd);

	if (ctx->m_running_shift || ctx->m_shift)
		*send_packet = ctx->m_charged_ticks == 1;

	if (!ctx->m_local_player->is_taunting())
	{
		engine_prediction->start(cmd); {
			hitscan->run(cmd);
			projectile_aim->run(cmd);
			melee->run(cmd);
			misc->fake_lag(cmd, config->m_hvh.m_max_ticks, send_packet);
			misc->anti_aim(cmd, send_packet);
			automations->run(cmd);
			misc->anti_backstab(cmd);
			misc->auto_warp(cmd);
			misc->shoot_sticky_at_charge(cmd);
			tf2::fix_movement(cmd, old_angles);
			misc->velocity_handler(cmd);
		} engine_prediction->end(cmd);
	}
	misc->handle_dt(cmd, send_packet);

	if (config->m_misc.m_scout_jump)
		misc->scout_jump(cmd);

	if (ctx->m_warping)
		cmd->m_buttons &= ~IN_ATTACK;

	if (!ctx->m_shift && !ctx->m_running_shift)
		*send_packet = *ctx->m_send_packet; // idk

	if (*send_packet)
		ctx->m_real_angles = cmd->m_view_angles;
	else ctx->m_fake_angles = cmd->m_view_angles;

	if (ctx->m_local_weapon) {
		if (ctx->m_local_weapon->can_shoot())
			ctx->finished_last_shot = true;

		else
			ctx->finished_last_shot = false;
	}

	ctx->was_in_attack = cmd->m_buttons & IN_ATTACK;
	ctx->m_actual_angles = cmd->m_view_angles;

	return false;
}

void hooks::create_move::init() {
	auto target = util::get_virtual< fn >(ctx->m_client_mode, 21u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::create_tf_gibs::function(c_tf_ragdoll* this_, void* ecx, bool destroy_ragdoll, bool current_position) {
	return original_function(this_, ecx, destroy_ragdoll, current_position);
}

void hooks::create_tf_gibs::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 83 EC ? 56 57 8B F9 8B 87 ? ? ? ? 83 F8 ? 0F 84 ? ? ? ? 8B 0D");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::create_tf_ragdoll::function(c_tf_ragdoll* this_, void* edx) {
	auto local_player = ctx->m_local_player;

	if (!config->m_visuals.m_ragdolls_enabled || !local_player || (config->m_visuals.m_ragdolls_enemy_only && this_->m_team() == local_player->m_team_num()))
		return original_function(this_, edx);

	// set the effects.
	this_->m_gib() = false;
	this_->m_burning() = config->m_visuals.m_ragdoll_burning;
	this_->m_electrocuted() = config->m_visuals.m_ragdoll_electrocuted;
	this_->m_dissolving() = config->m_visuals.m_ragdoll_dissolving;
	this_->m_feign_death() = false;
	this_->m_cloaked() = false;
	this_->m_become_ash() = config->m_visuals.m_ragdoll_become_ash;
	this_->m_gold_ragdoll() = config->m_visuals.m_ragdoll_type == 1;
	this_->m_ice_ragdoll() = config->m_visuals.m_ragdoll_type == 2;

	original_function(this_, edx);
}

void hooks::create_tf_ragdoll::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC B8 ? ? ? ? E8 ? ? ? ? 53 56 57 8B F9 8B 8F ? ? ? ? 85 C9 0F 85");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

static int anti_auto_balance = 0;
static const char* previous_server = { };
bool __fastcall hooks::dispatch_user_message::function(void* ecx, void* edx, int msg_type, bf_read& msg_data) {

	auto data = reinterpret_cast<const char*>(msg_data.m_pData);
	msg_data.SetAssertOnOverflow(false);

	if (data) {
		switch (msg_type) {
		case TextMsg: {
			if (msg_data.GetNumBitsLeft() > 35) {
				//ctx->m_cvar->console_color_printf( { 0, 255, 255, 255 }, "%s\n", data );
				if (strstr(reinterpret_cast<char*>(msg_data.m_pData), "#TF_Autobalance_TeamChangePending")) {
					if (ctx->m_engine_client->get_net_channel_info() && ctx->m_engine_client->get_net_channel_info()->get_address() != previous_server) {
						previous_server = ctx->m_engine_client->get_net_channel_info()->get_address();
						anti_auto_balance = 0;
					}

					if (anti_auto_balance < 2) {
						ctx->m_engine_client->client_cmd_unrestricted("retry");
					}

					anti_auto_balance++;
				}
			}

			break;
		}
		case VGUIMenu: {
			if (config->m_misc.m_skip_welcome) {
				if (strcmp(reinterpret_cast<char*>(msg_data.m_pData), "info") == 0) {
					ctx->m_engine_client->client_cmd_unrestricted("closedwelcomemenu");
					return true;
				}
			}

			break;
		}

		case VoteStart:
		case VoteFailed:
		case VotePass: {
			visuals->vote_revealer_register_message(msg_type, msg_data);
			break;
		}
		}
	}

	msg_data.Seek(0);
	return original_function(ecx, edx, msg_type, msg_data);
}

void hooks::dispatch_user_message::init() {
	auto target = util::get_virtual< fn >(ctx->m_client, 36u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

bool __fastcall hooks::do_post_screen_space_effects::function(void* ecx, void* edx, const c_view_setup* view) {
	models->render();
	outlines->render();
	visuals->trace_projectile_path();
	return original_function(ecx, edx, view);
}

void hooks::do_post_screen_space_effects::init() {
	auto target = util::get_virtual< fn >(ctx->m_client_mode, 39u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::draw_model_execute::function(void* ecx, void* edx, const draw_model_state_t& state, const model_render_info_t& info, matrix_3x4* matrix) {
	if (!matrix || !info.model || !config->m_models.m_enabled || !models->m_flat_material)
		return original_function(ecx, edx, state, info, matrix);

	c_base_player* entity = ctx->m_entity_list->get_client_entity(info.ent_index)->as<c_base_player>();

	static auto mat = models->m_flat_material;

	if (config->m_exploits.m_backtrack) {
		if (entity && entity->is_alive() && !models->is_rendering() && !outlines->is_rendering()) {
			if (entity->is_player() && entity->is_enemy()) {
				if (!backtrack->m_records[info.ent_index].empty() && config->m_models.m_backtrack_models) {
					if (config->m_models.m_backtrack_last_only) {
						if (entity->m_origin().dist_to(backtrack->best_last_tick(info.ent_index).m_origin) > 0.1f) {
							ctx->m_render_view->set_blend(0.4f);
							ctx->m_model_renderer->forced_material_override(mat);
							original_function(ecx, edx, state, info, backtrack->best_last_tick(info.ent_index).m_bones);
							ctx->m_model_renderer->forced_material_override(nullptr);
							ctx->m_render_view->set_blend(1.0f);
						}
					}

					else {
						for (size_t i = 0; i < backtrack->m_records[info.ent_index].size(); i++) {
							auto& record = backtrack->m_records[info.ent_index][i];
							if (!backtrack->is_tick_valid(record.m_simulation_time))
								continue;

							if (entity->m_origin().dist_to(record.m_origin) <= 0.1f)
								continue;

							//ctx->m_debug_overlay->add_text_overlay(record.m_world_space_center, TICK_INTERVAL * 2, "tick: %i", i);

							ctx->m_render_view->set_blend(0.4f);
							ctx->m_model_renderer->forced_material_override(mat);
							original_function(ecx, edx, state, info, record.m_bones);
							ctx->m_model_renderer->forced_material_override(nullptr);
							ctx->m_render_view->set_blend(1.0f);
						}
					}
				}
			}
		}
	}

	if ((models->is_entity_rendered(entity) || outlines->is_entity_rendered(entity)) && !outlines->m_drawing_glow)
		return;

	original_function(ctx->m_model_renderer, edx, state, info, matrix);
}

void hooks::draw_model_execute::init() {
	auto target = util::get_virtual< fn >(ctx->m_model_renderer, 19u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::draw_static_props::function(void* ecx, void* edx, void** props, int count, bool shadow_depth, bool draw_vcollide_wireframe) {
	ctx->m_drawing_static_props = true;
	original_function(ecx, edx, props, count, shadow_depth, draw_vcollide_wireframe);
	ctx->m_drawing_static_props = false;
}

void hooks::draw_static_props::init() {
	auto target = util::find_signature< fn >("engine.dll", "55 8B EC 83 EC 10 8B 15 ? ? ? ? 53 56 57 33 F6 89 4D FC 33 FF 89 75 F0 89 7D F4 8B 42 08");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::fire_bullet::function(c_base_player* this_, void* edx, c_base_combat_weapon* weapon, fire_bullets_info_t& info, bool do_effects, int damage_type, int custom_damage_type) {
	if (this_ == ctx->m_local_player && weapon == ctx->m_local_weapon) {
		if (ctx->m_local_weapon->get_weapon_id() != TF_WEAPON_MINIGUN)
			info.m_tracer_freq = 1;

		if (config->m_visuals.m_bullet_tracers && damage_type & DMG_CRITICAL)
			damage_type &= ~(DMG_CRITICAL);
	}

	return original_function(this_, edx, weapon, info, do_effects, damage_type, custom_damage_type);
}

void hooks::fire_bullet::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 81 EC ? ? ? ? 53 56 57 8B F9 8B 5D");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::forced_material_override::function(void* ecx, void* edx, i_material* mat, int override_type) {
	if ((models->is_rendering() && !models->is_used_material(mat)) || (outlines->is_rendering() && !outlines->is_used_material(mat))) { return; }

	original_function(ecx, edx, mat, override_type);
}

void hooks::forced_material_override::init() {
	auto target = util::get_virtual< fn >(ctx->m_model_renderer, 1u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::frame_stage_notify::function(void* ecx, void* edx, client_frame_stage_t stage) {
	auto old_punch = vector();
	backtrack->update_sequences();

	if (stage == client_frame_stage_t::FRAME_RENDER_START) {
		if (ctx->m_globals->m_absolute_frame_time != 0.f)
			ctx->m_fps = 1.f / ctx->m_globals->m_absolute_frame_time;

		if (ctx->m_local_player) {
			if (ctx->m_local_player->is_alive()) {
				static auto cvar = ctx->m_cvar->find_var("tf_avoidteammates_pushaway");
				static auto cvar2 = ctx->m_cvar->find_var("viewmodel_fov");
				if (cvar)
					cvar->set_value(!config->m_misc.m_avoid_push);

				if (cvar2)
				{
					static int old_cvar2 = cvar2->get_int();
					if (config->m_visuals.m_viewmodel_fov <= 0)
						cvar2->set_value(old_cvar2);
					else
						cvar2->set_value(config->m_visuals.m_viewmodel_fov);
				}

				misc->fix_local_animations();
				misc->handle_weapon_sway();

				ctx->m_punch_angle = ctx->m_local_player->m_punch_angle();
				old_punch = ctx->m_local_player->m_punch_angle();

				if (config->m_visuals.m_remove_recoil)
					ctx->m_local_player->m_punch_angle().set();

			}
		}

		backtrack->save_lag_comp();
	}

	else if (stage == client_frame_stage_t::FRAME_RENDER_END) {
		if (ctx->m_local_player) {
			if (ctx->m_local_player->is_alive()) {
				if (config->m_visuals.m_remove_recoil)
					ctx->m_local_player->m_punch_angle() = old_punch;
			}
		}
	}

	original_function(ecx, edx, stage);

	if (stage == client_frame_stage_t::FRAME_NET_UPDATE_START) {
		entity_cache->reset();
	}

	else if (stage == client_frame_stage_t::FRAME_NET_UPDATE_END) {
		entity_cache->fill();
		/*if ( ctx->m_local_player ) {
			auto diff = std::clamp( TIME_TO_TICKS( ctx->m_local_player->m_simulation_time( ) - ctx->m_local_player->m_old_simulation_time( ) ), 0, 22 );
			for ( int i = 0; i < diff; i++ ) {
				ctx->m_update_anims = true;
				ctx->m_local_player->update_client_side_animations( );
				ctx->m_update_anims = false;
			}
		}*/

		for (const auto& player : ctx->players) {
			if (!player)
				continue;

			auto diff = std::clamp(TIME_TO_TICKS(player->m_simulation_time() - player->m_old_simulation_time()), 0, 22);
			for (int i = 0; i < diff; i++) {
				ctx->m_update_anims = true;
				player->update_client_side_animations();
				ctx->m_update_anims = false;
			}
		}

		movement_sim->fill_directions();
		cheat_detection->scan_players();
	}
}

void hooks::frame_stage_notify::init() {
	auto target = util::get_virtual< fn >(ctx->m_client, 35u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __cdecl hooks::fx_fire_bullets::function(c_base_combat_weapon* pWpn, int iPlayer, const vector& vecOrigin, const vector& vecAngles, int iWeapon, int iMode, int iSeed, float flSpread, float flDamage /* = -1.0f */, bool bCritical /* = false*/) {
#ifdef JW_RELEASE_BUILD
	return original_function(pWpn, iPlayer, vecOrigin, vecAngles, iWeapon, iMode, iSeed, flSpread, flDamage, bCritical);
#endif

	if (!pWpn || pWpn != ctx->m_local_weapon || !config->m_seed_pred.m_enabled
		|| !(ctx->m_local_player->m_player_class() == CLASS_SCOUT && ctx->m_local_weapon->get_slot() == SLOT_SECONDARY
			|| ctx->m_local_player->m_player_class() == CLASS_HEAVY && ctx->m_local_weapon->get_slot() == SLOT_PRIMARY
			|| ctx->m_local_player->m_player_class() == CLASS_SNIPER && ctx->m_local_weapon->get_slot() == SLOT_SECONDARY
			|| ctx->m_local_player->m_player_class() == CLASS_ENGINEER && ctx->m_local_weapon->get_slot() == SLOT_SECONDARY
			|| ctx->m_local_player->m_player_class() == CLASS_SPY && ctx->m_local_weapon->get_slot() == SLOT_PRIMARY
			))
		return original_function(pWpn, iPlayer, vecOrigin, vecAngles, iWeapon, iMode, iSeed, flSpread, flDamage, bCritical);

	//replicate da nospread effect
	//use actual angles from create_move, as they later get changed based on the spread in the write_user_cmd hook we have, to replicate the nospread effect
	return original_function(pWpn, iPlayer, vecOrigin, pWpn->can_shoot() ? ctx->m_actual_angles : vecAngles, iWeapon, iMode, iSeed, 0.0f, flDamage, bCritical);
}

void hooks::fx_fire_bullets::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 81 EC ? ? ? ? 53 8B 5D 18 56 53 E8 ? ? ? ? 8B F0 83 C4 04 85 F6 75 17 53 68");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

const char* __fastcall hooks::get_shoot_sound::function(void* ecx, void* edx, int index) {
	auto weapon = reinterpret_cast<c_base_combat_weapon*>(ecx);

	if (!config->m_visuals.m_mvm_giant_sounds || weapon != ctx->m_local_weapon)
		return original_function(ecx, edx, index);

	auto old_team = weapon->m_team_num();
	auto old_item = weapon->m_item_definition_index();
	weapon->m_team_num() = 4;
	if (weapon->get_weapon_id() == TF_WEAPON_ROCKETLAUNCHER)
		weapon->m_item_definition_index() = Soldier_m_RocketLauncher;

	auto original = original_function(ecx, edx, index);
	weapon->m_team_num() = old_team;
	weapon->m_item_definition_index() = old_item;

	const auto name = fnv::hash(original);

	static auto constexpr hashed_flame_thrower_fire = fnv::hash("Weapon_FlameThrower.Fire");
	static auto constexpr hashed_flame_thrower_fire_loop = fnv::hash("Weapon_FlameThrower.FireLoop");
	static auto constexpr hashed_grenade_launcher_single = fnv::hash("Weapon_GrenadeLauncher.Single");

	if (name == hashed_flame_thrower_fire)
		return "MVM.GiantPyro_FlameStart";

	if (name == hashed_flame_thrower_fire_loop)
		return "MVM.GiantPyro_FlameLoop";

	if (name == hashed_grenade_launcher_single || weapon->get_weapon_id() == TF_WEAPON_GRENADELAUNCHER)
		return "MVM.GiantDemoman_Grenadeshoot";

	return original;
}

void hooks::get_shoot_sound::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 53 8B 5D 08 57 8B F9 80 BF ? ? ? ? ?");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

const char* __fastcall hooks::get_tracer_type::function(void* ecx, void* edx) {
	auto weapon = reinterpret_cast<c_base_combat_weapon*>(ecx);

	if (config->m_visuals.m_bullet_tracers == 0 || weapon != ctx->m_local_weapon)
		return original_function(ecx, edx);

	switch (config->m_visuals.m_bullet_tracers)
	{
	case 1: { return (weapon->m_team_num() == TF_TEAM_RED) ? "bullet_tracer_raygun_red" : "bullet_tracer_raygun_blue"; }
	case 2: { return (weapon->m_team_num() == TF_TEAM_RED) ? "dxhr_sniper_rail_red" : "dxhr_sniper_rail_blue"; }
	case 3: { return "dxhr_sniper_rail"; }
	case 4: { return "merasmus_zap"; }
	case 5: { return "merasmus_zap_beam02"; }
	case 6: { return "merasmus_zap_beam01"; }
	}

	return original_function(ecx, edx);
}

void hooks::get_tracer_type::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 51 53 56 57 8B F9 E8 ? ? ? ? 6A");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

c_user_cmd* __fastcall hooks::get_user_cmd::function(void* ecx, void* edx, int sequence_number) {
	if (c_user_cmd* cmd_list = *reinterpret_cast<c_user_cmd**>(reinterpret_cast<uint32_t>(ecx) + 0x0fc)) {
		if (c_user_cmd* cmd = &cmd_list[sequence_number % 90])
			return cmd;
	}

	return original_function(ecx, edx, sequence_number);
}

void hooks::get_user_cmd::init() {
	auto target = util::get_virtual< fn >(ctx->m_input, 8u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

bool __fastcall hooks::in_cond::function(void* ecx, void* edx, e_tf_cond id) {
	const auto ret_addr = reinterpret_cast<uintptr_t>(_ReturnAddress());
	static auto player_draw = util::find_signature< uintptr_t, 5u >("client.dll", "E8 ? ? ? ? 84 C0 75 C5");
	static auto wearable_draw = util::find_signature< uintptr_t, 5u >("client.dll", "E8 ? ? ? ? 84 C0 75 E1 6A 03");
	static auto hud_scope_draw = util::find_signature< uintptr_t >("client.dll", "84 C0 74 ? 8B CE E8 ? ? ? ? 85 C0 74 ? 8B CE E8 ? ? ? ? 8B C8 8B 10 FF 92 ? ? ? ? 83 F8 ? 0F 94");

	if (id == TF_COND_ZOOMED) {
		if (ret_addr == player_draw || ret_addr == wearable_draw || (config->m_visuals.m_remove_scope && ret_addr == hud_scope_draw))
			return false;
	}

	return original_function(ecx, edx, id);
}

void hooks::in_cond::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 83 EC 08 56 57 8B 7D 08 8B F1 83 FF 20");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

bool __fastcall hooks::interpolate::function(c_base_entity* ecx, void* edx, float current_time) {
	if (!ecx->is_player() || !ctx->m_local_player || !ctx->m_local_player->is_alive())
		return original_function(ecx, edx, current_time);

	return true;
}

void hooks::interpolate::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 83 EC 2C 56 8B F1 83 BE ? ? ? ? ? 0F 85 ? ? ? ? F3 0F 10 86 ? ? ? ?");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __cdecl hooks::interpolate_server_entities::function() {
	if (ctx->m_is_recharging)
		return;

	original_function();
}

void hooks::interpolate_server_entities::init() {
	static auto target = util::find_signature< fn >("client.dll", "55 8B EC 83 EC ? 8B 0D ? ? ? ? 53 33 DB 89 5D ? 89 5D ? 8B 41 ? 89 5D ? 89 5D ? 85 C0 74 ? 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 53 53 53 53 8D 4D ? 51 50 8B 40 ? FF D0 8B 45 ? 83 C4 ? 8B 0D ? ? ? ? 89 45 ? 8B 45 ? 89 45 ? 8B 59 ? 8B 0D ? ? ? ? 89 5D ? FF 15 ? ? ? ? 88 45 ? 84 C0 74 ? 8B 0D ? ? ? ? 6A ? 6A ? 68 ? ? ? ? 6A ? 68 ? ? ? ? FF 15 ? ? ? ? A1 ? ? ? ? 8B 0D");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

bool __fastcall hooks::is_pve_mode_active::function(void* ecx, void* edx) {
	static auto addr1 = util::find_signature< uintptr_t >("client.dll", "84 C0 0F 84 ? ? ? ? 8B 46 ? 8D 4E ? FF 90");
	static auto addr2 = util::find_signature< uintptr_t >("client.dll", "8B 8E ? ? ? ? 85 C9 0F 84 ? ? ? ? BA ? ? ? ? 83 F9 ? 74 ? 0F B7 D1 8B 3D ? ? ? ? C1 E2 ? 83 C7 ? 03 FA 0F 84 ? ? ? ? C1 E9 ? 39 4F ? 0F 85 ? ? ? ? 8B 3F 85 FF 0F 84 ? ? ? ? 8B 07 8B CF 8B 80 ? ? ? ? FF D0 84 C0 0F 84 ? ? ? ? 83 BE");
	if (reinterpret_cast<uintptr_t>(_ReturnAddress()) == addr1 && !ctx->m_sniper_dot_is_local && config->m_visuals.m_sniper_sightlines)
		*static_cast<uintptr_t*>(_AddressOfReturnAddress()) = addr2;

	return original_function(ecx, edx);
}

void hooks::is_pve_mode_active::init() {
	static auto target = util::find_signature< fn >("client.dll", "80 B9 ? ? ? ? ? 0F 95 C0 C3 CC CC CC CC CC 8A 81");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::level_init::function(void* ecx, void* edx) {
	original_function(ecx, edx);


	cheat_detection->reset_suspects();
	models->init_materials();
	outlines->init_materials();
}

void hooks::level_init::init() {
	auto target = util::get_virtual< fn >(ctx->m_client, 6u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::level_shutdown::function(void* ecx, void* edx) {
	original_function(ecx, edx);

	ctx->m_local_player = nullptr;
	ctx->m_local_weapon = nullptr;
	movement_sim->m_directions.clear();
	movement_sim->m_ground_state.clear();

	visuals->m_vote_in_progress = false;

	cheat_detection->reset_suspects();
	models->remove_materials();
	outlines->remove_materials();
}

void hooks::level_shutdown::init() {
	auto target = util::get_virtual< fn >(ctx->m_client, 7u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::lock_cursor::function(void* ecx, void* edx) {
	menu->backup_ecx = ecx;
	menu->backup_edx = edx;

	if (menu->m_open)
		return ctx->m_surface->unlock_cursor();

	original_function(ecx, edx);
}

void hooks::lock_cursor::init() {
	auto target = util::get_virtual< fn >(ctx->m_surface, 62u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::material_uncache::function(i_material* ecx, void* edx, bool preserve_vars) {
	if (ecx && ecx == models->m_flat_material)
		return;

	original_function(ecx, edx, preserve_vars);
}

void hooks::material_uncache::init() {
	static DWORD address = util::find_signature< DWORD >("materialsystem.dll", "E8 ? ? ? ? 83 7E 1C 00") + 0x1;
	auto target = reinterpret_cast<fn>(*(DWORD*)address + address + 0x4);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __cdecl hooks::notification_queue_add::function(void* notif) {
	return;
}

void hooks::notification_queue_add::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 8B 0D ? ? ? ? 56 57 8B 01 8B 40 ? FF D0 8B 75 ? 84 C0 75 ? 80 BE ? ? ? ? ? 75");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::on_remove_entity::function(void* ecx, void* edx, c_base_entity* ent, unsigned int unk) {
	if (ent)
		cheat_detection->m_suspects[ent->entindex()] = { };

	return original_function(ecx, edx, ent, unk);
}

void hooks::on_remove_entity::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 51 8B 45 0C 25 ? ? ? ? 53 8B D9 56 8D 0C C5 ? ? ? ? 03 CB 89 4D FC 57 3D ? ? ? ? 73 1B");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::on_screen_size_changed::function(void* ecx, void* edx, int old_width, int old_height) {
	original_function(ecx, edx, old_width, old_height);

	render->reload_fonts();
	ctx->m_engine_client->get_screen_size(ctx->m_screen_width, ctx->m_screen_height);
}

void hooks::on_screen_size_changed::init() {
	auto target = util::get_virtual< fn >(ctx->m_surface, 111u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::override_view::function(void* ecx, void* edx, c_view_setup* setup) {
	if (!ctx->m_local_player)
		return original_function(ecx, edx, setup);

	static auto aspect_ratio = ctx->m_cvar->find_var("r_aspectratio");
	aspect_ratio->set_value(config->m_visuals.m_aspect_ratio);

	if (ctx->m_local_player->is_alive()) {
		if ((GetAsyncKeyState(config->m_visuals.m_thirdperson_key.m_key) & 1) && util::is_window_in_focus())
			config->m_visuals.m_thirdperson = !config->m_visuals.m_thirdperson;
		ctx->m_local_player->m_force_taunt_cam() = config->m_visuals.m_thirdperson;
	}

	if (!config->m_visuals.m_remove_zoom && ctx->m_local_player->is_zoomed())
		return original_function(ecx, edx, setup);

	ctx->m_local_player->m_fov() = ctx->m_local_player->is_zoomed() ? config->m_visuals.m_zoomed_field_of_view : config->m_visuals.m_field_of_view;
	setup->m_fov = ctx->m_local_player->m_fov();

	original_function(ecx, edx, setup);
}

void hooks::override_view::init() {
	auto target = util::get_virtual< fn >(ctx->m_client_mode, 16u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::paint::function(void* ecx, void* edx, paint_mode_t mode) {
	original_function(ecx, edx, mode);

	if (mode & paint_mode_t::PAINT_UIPANELS) {
		if (!ctx->m_screen_width || !ctx->m_screen_height)
			ctx->m_engine_client->get_screen_size(ctx->m_screen_width, ctx->m_screen_height);

		tf2::update_w2s_matrix();

		ctx->m_surface->start_drawing(); {
			esp->run();
			movement_sim->draw_path();
			projectile_aim->draw_path();
			//visuals->draw_server_hitboxes( );
			visuals->visualize_stickies_path();
			visuals->draw_indicators();
			visuals->draw_camera_outline();
			menu->run();
		} ctx->m_surface->finish_drawing();
	}
}

void hooks::paint::init() {
	auto target = util::get_virtual< fn >(ctx->m_engine_vgui, 14u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::paint_traverse::function(void* ecx, void* edx, unsigned int vgui_panel, bool force_repaint, bool allow_force) {
	if (config->m_visuals.m_remove_scope)
		if (fnv::hash(ctx->m_panel->get_name(vgui_panel)) == fnv::hash("HudScope"))
			return;

	original_function(ecx, edx, vgui_panel, force_repaint, allow_force);
}

void hooks::paint_traverse::init() {
	auto target = util::get_virtual< fn >(ctx->m_panel, 41u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::physics_simulate::function(void* ecx, void* edx) {
	auto plr = reinterpret_cast<c_base_player*>(ecx);
	if (!plr || plr != ctx->m_local_player)
		return original_function(ecx, edx);


	// bypasses that check
	/*

		this is the wrong function
		hear me out
		it works

	*/
	//if (ctx->m_is_dting)
	//	*reinterpret_cast<int*>((DWORD*)ecx + 0xE0) = ctx->m_globals->m_tick_count + 1;

	original_function(ecx, edx);

	//int correct_simulation_tick = *reinterpret_cast<int*>((DWORD*)ecx + 0xE0);

	//if (ctx->m_is_dting)
	//{
		// 	m_nSimulationTick = gpGlobals->tickcount;
	//	*reinterpret_cast<int*>((DWORD*)ecx + 0xE0) = ctx->m_globals->m_tick_count; // make sure this is correct

		// repredict
		//ctx->m_prediction->run_command(ctx->m_local_player, ctx->m_local_player->m_current_command(), ctx->m_move_helper);
	//}
}

void hooks::physics_simulate::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC A1 ? ? ? ? 83 EC ? 8B 40 ? 56 8B F1 39 86");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::render_view::function(void* ecx, void* edx, const c_view_setup& view, int clear_flags, int what_to_draw) {
	original_function(ecx, edx, view, clear_flags, what_to_draw);

	if (ctx->m_local_weapon && (ctx->m_local_weapon->get_weapon_id() == TF_WEAPON_PIPEBOMBLAUNCHER || ctx->m_local_weapon->get_weapon_id() == TF_WEAPON_SYRINGEGUN_MEDIC) && config->m_projectile_aim.m_projectile_path_any_angle && config->m_visuals.m_projectile_camera && !ctx->m_projectile_camera_position.is_zero()) {
		c_view_setup projectile_camera = view;
		visuals->camera_position.m_x = ctx->m_screen_width - visuals->camera_position.m_w - 5;
		visuals->camera_position.m_y = ctx->m_screen_height / 2 - visuals->camera_position.m_h / 2;

		projectile_camera.m_x = projectile_camera.m_unscaled_x = visuals->camera_position.m_x;
		projectile_camera.m_y = projectile_camera.m_unscaled_y = visuals->camera_position.m_y;
		projectile_camera.m_width = projectile_camera.m_unscaled_width = visuals->camera_position.m_w;
		projectile_camera.m_height = projectile_camera.m_unscaled_height = visuals->camera_position.m_h;
		projectile_camera.m_aspect_ratio = float(projectile_camera.m_width) / float(projectile_camera.m_height);
		projectile_camera.m_fov = config->m_visuals.m_projectile_camera_fov;

		projectile_camera.m_origin = ctx->m_projectile_camera_position;
		vector forward{}, right{}, up{};
		math::angle_vectors(ctx->m_engine_client->get_view_angles(), &forward, &right, &up);
		vector offset = (forward * config->m_visuals.m_projectile_camera_forward) - (right * config->m_visuals.m_projectile_camera_right) - (up * config->m_visuals.m_projectile_camera_up);
		vector delta = projectile_camera.m_origin - offset;
		projectile_camera.m_origin -= offset;

		vector angle = math::calculate_angle(projectile_camera.m_origin, ctx->m_projectile_camera_position);
		projectile_camera.m_angles = { angle.m_x, angle.m_y, 0.f };

		ctx->m_drawing_projectile_camera = true;
		original_function(ecx, edx, projectile_camera, VIEW_CLEAR_COLOR | VIEW_CLEAR_DEPTH | VIEW_CLEAR_STENCIL, 0);
		ctx->m_drawing_projectile_camera = false;
	}
}

void hooks::render_view::init() {
	auto target = util::get_virtual< fn >(ctx->m_view_render, 6u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::run_command::function(void* ecx, void* edx, c_base_player* player, c_user_cmd* ucmd, i_move_helper* move_helper) {
	if (!player || player != ctx->m_local_player || !player->is_alive() || !ucmd || !move_helper || !player->get_active_weapon())
		return original_function(ecx, edx, player, ucmd, move_helper);

	if (ctx->m_running_prediction)
		return;

	original_function(ecx, edx, player, ucmd, move_helper);

}

void hooks::run_command::init() {
	auto target = util::get_virtual< fn >(ctx->m_prediction, 17u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __cdecl hooks::s_start_dynamic_sound::function(start_sound_params_t& params) {
	c_base_player* ent = ctx->m_entity_list->get_client_entity(params.m_sound_source)->as< c_base_player >();

	if (ent && ent->is_dormant() && ent->is_player() && ent != ctx->m_local_player) {
		ent->set_abs_origin(params.m_origin);
		ctx->m_far_esp_t[ent] = ctx->m_globals->m_current_time;
		if (ctx->m_player_resource)
			ent->m_health() = ctx->m_player_resource->get_health(ent->entindex());

		if (!ent->is_alive())
			ent->m_life_state() = LIFE_ALIVE;
	}

	return original_function(params);
}

void hooks::s_start_dynamic_sound::init() {
	auto target = util::find_signature< fn >("engine.dll", "55 8B EC 8B 0D ? ? ? ? 81 EC ? ? ? ? 85 C9 0F 84 ? ? ? ? 8B 01 8B 40 04 FF D0 84 C0 0F 84 ? ? ? ? 56");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}


int __fastcall hooks::send_datagram::function(void* channel, void* edx, bf_write* datagram) {
	if (!channel || datagram || !ctx->m_local_player || !config->m_exploits.m_fake_latency || !config->m_exploits.m_backtrack)
		return original_function(channel, edx, datagram);

	auto net_channel = (c_net_channel*)channel;

	const int inSequence = net_channel->m_in_sequence_nr;
	const int inState = net_channel->m_in_reliable_state;

	/*
		WARNING
			UNLESS U FOUND A BETTER WAY OR A PROPER ONE TO OFFSET THE WINDOW
			DO NOT CHANGE ANYTHING HERE
			THIS IS HELD BY JOD'S POWER AND MY WILL TO LIVE

		-- MAD?
	*/

	// 0.03f is needed here, it doesnt offset correctly if we dont use it
	// it works fine for values above the 400ms window tho!

	// this somewhat reduces the bt window
	// but it makes it more consistent

	float latency_needed = config->m_exploits.m_fake_latency_amount / 1000.f;
	backtrack->add_latency(channel, latency_needed - 0.06f); // wtfffff

	const int original = original_function(channel, edx, datagram);
	net_channel->m_in_sequence_nr = inSequence;
	net_channel->m_in_reliable_state = inState;

	return original;
}

void hooks::send_datagram::init() {
	auto target = util::find_signature< void* >("engine.dll", "55 8B EC B8 ? ? ? ? E8 ? ? ? ? A1 ? ? ? ? 53 56 8B D9");
	MH_CreateHook(target, &function, reinterpret_cast<void**>(&original_function));
}

bool __fastcall hooks::send_net_message::function(void* ecx, void* edx, i_net_message* m, bool force_reliable, bool voice) {
	return original_function(ecx, edx, m, force_reliable, voice);
}

void hooks::send_net_message::init() {
	auto target = util::find_signature< fn >("engine.dll", "55 8B EC 57 8B F9 8D 8F ? ? ? ? E8 ? ? ? ? 85 C0 75 07 B0 01 5F 5D C2 0C 00");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::set_alpha_modulation::function(void* ecx, void* edx, float alpha) {
	return original_function(ecx, edx, ctx->m_drawing_static_props ? config->m_visuals.m_prop_alpha : alpha);
}

void hooks::set_alpha_modulation::init() {
	auto target = util::get_virtual< fn >(ctx->m_studio_render, 28u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::set_color_modulation::function(void* ecx, void* edx, float const* color) {
	return original_function(ecx, edx, color);
}

void hooks::set_color_modulation::init() {
	auto target = util::get_virtual< fn >(ctx->m_studio_render, 27u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

bool __fastcall hooks::setup_bones::function(void* ecx, void* edx, matrix_3x4* bone_to_world, int max_bones, int bone_mask, float current_time) {
	if (ecx == ctx->m_local_player) {
		ctx->m_local_player->m_effects() |= EF_NOINTERP;
		original_function(ecx, edx, bone_to_world, max_bones, bone_mask, current_time);
		ctx->m_local_player->m_effects() &= ~EF_NOINTERP;
		return true;
	}

	return original_function(ecx, edx, bone_to_world, max_bones, bone_mask, current_time);
}

void hooks::setup_bones::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 81 EC ? ? ? ? 53 56 8B 35 ? ? ? ? 8B D9 33 C9 33 D2 89 4D ? 89 55 ? 8B 46 ? 85 C0");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

bool __fastcall hooks::should_draw_viewmodel::function(void* ecx, void* edx) {
	return true;
}

void hooks::should_draw_viewmodel::init() {
	auto target = util::get_virtual< fn >(ctx->m_client_mode, 24u);
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __fastcall hooks::update_client_side_animations::function(void* ecx, void* edx) {
	const auto& player = reinterpret_cast<c_base_player*>(ecx);

	if (!player)
		return original_function(ecx, edx);

	if (ctx->m_update_anims)
		original_function(ecx, edx);
}

void hooks::update_client_side_animations::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 83 EC 0C 56 57 8B F1 E8 ? ? ? ? 8B F8 85 FF 74 10 8B 17 8B CF 8B 92 ? ? ? ? FF D2");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

void __cdecl hooks::use_item_confirm::function(bool unkn, DWORD* context) {
	return;
}

void hooks::use_item_confirm::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC A1 ? ? ? ? 83 EC 20 A8 01 75 35 83 C8 01 C7 05 ? ? ? ? ? ? ? ?");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}

LRESULT CALLBACK hooks::wnd_proc::function(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (menu->m_open) {
		/*if ( uMsg == WM_MOUSEWHEEL ) {
			if ( input.hovered )
				input.scroll = GET_WHEEL_DELTA_WPARAM( wParam );
		}

		if ( i::engine_client->Con_IsVisible( ) || i::engine_vgui->IsGameUIVisible( ) ) {
			if ( uMsg != WM_MOUSEWHEEL )
				return 1;
		}*/

		if (input->prevent_inputs)
			return 0;
	}

	return CallWindowProcW(original_wndproc, hwnd, uMsg, wParam, lParam);
}

void hooks::wnd_proc::init() {
	while (!game_hwnd) {
		game_hwnd = FindWindowW(L"Valve001", nullptr);
		Sleep(100);
	}

	original_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongW(game_hwnd, GWL_WNDPROC, reinterpret_cast<LONG>(function)));
}

void __cdecl hooks::write_user_cmd::function(bf_write* buf, c_user_cmd* from, c_user_cmd* to) {

	original_function(buf, from, to);

}

void hooks::write_user_cmd::init() {
	auto target = util::find_signature< fn >("client.dll", "55 8B EC 83 EC ? 53 8B 5D ? 56 8B 75 ? 57 8B 7D ? 8B 46");
	MH_CreateHook(target, &function, reinterpret_cast<LPVOID*>(&original_function));
}