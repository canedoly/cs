#pragma once
#include "../../include/render.h"

class c_crithack {
public:
	void run( c_user_cmd* cmd );
    int m_bucket_crits_max = 0, m_bucket_crits = 0, m_official_crit_dmg = 0, m_crit_cost = 0;
	int m_random_seed_force = -1;
	bool m_is_going_through_crit_cmds = false;
	bool m_weapon_can_randomly_crit = false;
private:
	bool find_crit_command( c_base_combat_weapon* wep, c_user_cmd* cmd );
	void skip_random_crit(c_user_cmd* cmd);
	void run_crit_indicator_calc();
	bool m_wait_for_resync = false;
	int m_max_attempts = 100, m_crit_num = 0, m_old_dmg = 0, m_old_criticals = 0, m_old_headshots = 0, m_melee_dmg = 0, m_dmg_done_weapon = 0, m_crit_dmg = 0, m_old_player_resource_damage = 0, m_added_crit_dmg = 0, m_last_damage_change = 0;
};

inline c_crithack* crithack = new c_crithack;