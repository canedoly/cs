#pragma once
#include "definitions.h"
#include "netvar_manager.h"

#define OFFSET( name, type, offset ) inline type& name( ) { \
	return *reinterpret_cast< type* >( reinterpret_cast< uint32_t >( this ) + offset ); \
}

#define TF_AMMOPACK_SMALL_BDAY		"models/items/ammopack_small_bday.mdl"
#define TF_AMMOPACK_MEDIUM_BDAY		"models/items/ammopack_medium_bday.mdl"
#define TF_AMMOPACK_LARGE_BDAY		"models/items/ammopack_large_bday.mdl"
#define TF_AMMOPACK_SMALL "models/items/ammopack_small.mdl"
#define TF_AMMOPACK_MEDIUM "models/items/ammopack_medium.mdl"
#define TF_AMMOPACK_LARGE "models/items/ammopack_large.mdl"

#define TF_MEDKIT_SMALL_BDAY	"models/items/medkit_small_bday.mdl"
#define TF_MEDKIT_MEDIUM_BDAY	"models/items/medkit_medium_bday.mdl"
#define TF_MEDKIT_LARGE_BDAY	"models/items/medkit_large_bday.mdl"
#define TF_MEDKIT_SMALL_HALLOWEEN	"models/props_halloween/halloween_medkit_small.mdl"
#define TF_MEDKIT_MEDIUM_HALLOWEEN  "models/props_halloween/halloween_medkit_medium.mdl"
#define TF_MEDKIT_LARGE_HALLOWEEN	"models/props_halloween/halloween_medkit_large.mdl"
#define LUNCHBOX_DROP_MODEL  "models/items/plate.mdl"
#define LUNCHBOX_STEAK_DROP_MODEL  "models/items/plate_steak.mdl"
#define LUNCHBOX_ROBOT_DROP_MODEL  "models/items/plate_robo_sandwich.mdl"
#define LUNCHBOX_FESTIVE_DROP_MODEL  "models/items/plate_sandwich_xmas.mdl"
#define TF_MEDKIT_SMALL "models/items/medkit_small.mdl"
#define TF_MEDKIT_MEDIUM "models/items/medkit_medium.mdl"
#define TF_MEDKIT_LARGE "models/items/medkit_large.mdl"

class i_client_entity {
public:
	inline const vector& get_abs_angles( ) {
		typedef const vector& ( __thiscall* get_abs_angles_fn )( i_client_entity* );
		return util::get_virtual< get_abs_angles_fn>( this, 2u )( this );
	}

	inline vector const& get_render_origin( ) {
		typedef vector const& ( __thiscall* get_render_origin_fn )( i_client_entity* );
		return util::get_virtual<get_render_origin_fn>( this + 0x4, 1u )( this + 0x4 );
	}

	inline vector const& get_render_angles( ) {
		typedef vector const& ( __thiscall* get_render_origin_fn )( i_client_entity* );
		return util::get_virtual<get_render_origin_fn>( this + 0x4, 2u )( this + 0x4 );
	}

	inline bool should_draw( ) {
		typedef bool( __thiscall* draw_model_fn )( i_client_entity* );
		return util::get_virtual<draw_model_fn>( this + 0x4, 3u )( this + 0x4 );
	}

	inline model_t* get_model( ) {
		typedef model_t* ( __thiscall* get_model_fn )( i_client_entity* );
		return util::get_virtual< get_model_fn >( this + 0x4, 9u )( this + 0x4 );
	}

	inline int draw_model( int flags ) {
		typedef int( __thiscall* draw_model_fn )( i_client_entity*, int );
		return util::get_virtual<draw_model_fn>( this + 0x4, 10u )( this + 0x4, flags );
	}

	inline bool setup_bones( matrix_3x4* out, int max, int mask, float time ) {
		typedef bool( __thiscall* setup_bones_fn )( i_client_entity*, matrix_3x4*, int, int, float );
		return util::get_virtual< setup_bones_fn >( this + 0x4, 16u )( this + 0x4, out, max, mask, time );
	}

