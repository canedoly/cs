#include "entities.h"
#include "ctx.h"
#include "../features/engine_prediction/engine_prediction.h"
#include "tf2.h"

bool c_base_entity::is_enemy( ) {
	if ( ctx->m_local_player )
		return ctx->m_local_player->m_team_num( ) != this->m_team_num( );

	return false;
}

c_base_combat_weapon* c_base_player::get_active_weapon( ) {
	if (this && this->m_active_weapon())
		return ctx->m_entity_list->get_client_entity_from_handle(this->m_active_weapon())->as< c_base_combat_weapon >();
	else
		return NULL;
}

vector c_base_player::get_hitbox_position( int hitbox ) {
	if ( auto model = get_model( ) ) {
		if ( auto hdr = ctx->m_model_info->get_studio_model( model ) ) {
			matrix_3x4 bone_matrix[ 128 ];
			if ( setup_bones( bone_matrix, 128, 0x100, ctx->m_globals->m_current_time ) ) {
				if ( auto set = hdr->hitbox_set( m_hitbox_set( ) ) ) {
					if ( const auto& box = set->hitbox( hitbox ) ) {
						vector pos = ( box->bbmin + box->bbmax ) * 0.5f;
						return math::vector_transform( pos, bone_matrix[ box->bone ] );
					}
				}
			}
		}
	}

	return vector( );
}

int c_base_player::get_ammo_count(int ammo_index)
{
	typedef int(__thiscall* fn)(c_base_player*, int);
	static auto pattern = util::find_signature<fn>("client.dll", "55 8B EC 56 8B 75 08 57 8B F9 83 FE FF 75 08 5F 33 C0 5E 5D C2 04 00");
	return pattern(this, ammo_index);
}

vector c_base_player::get_hitbox_position_from_matrix(int hitbox, matrix_3x4* matrix, model_t* model) {
	if (auto hdr = ctx->m_model_info->get_studio_model(model)) {
		if (matrix) {
			if (auto set = hdr->hitbox_set(m_hitbox_set())) {
				if (const auto& box = set->hitbox(hitbox)) {
					vector pos = (box->bbmin + box->bbmax) * 0.5f;
					return math::vector_transform(pos, matrix[box->bone]);
				}
			}
		}
	}

	return vector();
}


bool c_base_player::is_player_on_friend_list( ) {
	using Fn = bool(__stdcall*)(c_base_player*);
	static auto pattern = util::find_signature<void*>("client.dll",
		"55 8B EC 81 EC ? ? ? ? E8 ? ? ? ? 85 C0 74 7E 8B 4D 08 85 C9 74 77 A1 ? ? ? ? 83 78 08 00 74 6C 83 78 0C 00 74 66 A1 ? ? ? ? 83 C1 08 56 8B 30 8D 85 ? ? ? ? 50 8B 01");
	return reinterpret_cast<Fn>(pattern)(this); // fuck you niggers
}

