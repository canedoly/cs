#include "game_events.h"
#include "../automations/automations.h"
#include "../visuals/visuals.h"
#include "../crithack/crithack.h"

static std::string yellow({ '\x7', 'E', 'D', 'B', '6', '2', '8' });
static std::string blue({ '\x7', '0', '0', '9', '5', 'F', 'F' });
static std::string white({ '\x7', 'F', 'F', 'F', 'F', 'F', 'F' });
static std::string red({ '\x7', 'F', 'F', '3', '2', '3', '2' });
static std::string green({ '\x7', '3', 'A', 'F', 'F', '4', 'D' });
static std::string gray({ '\x7', '4', '0', '4', '0', '4', '0' });
static std::string light_green({ '\x7', '8', '0', 'f', 'f', '8', '0' });
static std::string menu_accent({ '\x7', 'F', 'F', '4', '1', '4', '1' });

void c_game_events::init() {
	ctx->m_game_event->add_listener(this, "player_hurt", false);
	ctx->m_game_event->add_listener(this, "player_connect", false);
	ctx->m_game_event->add_listener(this, "player_disconnect", false);
	ctx->m_game_event->add_listener(this, "player_changeclass", false);
	ctx->m_game_event->add_listener(this, "player_changename", false);
	ctx->m_game_event->add_listener(this, "vote_cast", false);
}

void c_game_events::exit() {
	ctx->m_game_event->remove_listener(this);
}