	inline void get_render_bounds( vector& mins, vector& maxs ) {
		typedef void( __thiscall* get_render_bounds_fn )( i_client_entity*, vector&, vector& );
		return util::get_virtual< get_render_bounds_fn >( this + 0x4, 20u )( this + 0x4, mins, maxs );
	}

	inline matrix_3x4& renderable_to_world_transform( ) {
		typedef matrix_3x4& ( __thiscall* renderable_to_world_transform_fn )( i_client_entity* );
		return util::get_virtual< renderable_to_world_transform_fn >( this + 0x4, 34u )( this + 0x4 );
	}

	inline client_class* get_client_class( ) {
		typedef client_class* ( __thiscall* get_client_class_fn )( i_client_entity* );
		return util::get_virtual< get_client_class_fn >( this + 0x8, 2u )( this + 0x8 );
	}

	inline bool is_dormant( ) {
		typedef bool( __thiscall* is_dormant_fn )( i_client_entity* );
		return util::get_virtual< is_dormant_fn >( this + 0x8, 8u )( this + 0x8 );
	}

	inline int entindex( ) {
		typedef int( __thiscall* entindex_fn )( i_client_entity* );
		return util::get_virtual< entindex_fn >( this + 0x8, 9u )( this + 0x8 );
	}

	inline bool is_player( ) {
		return ( get_client_class( )->m_class_id == class_id_t::CTFPlayer );
	}

	inline bool is_building( ) {
		auto class_id = get_client_class( )->m_class_id;
		return ( class_id == class_id_t::CObjectSentrygun || class_id == class_id_t::CObjectDispenser || class_id == class_id_t::CObjectTeleporter );
	}

	inline bool is_projectile( ) {
		auto class_id = get_client_class( )->m_class_id;
		return ( class_id == class_id_t::CTFProjectile_Arrow || class_id == class_id_t::CTFProjectile_Cleaver || class_id == class_id_t::CTFProjectile_Flare || class_id == class_id_t::CTFProjectile_HealingBolt || class_id == class_id_t::CTFProjectile_Jar || class_id == class_id_t::CTFProjectile_JarGas || class_id == class_id_t::CTFProjectile_JarMilk || class_id == class_id_t::CTFProjectile_Rocket || class_id == class_id_t::CTFProjectile_SentryRocket || class_id == class_id_t::CTFGrenadePipebombProjectile );
	}

	bool is_health( ); 
	bool is_ammo( );

	template < typename T >
	inline T* as( ) {
		return reinterpret_cast< T* >( this );
	}
};

enum thinkmethods_t {
	THINK_FIRE_ALL_FUNCTIONS,
	THINK_FIRE_BASE_ONLY,
	THINK_FIRE_ALL_BUT_BASE
};

class c_base_entity : public i_client_entity {
public:
	NETVAR( m_simulation_time, float, "CBaseEntity", "m_flSimulationTime" );
	NETVAR( m_team_num, int, "CBaseEntity", "m_iTeamNum" );
	NETVAR( m_mins, vector, "CBaseEntity", "m_vecMins" );
	NETVAR( m_maxs, vector, "CBaseEntity", "m_vecMaxs" );
	NETVAR( m_origin, vector, "CBaseEntity", "m_vecOrigin" );
	//NETVAR( m_type, int, "CTFGrenadePipebombProjectile", "m_iType" );
	NETVAR( m_critical, bool, "CTFWeaponBaseGrenadeProj", "m_bCritical" );
	NETVAR( m_client_side_animations, bool, "CBaseAnimating", "m_bClientSideAnimation" );
	NETVAR( m_thrower, int, "CBaseGrenade", "m_hThrower" );
	NETVAR( m_owner, int, "CBaseGrenade", "m_hOwner" );
	NETVAR( m_owner_entity, int, "CBaseEntity", "m_hOwnerEntity" );
	NETVAR(m_initial_velocity, vector, "CTFWeaponBaseGrenadeProj", "m_vInitialVelocity");	
	NETVAR( m_cycle, float, "CBaseAnimating", "m_flCycle" );
	NETVAR( m_playbackrate, float, "CBaseAnimating", "m_flPlaybackRate" );
	NETVAR( m_next_attack, float, "CBaseCombatCharacter", "m_flNextAttack" );
	NETVAR( m_effects, int, "CBaseEntity", "m_fEffects" );
	OFFSET( m_move_type, move_type_t, 0x1A4 );
	OFFSET( m_move_child, DWORD, 0x1B0 );
	OFFSET( m_next_move_peer, DWORD, 0x1B4 );
	OFFSET( m_pipebomb_type, int, 0x8FC );