const char* c_base_player::get_weapon_name( ) {

	if (!get_active_weapon()) return "";

	switch ( get_active_weapon( )->m_item_definition_index( ) )
	{
		case Scout_m_ForceANature:
		case Scout_m_FestiveForceANature: { return "FORCE-A-NATURE"; }
		case Scout_m_FestiveScattergun: { return "SCATTERGUN"; }
		case Scout_m_BackcountryBlaster: { return "BACK SCATTER"; }
		case Scout_s_MutatedMilk: { return "MAD MILK"; }
		case Scout_s_TheWinger: { return "WINGER"; }
		case Scout_s_FestiveBonk:
		case Scout_s_BonkAtomicPunch: { return "BONK ATOMIC PUNCH"; }
		case Scout_s_PrettyBoysPocketPistol: { return "POCKET PISTOL"; }
		case Scout_s_CritaCola: { return "CRIT A COLA"; }
		case Scout_t_FestiveBat: { return "BAT"; }
		case Scout_t_FestiveHolyMackerel: {return "HOLY MACKEREL"; }
		case Scout_t_TheAtomizer: { return "ATOMIZER"; }
		case Scout_t_TheCandyCane: { return "CANDY CANE"; }
		case Scout_t_TheFanOWar: { return "FAN O WAR"; }
		case Scout_t_SunonaStick: { return "SUN ON A STICK"; }
		case Scout_t_TheBostonBasher: { return "BOSTON BASHER"; }
		case Scout_t_ThreeRuneBlade: { return "THREE RUNE BLADE"; }
		case Scout_t_TheFreedomStaff: { return "FREEDOM STAFF"; }
		case Scout_t_TheBatOuttaHell: { return "BAT OUTTA HELL"; }
		case Scout_s_Lugermorph:
		case Scout_s_VintageLugermorph: { return "LUGERMORPH"; }
		case Scout_s_TheCAPPER: { return "C.A.P.P.E.R"; }
		case Scout_t_UnarmedCombat: { return "UNARMED COMBAT"; }
		case Scout_t_Batsaber: { return "BATSABER"; }
		case Scout_t_TheHamShank: { return "HAM SHANK"; }
		case Scout_t_TheNecroSmasher: { return "NEGRO SMASHER"; }
		case Scout_t_TheConscientiousObjector: { return "OBJECTOR"; }
		case Scout_t_TheCrossingGuard: { return "CROSSING GUARD"; }
		case Scout_t_TheMemoryMaker: { return "MEMORY MAKER"; }

		case Soldier_m_FestiveRocketLauncher: {return "ROCKET LAUNCHER"; }
		case Soldier_m_RocketJumper: {return "ROCKET JUMPER"; }
		case Soldier_m_TheAirStrike: { return "AIR STRIKE"; }
		case Soldier_m_TheLibertyLauncher: { return "LIBERTY LAUNCHER"; }
		case Soldier_m_TheOriginal: { return "ORIGINAL"; }
		case Soldier_m_FestiveBlackBox:
		case Soldier_m_TheBlackBox: { return "BLACK BOX"; }
		case Soldier_m_TheBeggarsBazooka: { return "BEGGARS BAZOOKA"; }
		case Soldier_s_FestiveShotgun: { return "SHOTGUN"; }
		case Soldier_s_FestiveBuffBanner: { return "BUFF BANNER"; }
		case Soldier_s_TheConcheror: { return "CONCHEROR"; }
		case Soldier_s_TheBattalionsBackup: { return "BATTALIONS BACKUP"; }
		case Soldier_s_PanicAttack: { return "PANIC ATTACK"; }
		case Soldier_t_TheMarketGardener: { return "MARKET GARDENER"; }
		case Soldier_t_TheDisciplinaryAction: { return "DISCIPLINARY ACTION"; }
		case Soldier_t_TheEqualizer: { return "EQUALIZER"; }
		case Soldier_t_ThePainTrain: { return "PAIN TRAIN"; }
		case Soldier_t_TheHalfZatoichi: { return "HALF ZATOICHI"; }

		case Pyro_m_FestiveFlameThrower: { return "FLAME THROWER"; }
		case Pyro_m_ThePhlogistinator: { return "PHLOGISTINATOR"; }
		case Pyro_m_FestiveBackburner:
		case Pyro_m_TheBackburner: { return "BACKBURNER"; }
		case Pyro_m_TheRainblower: { return "RAINBLOWER"; }
		case Pyro_m_TheDegreaser: { return "DEGREASER"; }
		case Pyro_m_NostromoNapalmer: { return "NOSTROMO NAPALMER"; }
		case Pyro_s_FestiveFlareGun: { return "FLARE GUN"; }
		case Pyro_s_TheScorchShot: { return "SCORCH SHOT"; }
		case Pyro_s_TheDetonator: { return "DETONATOR"; }
		case Pyro_s_TheReserveShooter: { return "RESERVE SHOOTER"; }
		case Pyro_t_TheFestiveAxtinguisher:
		case Pyro_t_TheAxtinguisher: { return "AXTINGUISHER"; }
		case Pyro_t_Homewrecker: { return "HOMEWRECKER"; }
		case Pyro_t_ThePowerjack: { return "POWERJACK"; }
		case Pyro_t_TheBackScratcher: { return "BACK SCRATCHER"; }
		case Pyro_t_TheThirdDegree: { return "THIRD DEGREE"; }
		case Pyro_t_ThePostalPummeler: { return "POSTAL PUMMELER"; }
		case Pyro_t_PrinnyMachete: { return "PRINNY MACHETE"; }
		case Pyro_t_SharpenedVolcanoFragment: { return "VOLCANO FRAGMENT"; }
		case Pyro_t_TheMaul: { return "MAUL"; }
		case Pyro_t_TheLollichop: { return "LOLLICHOP"; }

		case Demoman_m_FestiveGrenadeLauncher: { return "GRENADE LAUNCHER"; }
		case Demoman_m_TheIronBomber: { return "IRON BOMBER"; }
		case Demoman_m_TheLochnLoad: {return "LOCH N LOAD"; }
		case Demoman_s_FestiveStickybombLauncher: { return "STICKYBOMB LAUNCHER"; }
		case Demoman_s_StickyJumper: {return "STICKY JUMPER"; }
		case Demoman_s_TheQuickiebombLauncher: { return "QUICKIEBOMB LAUNCHER"; }
		case Demoman_s_TheScottishResistance: { return "SCOTTISH RESISTANCE"; }
		case Demoman_t_HorselessHeadlessHorsemannsHeadtaker: { return "HORSEMANNS HEADTAKER"; }
		case Demoman_t_TheScottishHandshake: { return "SCOTTISH HANDSHAKE"; }
		case Demoman_t_FestiveEyelander:
		case Demoman_t_TheEyelander: { return "EYELANDER"; }
		case Demoman_t_TheScotsmansSkullcutter: { return "SCOTSMANS SKULLCUTTER"; }
		case Demoman_t_ThePersianPersuader: { return "PERSIAN PERSUADER"; }
		case Demoman_t_NessiesNineIron: { return "NESSIES NINE IRON"; }
		case Demoman_t_TheClaidheamhMor: { return "CLAIDHEAMH MOR"; }

		case Heavy_m_IronCurtain: { return "IRON CURTAIN"; }
		case Heavy_m_FestiveMinigun: { return "MINIGUN"; }
		case Heavy_m_Tomislav: { return "TOMISLAV"; }
		case Heavy_m_TheBrassBeast: { return "BRASS BEAST"; }
		case Heavy_m_Natascha: { return "NATASCHA"; }
		case Heavy_m_TheHuoLongHeaterG:
		case Heavy_m_TheHuoLongHeater: { return "HUO-LONG HEATER"; }
		case Heavy_s_TheFamilyBusiness: { return "FAMILY BUSINESS"; }
		case Heavy_s_FestiveSandvich:
		case Heavy_s_RoboSandvich:
		case Heavy_s_Sandvich: { return "SANDVICH"; }
		case Heavy_s_Fishcake: { return "FISHCAKE"; }
		case Heavy_s_SecondBanana: { return "BANANA"; }
		case Heavy_s_TheDalokohsBar: { return "CHOCOLATE"; }
		case Heavy_s_TheBuffaloSteakSandvich: { return "STEAK"; }
		case Heavy_t_FistsofSteel: {return "FISTS OF STEEL"; }
		case Heavy_t_TheHolidayPunch: { return "HOLIDAY PUNCH"; }
		case Heavy_t_WarriorsSpirit: { return "WARRIORS SPIRIT"; }
		case Heavy_t_TheEvictionNotice: { return "EVICTION NOTICE"; }
		case Heavy_t_TheKillingGlovesofBoxing: { return "KILLING GLOVES OF BOXING"; }
		case Heavy_t_ApocoFists: { return "APOCO-FISTS"; }
		case Heavy_t_FestiveGlovesofRunningUrgently:
		case Heavy_t_GlovesofRunningUrgently: { return "GLOVES OF RUNNING URGENTLY"; }
		case Heavy_t_TheBreadBite: { return "BREAD BITE"; }

		case Engi_m_FestiveFrontierJustice: { return "FRONTIER JUSTICE"; }
		case Engi_m_TheWidowmaker: { return "WIDOWMAKER"; }
		case Engi_s_TheGigarCounter:
		case Engi_s_FestiveWrangler: { return "WRANGLER"; }
		case Engi_s_TheShortCircuit: { return "SHORT CIRCUIT"; }
		case Engi_t_FestiveWrench: { return "WRENCH"; }
		case Engi_t_GoldenWrench: { return "GOLDEN WRENCH"; }
		case Engi_t_TheGunslinger: { return "GUNSLINGER"; }
		case Engi_t_TheJag: { return "JAG"; }
		case Engi_t_TheEurekaEffect: { return "EUREKA EFFECT"; }
		case Engi_t_TheSouthernHospitality: { return "SOUTHERN HOSPITALITY"; }

		case Medic_m_FestiveCrusadersCrossbow: { return "CRUSADERS CROSSBOW"; }
		case Medic_m_TheOverdose: { return "OVERDOSE"; }
		case Medic_m_TheBlutsauger: { return "BLUTSAUGER"; }
		case Medic_s_FestiveMediGun: { return "MEDIGUN"; }
		case Medic_s_TheQuickFix: { return "QUICK FIX"; }
		case Medic_s_TheKritzkrieg: { return "KRITZKRIEG"; }
		case Medic_s_TheVaccinator: { return "VACCINATOR"; }
		case Medic_t_FestiveBonesaw: { return "BONESAW"; }
		case Medic_t_FestiveUbersaw:
		case Medic_t_TheUbersaw: { return "UBERSAW"; }
		case Medic_t_TheVitaSaw: { return "VITASAW"; }
		case Medic_t_TheSolemnVow: { return "SOLEMN VOW"; }
		case Medic_t_Amputator: { return "AMPUTATOR"; }

		case Sniper_m_FestiveSniperRifle: { return "SNIPER RIFLE"; }
		case Sniper_m_FestiveHuntsman:
		case Sniper_m_TheHuntsman: { return "HUNTSMAN"; }
		case Sniper_m_TheMachina: { return "MACHINA"; }
		case Sniper_m_TheAWPerHand: { return "AWPER HAND"; }
		case Sniper_m_TheHitmansHeatmaker: { return "HITMANS HEATMAKER"; }
		case Sniper_m_TheSydneySleeper: { return "SYDNEY SLEEPER"; }
		case Sniper_m_ShootingStar: { return "SHOOTING STAR"; }
		case Sniper_s_FestiveJarate: { return "JARATE"; }
		case Sniper_s_TheSelfAwareBeautyMark: { return "JARATE"; }
		case Sniper_s_FestiveSMG: { return "SMG"; }
		case Sniper_t_TheBushwacka: { return "BUSHWACKA"; }
		case Sniper_t_KukriR:
		case Sniper_t_Kukri: { return "KUKRI"; }
		case Sniper_t_TheShahanshah: { return "SHAHANSHAH"; }
		case Sniper_t_TheTribalmansShiv: { return "TRIBALMANS SHIV"; }

		case Spy_m_FestiveRevolver: { return "REVOLVER"; }
		case Spy_m_FestiveAmbassador:
		case Spy_m_TheAmbassador: { return "AMBASSADOR"; }
		case Spy_m_BigKill: { return "BIG KILL"; }
		case Spy_m_TheDiamondback: { return "DIAMONDBACK"; }
		case Spy_m_TheEnforcer: { return "ENFORCER"; }
		case Spy_m_LEtranger: { return "LETRANGER"; }
		case Spy_s_Sapper:
		case Spy_s_SapperR:
		case Spy_s_FestiveSapper: { return "SAPPER"; }
		case Spy_s_TheRedTapeRecorder:
		case Spy_s_TheRedTapeRecorderG: { return "RED TAPE RECORDER"; }
		case Spy_s_TheApSapG: { return "AP-SAP"; }
		case Spy_s_TheSnackAttack: { return "SNACK ATTACK"; }
		case Spy_t_FestiveKnife: { return "KNIFE"; }
		case Spy_t_ConniversKunai: { return "KUNAI"; }
		case Spy_t_YourEternalReward: { return "YOUR ETERNAL REWARD"; }
		case Spy_t_TheBigEarner: { return "BIG EARNER"; }
		case Spy_t_TheSpycicle: { return "SPYCICLE"; }
		case Spy_t_TheSharpDresser: { return "SHARP DRESSER"; }
		case Spy_t_TheWangaPrick: { return "WANGA PRICK"; }
		case Spy_t_TheBlackRose: { return "BLACK ROSE"; }

		case Heavy_m_Deflector_mvm: { return "DEFLECTOR"; }
		case Misc_t_FryingPan: { return "FRYING PAN"; }
		case Misc_t_GoldFryingPan: { return "GOLDEN FRYING PAN"; }
		case Misc_t_Saxxy: { return "SAXXY"; }

		default:
		{
			switch ( get_active_weapon( )->get_weapon_id( ) )
			{
				//scout
				case TF_WEAPON_SCATTERGUN: { return "SCATTERGUN"; }
				case TF_WEAPON_HANDGUN_SCOUT_PRIMARY: { return "SHORTSTOP"; }
				case TF_WEAPON_HANDGUN_SCOUT_SECONDARY: {return "PISTOL"; }
				case TF_WEAPON_SODA_POPPER: { return "SODA POPPER"; }
				case TF_WEAPON_PEP_BRAWLER_BLASTER: { return "BABY FACES BLASTER"; }
				case TF_WEAPON_PISTOL_SCOUT: { return "PISTOL"; }
				case TF_WEAPON_JAR_MILK: { return "MAD MILK"; }
				case TF_WEAPON_CLEAVER: { return "CLEAVER"; }
				case TF_WEAPON_BAT: { return "BAT"; }
				case TF_WEAPON_BAT_WOOD: { return "SANDMAN"; }
				case TF_WEAPON_BAT_FISH: { return "HOLY MACKEREL"; }
				case TF_WEAPON_BAT_GIFTWRAP: { return "WRAP ASSASSIN"; }

										   //soldier
				case TF_WEAPON_ROCKETLAUNCHER: { return "ROCKET LAUNCHER"; }
				case TF_WEAPON_ROCKETLAUNCHER_DIRECTHIT: { return "DIRECT HIT"; }
				case TF_WEAPON_PARTICLE_CANNON: { return "COW MANGLER 5000"; }
				case TF_WEAPON_SHOTGUN_SOLDIER: { return "SHOTGUN"; }
				case TF_WEAPON_BUFF_ITEM: { return "BUFF BANNER"; }
				case TF_WEAPON_RAYGUN: { return "RIGHTEOUS BISON"; }
				case TF_WEAPON_SHOVEL: { return "SHOVEL"; }

									 //pyro
				case TF_WEAPON_FLAMETHROWER: { return "FLAME THROWER"; }
				case TF_WEAPON_FLAME_BALL: { return "DRAGONS FURY"; }
				case TF_WEAPON_SHOTGUN_PYRO: { return "SHOTGUN"; }
				case TF_WEAPON_FLAREGUN: { return "FLAREGUN"; }
				case TF_WEAPON_FLAREGUN_REVENGE: { return "MANMELTER"; }
				case TF_WEAPON_JAR_GAS: { return "GAS PASSER"; }
				case TF_WEAPON_ROCKETPACK: { return "THERMAL THRUSTER"; }
				case TF_WEAPON_FIREAXE: { return "FIRE AXE"; }
				case TF_WEAPON_BREAKABLE_SIGN: {return "NEON ANNIHILATOR"; }
				case TF_WEAPON_SLAP: {return "HOT HAND"; }

								   //demoman
				case TF_WEAPON_GRENADELAUNCHER: { return "GRENADE LAUNCHER"; }
				case TF_WEAPON_PIPEBOMBLAUNCHER: { return "STICKYBOMB LAUNCHER"; }
				case TF_WEAPON_CANNON: {return "LOOSE CANNON"; }
				case TF_WEAPON_BOTTLE: { return "BOTTLE"; }
				case TF_WEAPON_SWORD: { return "SWORD"; }
				case TF_WEAPON_STICKBOMB: { return "ULLAPOOL CABER"; }

										//heavy
				case TF_WEAPON_MINIGUN: { return "MINIGUN"; }
				case TF_WEAPON_SHOTGUN_HWG: { return "SHOTGUN"; }
				case TF_WEAPON_LUNCHBOX: { return "LUNCHBOX"; }
				case TF_WEAPON_FISTS: { return "FISTS"; }

									//engineer
				case TF_WEAPON_SHOTGUN_PRIMARY: { return "SHOTGUN"; }
				case TF_WEAPON_SHOTGUN_BUILDING_RESCUE: { return "RESCUE RANGER"; }
				case TF_WEAPON_SENTRY_REVENGE: { return "FRONTIER JUSTICE"; }
				case TF_WEAPON_DRG_POMSON: { return "POMSON 6000"; }
				case TF_WEAPON_PISTOL: { return "PISTOL"; }
				case TF_WEAPON_LASER_POINTER: { return "WRANGLER"; }
				case TF_WEAPON_MECHANICAL_ARM: { return "MECHANICAL ARM"; }
				case TF_WEAPON_WRENCH: { return "WRENCH"; }
				case TF_WEAPON_PDA_ENGINEER_DESTROY: { return "DESTRUCTION PDA"; }
				case TF_WEAPON_PDA_ENGINEER_BUILD: { return "CONSTRUCTION PDA"; }
				case TF_WEAPON_BUILDER: { return "TOOLBOX"; }

									  //medic
				case TF_WEAPON_SYRINGEGUN_MEDIC: { return "SYRINGE GUN"; }
				case TF_WEAPON_CROSSBOW: { return "CROSSBOW"; }
				case TF_WEAPON_MEDIGUN: { return "MEDIGUN"; }
				case TF_WEAPON_BONESAW: { return "BONESAW"; }

									  //sniper
				case TF_WEAPON_SNIPERRIFLE: { return "SNIPER RIFLE"; }
				case TF_WEAPON_COMPOUND_BOW: { return "COMPOUND BOW"; }
				case TF_WEAPON_SNIPERRIFLE_DECAP: { return "BAZAAR BARGAIN"; }
				case TF_WEAPON_SNIPERRIFLE_CLASSIC: { return "CLASSIC"; }
				case TF_WEAPON_SMG: { return "SMG"; }
				case TF_WEAPON_CHARGED_SMG: { return "CLEANERS CARBINE"; }
				case TF_WEAPON_JAR: { return "JARATE"; }
				case TF_WEAPON_CLUB: { return "CLUB"; }

								   //spy
				case TF_WEAPON_REVOLVER: { return "REVOLVER"; }
				case TF_WEAPON_PDA_SPY_BUILD: { return "SAPPER"; }
				case TF_WEAPON_KNIFE: { return "KNIFE"; }
				case TF_WEAPON_PDA_SPY: { return "DISGUISE KIT"; }
				case TF_WEAPON_INVIS: { return "INVIS WATCH"; }

				case TF_WEAPON_GRAPPLINGHOOK: { return "GRAPPLING HOOK"; }

				default: break;
			}
		}
	}

	return "";
}

