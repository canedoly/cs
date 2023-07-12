#pragma once
#include "../../include/tf2.h"
#include "../backtrack/backtrack.h"

class c_automations {
public:
	void run( c_user_cmd* cmd );

private:
	void auto_detonate( c_base_player* player, c_base_combat_weapon* weapon, c_user_cmd* cmd );
	void auto_vaccinator(c_user_cmd* cmd);

private:
	int get_projectile_resistance_type(c_base_player* weapon);

	enum internal_projectile_types
	{
		HITSCAN = 0,
		EXPLOSIVE = 1,
		FIRE = 2
	};

public:

	struct c_auto_vacc_healing_data
	{
		int m_event_health = 0;
		bool m_should_pop = false;
		int m_required_resistance = -99;
		float m_hurt_time = 0.f;

		c_auto_vacc_healing_data() = default;

		c_auto_vacc_healing_data(int m_event_health, bool m_should_pop, int m_required_resistance)
			: m_event_health(m_event_health), m_should_pop(m_should_pop), m_required_resistance(m_required_resistance)
		{
		}
	} auto_vacc_healing_data;

	void gather_autovacc_data();
	void draw_autovacc_status();
	const char* m_autovacc_status = "Idle";

private:
	struct c_autovacc_threat
	{
		bool m_projectile = false;
		int m_threat_scale = 10;
		c_base_player* m_entity = {};
		float m_distance = FLT_MAX;
	};

	struct c_autovacc_healing
	{
		int m_priority = 0;
		bool m_is_friend = false;
		c_base_player* m_entity = {};
	};

	std::vector<c_autovacc_threat> m_threats = {};
	std::vector<c_autovacc_healing> m_healing_targets = {};
};

inline c_automations* automations = new c_automations;