	inline float m_old_simulation_time( ) {
		static int offset = netvar_manager->get_netvar( "CBaseEntity", "m_flSimulationTime" );
		return *reinterpret_cast< float* >( reinterpret_cast< DWORD >( this ) + offset + sizeof( int ) );
	}

	vector get_world_space_center( ) {
		auto out = m_origin( );
		out.m_z += ( m_mins( ).m_z + m_maxs( ).m_z ) * 0.5f;
		return out;
	}

	inline void set_abs_origin( const vector& origin ) {
		typedef void( __thiscall* fn )( c_base_entity*, const vector& );
		static auto function = util::find_signature< fn >( "client.dll", "55 8B EC 56 57 8B F1 E8 ? ? ? ? 8B 7D 08 F3 0F 10 07" );
		return function( this, origin );
	}

	inline void set_abs_angles( vector angles ) {
		typedef void( __thiscall* fn )( c_base_entity*, const vector& );
		static auto function = util::find_signature< fn >( "client.dll", "55 8B EC 83 EC ? 56 57 8B F1 E8 ? ? ? ? 8B 7D ? F3 0F 10 07 0F 2E 86" );
		return function( this, angles );
	}

	void think( ) {
		typedef void( __thiscall* fn )( void* );
		return util::get_virtual< fn >( this, 174u )( this );
	}

	bool is_entity_on_screen( );
	bool is_enemy( );
	const char* get_projectile_name( );
	void set_next_think( float time, const char* context );
	int get_next_think( const char* context );
	bool physics_run_tick( int think_method );
	vector estimate_abs_velocity( );
	c_base_entity* get_move_child( );
	c_base_entity* next_move_peer( );
};