const char* c_base_object::get_object_name( ) {
	switch ( get_client_class( )->m_class_id ) {
		case class_id_t::CObjectSentrygun:
			if ( m_mini_building( ) )
				return "Mini Sentry";
			else
				return "Sentry";

		case class_id_t::CObjectDispenser:
			return "Dispenser";

		case class_id_t::CObjectTeleporter:
			if ( m_object_mode( ) )
				return "Teleporter Exit";
			else
				return "Teleporter Entrance";

		default: return "";
	}
}

const char* c_base_entity::get_projectile_name( ) {
	switch ( get_client_class( )->m_class_id ) {
		case class_id_t::CTFProjectile_Rocket:
		case class_id_t::CTFProjectile_SentryRocket:
			return "Rocket";
		
		case class_id_t::CTFGrenadePipebombProjectile:
			if ( m_pipebomb_type( ) == TYPE_STICKY )
				return "Sticky";
			else
				return "Pipebomb";
		
		case class_id_t::CTFProjectile_Jar:
		case class_id_t::CTFProjectile_ThrowableRepel:
			return "Jarate";
		
		case class_id_t::CTFProjectile_JarGas:
			return "Gas Passer";
		
		case class_id_t::CTFProjectile_JarMilk:
		case class_id_t::CTFProjectile_ThrowableBreadMonster:
			return "Mad Milk";
		
		case class_id_t::CTFProjectile_Arrow:
			return "Arrow";
		
		case class_id_t::CTFProjectile_Flare:
			return "Flare";
		
		case class_id_t::CTFProjectile_Cleaver:
			return "Cleaver";
		
		case class_id_t::CTFProjectile_HealingBolt:
			return "Healing Bolt";
		
		case class_id_t::CTFProjectile_EnergyRing:
			return "Energy Ring";
		
		case class_id_t::CTFProjectile_EnergyBall:
			return "Energy Ball";
		
		case class_id_t::CTFStunBall:
			return "Baseball";
		
		case class_id_t::CTFBall_Ornament:
			return "Ornament Ball";
		
		default: return "";
	}
}

