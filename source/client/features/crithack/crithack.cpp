#include "crithack.h"
#include "../melee/melee.h"

void c_crithack::run( c_user_cmd* cmd ) { 
	if ( !ctx->m_local_player || !ctx->m_local_player->is_alive() || !ctx->m_local_weapon || tf2::is_non_aimable(ctx->m_local_weapon))
		return;

	if ( ctx->m_local_weapon->m_item_definition_index( ) == Pyro_s_GasPasser 
		 || ctx->m_local_weapon->get_weapon_id( ) == TF_WEAPON_JAR 
		 || ctx->m_local_weapon->get_weapon_id( ) == TF_WEAPON_JAR_MILK )
		return;

	//run crit indicator here since its related to the crithack now
	//run_crit_indicator_calc();

	if (!config->m_exploits.m_crithack)
		return;

	if (!config->m_exploits.m_crithack_key.is_held())
	{
		if (!ctx->m_local_player->is_crit_boosted())
			skip_random_crit(cmd);

		return;
	}

	if ( cmd->m_command_number <= m_crit_num && m_crit_num - cmd->m_command_number <= m_max_attempts ) {
		cmd->m_command_number = m_crit_num;
		return;
	}

	if ( !find_crit_command( ctx->m_local_weapon, cmd ) )
		m_crit_num = cmd->m_command_number;

	cmd->m_command_number = m_crit_num;
	m_random_seed_force = md5_pseudo_random(cmd->m_command_number) & 0x7FFFFFFF;
}

void c_crithack::skip_random_crit(c_user_cmd* cmd) {
	//skip random crits, and find out if weapon can randomly crit.
	auto old_crit_token_bucket = ctx->m_local_weapon->m_crit_token_bucket();
	auto old_seed = *ctx->m_random_seed;
	int old_weapon_mode = ctx->m_local_weapon->m_weapon_mode();
	for (int i = 0; i < 10; i++) {
		*ctx->m_random_seed = md5_pseudo_random(cmd->m_command_number + i) & INT_MAX;
		if (!ctx->m_local_weapon->calc_is_attack_critical()) {
			cmd->m_command_number += i;
			break;
		}
	}
	ctx->m_local_weapon->m_weapon_mode() = old_weapon_mode;
	*ctx->m_random_seed = old_seed;
	ctx->m_local_weapon->m_crit_token_bucket() = old_crit_token_bucket;
}

bool c_crithack::find_crit_command( c_base_combat_weapon* weapon, c_user_cmd* cmd ) {
	int old_seed = *ctx->m_random_seed;
	int old_weapon_mode = weapon->m_weapon_mode( );
	float old_crit_token_bucket = weapon->m_crit_token_bucket(); //we only need this stable.
	m_is_going_through_crit_cmds = true; //need this var to fix addtocritbucket.

	for ( auto i = 0; i < m_max_attempts; i++ ) {
		*ctx->m_random_seed = md5_pseudo_random( cmd->m_command_number + i ) & INT_MAX;
		weapon->m_weapon_mode( ) = 0;
		weapon->m_crit_token_bucket( ) = 1000.0f;
		weapon->m_last_crit_check_time( ) = 0.0f;
		weapon->m_last_rapid_fire_crit_check_time( ) = 0.0f;

		if ( weapon->calc_is_attack_critical( ) ) {
			m_crit_num = cmd->m_command_number + i;
			*ctx->m_random_seed = old_seed;
			weapon->m_weapon_mode() = old_weapon_mode;
			m_is_going_through_crit_cmds = false;
			weapon->m_crit_token_bucket() = old_crit_token_bucket;
			return true;
		}
		weapon->m_weapon_mode() = old_weapon_mode;
		weapon->m_crit_token_bucket() = old_crit_token_bucket;
	}

	*ctx->m_random_seed = old_seed;
	weapon->m_weapon_mode( ) = old_weapon_mode;
	weapon->m_crit_token_bucket() = old_crit_token_bucket;
	m_is_going_through_crit_cmds = false;

	return false;
}