class c_base_player : public c_base_entity {
public:
	NETVAR( m_life_state, uint8_t, "CBasePlayer", "m_lifeState" );
	NETVAR( m_health, int, "CBasePlayer", "m_iHealth" );
	NETVAR( m_view_offset, vector, "CBasePlayer", "m_vecViewOffset[0]" );
	NETVAR( m_ducked, bool, "CBasePlayer", "m_bDucked" );
	NETVAR( m_model_scale, float, "CBaseAnimating", "m_flModelScale" );
	NETVAR( m_ducking, bool, "CBasePlayer", "m_bDucking" );
	NETVAR( m_velocity, vector, "CBasePlayer", "m_vecVelocity[0]" );
	NETVAR( m_base_velocity, vector, "CBasePlayer", "m_vecBaseVelocity" );
	NETVAR( m_ground_entity, int, "CBasePlayer", "m_hGroundEntity" );
	NETVAR( m_flags, int, "CBasePlayer", "m_fFlags" );
	NETVAR( m_in_duck_jump, bool, "CBasePlayer", "m_bInDuckJump" );
	NETVAR( m_duck_time, float, "CBasePlayer", "m_flDucktime" );
	NETVAR( m_duck_jump_time, float, "CBasePlayer", "m_flDuckJumpTime" );
	NETVAR( m_active_weapon, int, "CBaseCombatCharacter", "m_hActiveWeapon" );
	NETVAR( m_punch_angle, vector, "CBasePlayer", "m_vecPunchAngle" );
	NETVAR( m_hitbox_set, int, "CBaseAnimating", "m_nHitboxSet" );
	OFFSET( m_current_command, c_user_cmd*, 0x1184 );
	NETVAR( m_next_attack, float, "CBaseCombatCharacter", "m_flNextAttack" );
	NETVAR( m_tick_base, int, "CBasePlayer", "m_nTickBase" );
	NETVAR( m_damage_done, int, "CTFPlayer", "m_iDamageDone" );
	NETVAR( m_criticals, int, "CTFPlayer", "m_iCrits" );
	NETVAR( m_crit_mult, int, "CTFPlayer", "m_iCritMult" );
	NETVAR( m_headshots, int, "CTFPlayer", "m_iHeadshots" );
	NETVAR( m_player_class, int, "CTFPlayer", "m_iClass" );
	NETVAR( m_player_cond, int, "CTFPlayer", "m_nPlayerCond" );
	NETVAR( m_condition_bits, int, "CTFPlayer", "_condition_bits" );
	NETVAR( m_player_cond_ex, int, "CTFPlayer", "m_nPlayerCondEx" );
	NETVAR( m_player_cond_ex2, int, "CTFPlayer", "m_nPlayerCondEx2" );
	NETVAR( m_player_cond_ex3, int, "CTFPlayer", "m_nPlayerCondEx3" );
	NETVAR( m_player_cond_ex4, int, "CTFPlayer", "m_nPlayerCondEx4" );
	NETVAR( m_fov, int, "CBasePlayer", "m_iFOV" );
	NETVAR( m_hide_hud, int, "CBasePlayer", "m_iHideHUD" ); // idea.jpg -- Mad?
	NETVAR( m_water_level, BYTE, "CTFPlayer", "m_nWaterLevel");
	NETVAR( m_max_speed, float, "CTFPlayer", "m_flMaxspeed");
	NETVAR( m_force_taunt_cam, int, "CTFPlayer", "m_nForceTauntCam");
	NETVAR( m_eye_angles, vector, "CTFPlayer", "m_angEyeAngles[0]");
	NETVAR( m_next_think_tick, int, "CBasePlayer", "m_nNextThinkTick");
	OFFSET( m_player_anim_state, c_tf_player_anim_state*, 0x1D00 );
	OFFSET( m_tank_pressure, float, 0x1B40 );

	inline int get_max_health( ) {
		typedef int( __thiscall* get_max_health_fn )( c_base_player* );
		return util::get_virtual< get_max_health_fn >( this, 107u )( this );
	}

	inline bool is_on_ground( ) {
		return m_flags( ) & FL_ONGROUND;
	}

	inline bool is_alive( ) {
		return ( m_life_state( ) == LIFE_ALIVE && m_health() > 0 );// lifestate might be enough tbh -- Mad?
	}

	inline vector get_shoot_position( ) {
		return m_origin( ) + m_view_offset( );
	}

	inline bool is_crit_boosted( ) {
		return this->m_player_cond( ) & TFCond_Kritzkrieged
			|| this->m_condition_bits( ) & TFCond_Kritzkrieged
			|| this->m_player_cond_ex( ) & TFCondEx_HalloweenCritCandy	// Only for Scream Fortress event maps that drop crit candy. 
			|| this->m_player_cond_ex( ) & TFCondEx_CritCanteen			// Player is getting a crit boost from a MVM canteen.
			|| this->m_player_cond_ex( ) & TFCondEx_CritDemoCharge		// From demo's shield
			|| this->m_player_cond_ex( ) & TFCondEx_CritOnFirstBlood		// Arena first blood crit buff. 
			|| this->m_player_cond_ex( ) & TFCondEx_CritOnWin				// End of round crits. 
			|| this->m_player_cond_ex( ) & TFCondEx_CritOnFlagCapture		// CTF intelligence capture crits. 
			|| this->m_player_cond_ex( ) & TFCondEx_CritOnKill
			|| this->m_player_cond_ex( ) & TFCondEx_PyroCrits;
	}