c_tf_weapon_info* c_base_combat_weapon::get_weapon_info( ) {
	typedef c_tf_weapon_info* ( __thiscall* fn )( c_base_combat_weapon* );
	static auto function = util::find_signature< fn >( "client.dll", "0F B7 81 DA 0A 00 00 50 E8 ? ? ? ? 83 C4 04 C3" );
	return function( this );
}

weapon_data_t c_base_combat_weapon::get_weapon_data( int weapon_mode ) {
	return get_weapon_info( )->m_weapon_data[ weapon_mode ];
}

int c_base_combat_weapon::get_ammo()
{
	if (!ctx->m_local_player)
		return -1;

	if (get_slot() == 2)
		return 1;

	if (m_clip1() <= -1)
		return ctx->m_local_player->get_ammo_count(m_primary_ammo_type());

	return m_clip1();
}

bool c_base_combat_weapon::is_attacking(c_user_cmd* cmd)
{
	if (!ctx->m_local_player || !ctx->m_local_player->is_alive() || !this )
		return false;

	if (m_item_definition_index() == Soldier_m_TheBeggarsBazooka)
	{
		static bool loading = false;

		if (this->m_clip1() > 0)
			loading = true;

		if (!(cmd->m_buttons & IN_ATTACK) && loading) {
			loading = false;
			return true;
		}
	}
	else
	{
		if (get_weapon_id() == TF_WEAPON_COMPOUND_BOW || ((ctx->m_local_player->m_player_class() == CLASS_DEMOMAN && get_slot() == 1) || get_weapon_id() == TF_WEAPON_STICKY_BALL_LAUNCHER))
		{
			static bool charging = false;

			if (m_charge_begin_time() > 0.0f)
				charging = true;

			if (!(cmd->m_buttons & IN_ATTACK) && charging) {
				charging = false;
				return true;
			}
		}
	}

	if (get_slot() == 2 && ctx->m_local_player->m_player_class() != CLASS_SPY)
			return fabs(ctx->m_local_weapon->get_smack_time() - ctx->m_globals->m_current_time) < TICK_INTERVAL * 2.0f;

	bool shooting = cmd->m_buttons & IN_ATTACK && can_shoot();
	return shooting;
}