void c_game_events::fire_game_event(c_game_event* event) {
	if (!event || !ctx->m_local_player || !ctx->m_local_weapon)
		return;

	visuals->vote_revealer_register_event(event);

	constexpr auto player_hurt_hash = fnv::hash("player_hurt");

	if (fnv::hash(event->get_name()) == player_hurt_hash) {
		const auto victim = ctx->m_entity_list->get_client_entity(ctx->m_engine_client->get_player_for_user_id(event->get_int("userid")));
		const auto attacker = ctx->m_entity_list->get_client_entity(ctx->m_engine_client->get_player_for_user_id(event->get_int("attacker")));

		if (!victim || !attacker)
			return;

		bool is_critical = event->get_bool("crit");
		int damage = event->get_int("damageamount");
		int health_remaning = event->get_int("health"); // iirc its remaning not current or after event

		if (attacker == ctx->m_entity_list->get_client_entity(ctx->m_engine_client->get_local_player())) {
			const auto weapon_id = event->get_int("weaponid");
			const auto& player = victim->as<c_base_player>();

			if (victim != ctx->m_local_player && ctx->m_local_weapon->get_weapon_id() != TF_WEAPON_FLAMETHROWER && tf2::is_projectile_weapon(ctx->m_local_weapon) && player)
				ctx->m_debug_overlay->add_box_overlay(player->m_origin(), player->m_mins(), player->m_maxs(), vector(0.0f, math::direction_to_angles(player->m_velocity()).m_y, 0.0f), 255, 255, 255, 25, 2.0f);
		}

		// auto vacc
		if (ctx->m_local_weapon && ctx->m_local_weapon->m_item_definition_index() == Medic_s_TheVaccinator)
		{
			c_base_player* healing_target = ctx->m_entity_list->get_client_entity_from_handle(ctx->m_local_weapon->m_healing_target())->as<c_base_player>();
			if (victim != healing_target || attacker == victim || !healing_target)
				return;

			if (healing_target && damage > 25 && is_critical) // autopop on critical damage no matter what
			{
				automations->auto_vacc_healing_data.m_should_pop = true;
				automations->auto_vacc_healing_data.m_hurt_time = ctx->m_engine_client->time() + 0.2f;

				if (auto player = attacker->as<c_base_player>())
				{
					if (player && player->is_alive() && player->m_player_class() != CLASS_SPY)
					{
						switch (player->m_player_class())
						{
						case CLASS_SCOUT:
						case CLASS_ENGINEER:
						case CLASS_MEDIC:
						case CLASS_SNIPER:
						case CLASS_HEAVY:
						{
							automations->auto_vacc_healing_data.m_required_resistance = 0;
							break;
						}
						case CLASS_DEMOMAN:
						{
							automations->auto_vacc_healing_data.m_required_resistance = 1;
							break;
						}
						case CLASS_SOLDIER:
						{
							automations->auto_vacc_healing_data.m_required_resistance = 1;
							auto weapon = player->get_active_weapon(); // this is not perfect, but its good
							if (weapon) // since the player can quickly switch weapons to another one and blast with that
								if (weapon->get_weapon_id() == TF_WEAPON_SHOTGUN_SOLDIER)
									automations->auto_vacc_healing_data.m_required_resistance = 0;
							break;
						}
						case CLASS_PYRO:
						{
							automations->auto_vacc_healing_data.m_required_resistance = 2;
							auto weapon = player->get_active_weapon();
							if (weapon)
								if (weapon->get_weapon_id() == TF_WEAPON_SHOTGUN_PYRO)
									automations->auto_vacc_healing_data.m_required_resistance = 0;

							break;
						}
						}
					}
				}
			}
		}
	}

	if (fnv::hash(event->get_name()) == fnv::hash("player_connect") && config->m_misc.m_chat_player_connects) {
		if (const auto& entity = ctx->m_entity_list->get_client_entity(ctx->m_engine_client->get_player_for_user_id(event->get_int("userid")))) {
			if (!entity)
				return;

			const auto& player = entity->as<c_base_player>();

			int index = entity->entindex();
			player_info_t pi = {};
			ctx->m_engine_client->get_player_info(index, &pi);

			std::string team = player->m_team_num() != ctx->m_local_player->m_team_num() ? white + "ENEMY" + gray : white + "TEAM" + gray;
			std::string cheater = red + "CHEATER" + gray;
			std::string name = blue + pi.m_name + white;
			std::string guid = blue + pi.m_guid + white;
			std::string connect = gray + "[" + menu_accent + "spook953paste" + gray + "]  [" + team + "] " + name + " has joined. [" + guid + "]";
			std::string cheaterdetection = gray + "[" + menu_accent + "spook953paste" + gray + "] " + name + "is a known " + cheater + "!";

			ctx->m_client_mode->m_chat_element->chat_printf(0, connect.c_str());

		}
	}

	if (fnv::hash(event->get_name()) == fnv::hash("player_disconnect") && config->m_misc.m_chat_player_disconnects) {
		if (const auto& entity = ctx->m_entity_list->get_client_entity(ctx->m_engine_client->get_player_for_user_id(event->get_int("userid")))) {
			if (!entity)
				return;

			//std::string team = player->m_team_num( ) != ctx->m_local_player->m_team_num( ) ? white + "ENEMY" + gray : white + "TEAM" + gray;
			std::string name = blue + event->get_string("name") + white;
			//std::string guid = blue + pi.m_guid + white;
			std::string disconnect = gray + "[" + menu_accent + "spook953paste" + gray + "] " + name + " has left.";

			ctx->m_client_mode->m_chat_element->chat_printf(0, disconnect.c_str());
		}
	}

	if (fnv::hash(event->get_name()) == fnv::hash("player_changeclass") && config->m_misc.m_chat_player_class_changes) {
		if (const auto& entity = ctx->m_entity_list->get_client_entity(ctx->m_engine_client->get_player_for_user_id(event->get_int("userid")))) {
			if (!entity)
				return;

			const auto& player = entity->as<c_base_player>();

			int index = entity->entindex();
			player_info_t pi = {};
			ctx->m_engine_client->get_player_info(index, &pi);

			std::string team = player->m_team_num() != ctx->m_local_player->m_team_num() ? white + "ENEMY" + gray : white + "TEAM" + gray;
			std::string name = blue + pi.m_name + white;
			std::string class_str = blue + tf2::get_player_class(event->get_int("class")) + white;
			std::string class_change = gray + "[" + menu_accent + "spook953paste" + gray + "]  [" + team + "] " + name + " changed class to " + class_str + ".";

			ctx->m_client_mode->m_chat_element->chat_printf(0, class_change.c_str());
		}
	}

	if (fnv::hash(event->get_name()) == fnv::hash("player_changename") && config->m_misc.m_chat_player_name_changes) {
		if (const auto& entity = ctx->m_entity_list->get_client_entity(ctx->m_engine_client->get_player_for_user_id(event->get_int("userid")))) {
			if (!entity)
				return;

			const auto& player = entity->as<c_base_player>();

			std::string old_name = blue + event->get_string("oldname") + white;
			std::string new_name = blue + event->get_string("newname") + white;
			std::string team = player->m_team_num() != ctx->m_local_player->m_team_num() ? white + "ENEMY" + gray : white + "TEAM" + gray;
			std::string name_change = gray + "[" + menu_accent + "spook953paste" + gray + "]  [" + team + "] " + old_name + " changed name to " + new_name + ".";

			ctx->m_client_mode->m_chat_element->chat_printf(0, name_change.c_str());
		}
	}

	if (fnv::hash(event->get_name()) == fnv::hash("vote_cast") && config->m_misc.m_chat_vote_casts) {
		if (const auto& entity = ctx->m_entity_list->get_client_entity(event->get_int("entityid"))) {
			if (!entity)
				return;

			const bool voted_yes = event->get_int("vote_option") == 0;
			const auto& player = entity->as<c_base_player>();

			int index = entity->entindex();
			player_info_t pi = {};
			ctx->m_engine_client->get_player_info(index, &pi);

			std::string team = player->m_team_num() != ctx->m_local_player->m_team_num() ? white + "ENEMY" + gray : white + "TEAM" + gray;
			std::string name = blue + pi.m_name + white;
			std::string vote = voted_yes ? green + "Yes" + white : red + "No" + white;

			std::string vote_str = gray + "[" + menu_accent + "spook953paste" + gray + "]  [" + team + "] " + name + " voted " + vote + ".";
			ctx->m_client_mode->m_chat_element->chat_printf(0, vote_str.c_str());
		}
	}
}