	inline bool is_mini_crit_boosted( ) {
		return this->m_player_cond( ) & TFCond_MiniCrits;
	}

	inline bool is_bonked( ) {
		return this->m_player_cond( ) & TFCond_Bonked;
	}

	inline bool is_charging( ) {
		return this->m_player_cond( ) & TFCond_Charging;
	}

	inline bool is_taunting( ) {
		return this->m_player_cond( ) & TFCond_Taunting;
	}

	inline bool is_marked_for_death() {
		return this->m_player_cond() & TFCond_Jarated
			|| this->m_player_cond() & TFCond_MarkedForDeath
			|| this->m_player_cond_ex() & TFCondEx_MarkedForDeathSilent;
	}

	inline bool is_stunned( ) {
		return this->m_player_cond( ) & TFCond_Stunned;
	}

	inline bool is_in_kart( ) {
		return this->m_player_cond_ex( ) & TFCondEx_InKart;
	}

	inline bool is_ghost( ) {
		return this->m_player_cond_ex2( ) & TFCondEx2_HalloweenGhostMode;
	}

	inline bool is_cloaked( ) {
		return this->m_player_cond( ) & TFCond_Cloaked
			|| this->m_player_cond( ) & TFCond_CloakFlicker
			|| this->m_player_cond_ex2( ) & TFCondEx2_Stealthed
			|| this->m_player_cond_ex2( ) & TFCondEx2_StealthedUserBuffFade;
	}

	inline bool is_invulnerable( ) {
		return this->m_player_cond() & TFCond_Ubercharged;
			//|| m_player_cond( ) & TFCond_UberchargeFading
			//|| this->m_player_cond_ex( ) & TFCondEx_UberchargedHidden
			//|| this->m_player_cond_ex( ) & TFCondEx_UberchargedCanteen;
	}

	inline bool is_zoomed( ) {
		return this->m_player_cond( ) & TFCond_Zoomed;
	}

	inline bool is_overhealed( ) {
		return this->m_health( ) > this->get_max_health( );
	}

	inline bool is_quick_fix_uber( ) {
		return this->m_player_cond( ) & TFCond_MegaHeal;
	}

	inline bool is_in_concheror_range( ) {
		return this->m_player_cond( ) & TFCond_RegenBuffed;
	}

	inline bool is_in_battalions_range( ) {
		return this->m_player_cond( ) & TFCond_DefenseBuffed;
	}

	inline bool is_in_buff_banner_range( ) {
		return this->m_player_cond( ) & TFCond_Buffed;
	}

	inline bool is_bleeding( ) {
		return this->m_player_cond( ) & TFCond_Bleeding;
	}

	inline bool is_covered_in_milk( ) {
		return this->m_player_cond( ) & TFCond_Milked;
	}

	inline bool is_slowed( ) {
		return this->m_player_cond( ) & TFCond_Slowed;
	}

	inline bool is_bullet_resistant( ) {
		return this->m_player_cond_ex( ) & TFCondEx_BulletResistance;
	}

	inline bool is_explosive_resistant( ) {
		return this->m_player_cond_ex( ) & TFCondEx_ExplosiveResistance;
	}

	inline bool is_fire_resistant( ) {
		return this->m_player_cond_ex( ) & TFCondEx_FireResistance;
	}

	inline bool is_bullet_charged( ) {
		return this->m_player_cond_ex( ) & TFCondEx_BulletCharge;
	}

	inline bool is_explosive_charged( ) {
		return this->m_player_cond_ex( ) & TFCondEx_ExplosiveCharge;
	}

	inline bool is_fire_charged( ) {
		return this->m_player_cond_ex( ) & TFCondEx_FireCharge;
	}

	void pre_think( ) {
		using fn = void(__thiscall*)(void*);
		return util::get_virtual< fn >( this, 260u )( this );
	}

	void post_think( ) {
		using fn = void( __thiscall* )( void* );
		return util::get_virtual< fn >( this, 261u )( this );
	}