void c_crithack::run_crit_indicator_calc( ) {
	//this calculates most shit.
	//this has tons of issues as of now, we will have to filter them out
	if ( !ctx->m_local_player || !ctx->m_local_weapon )
		return;

	//dont want to bother writting a long ass line again and again, save in a var
	int player_resource_dmg = ctx->m_player_resource->get_damage(ctx->m_local_player->entindex());

	//resyncing here
	//this will resync our damage if its incorrect to what player resource fed us by correcting it
	if (m_wait_for_resync && m_old_player_resource_damage < player_resource_dmg) {
		int damage_diff = player_resource_dmg - m_old_player_resource_damage;
		m_wait_for_resync = false;
		if (m_added_crit_dmg) {
			if (m_last_damage_change != damage_diff) {//means its desynced lets change to actual 
				m_crit_dmg -= m_last_damage_change;
				//now add fixed damage
				m_crit_dmg += damage_diff;
			}
			m_added_crit_dmg = false;
		}
		else {
			if (m_last_damage_change/3 != damage_diff) {//means its desynced lets change to actual 
				m_crit_dmg += m_last_damage_change;
				//now add fixed damage
				m_crit_dmg -= damage_diff*3;
			}
		}
	}

	if (ctx->m_local_player->m_damage_done() > m_old_dmg) {
		if (ctx->m_local_weapon->get_slot() != e_weapon_slots::SLOT_MELEE) {
			if (ctx->m_local_player->m_criticals() > m_old_criticals || ctx->m_local_player->m_headshots() > m_old_headshots)
				m_crit_dmg -= m_last_damage_change = (ctx->m_local_player->m_damage_done() - m_old_dmg) * 3;
			else {
				m_crit_dmg += m_last_damage_change = (ctx->m_local_player->m_damage_done() - m_old_dmg);
				m_added_crit_dmg = true;
			}

			m_wait_for_resync = true;
		}

		else m_melee_dmg += ctx->m_local_player->m_damage_done() - m_old_dmg;

		m_old_dmg = ctx->m_local_player->m_damage_done();
		m_old_criticals = ctx->m_local_player->m_criticals();
		m_old_headshots = ctx->m_local_player->m_headshots();
		//damage done on a shooting weapon
		m_dmg_done_weapon = m_old_dmg - m_melee_dmg;
	}

	else if (ctx->m_local_player->m_damage_done() < m_old_dmg) {
		//this usually only happens if you join a new server, this shouldnt happen in gameplay, reset.
		m_crit_dmg = 0;
		m_old_dmg = ctx->m_local_player->m_damage_done();
		m_old_criticals = ctx->m_local_player->m_criticals();
		m_old_headshots = ctx->m_local_player->m_headshots();
		m_old_player_resource_damage = player_resource_dmg;
		m_melee_dmg = 0;
		m_dmg_done_weapon = 0;
	}

	m_old_player_resource_damage = player_resource_dmg; //set this outside.

	//calculate how many crits we have from bucket, and store our new official crit damage.
	if ( ctx->m_local_player->m_player_class( ) == CLASS_SPY && ctx->m_local_weapon->get_slot( ) > 0 || ctx->m_local_weapon->get_slot( ) > 2 || ctx->m_local_weapon->get_weapon_id( ) == TF_WEAPON_LUNCHBOX )
		return;

	if (ctx->m_local_weapon->get_slot() != e_weapon_slots::SLOT_MELEE) {
		if (ctx->m_local_weapon->get_weapon_data().m_use_rapid_fire_crits) {
			//for rapidfire weapons.
			//this is not that correct but for now
			m_bucket_crits_max = 1;
			//this should be 1 if full.
			m_bucket_crits = ctx->m_local_weapon->m_crit_token_bucket() / 1000;
			m_official_crit_dmg = m_crit_dmg + ctx->m_local_player->m_crit_mult() * 3 - 1000; //assume its like this for rapidfire weapons (FOR NOW.)
		}
		else {
			//this should be pretty much accurate compared to the rapidfire shit we just did
			//calculate bucket crits max (and round up the value)
			int crit_mulitplier = 3, weapon_damage = ctx->m_local_weapon->get_weapon_data().m_damage, per_shot = ctx->m_local_weapon->get_weapon_data().m_bullets_per_shot, cum_bucket = ctx->m_local_weapon->m_crit_token_bucket(), base_damage = (1000 - weapon_damage);
			//da basics now
			int full_damage = weapon_damage * per_shot; //calculate damage per shot
			int critical_full_damage = full_damage * crit_mulitplier; //calculate critical damage per shot
			//its as easy as this
			m_bucket_crits_max = base_damage / (critical_full_damage + 1);
			m_bucket_crits = (cum_bucket - weapon_damage) / critical_full_damage;
			m_crit_cost = critical_full_damage;

			m_official_crit_dmg = m_crit_dmg + ctx->m_local_player->m_crit_mult() * 3;
		}
	}
	else {
		//if its a melee, it gets easier, we dont need to bother with crit damage and shit.
		m_bucket_crits_max = 1000 / (ctx->m_local_weapon->get_weapon_data().m_damage/2.f);
		m_bucket_crits = ctx->m_local_weapon->m_crit_token_bucket() / (ctx->m_local_weapon->get_weapon_data().m_damage / 2.f);
	}
}