bool c_base_combat_weapon::can_shoot( ) {

	if (!ctx->m_local_player || !ctx->m_local_player->is_alive() || ctx->m_local_player->is_taunting() || ctx->m_local_player->is_cloaked())
		return false;

	// C_TFWeaponFlameBall::PrimaryAttack
	if ( get_weapon_id( ) == TF_WEAPON_FLAME_BALL )
		return ( ctx->m_local_player->m_tank_pressure( ) >= 100.0f );

	if (get_ammo() > 0 && is_reloading())
	{
		return true;
	}

	return m_next_primary_attack() < TICKS_TO_TIME(ctx->m_local_player->m_tick_base());
}

bool c_base_combat_weapon::can_fire_critical_shot( bool is_headshot = false ) {
	typedef bool( __thiscall* can_fire_critical_shot_fn )( c_base_combat_weapon*, bool, c_base_player* );
	bool result = false;

	if ( ctx->m_local_player ) {
		const int old_fov = ctx->m_local_player->m_fov( );
		ctx->m_local_player->m_fov( ) = 70;
		result = util::get_virtual< can_fire_critical_shot_fn >( this, 425u )( this, is_headshot, nullptr );
		ctx->m_local_player->m_fov( ) = old_fov;
	}

	return result;
}

void c_base_entity::set_next_think( float time, const char* context ) {
	typedef void( __thiscall* set_next_think_fn )(void*, float, const char*);
	static auto function = util::find_signature< set_next_think_fn >( "client.dll", "55 8B EC F3 0F 10 45 ? 0F 2E 05 ? ? ? ? 53" );
	return function( this, time, context );
}