	void select_item( const char* name, int subtype ) {
		using fn = void( __thiscall* )( void*, const char*, int );
		return util::get_virtual< fn >( this, 271u )( this, name, subtype );
	}

	void anim_state_update( float yaw, float pitch );
	void update_client_side_animations( );
	bool is_local_player( );
	bool is_player_on_friend_list( );
	const char* get_weapon_name( );
	c_base_combat_weapon* get_active_weapon( );
	vector get_hitbox_position( int hitbox );
	int get_ammo_count(int ammo_index);
	vector get_hitbox_position_from_matrix( int hitbox, matrix_3x4* matrix, model_t* model );

	enum e_player_state {
		STATE_NEUTRAL,
		STATE_CHEATER,
	};

	e_player_state player_state = STATE_NEUTRAL;
};

class c_base_combat_weapon : public c_base_entity {
public:
	OFFSET( m_crit_token_bucket, float, 0xa54 );
	OFFSET( m_weapon_mode, int, 0xb24 );
	OFFSET( m_last_crit_check_time, float, 0xb54 );
	OFFSET( m_last_rapid_fire_crit_check_time, float, 0xb60 );
	OFFSET( m_clip2, int, 0xaac);
	NETVAR( m_next_primary_attack, float, "CBaseCombatWeapon", "m_flNextPrimaryAttack" );
	NETVAR( m_next_secondary_attack, float, "CBaseCombatWeapon", "m_flNextSecondaryAttack" );
	NETVAR( m_clip1, int, "CBaseCombatWeapon", "m_iClip1" );
	//NETVAR( m_clip2, int, "CBaseCombatWeapon", "m_iClip2" );
	NETVAR( m_item_definition_index, int, "CEconEntity", "m_iItemDefinitionIndex" );
	NETVAR( m_charge_damage, float, "CTFSniperRifle", "m_flChargedDamage" );
	NETVAR( m_last_fire_time, float, "CTFWeaponBase", "m_flLastFireTime" );
	OFFSET( m_minigun_state, int, 0xC48 );
	NETVAR( m_charge_begin_time, float, "CTFPipebombLauncher", "m_flChargeBeginTime" );
	NETVAR( m_healing_target, unsigned int, "CWeaponMedigun", "m_hHealingTarget" );
	NETVAR( m_charge_resistance_type, int, "CWeaponMedigun", "m_nChargeResistType" );
	NETVAR( m_charge_level, float, "CWeaponMedigun", "m_flChargeLevel" );
	NETVAR( m_primary_ammo_type, int, "CBaseCombatWeapon", "m_iPrimaryAmmoType" );

	inline int get_slot( ) {
		typedef int( __thiscall* get_slot_fn )( c_base_combat_weapon* );
		return util::get_virtual< get_slot_fn >( this, 330u )( this );
	}
	
	__inline float get_smack_time() {
		static auto dwOffset = netvar_manager->get_netvar("CTFWeaponBase", "m_nInspectStage") + 0x1C;
		return *reinterpret_cast<float*>(this + dwOffset);
	}

	inline int get_max_clip( ) {
		typedef int( __thiscall* fn )( c_base_combat_weapon* );
		return util::get_virtual< fn >( this, 321u )( this );
	}

	inline bool is_ready( ) {
		typedef bool( __thiscall* fn )( c_base_combat_weapon* );
		return util::get_virtual< fn >( this, 372u )( this );
	}

	const char* get_name( ) {
		typedef const char* ( __thiscall* get_name_fn )( c_base_combat_weapon* );
		return util::get_virtual< get_name_fn >( this, 331u )( this );
	}

	inline int get_weapon_id( ) {
		typedef int( __thiscall* get_weapon_id_fn )( c_base_combat_weapon* );
		return util::get_virtual< get_weapon_id_fn >( this, 381u )( this );
	}

	inline bool calc_is_attack_critical( ) {
		typedef bool( __thiscall* calc_is_attack_critical_fn )( c_base_combat_weapon* );
		return util::get_virtual< calc_is_attack_critical_fn >( this, 396u )( this );
	}

	inline bool can_fire_random_critical_shot( float crit_chance ) {
		typedef bool( __thiscall* can_fire_random_critical_shot_fn )( c_base_combat_weapon*, float );
		return util::get_virtual< can_fire_random_critical_shot_fn >( this, 426u )( this, crit_chance );
	}

	inline float get_swing_range( c_base_player* plr )
	{
		typedef bool( __thiscall* get_swing_range_fn )( c_base_combat_weapon*, c_base_player* );
		return util::get_virtual< get_swing_range_fn >(this, 451u)(this, plr);
	}

	inline bool is_reloading( ) {
		static auto next_primary_attack_offset = netvar_manager->get_netvar( "CBaseCombatWeapon", "m_flNextPrimaryAttack" );
		bool in_reload = *reinterpret_cast< bool* >( this + (next_primary_attack_offset + 0xc ) );
		int reload_mode = *reinterpret_cast< int* >( this + 0xb28 );
		return ( in_reload || reload_mode != 0 );
	}

	c_tf_weapon_info* get_weapon_info( );
	weapon_data_t get_weapon_data( int weapon_mode = 0 );
	int get_ammo();
	bool is_attacking(c_user_cmd* cmd);
	bool can_shoot( );
	bool can_fire_critical_shot( bool is_headshot );
	float get_weapon_spread( );
	bool is_spread_weapon( );
};

class c_base_object : public c_base_entity {
public:
	NETVAR( m_health, int, "CBaseObject", "m_iHealth" );
	NETVAR( m_max_health, int, "CBaseObject", "m_iMaxHealth" );
	NETVAR( m_upgrade_level, int, "CBaseObject", "m_iUpgradeLevel" );
	NETVAR( m_object_mode, int, "CBaseObject", "m_iObjectMode" );
	NETVAR( m_recharge_time, float, "CObjectTeleporter", "m_flRechargeTime" );
	NETVAR( m_state, int, "CObjectTeleporter", "m_iState" );
	NETVAR( m_mini_building, bool, "CBaseObject", "m_bMiniBuilding" );
	NETVAR( m_builder, int, "CBaseObject", "m_hBuilder" );
	NETVAR( m_placing, bool, "CBaseObject", "m_bPlacing" );

	inline bool is_teleporter_and_recharging( ) {
		return get_client_class( )->m_class_id == class_id_t::CObjectTeleporter && m_state( ) == TELEPORTER_STATE_RECHARGING;
	}

	const char* get_object_name( );
};

class c_tf_ragdoll : public c_base_entity {
public:
	OFFSET( m_gib, bool, 0xc91 );
	OFFSET( m_burning, bool, 0xc92 );
	OFFSET( m_electrocuted, bool, 0xc93 );
	OFFSET( m_dissolving, bool, 0xc95 );
	OFFSET( m_feign_death, bool, 0xc96 );
	OFFSET( m_cloaked, bool, 0xc98 );
	OFFSET( m_become_ash, bool, 0xc99 );
	OFFSET( m_gold_ragdoll, bool, 0xca0 );
	OFFSET( m_ice_ragdoll, bool, 0xca1 );
	OFFSET( m_team, int, 0xcbc );
};

class c_player_resource {
public:
	int get_health( int idx ) {
		static auto offset = netvar_manager->get_netvar( "CPlayerResource", "m_iHealth" );
		return *reinterpret_cast< int* >( reinterpret_cast< uint32_t >( this ) + offset + ( idx * 4 ) );
	}

	int get_damage( int idx ) {
		static auto offset = netvar_manager->get_netvar( "CTFPlayerResource", "m_iDamage" );
		return *reinterpret_cast< int* >( reinterpret_cast< uint32_t >( this ) + offset + ( idx * 4 ) );
	}
};

class c_entity_cache {
public:
	void fill( );
	void reset( );
};

inline c_entity_cache* entity_cache = new c_entity_cache;