int c_base_entity::get_next_think( const char* context ) {
	typedef int( __thiscall* get_next_think_fn )( void*, const char* );
	static auto function = util::find_signature< get_next_think_fn >( "client.dll", "55 8B EC 8B 45 ? 56 8B F1 85 C0 75 ? 8B 86" );
	return function( this, context );
}

bool c_base_entity::physics_run_tick( int think_method = 0 ) {
	typedef bool( __thiscall* physics_run_tick_fn )( void*, int );
	static auto function = util::find_signature< physics_run_tick_fn >( "client.dll", "55 8B EC 53 8B D9 56 57 8B 83 ? ? ? ? C1" );
	return function( this, think_method );
}

// todo: get non-e8 sig
// FIXED remove when you see this
vector c_base_entity::estimate_abs_velocity( ) {
	typedef void( __thiscall* physics_run_tick_fn )( c_base_entity*, vector& );
	static auto function = util::find_signature< physics_run_tick_fn >( "client.dll", "55 8B EC 83 EC ? 56 8B F1 E8 ? ? ? ? 3B" );
	vector v;
	function( this, v );
	return v;
}

c_base_entity* c_base_entity::get_move_child( ) {
	return ctx->m_entity_list->get_client_entity( *reinterpret_cast< int* >( reinterpret_cast< DWORD >( this ) + 0x1B0 ) & 0xFFF )->as<c_base_entity>( );
}

c_base_entity* c_base_entity::next_move_peer( ) {
	return ctx->m_entity_list->get_client_entity( *reinterpret_cast< int* >( reinterpret_cast<DWORD>( this ) + 0x1B4 ) & 0xFFF )->as<c_base_entity>( );
}

bool c_base_entity::is_entity_on_screen( ) {
	if ( ctx->m_local_player->get_world_space_center( ).dist_to( get_world_space_center( ) ) > 200.f ) {
		vector screen = {};
		if ( tf2::world_to_screen( get_world_space_center( ), screen ) ) {
			if ( screen.m_x < -250 || screen.m_x > ctx->m_screen_width + 250
				 || screen.m_y < -250 || screen.m_y > ctx->m_screen_height + 250 )
				return false;
		}
		else return false;
	}

	return true;
}

float c_base_combat_weapon::get_weapon_spread( ) {
	static auto fn = reinterpret_cast< float( __thiscall* )( decltype( this ) ) >( util::find_signature<DWORD>( "client.dll", "55 8B EC 83 EC 08 56 8B F1 57 6A 01 6A 00 8B 96 ? ? ? ? 8B 86 ? ? ? ? C1 E2 06 56 68 ? ? ? ? 51" ) );
	return fn( this );
}

bool c_base_combat_weapon::is_spread_weapon( ) {
	if ( m_item_definition_index( ) == Scout_s_PrettyBoysPocketPistol )
		return true;

	switch ( get_weapon_id( ) ) {
		case TF_WEAPON_PISTOL:
		case TF_WEAPON_PISTOL_SCOUT:
		case TF_WEAPON_MINIGUN:
		case TF_WEAPON_SMG: { return true; }
		default: { return false; }
	}

	return false;
}

bool c_base_player::is_local_player( ) {
	return this == ctx->m_local_player;
}

void c_base_player::anim_state_update( float yaw, float pitch ) {
	static auto FN = reinterpret_cast< void( __thiscall* )( void*, float, float ) >( ctx->m_anim_state_update );
	FN( this->m_player_anim_state( ), yaw, pitch );
}

void c_base_player::update_client_side_animations( ) {
	static auto FN = reinterpret_cast< void( __thiscall* )( void* ) >( ctx->m_update_client_side_animations );
	FN( this );
}

bool i_client_entity::is_health( ) {
	switch ( fnv::hash( ctx->m_model_info->get_model_name( get_model( ) ) ) ) {
		case fnv::hash( TF_MEDKIT_SMALL_BDAY ):
		case fnv::hash( TF_MEDKIT_MEDIUM_BDAY ):
		case fnv::hash( TF_MEDKIT_LARGE_BDAY ):
		case fnv::hash( TF_MEDKIT_SMALL_HALLOWEEN ):
		case fnv::hash( TF_MEDKIT_MEDIUM_HALLOWEEN ):
		case fnv::hash( TF_MEDKIT_LARGE_HALLOWEEN ):
		case fnv::hash( LUNCHBOX_DROP_MODEL ):
		case fnv::hash( LUNCHBOX_STEAK_DROP_MODEL ):
		case fnv::hash( LUNCHBOX_ROBOT_DROP_MODEL ):
		case fnv::hash( LUNCHBOX_FESTIVE_DROP_MODEL ):
		case fnv::hash( TF_MEDKIT_SMALL ):
		case fnv::hash( TF_MEDKIT_MEDIUM ):
		case fnv::hash( TF_MEDKIT_LARGE ): { return true; }
		default: { return false; }
	}
}

bool i_client_entity::is_ammo( ) {
	if ( get_client_class( )->m_class_id == class_id_t::CTFAmmoPack ) {
		return true;
	}
	else {
		switch ( fnv::hash( ctx->m_model_info->get_model_name( get_model( ) ) ) ) {
			case fnv::hash( TF_AMMOPACK_SMALL_BDAY ):
			case fnv::hash( TF_AMMOPACK_MEDIUM_BDAY ):
			case fnv::hash( TF_AMMOPACK_LARGE_BDAY ):
			case fnv::hash( TF_AMMOPACK_SMALL ):
			case fnv::hash( TF_AMMOPACK_MEDIUM ):
			case fnv::hash( TF_AMMOPACK_LARGE ): { return true; }
			default: { return false; }
		}
	}
}

void c_entity_cache::fill( ) {
	if ( !ctx->m_local_player ) {
		ctx->m_local_player = ctx->m_entity_list->get_client_entity( ctx->m_engine_client->get_local_player( ) )->as< c_base_player >( );
	}
	ctx->m_local_weapon = ctx->m_entity_list->get_client_entity_from_handle( ctx->m_local_player->m_active_weapon( ) )->as< c_base_combat_weapon >( );
	
	for ( int i = 1; i < ctx->m_entity_list->get_highest_entity_index( ); i++ ) {
		const auto& entity = ctx->m_entity_list->get_client_entity( i )->as<c_base_entity>( );
		if ( !entity )
			continue;

		auto class_id = entity->get_client_class( )->m_class_id;

		switch ( class_id ) {
			case class_id_t::CTFPlayer: {
				/*if ( entity == ctx->m_local_player )
					break;*/

				ctx->players.push_back( entity->as<c_base_player>( ) );
				ctx->aimbot_entities.push_back( entity );
				break;
			}

			case class_id_t::CObjectSentrygun:
			case class_id_t::CObjectDispenser:
			case class_id_t::CObjectTeleporter: {
				if ( entity->is_dormant( ) )
					break;

				ctx->buildings.push_back( entity->as<c_base_object>( ) );
				ctx->aimbot_entities.push_back( entity );
				break;
			}

			case class_id_t::CTFAmmoPack: {
				if ( entity->is_dormant( ) )
					break;

				ctx->ammopacks.push_back( entity );
				break;
			}

			case class_id_t::CBaseAnimating: {
				if ( entity->is_dormant( ) )
					break;

				if ( entity->is_health( ) )
					ctx->healthpacks.push_back( entity );

				if ( entity->is_ammo( ) )
					ctx->ammopacks.push_back( entity );
				break;
			}

			case class_id_t::CTFProjectile_Rocket:
			case class_id_t::CTFGrenadePipebombProjectile:
			case class_id_t::CTFProjectile_Jar:
			case class_id_t::CTFProjectile_JarGas:
			case class_id_t::CTFProjectile_JarMilk:
			case class_id_t::CTFProjectile_Arrow:
			case class_id_t::CTFProjectile_SentryRocket:
			case class_id_t::CTFProjectile_Flare:
			case class_id_t::CTFProjectile_Cleaver:
			case class_id_t::CTFProjectile_HealingBolt:
			case class_id_t::CTFProjectile_EnergyRing:
			case class_id_t::CTFProjectile_EnergyBall:
			case class_id_t::CTFProjectile_ThrowableBreadMonster:
			case class_id_t::CTFStunBall:
			case class_id_t::CTFBall_Ornament: {
				if ( entity->is_dormant( ) )
					break;

				ctx->projectiles.push_back( entity );
				break;
			}

			case class_id_t::CTFPlayerResource: {
				ctx->m_player_resource = entity->as< c_player_resource >( );
				break;
			}

			default: break;
		}
	}
}

void c_entity_cache::reset( ) {
	ctx->m_local_player = nullptr;
	ctx->m_local_weapon = nullptr;
	ctx->m_player_resource = nullptr;

	ctx->players.clear( );
	ctx->buildings.clear( );
	ctx->aimbot_entities.clear( );
	ctx->healthpacks.clear( );
	ctx->ammopacks.clear( );
	ctx->projectiles.clear( );
}