#pragma once
#include "bitbuf.h"
#include "checksum_md5.h"
#include "util.h"

#define IN_ATTACK		( 1 << 0 )
#define IN_JUMP			( 1 << 1 )
#define IN_DUCK			( 1 << 2 )
#define IN_FORWARD		( 1 << 3 )
#define IN_BACK			( 1 << 4 )
#define IN_USE			( 1 << 5 )
#define IN_CANCEL		( 1 << 6 )
#define IN_LEFT			( 1 << 7 )
#define IN_RIGHT		( 1 << 8 )
#define IN_MOVELEFT		( 1 << 9 )
#define IN_MOVERIGHT	( 1 << 10 )
#define IN_ATTACK2		( 1 << 11 )
#define IN_RUN			( 1 << 12 )
#define IN_RELOAD		( 1 << 13 )
#define IN_ALT1			( 1 << 14 )
#define IN_ALT2			( 1 << 15 )
#define IN_SCORE		( 1 << 16 )
#define IN_SPEED		( 1 << 17 )
#define IN_WALK			( 1 << 18 )
#define IN_ZOOM			( 1 << 19 )
#define IN_WEAPON1		( 1 << 20 )
#define IN_WEAPON2		( 1 << 21 )
#define IN_BULLRUSH		( 1 << 22 )
#define IN_GRENADE1		( 1 << 23 )
#define IN_GRENADE2		( 1 << 24 )
#define	IN_ATTACK3		( 1 << 25 )

#define	FL_ONGROUND		( 1 << 0 )
#define FL_DUCKING		( 1 << 1 )
#define	FL_WATERJUMP	( 1 << 2 )
#define FL_ONTRAIN		( 1 << 3 )
#define FL_INRAIN		( 1 << 4 )
#define FL_FROZEN		( 1 << 5 )
#define FL_ATCONTROLS	( 1 << 6 )
#define	FL_CLIENT		( 1 << 7 )
#define FL_FAKECLIENT	( 1 << 8 )
#define	FL_INWATER		( 1 << 9 )
#define	FL_CONVEYOR		( 1 << 12)

#define	LIFE_ALIVE 0
#define	LIFE_DYING 1
#define	LIFE_DEAD 2
#define LIFE_RESPAWNABLE 3
#define LIFE_DISCARDBODY 4

#define TF_TEAM_SPECTATOR 1
#define TF_TEAM_RED 2
#define TF_TEAM_BLU 3
#define TF_TEAM_PVE_INVADERS TF_TEAM_BLU
#define TF_TEAM_PVE_DEFENDERS TF_TEAM_RED
#define TF_TEAM_PVE_INVADERS_GIANTS 4

#define NUM_NEW_COMMAND_BITS		4
#define NUM_BACKUP_COMMAND_BITS		3

#define MAX_NEW_COMMANDS			((1 << NUM_NEW_COMMAND_BITS)-1)
#define MAX_BACKUP_COMMANDS			((1 << NUM_BACKUP_COMMAND_BITS)-1)

#define DMG_GENERIC			0
#define DMG_CRUSH			( 1 << 0 )
#define DMG_BULLET			( 1 << 1 )
#define DMG_SLASH			( 1 << 2 )
#define DMG_BURN			( 1 << 3 )
#define DMG_VEHICLE			( 1 << 4 )
#define DMG_FALL			( 1 << 5 )
#define DMG_BLAST			( 1 << 6 )
#define DMG_CLUB			( 1 << 7 )
#define DMG_SHOCK			( 1 << 8 )
#define DMG_SONIC			( 1 << 9 )
#define DMG_ENERGYBEAM		( 1 << 10 )
#define DMG_PREVENT_PHYSICS_FORCE		( 1 << 11 )
#define DMG_NEVERGIB		( 1 << 12 )
#define DMG_ALWAYSGIB		( 1 << 13 )
#define DMG_DROWN			( 1 << 14 )


#define DMG_PARALYZE		( 1 << 15 )
#define DMG_NERVEGAS		( 1 << 16 )
#define DMG_POISON			( 1 << 17 )
#define DMG_RADIATION		( 1 << 18 )
#define DMG_DROWNRECOVER	( 1 << 19 )
#define DMG_ACID			( 1 << 20 )
#define DMG_SLOWBURN		( 1 << 21 )

#define DMG_REMOVENORAGDOLL	( 1 << 22 )

#define DMG_PHYSGUN			( 1 << 23 )
#define DMG_PLASMA			( 1 << 24 )
#define DMG_AIRBOAT			( 1 << 25 )
#define DMG_DISSOLVE		( 1 << 26 )
#define DMG_BLAST_SURFACE	( 1 << 27 )
#define DMG_DIRECT			( 1 << 28 )
#define DMG_BUCKSHOT		( 1 << 29 )
#define DMG_LASTGENERICFLAG	DMG_BUCKSHOT

#define DMG_USE_HITLOCATIONS					( DMG_AIRBOAT )
#define DMG_HALF_FALLOFF						( DMG_RADIATION )
#define DMG_CRITICAL							( DMG_ACID )
#define DMG_RADIUS_MAX							( DMG_ENERGYBEAM )
#define DMG_IGNITE								( DMG_PLASMA )
#define DMG_USEDISTANCEMOD						( DMG_SLOWBURN )
#define DMG_NOCLOSEDISTANCEMOD					( DMG_POISON )
#define DMG_FROM_OTHER_SAPPER					( DMG_IGNITE )
#define DMG_MELEE								( DMG_BLAST_SURFACE )
#define DMG_DONT_COUNT_DAMAGE_TOWARDS_CRIT_RATE	( DMG_DISSOLVE )
#define DMG_IGNORE_MAXHEALTH	( DMG_BULLET )
#define DMG_IGNORE_DEBUFFS		( DMG_SLASH )

#define CONTENTS_EMPTY 0 
#define CONTENTS_SOLID 0x1  
#define CONTENTS_WINDOW 0x2 
#define CONTENTS_AUX 0x4
#define CONTENTS_GRATE 0x8 
#define CONTENTS_SLIME 0x10
#define CONTENTS_WATER 0x20
#define CONTENTS_BLOCKLOS 0x40 
#define CONTENTS_OPAQUE 0x80   
#define LAST_VISIBLE_CONTENTS 0x80
#define ALL_VISIBLE_CONTENTS ( LAST_VISIBLE_CONTENTS | ( LAST_VISIBLE_CONTENTS - 1 ) )
#define ALL_VISIBLE_CONTENTS ( LAST_VISIBLE_CONTENTS | ( LAST_VISIBLE_CONTENTS - 1 ) )
#define CONTENTS_TESTFOGVOLUME 0x100
#define CONTENTS_UNUSED 0x200
#define CONTENTS_UNUSED6 0x400
#define CONTENTS_TEAM1 0x800 
#define CONTENTS_TEAM2 0x1000
#define CONTENTS_IGNORE_NODRAW_OPAQUE 0x2000
#define CONTENTS_MOVEABLE 0x4000
#define CONTENTS_AREAPORTAL 0x8000
#define CONTENTS_PLAYERCLIP 0x10000
#define CONTENTS_MONSTERCLIP 0x20000
#define CONTENTS_CURRENT_0 0x40000
#define CONTENTS_CURRENT_90 0x80000
#define CONTENTS_CURRENT_180 0x100000
#define CONTENTS_CURRENT_270 0x200000
#define CONTENTS_CURRENT_UP 0x400000
#define CONTENTS_CURRENT_DOWN 0x800000
#define CONTENTS_ORIGIN 0x1000000
#define CONTENTS_MONSTER 0x2000000
#define CONTENTS_DEBRIS 0x4000000
#define CONTENTS_DETAIL 0x8000000	
#define CONTENTS_TRANSLUCENT 0x10000000 
#define CONTENTS_LADDER 0x20000000
#define CONTENTS_HITBOX 0x40000000
#define MASK_ALL ( 0xFFFFFFFF )
#define MASK_SOLID ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE )
#define MASK_PLAYERSOLID ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_PLAYERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE )
#define MASK_NPCSOLID ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE )
#define MASK_WATER ( CONTENTS_WATER | CONTENTS_MOVEABLE | CONTENTS_SLIME )
#define MASK_OPAQUE ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_OPAQUE )
#define MASK_OPAQUE_AND_NPCS ( MASK_OPAQUE | CONTENTS_MONSTER )
#define MASK_BLOCKLOS ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_BLOCKLOS )
#define MASK_BLOCKLOS_AND_NPCS ( MASK_BLOCKLOS | CONTENTS_MONSTER )
#define MASK_VISIBLE ( MASK_OPAQUE | CONTENTS_IGNORE_NODRAW_OPAQUE )
#define MASK_VISIBLE_AND_NPCS ( MASK_OPAQUE_AND_NPCS | CONTENTS_IGNORE_NODRAW_OPAQUE )
#define MASK_SHOT ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX)
#define MASK_SHOT_HULL ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_GRATE )
#define MASK_SHOT_PORTAL ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTER )
#define MASK_SOLID_BRUSHONLY ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_GRATE )
#define MASK_PLAYERSOLID_BRUSHONLY ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_PLAYERCLIP | CONTENTS_GRATE )
#define MASK_NPCSOLID_BRUSHONLY ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE )
#define MASK_NPCWORLDSTATIC ( CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE )
#define MASK_SPLITAREAPORTAL ( CONTENTS_WATER | CONTENTS_SLIME )
#define net_StringCmd 4   // a string command
#define clc_moveval 9
#define FLOW_OUTGOING	0		
#define FLOW_INCOMING	1

#define	HIDEHUD_WEAPONSELECTION		( 1<<0 )	// Hide ammo count & weapon selection
#define	HIDEHUD_FLASHLIGHT			( 1<<1 )
#define	HIDEHUD_ALL					( 1<<2 )
#define HIDEHUD_HEALTH				( 1<<3 )	// Hide health & armor / suit battery
#define HIDEHUD_PLAYERDEAD			( 1<<4 )	// Hide when local player's dead
#define HIDEHUD_NEEDSUIT			( 1<<5 )	// Hide when the local player doesn't have the HEV suit
#define HIDEHUD_MISCSTATUS			( 1<<6 )	// Hide miscellaneous status elements (trains, pickup history, death notices, etc)
#define HIDEHUD_CHAT				( 1<<7 )	// Hide all communication elements (saytext, voice icon, etc)
#define	HIDEHUD_CROSSHAIR			( 1<<8 )	// Hide crosshairs
#define	HIDEHUD_VEHICLE_CROSSHAIR	( 1<<9 )	// Hide vehicle crosshair
#define HIDEHUD_INVEHICLE			( 1<<10 )
#define HIDEHUD_BONUS_PROGRESS		( 1<<11 )	// Hide bonus progress display (for bonus map challenges)

#define DECLARE_BASE_MESSAGE(msgtype)     \
public:                                   \
    bool ReadFromBuffer(bf_read &buffer); \
    bool WriteToBuffer(bf_write &buffer); \
    const char *ToString() const;         \
    int GetType() const                   \
    {                                     \
        return msgtype;                   \
    }                                     \
    const char *GetName() const           \
    {                                     \
        return #msgtype;                  \
    }

#define DECLARE_NET_MESSAGE(name)          \
    DECLARE_BASE_MESSAGE(net_##name);      \
    void *m_pMessageHandler; \
   /* bool Process()                         \
    {                                      \
        return false;                      \
    }                                      \*/


struct start_sound_params_t {
	bool			m_static_sound;
	int				m_user_data;
	int				m_sound_source;
	int				m_ent_channel;
	DWORD*			m_sfx;
	vector			m_origin;
	vector			m_direction;
	bool			m_update_positions;
	float			m_vol;
	DWORD			m_sound_level;
	int				m_flags;
	int				m_pitch;
	int				m_special_dsp;
	bool			m_from_server;
	float			m_delay;
	int				m_speaker_entity;
	bool			m_suppress_recording;
	int				m_initial_stream_position;
};

enum vgui_panel_t {
	PANEL_ROOT = 0,
	PANEL_GAMEUIDLL,
	PANEL_CLIENTDLL,
	PANEL_TOOLS,
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS
};

enum paint_mode_t {
	PAINT_UIPANELS = ( 1 << 0 ),
	PAINT_INGAMEPANELS = ( 1 << 1 ),
	PAINT_CURSOR = ( 1 << 2 )
};

class i_engine_vgui {
public:
	virtual ~i_engine_vgui( void ) = 0;
	virtual unsigned int get_panel( vgui_panel_t type ) = 0;
	virtual bool is_game_ui_visible( ) = 0;
};

enum e_font_flags {
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

enum e_image_format
{
	IMAGE_FORMAT_UNKNOWN = -1,
	IMAGE_FORMAT_RGBA8888 = 0,
	IMAGE_FORMAT_ABGR8888,
	IMAGE_FORMAT_RGB888,
	IMAGE_FORMAT_BGR888,
	IMAGE_FORMAT_RGB565,
	IMAGE_FORMAT_I8,
	IMAGE_FORMAT_IA88,
	IMAGE_FORMAT_P8,
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_RGB888_BLUESCREEN,
	IMAGE_FORMAT_BGR888_BLUESCREEN,
	IMAGE_FORMAT_ARGB8888,
	IMAGE_FORMAT_BGRA8888,
	IMAGE_FORMAT_DXT1,
	IMAGE_FORMAT_DXT3,
	IMAGE_FORMAT_DXT5,
	IMAGE_FORMAT_BGRX8888,
	IMAGE_FORMAT_BGR565,
	IMAGE_FORMAT_BGRX5551,
	IMAGE_FORMAT_BGRA4444,
	IMAGE_FORMAT_DXT1_ONEBITALPHA,
	IMAGE_FORMAT_BGRA5551,
	IMAGE_FORMAT_UV88,
	IMAGE_FORMAT_UVWQ8888,
	IMAGE_FORMAT_RGBA16161616F,
	IMAGE_FORMAT_RGBA16161616,
	IMAGE_FORMAT_UVLX8888,
	IMAGE_FORMAT_R32F,
	IMAGE_FORMAT_RGB323232F,
	IMAGE_FORMAT_RGBA32323232F,
	IMAGE_FORMAT_NV_DST16,
	IMAGE_FORMAT_NV_DST24,
	IMAGE_FORMAT_NV_INTZ,
	IMAGE_FORMAT_NV_RAWZ,
	IMAGE_FORMAT_ATI_DST16,
	IMAGE_FORMAT_ATI_DST24,
	IMAGE_FORMAT_NV_NULL,
	IMAGE_FORMAT_ATI2N,
	IMAGE_FORMAT_ATI1N,
	IMAGE_FORMAT_DXT1_RUNTIME,
	IMAGE_FORMAT_DXT5_RUNTIME,
	NUM_IMAGE_FORMATS
};

struct vertex_t
{
	vector_2d m_position;
	vector_2d m_tex_coord;
	vertex_t( ) {}
	vertex_t( const vector_2d& pos, const vector_2d& coord = vector_2d( 0, 0 ) )
	{
		m_position = pos;
		m_tex_coord = coord;
	}
	void init( const vector_2d& pos, const vector_2d& coord = vector_2d( 0, 0 ) )
	{
		m_position = pos;
		m_tex_coord = coord;
	}
};

class i_surface {
public:
	inline void draw_set_color( color col ) {
		typedef void( __thiscall* draw_set_color_fn )( i_surface*, int, int, int, int );
		return util::get_virtual< draw_set_color_fn >( this, 11u )( this, col.m_r, col.m_g, col.m_b, col.m_a );
	}

	inline void draw_filled_rect( int x, int y, int x_, int y_ ) {
		typedef void( __thiscall* draw_filled_rect_fn )( i_surface*, int, int, int, int );
		return util::get_virtual< draw_filled_rect_fn >( this, 12u )( this, x, y, x_, y_ );
	}

	inline void draw_outlined_rect( int x, int y, int x_, int y_ ) {
		typedef void( __thiscall* draw_outlined_rect_fn )( i_surface*, int, int, int, int );
		return util::get_virtual< draw_outlined_rect_fn >( this, 14u )( this, x, y, x_, y_ );
	}

	inline void draw_line( int x, int y, int x_, int y_ ) {
		typedef void( __thiscall* draw_line_fn )( i_surface*, int, int, int, int );
		return util::get_virtual< draw_line_fn >( this, 15u )( this, x, y, x_, y_ );
	}

	inline void draw_set_text_font( DWORD font ) {
		typedef void( __thiscall* draw_set_text_font_fn )( i_surface*, DWORD );
		return util::get_virtual< draw_set_text_font_fn >( this, 17u )( this, font );
	}

	inline void draw_set_text_color( color col ) {
		typedef void( __thiscall* draw_set_text_color_fn )( i_surface*, int, int, int, int );
		return util::get_virtual< draw_set_text_color_fn >( this, 19u )( this, col.m_r, col.m_g, col.m_b, col.m_a );
	}

	inline void draw_set_text_pos( int x, int y ) {
		typedef void( __thiscall* draw_set_text_pos_fn )( i_surface*, int, int );
		return util::get_virtual< draw_set_text_pos_fn >( this, 20u )( this, x, y );
	}

	inline void draw_print_text( const wchar_t* text, int text_len ) {
		typedef void( __thiscall* draw_print_text_fn )( i_surface*, const wchar_t*, int, int );
		return util::get_virtual< draw_print_text_fn >( this, 22u )( this, text, text_len, 0 );
	}

	inline void draw_set_texture( int id ) {
		typedef void( __thiscall* draw_set_texture_fn )( i_surface*, int );
		return util::get_virtual< draw_set_texture_fn >( this, 32u )( this, id );
	}

	inline void draw_textured_rect( int x, int y, int x_, int y_ ) {
		typedef void( __thiscall* draw_textured_rect_fn )( i_surface*, int, int, int, int );
		return util::get_virtual< draw_textured_rect_fn >( this, 34u )( this, x, y, x_, y_ );
	}

	inline bool delete_texture_by_id( int id ) {
		typedef bool( __thiscall* delete_texture_by_id_fn )( i_surface*, int );
		return util::get_virtual< delete_texture_by_id_fn >( this, 36u )( this, id );
	}

	inline int create_new_texture_id( bool procedural = false ) {
		typedef int( __thiscall* create_new_texture_id_fn )( i_surface*, bool );
		return util::get_virtual< create_new_texture_id_fn >( this, 37u )( this, procedural );
	}

	inline void set_cursor_visible( bool visible ) {
		typedef void( __thiscall* set_cursor_visible_fn )( i_surface*, bool );
		return util::get_virtual< set_cursor_visible_fn >( this, 52u )( this, visible );
	}

	inline bool is_cursor_visible( ) {
		typedef bool( __thiscall* is_cursor_visible_fn )( i_surface* );
		return util::get_virtual< is_cursor_visible_fn >( this, 53u )( this );
	}

	inline void unlock_cursor( ) {
		typedef void( __thiscall* unlock_cursor_fn )( i_surface* );
		return util::get_virtual<unlock_cursor_fn >( this, 61u )( this );
	}

	inline DWORD create_font( ) {
		typedef DWORD(__thiscall* create_fn )( i_surface* );
		return util::get_virtual< create_fn >( this, 66u )( this );
	}

	inline void set_font_glyph_set( DWORD& font, const char* windows_font_name, int tall, int weight, int blur, int scanlines, int flags ) {
		typedef void( __thiscall* set_font_glyph_set_fn )( i_surface*, DWORD, const char*, int, int, int, int, int, int, int );
		return util::get_virtual< set_font_glyph_set_fn >( this, 67u )( this, font, windows_font_name, tall, weight, blur, scanlines, flags, 0, 0 );
	}

	inline void get_text_size( DWORD font, const wchar_t* text, int& wide, int& tall ) {
		typedef void( __thiscall* get_text_size_fn )( i_surface*, DWORD, const wchar_t*, int&, int& );
		return util::get_virtual< get_text_size_fn >( this, 75u )( this, font, text, wide, tall );
	}

	inline void play_sound( const char* file_name ) {
		typedef void( __thiscall* play_sound_fn )( i_surface*, const char* );
		return util::get_virtual< play_sound_fn>( this, 78u )( this, file_name );
	}

	inline void get_cursor_pos( int& x, int& y ) {
		typedef void( __thiscall* get_cursor_pos_fn )( i_surface*, int&, int& );
		return util::get_virtual< get_cursor_pos_fn>( this, 96u )( this, x, y );
	}

	inline void draw_textured_polygon( int count, vertex_t* vertices, bool clip_vertices = true ) {
		typedef void( __thiscall* draw_textured_polygon_fn )( i_surface*, int, vertex_t*, bool );
		return util::get_virtual< draw_textured_polygon_fn>( this, 102u )( this, count, vertices, clip_vertices );
	}

	inline void draw_set_alpha( float alpha ) {
		typedef void( __thiscall* draw_set_alpha_fn )( i_surface*, float );
		return util::get_virtual< draw_set_alpha_fn>( this, 108u )( this, alpha );
	}

	inline void draw_filled_rect_fade( int x, int y, int x_, int y_, unsigned int alpha, unsigned int alpha_, bool horizontal ) {
		typedef void( __thiscall* draw_filled_rect_fade_fn )( i_surface*, int, int, int, int, unsigned int, unsigned int, bool );
		return util::get_virtual< draw_filled_rect_fade_fn >( this, 118u )( this, x, y, x_, y_, alpha, alpha_, horizontal );
	}

	inline void draw_set_texture_rgba_ex( int id, const unsigned char* rgba, int wide, int tall, e_image_format image_format ) {
		typedef void( __thiscall* draw_set_texture_rgba_ex_fn )( i_surface*, int, const unsigned char*, int, int, e_image_format );
		return util::get_virtual< draw_set_texture_rgba_ex_fn>( this, 119u )( this, id, rgba, wide, tall, image_format );
	}

	inline void disable_clipping( bool disable ) {
		typedef void( __thiscall* disable_clipping_fn )( i_surface*, bool );
		return util::get_virtual< disable_clipping_fn>( this, 156u )( this, disable );
	}

	inline void get_clipping_rect( int& left, int& top, int& right, int& bottom, bool& clipping_disabled ) {
		typedef void( __thiscall* get_clipping_rect_fn )( i_surface*, int&, int&, int&, int&, bool& );
		return util::get_virtual< get_clipping_rect_fn>( this, 157u )( this, left, top, right, bottom, clipping_disabled );
	}

	inline void set_clipping_rect( int left, int top, int right, int bottom ) {
		typedef void( __thiscall* set_clipping_rect_fn )( i_surface*, int, int, int, int );
		return util::get_virtual< set_clipping_rect_fn>( this, 158u )( this, left, top, right, bottom );
	}

	inline void start_drawing( ) {
		typedef void( __thiscall* start_drawing_fn )( i_surface* );
		static auto start_drawing_ = util::find_signature< start_drawing_fn >( "vguimatsurface.dll", "55 8B EC 64 A1 ? ? ? ? 6A FF 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 14" );
		return start_drawing_( this );
	}

	inline void finish_drawing( ) {
		typedef void( __thiscall* finish_drawing_fn )( i_surface* );
		static auto finish_drawing_ = util::find_signature< finish_drawing_fn >( "vguimatsurface.dll", "55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 51 56 6A 00" );
		return finish_drawing_( this );
	}
};

enum struct class_id_t {
	CAI_BaseNPC,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseObject,
	CBaseObjectUpgrade,
	CBaseParticleEntity,
	CBasePlayer,
	CBaseProjectile,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseViewModel,
	CBeam,
	CBoneFollower,
	CBonusDuckPickup,
	CBonusPack,
	CBonusRoundLogic,
	CBreakableProp,
	CBreakableSurface,
	CCaptureFlag,
	CCaptureFlagReturnIcon,
	CCaptureZone,
	CColorCorrection,
	CColorCorrectionVolume,
	CCurrencyPack,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEconWearable,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityParticleTrail,
	CEnvDetailController,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CEyeballBoss,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFogController,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncConveyor,
	CFuncForceField,
	CFuncLadder,
	CFuncMonitor,
	CFuncOccluder,
	CFuncPasstimeGoal,
	CFuncReflectiveGlass,
	CFuncRespawnRoom,
	CFuncRespawnRoomVisualizer,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CHalloweenGiftPickup,
	CHalloweenPickup,
	CHalloweenSoulPack,
	CHandleTest,
	CHeadlessHatman,
	CHightower_TeleportVortex,
	CInfoLadderDismount,
	CInfoLightingRelative,
	CInfoOverlayAccessor,
	CLaserDot,
	CLightGlow,
	CMannVsMachineStats,
	CMaterialModifyControl,
	CMerasmus,
	CMerasmusDancer,
	CMonsterResource,
	CObjectCartDispenser,
	CObjectDispenser,
	CObjectSapper,
	CObjectSentrygun,
	CObjectTeleporter,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPasstimeBall,
	CPasstimeGun,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPlasma,
	CPlayerDestructionDispenser,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPointWorldText,
	CPoseController,
	CPrecipitation,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRobotDispenser,
	CRopeKeyframe,
	CSceneEntity,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeStack,
	CSniperDot,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CSteamJet,
	CSun,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTeamRoundTimer,
	CTeamTrainWatcher,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTeleportVortex,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTETFBlood,
	CTETFExplosion,
	CTETFParticleEffect,
	CTEWorldDecal,
	CTFAmmoPack,
	CTFBall_Ornament,
	CTFBaseBoss,
	CTFBaseProjectile,
	CTFBaseRocket,
	CTFBat,
	CTFBat_Fish,
	CTFBat_Giftwrap,
	CTFBat_Wood,
	CTFBonesaw,
	CTFBotHintEngineerNest,
	CTFBottle,
	CTFBreakableMelee,
	CTFBreakableSign,
	CTFBuffItem,
	CTFCannon,
	CTFChargedSMG,
	CTFCleaver,
	CTFClub,
	CTFCompoundBow,
	CTFCrossbow,
	CTFDRGPomson,
	CTFDroppedWeapon,
	CTFFireAxe,
	CTFFists,
	CTFFlameManager,
	CTFFlameRocket,
	CTFFlameThrower,
	CTFFlareGun,
	CTFFlareGun_Revenge,
	CTFGameRulesProxy,
	CTFGasManager,
	CTFGenericBomb,
	CTFGlow,
	CTFGrapplingHook,
	CTFGrenadeLauncher,
	CTFGrenadePipebombProjectile,
	CTFHalloweenMinigame,
	CTFHalloweenMinigame_FallingPlatforms,
	CTFHellZap,
	CTFItem,
	CTFJar,
	CTFJarGas,
	CTFJarMilk,
	CTFKatana,
	CTFKnife,
	CTFLaserPointer,
	CTFLunchBox,
	CTFLunchBox_Drink,
	CTFMechanicalArm,
	CTFMedigunShield,
	CTFMiniGame,
	CTFMinigameLogic,
	CTFMinigun,
	CTFObjectiveResource,
	CTFParachute,
	CTFParachute_Primary,
	CTFParachute_Secondary,
	CTFParticleCannon,
	CTFPasstimeLogic,
	CTFPEPBrawlerBlaster,
	CTFPipebombLauncher,
	CTFPistol,
	CTFPistol_Scout,
	CTFPistol_ScoutPrimary,
	CTFPistol_ScoutSecondary,
	CTFPlayer,
	CTFPlayerDestructionLogic,
	CTFPlayerResource,
	CTFPointManager,
	CTFPowerupBottle,
	CTFProjectile_Arrow,
	CTFProjectile_BallOfFire,
	CTFProjectile_Cleaver,
	CTFProjectile_EnergyBall,
	CTFProjectile_EnergyRing,
	CTFProjectile_Flare,
	CTFProjectile_GrapplingHook,
	CTFProjectile_HealingBolt,
	CTFProjectile_Jar,
	CTFProjectile_JarGas,
	CTFProjectile_JarMilk,
	CTFProjectile_MechanicalArmOrb,
	CTFProjectile_Rocket,
	CTFProjectile_SentryRocket,
	CTFProjectile_SpellBats,
	CTFProjectile_SpellFireball,
	CTFProjectile_SpellKartBats,
	CTFProjectile_SpellKartOrb,
	CTFProjectile_SpellLightningOrb,
	CTFProjectile_SpellMeteorShower,
	CTFProjectile_SpellMirv,
	CTFProjectile_SpellPumpkin,
	CTFProjectile_SpellSpawnBoss,
	CTFProjectile_SpellSpawnHorde,
	CTFProjectile_SpellSpawnZombie,
	CTFProjectile_SpellTransposeTeleport,
	CTFProjectile_Throwable,
	CTFProjectile_ThrowableBreadMonster,
	CTFProjectile_ThrowableBrick,
	CTFProjectile_ThrowableRepel,
	CTFPumpkinBomb,
	CTFRagdoll,
	CTFRaygun,
	CTFReviveMarker,
	CTFRevolver,
	CTFRobotArm,
	CTFRobotDestruction_Robot,
	CTFRobotDestruction_RobotGroup,
	CTFRobotDestruction_RobotSpawn,
	CTFRobotDestructionLogic,
	CTFRocketLauncher,
	CTFRocketLauncher_AirStrike,
	CTFRocketLauncher_DirectHit,
	CTFRocketLauncher_Mortar,
	CTFRocketPack,
	CTFScatterGun,
	CTFShotgun,
	CTFShotgun_HWG,
	CTFShotgun_Pyro,
	CTFShotgun_Revenge,
	CTFShotgun_Soldier,
	CTFShotgunBuildingRescue,
	CTFShovel,
	CTFSlap,
	CTFSMG,
	CTFSniperRifle,
	CTFSniperRifleClassic,
	CTFSniperRifleDecap,
	CTFSodaPopper,
	CTFSpellBook,
	CTFStickBomb,
	CTFStunBall,
	CTFSword,
	CTFSyringeGun,
	CTFTankBoss,
	CTFTauntProp,
	CTFTeam,
	CTFThrowable,
	CTFViewModel,
	CTFWeaponBase,
	CTFWeaponBaseGrenadeProj,
	CTFWeaponBaseGun,
	CTFWeaponBaseMelee,
	CTFWeaponBaseMerasmusGrenade,
	CTFWeaponBuilder,
	CTFWeaponFlameBall,
	CTFWeaponInvis,
	CTFWeaponPDA,
	CTFWeaponPDA_Engineer_Build,
	CTFWeaponPDA_Engineer_Destroy,
	CTFWeaponPDA_Spy,
	CTFWeaponPDAExpansion_Dispenser,
	CTFWeaponPDAExpansion_Teleporter,
	CTFWeaponSapper,
	CTFWearable,
	CTFWearableCampaignItem,
	CTFWearableDemoShield,
	CTFWearableItem,
	CTFWearableLevelableItem,
	CTFWearableRazorback,
	CTFWearableRobotArm,
	CTFWearableVM,
	CTFWrench,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponIFMBase,
	CWeaponIFMBaseCamera,
	CWeaponIFMSteadyCam,
	CWeaponMedigun,
	CWorld,
	CZombie,
	DustTrail,
	MovieExplosion,
	NextBotCombatCharacter,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail,
};

typedef void*( *create_client_class_fn )( int entnum, int serial_num );
typedef void*( *create_event_fn )( );

class recv_table;

class client_class {
public:
	create_client_class_fn m_create_fn;
	create_event_fn m_create_event_fn;
	const char* m_network_name;
	recv_table* m_recv_table;
	client_class* m_next;
	class_id_t m_class_id;
};

class i_client_entity;
class client_class;
class i_client_networkable;
class i_client_unknown;

using c_base_handle = uint32_t;

class i_handle_entity {
public:
	virtual ~i_handle_entity( ) { }
	virtual void set_ref_e_handle( const c_base_handle& handle ) = 0;
	virtual const c_base_handle& get_ref_e_handle( ) const = 0;
};

class i_client_entity_list {
public:
	virtual i_client_networkable* get_client_networkable( int entnum ) = 0;
	virtual i_client_networkable* get_client_networkable_from_handle( c_base_handle ent ) = 0;
	virtual i_client_unknown* get_client_unknown_from_handle( c_base_handle ent ) = 0;
	virtual i_client_entity* get_client_entity( int entnum ) = 0;
	virtual i_client_entity* get_client_entity_from_handle( c_base_handle ent ) = 0;
	virtual int number_of_entities( bool include_non_networkable ) = 0;
	virtual int get_highest_entity_index( void ) = 0;
	virtual void set_max_entities( int maxents ) = 0;
	virtual int get_max_entities( ) = 0;
};

class c_user_cmd {
public:
	virtual ~c_user_cmd( ) { };
	int	m_command_number;
	int	m_tick_count;
	vector m_view_angles;
	float m_forward_move;
	float m_side_move;
	float m_up_move;
	int m_buttons;
	byte m_impulse;
	int m_weapon_select;
	int m_weapon_subtype;
	int m_random_seed;
	short m_mouse_dx;
	short m_mouse_dy;
	bool m_has_been_predicted;
};

class c_base_hud_chat {
public:
	void chat_printf( int index, const char *fmt, ... ) {
		typedef void( _cdecl* chat_printf_fn )( c_base_hud_chat*, int, int, const char*, ... );
		return util::get_virtual< chat_printf_fn >( this, 19 )( this, index, 0, fmt );
	}
};

class i_client_mode {
public:
	uint8_t m_pad[ 28 ];
	c_base_hud_chat* m_chat_element;
};

class button_code_t;
class c_base_combat_weapon;
class c_user_cmd;
class kbutton_t;

struct camera_third_data_t {
	float m_pitch;
	float m_yaw;
	float m_dist;
	float m_lag;
	vector m_hull_min;
	vector m_hull_max;
};

enum game_action_set_t {
	game_action_set_none = -1,
	game_action_set_menucontrols = 0,
	game_action_set_fpscontrols,
	game_action_set_in_game_hud,
	game_action_set_spectator,
};

enum game_action_set_flags_t {
	game_action_set_flags_none = 0,
	game_action_set_flags_taunting = ( 1 << 0 ),
};

class i_input {
public:
	virtual	void init_all( void ) = 0;
	virtual void shutdown_all( void ) = 0;
	virtual int get_button_bits( int ) = 0;
	virtual void create_move( int sequence_number, float input_sample_frametime, bool active ) = 0;
	virtual void extra_mouse_sample( float frametime, bool active ) = 0;
	virtual bool write_usercmd_delta_to_buffer( bf_write* buf, int from, int to, bool isnewcommand ) = 0;
	virtual void encode_user_cmd_to_buffer( bf_write& buf, int slot ) = 0;
	virtual void decode_user_cmd_from_buffer( bf_read& buf, int slot ) = 0;
	virtual c_user_cmd* get_user_cmd( int sequence_number ) = 0;
	virtual void MakeWeaponSelection( c_base_combat_weapon* weapon ) = 0;
	virtual float key_state( kbutton_t* key ) = 0;
	virtual int key_event( int eventcode, button_code_t keynum, const char* current_binding ) = 0;
	virtual kbutton_t* find_key( const char* name ) = 0;
	virtual void controller_commands( void ) = 0;
	virtual void joystick_advanced( void ) = 0;
	virtual void joystick_set_sample_time( float frametime ) = 0;
	virtual void in_set_sample_time( float frametime) = 0;
	virtual void accumulate_mouse( void ) = 0;
	virtual void activate_mouse( void ) = 0;
	virtual void deactivate_mouse( void ) = 0;
	virtual void clear_states( void ) = 0;
	virtual float get_look_spring( void ) = 0;
	virtual void get_fullscreen_mouse_pos( int* mx, int* my, int* unclampedx = 0, int* unclampedy = 0 ) = 0;
	virtual void set_fullscreen_mouse_pos( int mx, int my ) = 0;
	virtual void reset_mouse( void ) = 0;
	virtual	float get_last_forward_move( void ) = 0;
	virtual	float joystick_get_forward( void ) = 0;
	virtual	float joystick_get_side( void ) = 0;
	virtual	float joystick_get_pitch( void ) = 0;
	virtual	float joystick_get_yaw( void ) = 0;
	virtual void cam_think( void ) = 0;
	virtual int cam_is_third_person( void ) = 0;
	virtual void cam_to_third_person( void ) = 0;
	virtual void cam_to_first_person( void ) = 0;
	virtual void cam_start_mouse_move( void ) = 0;
	virtual void cam_end_mouse_move( void ) = 0;
	virtual void cam_start_distance( void ) = 0;
	virtual void cam_end_distance( void ) = 0;
	virtual int	cam_intercepting_mouse( void ) = 0;
	virtual void cam_to_orthographic( ) = 0;
	virtual	bool cam_is_orthographic( ) const = 0;
	virtual	void cam_orthographic_size( float& w, float& h ) const = 0;
	virtual void set_preferred_game_action_set( game_action_set_t action_set ) = 0;
	virtual game_action_set_t get_preferred_game_action_set( ) = 0;
	virtual void set_game_action_set_flags( game_action_set_flags_t action_set_flags ) = 0;
	virtual void level_init( void ) = 0;
	virtual void clear_input_button( int bits ) = 0;
	virtual	void cam_set_camera_third_data( camera_third_data_t* camera_data, const vector& camera_offset ) = 0;
	virtual void cam_camera_third_think( void ) = 0;
	virtual	bool enable_joystick_mode( ) = 0;
	virtual bool is_steam_controller_active( ) = 0;
};

#define MAX_PLAYERS		16
#define MAX_PLAYER_NAME_LENGTH 32
#define SIGNED_GUID_LEN 32
#define MAX_CUSTOM_FILES 4

typedef struct player_info_s {
	char m_name[ MAX_PLAYER_NAME_LENGTH ];
	int m_user_id;
	char m_guid[ SIGNED_GUID_LEN + 1 ];
	uint32_t m_friends_id;
	char m_friends_name[ MAX_PLAYER_NAME_LENGTH ];
	bool m_fake_player;
	bool m_is_hltv;
	bool m_is_replay;
	uint32_t m_custom_files[ MAX_CUSTOM_FILES ];
	unsigned char m_files_downloaded;
} player_info_t;

class i_net_channel_info;

enum user_message_type_t
{
	Geiger = 0,
	Train,
	HudText,
	SayText,
	SayText2,
	TextMsg,
	ResetHUD,
	GameTitle,
	ItemPickup,
	ShowMenu,
	Shake,
	Fade,
	VGUIMenu,
	Rumble,
	CloseCaption,
	SendAudio,
	VoiceMask,
	RequestState,
	Damage,
	HintText,
	KeyHintText,
	HudMsg,
	AmmoDenied,
	AchievementEvent,
	UpdateRadar,
	VoiceSubtitle,
	HudNotify,
	HudNotifyCustom,
	PlayerStatsUpdate,
	MapStatsUpdate,
	PlayerIgnited,
	PlayerIgnitedInv,
	HudArenaNotify,
	UpdateAchievement,
	TrainingMsg,
	TrainingObjective,
	DamageDodged,
	PlayerJarated,
	PlayerExtinguished,
	PlayerJaratedFade,
	PlayerShieldBlocked,
	BreakModel,
	CheapBreakModel,
	BreakModel_Pumpkin,
	BreakModelRocketDud,
	CallVoteFailed,
	VoteStart,
	VotePass,
	VoteFailed,
	VoteSetup,
	PlayerBonusPoints,
	RDTeamPointsChanged,
	SpawnFlyingBird,
	PlayerGodRayEffect,
	PlayerTeleportHomeEffect,
	MVMStatsReset,
	MVMPlayerEvent,
	MVMResetPlayerStats,
	MVMWaveFailed,
	MVMAnnouncement,
	MVMPlayerUpgradedEvent,
	MVMVictory,
	MVMWaveChange,
	MVMLocalPlayerUpgradesClear,
	MVMLocalPlayerUpgradesValue,
	MVMResetPlayerWaveSpendingStats,
	MVMLocalPlayerWaveSpendingValue,
	MVMResetPlayerUpgradeSpending,
	MVMServerKickTimeUpdate,
	PlayerLoadoutUpdated,
	PlayerTauntSoundLoopStart,
	PlayerTauntSoundLoopEnd,
	ForcePlayerViewAngles,
	BonusDucks,
	EOTLDuckEvent,
	PlayerPickupWeapon,
	QuestObjectiveCompleted,
	SPHapWeapEvent,
	HapDmg,
	HapPunch,
	HapSetDrag,
	HapSetConst,
	HapMeleeContact
};

class iv_engine_client {
public:
	inline void get_screen_size( int& width_out, int& height_out ) {
		typedef void( __thiscall* get_screen_size_fn )( iv_engine_client*, int&, int& );
		return util::get_virtual< get_screen_size_fn >( this, 5u )( this, width_out, height_out );
	}

	bool get_player_info( int ent_num, player_info_t* info ) {
		typedef bool( __thiscall* get_player_info_fn )( iv_engine_client*, int, player_info_t* );
		return util::get_virtual< get_player_info_fn >( this, 8u )( this, ent_num, info );
	}

	inline int get_local_player( ) {
		typedef int( __thiscall* get_local_player_fn )( iv_engine_client* );
		return util::get_virtual< get_local_player_fn >( this, 12u )( this );
	}
	
	inline vector get_view_angles( ) {
		typedef void( __thiscall* get_view_angles_fn )( iv_engine_client*, vector& );
		auto out = vector( );
		util::get_virtual< get_view_angles_fn >( this, 19u )( this, out );
		return out;
	}

	inline void set_view_angles( vector& angles ) {
		typedef void( __thiscall* set_view_angles_fn )( iv_engine_client*, vector& );
		return util::get_virtual< set_view_angles_fn >( this, 20u )( this, angles );
	}

	inline bool is_in_game( ) {
		typedef bool( __thiscall* is_in_game_fn )( iv_engine_client* );
		return util::get_virtual< is_in_game_fn >( this, 26u )( this );
	}

	inline float time( ) {
		typedef float( __thiscall* time_fn )( iv_engine_client* );
		return util::get_virtual< time_fn >( this, 14u )( this );
	}
	
	inline i_net_channel_info* get_net_channel_info( ) {
		typedef i_net_channel_info* ( __thiscall* get_net_channel_info_fn )( iv_engine_client* );
		return util::get_virtual< get_net_channel_info_fn >( this, 72u )( this );
	}

	inline void client_cmd_unrestricted( const char* command ) {
		typedef void( __thiscall* client_cmd_unrestricted_fn )( iv_engine_client*, const char* );
		return util::get_virtual< client_cmd_unrestricted_fn>( this, 106u )( this, command );
	}

	inline void send_key_values( void* kv ) {
		typedef void( __thiscall* send_key_values_fn )( iv_engine_client*, void* );
		return util::get_virtual< send_key_values_fn >( this, 127u )( this, kv );
	}
	
	inline int get_player_for_user_id( int uid ) {
		typedef int( __thiscall* get_player_for_user_id_fn )( iv_engine_client*, int );
		return util::get_virtual< get_player_for_user_id_fn >( this, 9u )( this, uid );
	}
};

enum stereo_eye_t {
	STEREO_EYE_MONO = 0,
	STEREO_EYE_LEFT = 1,
	STEREO_EYE_RIGHT = 2,
	STEREO_EYE_MAX = 3,
};

class c_view_setup {
public:
	int m_x;
	int m_unscaled_x;
	int m_y;
	int m_unscaled_y;
	int m_width;
	int m_unscaled_width;
	int m_height;
	stereo_eye_t m_stereo_eye;
	int m_unscaled_height;
	bool m_ortho;
	float m_ortho_left;
	float m_ortho_top;
	float m_ortho_right;
	float m_ortho_bottom;
	float m_fov;
	float m_fov_viewmodel;
	vector m_origin;
	vector m_angles;
	float m_z_near;
	float m_z_far;
	float m_z_near_viewmodel;
	float m_z_far_viewmodel;
	bool m_render_to_subrect_of_larger_screen;
	float m_aspect_ratio;
	bool m_off_center;
	float m_off_center_top;
	float m_off_center_bottom;
	float m_off_center_left;
	float m_off_center_right;
	bool m_do_bloom_and_tone_mapping;
	bool m_cache_full_scene_state;
	bool m_view_to_projection_override;
	view_matrix m_view_to_projection;
};

enum class client_frame_stage_t {
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

class i_base_client_dll {
public:
	inline client_class* get_all_classes( ) {
		typedef client_class* ( __thiscall* get_all_classes_fn )( i_base_client_dll* );
		return util::get_virtual< get_all_classes_fn >( this, 8 )( this );
	}

	inline bool write_usercmd_delta_to_buffer( bf_write* buf, int from, int to, bool is_new_command ) {
		typedef bool( __thiscall* write_usercmd_delta_to_buffer_fn )( i_base_client_dll*, bf_write*, int, int, bool );
		return util::get_virtual< write_usercmd_delta_to_buffer_fn >(this, 23 )( this, buf, from, to, is_new_command );
	}

	inline bool get_player_view( c_view_setup& player_view ) {
		typedef bool( __thiscall* get_player_view_fn )( i_base_client_dll*, c_view_setup& );
		return util::get_virtual< get_player_view_fn >( this, 59 )( this, player_view );
	}
};

#define MAX_AREA_STATE_BYTES 32
#define MAX_AREA_PORTAL_STATE_BYTES 24

struct visible_fog_volume_info_t;
class i_world_render_list;
struct vis_override_data_t;
class i_brush_renderer;
class frustum;
struct draw_brush_model_mode_t;
class world_list_info_t;
class i_texture;
class i_material;

typedef uint64_t vertex_format_t;
typedef uint32_t morph_format_t;
using occlusion_query_object_handle_t = void*;

enum material_var_flags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),
	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17),
	MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19),
	MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23),
	MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
	MATERIAL_VAR_ENVMAPMODE = (1 << 25),
	MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT = (1 << 27),
	MATERIAL_VAR_WIREFRAME = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
	MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = (1 << 30),
	MATERIAL_VAR_VERTEXFOG = (1 << 31),
};

class i_material_var
{
public:
	virtual i_texture* get_texture_value(void) = 0;
	virtual const char* get_name(void) const = 0;
	virtual int get_name_as_symbol() const = 0;
	virtual void set_float_value(float val) = 0;
	virtual void set_int_value(int val) = 0;
	virtual void set_string_value(const char* val) = 0;
	virtual const char* get_string_value(void) const = 0;
	virtual void set_four_cc_value(void* type, void* pData) = 0;
	virtual void get_four_cc_value(void* type, void** ppData) = 0;
	virtual void set_vec_value(const float* val, int num_comps) = 0;
	virtual void set_vec_value(float x, float y) = 0;
	virtual void set_vec_value(float x, float y, float z) = 0;
	virtual void set_vec_value(float x, float y, float z, float w) = 0;
	virtual void get_linear_vec_value(float* val, int num_comps) const = 0;
	virtual void set_texture_value(i_texture*) = 0;
	virtual i_material* get_material_value(void) = 0;
	virtual void set_material_value(i_material*) = 0;
	virtual bool is_defined() const = 0;
	virtual void set_undefined() = 0;
	virtual void set_matrix_value(const view_matrix& matrix) = 0;
	virtual const view_matrix& get_matrix_value() = 0;
	virtual bool matrix_is_identity() const = 0;
	virtual void copy_from(i_material_var* p_material_var) = 0;
	virtual void set_value_autodetect_type(const char* val) = 0;
	virtual i_material* get_owning_material() = 0;
	virtual void set_vec_component_value(float f_val, int n_component) = 0;

protected:
	virtual int get_int_value_internal(void) const = 0;
	virtual float get_float_value_internal(void) const = 0;
	virtual const float* get_vec_value_internal() const = 0;
	virtual void get_vec_value_internal(float* val, int num_comps) const = 0;
	virtual int vector_size_internal() const = 0;
};

enum render_target_size_mode_t
{
	RT_SIZE_NO_CHANGE = 0,
	RT_SIZE_DEFAULT = 1,
	RT_SIZE_PICMIP = 2,
	RT_SIZE_HDR = 3,
	RT_SIZE_FULL_FRAME_BUFFER = 4,
	RT_SIZE_OFFSCREEN = 5,
	RT_SIZE_FULL_FRAME_BUFFER_ROUNDED_UP = 6,
	RT_SIZE_REPLAY_SCREENSHOT = 7,
	RT_SIZE_LITERAL = 8,
	RT_SIZE_LITERAL_PICMIP = 9

};

enum material_render_target_depth_t
{
	MATERIAL_RT_DEPTH_SHARED = 0x0,
	MATERIAL_RT_DEPTH_SEPARATE = 0x1,
	MATERIAL_RT_DEPTH_NONE = 0x2,
	MATERIAL_RT_DEPTH_ONLY = 0x3,
};

enum compiled_vtf_flags
{
	TEXTUREFLAGS_POINTSAMPLE = 0x00000001,
	TEXTUREFLAGS_TRILINEAR = 0x00000002,
	TEXTUREFLAGS_CLAMPS = 0x00000004,
	TEXTUREFLAGS_CLAMPT = 0x00000008,
	TEXTUREFLAGS_ANISOTROPIC = 0x00000010,
	TEXTUREFLAGS_HINT_DXT5 = 0x00000020,
	TEXTUREFLAGS_SRGB = 0x00000040,
	TEXTUREFLAGS_NORMAL = 0x00000080,
	TEXTUREFLAGS_NOMIP = 0x00000100,
	TEXTUREFLAGS_NOLOD = 0x00000200,
	TEXTUREFLAGS_ALL_MIPS = 0x00000400,
	TEXTUREFLAGS_PROCEDURAL = 0x00000800,
	TEXTUREFLAGS_ONEBITALPHA = 0x00001000,
	TEXTUREFLAGS_EIGHTBITALPHA = 0x00002000,
	TEXTUREFLAGS_ENVMAP = 0x00004000,
	TEXTUREFLAGS_RENDERTARGET = 0x00008000,
	TEXTUREFLAGS_DEPTHRENDERTARGET = 0x00010000,
	TEXTUREFLAGS_NODEBUGOVERRIDE = 0x00020000,
	TEXTUREFLAGS_SINGLECOPY = 0x00040000,
	TEXTUREFLAGS_STAGING_MEMORY = 0x00080000,
	TEXTUREFLAGS_IMMEDIATE_CLEANUP = 0x00100000,
	TEXTUREFLAGS_IGNORE_PICMIP = 0x00200000,
	TEXTUREFLAGS_UNUSED_00400000 = 0x00400000,
	TEXTUREFLAGS_NODEPTHBUFFER = 0x00800000,
	TEXTUREFLAGS_UNUSED_01000000 = 0x01000000,
	TEXTUREFLAGS_CLAMPU = 0x02000000,
	TEXTUREFLAGS_VERTEXTEXTURE = 0x04000000,
	TEXTUREFLAGS_SSBUMP = 0x08000000,
	TEXTUREFLAGS_UNUSED_10000000 = 0x10000000,
	TEXTUREFLAGS_BORDER = 0x20000000,
	TEXTUREFLAGS_STREAMABLE_COARSE = 0x40000000,
	TEXTUREFLAGS_STREAMABLE_FINE = 0x80000000,
	TEXTUREFLAGS_STREAMABLE = ( TEXTUREFLAGS_STREAMABLE_COARSE | TEXTUREFLAGS_STREAMABLE_FINE )
};

enum normal_decode_mode_t
{
	NORMAL_DECODE_NONE = 0
};

class i_vtf_texture;
class i_texture;
class i_texture_regenerator
{
public:
	virtual void RegenerateTextureBits( i_texture* pTexture, i_vtf_texture* pVTFTexture, rect_t* pRect ) = 0;
	virtual void Release( ) = 0;
};

class i_texture
{
public:
	virtual const char* get_name( ) const = 0;
	virtual int get_mapping_width( ) const = 0;
	virtual int get_mapping_height( ) const = 0;
	virtual int get_actual_width( ) const = 0;
	virtual int get_actual_height( ) const = 0;
	virtual int get_num_animation_frames( ) const = 0;
	virtual bool is_translucent( ) const = 0;
	virtual bool is_mipmapped( ) const = 0;
	virtual void get_low_res_color_sample( float s, float t, float* color ) const = 0;
	virtual void* get_resource_data( uint32_t e_data_type, size_t* p_num_bytes ) const = 0;
	virtual void increment_reference_count( ) = 0;
	virtual void decrement_reference_count( ) = 0;
	inline void add_ref( ) { increment_reference_count( ); }
	inline void release( ) { decrement_reference_count( ); }
	virtual void set_texture_regenerator( i_texture_regenerator* p_texture_regen ) = 0;
	virtual void download( rect_t* p_rect = 0, int n_additional_creation_flags = 0 ) = 0;
	virtual int get_approximate_vid_mem_bytes( ) const = 0;
	virtual bool is_error( ) const = 0;
	virtual bool is_volume_texture( ) const = 0;
	virtual int get_mapping_depth( ) const = 0;
	virtual int get_actual_depth( ) const = 0;
	virtual e_image_format get_image_format( ) const = 0;
	virtual normal_decode_mode_t get_normal_decode_mode( ) const = 0;
	virtual bool is_render_target( ) const = 0;
	virtual bool is_cube_map( ) const = 0;
	virtual bool is_normal_map( ) const = 0;
	virtual bool is_procedural( ) const = 0;
	virtual void delete_if_unreferenced( ) = 0;
	virtual void swap_contents( i_texture* p_other ) = 0;
	virtual unsigned int get_flags( ) const = 0;
	virtual void force_lod_override( int i_num_lods_override_up_or_down ) = 0;
	virtual bool save_to_file( const char* file_name ) = 0;
	virtual void copy_to_staging_texture( i_texture* p_dst_tex ) = 0;
	virtual void set_error_texture( bool b_is_error_texture ) = 0;
};

class i_material
{
public:
	virtual const char* get_name() const = 0;
	virtual const char* get_texture_group_name() const = 0;
	virtual int get_preview_image_properties(int* width, int* height,
		int* image_format, bool* is_translucent) const = 0;
	virtual int get_preview_image(unsigned char* data,
		int width, int height,
		int image_format) const = 0;
	virtual int get_mapping_width() = 0;
	virtual int get_mapping_height() = 0;
	virtual int get_num_animation_frames() = 0;
	virtual bool in_material_page() = 0;
	virtual	void get_material_offset(float* p_offset) = 0;
	virtual void get_material_scale(float* p_scale) = 0;
	virtual i_material* get_material_page() = 0;
	virtual i_material_var* find_var(const char* var_name, bool* found, bool complain = true) = 0;
	virtual void increment_reference_count() = 0;
	virtual void decrement_reference_count() = 0;
	virtual int get_enumeration_id() const = 0;
	virtual void get_low_res_color_sample(float s, float t, float* color) const = 0;
	virtual void recompute_state_snapshots() = 0;
	virtual bool is_translucent() = 0;
	virtual bool is_alpha_tested() = 0;
	virtual bool is_vertex_lit() = 0;
	virtual void* get_vertex_format() const = 0;
	virtual bool has_proxy() const = 0;
	virtual bool uses_env_cubemap() = 0;
	virtual bool needs_tangent_space() = 0;
	virtual bool needs_power_of_two_frame_buffer_texture(bool b_check_specific_to_this_frame = true) = 0;
	virtual bool needs_full_frame_buffer_texture(bool b_check_specific_to_this_frame = true) = 0;
	virtual bool needs_software_skinning() = 0;
	virtual void alpha_modulate(float alpha) = 0;
	virtual void color_modulate(float r, float g, float b) = 0;
	virtual void set_material_var_flag(material_var_flags_t flag, bool on) = 0;
	virtual bool get_material_var_flag(material_var_flags_t flag) const = 0;
	virtual void get_reflectivity(vector& reflect) = 0;
	virtual bool get_property_flag(int type) = 0;
	virtual bool is_two_sided() = 0;
	virtual void set_shader(const char* p_shader_name) = 0;
	virtual int get_num_passes() = 0;
	virtual int get_texture_memory_bytes() = 0;
	virtual void refresh() = 0;
	virtual bool needs_lightmap_blend_alpha() = 0;
	virtual bool needs_software_lighting() = 0;
	virtual int shader_param_count() const = 0;
	virtual void** get_shader_params() = 0;
	virtual bool is_error_material() const = 0;
	virtual void set_use_fixed_function_baked_lighting(bool b_enable) = 0;
	virtual float get_alpha_modulation() = 0;
	virtual void get_color_modulation(float* r, float* g, float* b) = 0;
	virtual morph_format_t	get_morph_format( ) const = 0;
	virtual i_material_var* find_var_fast( char const* pVarName, unsigned int* pToken ) = 0;
	virtual void set_shader_and_params( void* pKeyValues ) = 0;
	virtual const char* get_shader_name( ) const = 0;
	virtual void delete_if_unreferenced( ) = 0;
	virtual bool is_sprite_card( ) = 0;
	virtual void call_bind_proxy( void* proxyData ) = 0;
	virtual i_material* check_proxy_replacement( void* proxyData ) = 0;
	virtual void refresh_preserving_material_vars( ) = 0;
	virtual bool was_reloaded_from_whitelist( ) = 0;
	virtual bool is_precached( ) const = 0;
};

class i_client_renderable;
struct model_t;

enum e_render_depth_mode {
	depth_mode_normal = 0,
	depth_mode_shadow = 1,
	depth_mode_ssa0 = 2,
	depth_mode_override = 3,
	depth_mode_max
};

inline float color_to_float( unsigned char col ) {
	return ( static_cast< float >( col ) / 255.0f );
}

inline vector color_to_vector( color col ) {
	return vector( color_to_float( col.m_r ), color_to_float( col.m_g ), color_to_float( col.m_b ) );
}

class iv_render_view {
public:
	virtual void draw_brush_model( i_client_entity* baseentity, model_t* model, const vector& origin, const vector& angles, bool unused ) = 0;
	virtual void draw_identity_brush_model( i_world_render_list* list, model_t* model ) = 0;
	virtual void touch_light( struct dlight_t* light ) = 0;
	virtual void draw_3d_debug_overlays( void ) = 0;
	virtual void set_blend( float blend ) = 0;
	virtual float get_blend( void ) = 0;
	virtual void set_color_modulation( float const* blend ) = 0;
	virtual void get_color_modulation( float* blend ) = 0;
	virtual void scene_begin( void ) = 0;
	virtual void scene_end( void ) = 0;
	virtual void get_visible_fog_volume( const vector& eye_point, visible_fog_volume_info_t* info ) = 0;
	virtual i_world_render_list* create_world_list( ) = 0;
	virtual void build_world_lists( i_world_render_list* list, world_list_info_t* info, int force_fview_leaf, const vis_override_data_t* vis_data = NULL, bool shadow_depth = false, float* reflection_water_height = NULL ) = 0;
	virtual void draw_world_lists( i_world_render_list* list, unsigned long flags, float water_z_adjust ) = 0;
	virtual void draw_top_view( bool enable ) = 0;
	virtual void top_view_bounds( vector_2d const& mins, vector_2d const& maxs ) = 0;
	virtual void draw_lights( void ) = 0;
	virtual void draw_mask_entities( void ) = 0;
	virtual void draw_translucent_surfaces( i_world_render_list* list, int sort_index, unsigned long flags, bool shadow_depth ) = 0;
	virtual void draw_line_file( void ) = 0;
	virtual void draw_lightmaps( i_world_render_list* list, int page_id ) = 0;
	virtual void view_setup_vis( bool novis, int numorigins, const vector origin[ ] ) = 0;
	virtual bool are_any_leaves_visible( int* leaf_list, int leaves ) = 0;
	virtual	void vgui_paint( void ) = 0;
	virtual void view_draw_fade( byte* color, i_material* material ) = 0;
	virtual void old_set_projection_matrix( float fov, float z_near, float z_far ) = 0;
	virtual color get_light_at_point( vector& pos ) = 0;
	virtual int get_view_entity( void ) = 0;
	virtual float get_field_of_view( void ) = 0;
	virtual unsigned char** get_area_bits( void ) = 0;
	virtual void set_fog_volume_state( int visible_fog_volume, bool use_height_fog ) = 0;
	virtual void install_brush_surface_renderer( i_brush_renderer* brush_renderer ) = 0;
	virtual void draw_brush_model_shadow( i_client_renderable* renderable) = 0;
	virtual	bool leaf_contains_translucent_surfaces( i_world_render_list* list, int sort_index, unsigned long flags ) = 0;
	virtual bool does_box_intersect_water_volume( const vector& mins, const vector& maxs, int leaf_water_data_id ) = 0;
	virtual void set_area_state( unsigned char area_bits[ MAX_AREA_STATE_BYTES ], unsigned char area_portal_bits[ MAX_AREA_PORTAL_STATE_BYTES ] ) = 0;
	virtual void vgui_paint( int mode ) = 0;
	virtual void push_3d_view( const c_view_setup& view, int flags, i_texture* render_target, frustum frustum_planes ) = 0;
	virtual void push_2d_view( const c_view_setup& view, int flags, i_texture* render_target, frustum frustum_planes ) = 0;
	virtual void pop_view( frustum frustum_planes ) = 0;
	virtual void set_main_view( const vector& origin, const vector& angles ) = 0;
	virtual void view_setup_vis_ex( bool novis, int numorigins, const vector origin[ ], unsigned int& return_flags ) = 0;
	virtual void override_view_frustum( frustum custom ) = 0;
	virtual void draw_brush_model_shadow_depth( i_client_entity* baseentity, model_t* model, const vector& origin, const vector& angles, e_render_depth_mode depth_mode ) = 0;
	virtual void update_brush_model_lightmap( model_t* model, i_client_renderable* renderable ) = 0;
	virtual void begin_update_lightmaps( void ) = 0;
	virtual void end_update_lightmaps( void ) = 0;
	virtual void old_set_off_center_projection_matrix( float fov, float z_near, float z_far, float aspect_ratio, float bottom, float top, float left, float right ) = 0;
	virtual void old_set_projection_matrix_ortho( float left, float top, float right, float bottom, float z_near, float z_far ) = 0;
	virtual void push_3d_view( const c_view_setup& view, int flags, i_texture* render_target, frustum frustum_planes, i_texture* depth_texture ) = 0;
	virtual void get_matrices_for_view( const c_view_setup& view, view_matrix* world_to_view, view_matrix* view_to_projection, view_matrix* world_to_projection, view_matrix* world_to_pixels ) = 0;
	virtual void draw_brush_model_ex( i_client_entity* baseentity, model_t* model, const vector& origin, const vector& angles, draw_brush_model_mode_t mode ) = 0;

	inline void set_color_modulation( float r, float g, float b ) {
		float v[ 3 ] = { r, g, b };
		this->set_color_modulation( v );
	}

	inline void set_color_modulation( color clr ) {
		auto v = color_to_vector( clr );
		this->set_color_modulation( &v.m_x );
	}
};

class i_move_helper;
using entity_handle_t = c_base_handle;
class c_base_player;

class c_move_data {
public:
	bool m_first_run_of_functions : 1;
	bool m_game_code_moved_player : 1;
	entity_handle_t m_player_handle;
	int m_impulse_command;
	vector m_view_angles;
	vector m_abs_view_angles;
	int m_buttons;
	int m_old_buttons;
	float m_forward_move;
	float m_old_forward_move;
	float m_side_move;
	float m_up_move;
	float m_max_speed;
	float m_client_max_speed;
	vector m_velocity;
	vector m_angles;
	vector m_old_angles;
	float m_out_step_height;
	vector m_out_wish_vel;
	vector m_out_jump_vel;
	vector m_constraint_center;
	float m_constraint_radius;
	float m_constraint_width;
	float m_constraint_speed_factor;
	vector m_abs_origin;
};

class i_prediction {
public:
	virtual ~i_prediction( void ) { };
	virtual void init( void ) = 0;
	virtual void shutdown( void ) = 0;
	virtual void update( int startframe, bool validframe, int incoming_acknowledged, int outgoing_command ) = 0;
	virtual void pre_entity_packet_received( int commands_acknowledged, int current_world_update_packet ) = 0;
	virtual void post_entity_packet_received( void ) = 0;
	virtual void post_network_data_received( int commands_acknowledged ) = 0;
	virtual void on_received_uncompressed_packet( void ) = 0;
	virtual void get_view_origin( vector& org ) = 0;
	virtual void set_view_origin( vector& org ) = 0;
	virtual void get_view_angles( vector& ang ) = 0;
	virtual void set_view_angles( vector& ang ) = 0;
	virtual void get_local_view_angles( vector& ang ) = 0;
	virtual void set_local_view_angles( vector& ang ) = 0;
};

class c_prediction : public i_prediction {
public:
	virtual ~c_prediction( ) = 0;
	virtual void init( ) = 0;
	virtual void shutdown( ) = 0;
	virtual void update( int startframe, bool validframe, int incoming_acknowledged, int outgoing_command ) = 0;
	virtual void on_received_uncompressed_packet( ) = 0;
	virtual void pre_entity_packet_received( int commands_acknowledged, int current_world_update_packet ) = 0;
	virtual void post_entity_packet_received( ) = 0;
	virtual void post_network_data_received( int commands_acknowledged ) = 0;
	virtual bool in_prediction( ) = 0;
	virtual bool is_first_time_predicted( ) = 0;
	virtual int	get_incoming_packet_number( ) = 0;
	virtual void get_view_origin( vector& org ) = 0;
	virtual void set_view_origin( vector& org ) = 0;
	virtual void get_view_angles( vector& ang ) = 0;
	virtual void set_view_angles( vector& ang ) = 0;
	virtual void get_local_view_angles( vector& ang ) = 0;
	virtual void set_local_view_angles( vector& ang ) = 0;
	virtual void run_command( c_base_player* player, c_user_cmd* ucmd, i_move_helper* move_helper ) = 0;
	virtual void setup_move( c_base_player* player, c_user_cmd* ucmd, i_move_helper* helper, c_move_data* move ) = 0;
	virtual void finish_move( c_base_player* player, c_user_cmd* ucmd, c_move_data* move ) = 0;
	virtual void set_ideal_pitch( c_base_player* player, const vector& origin, const vector& angles, const vector& viewheight ) = 0;
	virtual void _update( bool received_new_world_update, bool validframe, int incoming_acknowledged, int outgoing_command ) = 0;

	uint32_t m_last_ground;
	bool m_in_prediction;
	bool m_first_time_predicted;
	bool m_old_cl_predict_value;
	bool m_engine_paused;
	int m_previous_start_frame;
	int m_commands_predicted;
	int m_server_commands_acknowledged;
	int m_previous_ack_had_errors;
	int m_incoming_packet_number;
	float m_ideal_pitch;
};

class c_game_movement {
public:
	virtual ~c_game_movement( void ) { }
	virtual void process_movement( c_base_player* player, c_move_data* move ) = 0;
	virtual void start_track_prediction_errors( c_base_player* player ) = 0;
	virtual void finish_track_prediction_errors( c_base_player* player ) = 0;
	virtual void diff_print( char const* fmt, ... ) = 0;
	virtual vector get_player_mins( bool ducked ) const = 0;
	virtual vector get_player_maxs( bool ducked ) const = 0;
	virtual vector get_player_view_offset( bool ducked ) const = 0;
};

class c_save_restore_data;

class c_global_vars_base {
public:
	float m_real_time;
	int m_frame_count;
	float m_absolute_frame_time;
	float m_current_time;
	float m_frame_time;
	int m_max_clients;
	int m_tick_count;
	float m_interval_per_tick;
	float m_interpolation_amount;
	int m_sim_ticks_this_frame;
	int m_network_protocol;
	c_save_restore_data* m_save_data;
	bool m_client;
	int m_timestamp_networking_base;
	int m_timestamp_randomize_window;
};

class d_variant;
class recv_table;
class recv_prop;
class c_recv_proxy_data;

using recv_var_proxy_fn = void( * )( const c_recv_proxy_data* data, void* struct_ptr, void* out_ptr );
using array_length_recv_proxy_fn = void( * )( void* struct_ptr, int object_id, int current_array_length );
using data_table_recv_var_proxy_fn = void( * )( const recv_prop* prop, void** out_ptr, void* data_ptr, int object_id );

enum send_prop_type {
	_int = 0,
	_float,
	_vec,
	_vec_xy,
	_string,
	_array,
	_data_table,
	_int_64,
};

class d_variant {
public:
	union {
		float m_float;
		int m_int;
		char* m_string;
		void* m_data;
		float m_vector[ 3 ];
		__int64 m_int64;
	};

	send_prop_type m_type;
};

class c_recv_proxy_data {
public:
	const recv_prop* m_recv_prop;
	d_variant m_value;
	int m_element_index;
	int m_object_id;
};

class recv_prop {
public:
	char* m_prop_name;
	send_prop_type m_prop_type;
	int m_prop_flags;
	int m_buffer_size;
	int m_is_inside_of_array;
	const void* m_extra_data_ptr;
	recv_prop* m_array_prop;
	array_length_recv_proxy_fn m_array_length_proxy;
	void* m_proxy_fn;
	data_table_recv_var_proxy_fn m_data_table_proxy_fn;
	recv_table* m_data_table;
	int m_offset;
	int m_element_stride;
	int m_elements_count;
	const char* m_parent_array_prop_name;
};

class recv_table {
public:
	recv_prop* m_props;
	int m_props_count;
	void* m_decoder_ptr;
	char* m_table_name;
	bool m_is_initialized;
	bool m_is_in_main_list;
};

class c_game_event {
public:
	virtual ~c_game_event( ) { };
	virtual const char* get_name( ) const = 0;
	virtual bool is_reliable( ) const = 0;
	virtual bool is_local( ) const = 0;
	virtual bool is_empty( const char* key = 0) = 0;
	virtual bool get_bool( const char* key = 0, bool default_ = false ) = 0;
	virtual int	get_int( const char* key = 0, int default_ = 0 ) = 0;
	virtual float get_float( const char* key = 0, float default_ = 0.0f ) = 0;
	virtual const char* get_string( const char* key = 0, const char* default_ = "" ) = 0;
	virtual void set_bool( const char* key, bool new_ ) = 0;
	virtual void set_int( const char* key, int new_ ) = 0;
	virtual void set_float( const char* key, float new_ ) = 0;
	virtual void set_string( const char* key, const char* new_ ) = 0;
};

class c_game_event_listener {
public:
	virtual ~c_game_event_listener( void ) { };
	virtual void fire_game_event( c_game_event* event ) = 0;
};

class c_game_event_manager {
public:
	inline bool add_listener( c_game_event_listener* listener, const char* name, bool server_side ) {
		typedef bool( __thiscall* add_listener_fn )( c_game_event_manager*, c_game_event_listener*, const char*, bool );
		return util::get_virtual< add_listener_fn >( this, 3 )( this, listener, name, server_side );
	}

	inline void remove_listener( c_game_event_listener* listener) {
		typedef bool(__thiscall* remove_listener_fn )( c_game_event_manager*, c_game_event_listener* );
		util::get_virtual< remove_listener_fn >( this, 5 )( this, listener );
	}
};

enum e_player_class {
	CLASS_NONE = 0,
	CLASS_SCOUT,
	CLASS_SNIPER,
	CLASS_SOLDIER,
	CLASS_DEMOMAN,
	CLASS_MEDIC,
	CLASS_HEAVY,
	CLASS_PYRO,
	CLASS_SPY,
	CLASS_ENGINEER
};

enum {
	TELEPORTER_STATE_BUILDING = 0,				// Building, not active yet
	TELEPORTER_STATE_IDLE,						// Does not have a matching teleporter yet
	TELEPORTER_STATE_READY,						// Found match, charged and ready
	TELEPORTER_STATE_SENDING,					// Teleporting a player away
	TELEPORTER_STATE_RECEIVING,
	TELEPORTER_STATE_RECEIVING_RELEASE,
	TELEPORTER_STATE_RECHARGING,				// Waiting for recharge
	TELEPORTER_STATE_UPGRADING,

	//
	// ADD NEW ITEMS HERE TO AVOID BREAKING DEMOS
	//
};

#define TELEPORTER_TYPE_ENTRANCE	0
#define TELEPORTER_TYPE_EXIT		1

enum e_tf_grenade_projectile_type {
	TYPE_PIPE,
	TYPE_STICKY
};

enum e_weapon_slots {
	SLOT_PRIMARY,
	SLOT_SECONDARY,
	SLOT_MELEE
};

enum e_minigun_state {
	AC_STATE_IDLE = 0,
	AC_STATE_STARTFIRING,
	AC_STATE_FIRING,
	AC_STATE_SPINNING,
	AC_STATE_DRYFIRE
};

enum e_tf_conds {
	TFCond_Slowed = ( 1 << 0 ),		// Toggled when a player is slowed down. 
	TFCond_Zoomed = ( 1 << 1 ),		// Toggled when a player is zoomed. 
	TFCond_Disguising = ( 1 << 2 ),		// Toggled when a Spy is disguising.  
	TFCond_Disguised = ( 1 << 3 ),		// Toggled when a Spy is disguised. 
	TFCond_Cloaked = ( 1 << 4 ),		// Toggled when a Spy is invisible. 
	TFCond_Ubercharged = ( 1 << 5 ),		// Toggled when a player is UberCharged. 
	TFCond_TeleportedGlow = ( 1 << 6 ),		// Toggled when someone leaves a teleporter and has glow beneath their feet. 
	TFCond_Taunting = ( 1 << 7 ),		// Toggled when a player is taunting. 
	TFCond_UberchargeFading = ( 1 << 8 ),		// Toggled when the UberCharge is fading. 
	TFCond_CloakFlicker = ( 1 << 9 ),		// Toggled when a Spy is visible during cloak. 
	TFCond_Teleporting = ( 1 << 10 ),	// Only activates for a brief second when the player is being teleported; not very useful. 
	TFCond_Kritzkrieged = ( 1 << 11 ),	// Toggled when a player is being crit buffed by the KritzKrieg. 
	TFCond_TmpDamageBonus = ( 1 << 12 ),	// Unknown what this is for. Name taken from the AlliedModders SDK. 
	TFCond_DeadRingered = ( 1 << 13 ),	// Toggled when a player is taking reduced damage from the Deadringer. 
	TFCond_Bonked = ( 1 << 14 ),	// Toggled when a player is under the effects of The Bonk! Atomic Punch. 
	TFCond_Stunned = ( 1 << 15 ),	// Toggled when a player's speed is reduced from airblast or a Sandman ball. 
	TFCond_Buffed = ( 1 << 16 ),	// Toggled when a player is within range of an activated Buff Banner. 
	TFCond_Charging = ( 1 << 17 ),	// Toggled when a Demoman charges with the shield. 
	TFCond_DemoBuff = ( 1 << 18 ),	// Toggled when a Demoman has heads from the Eyelander. 
	TFCond_CritCola = ( 1 << 19 ),	// Toggled when the player is under the effect of The Crit-a-Cola. 
	TFCond_InHealRadius = ( 1 << 20 ),	// Unused condition, name taken from AlliedModders SDK. 
	TFCond_Healing = ( 1 << 21 ),	// Toggled when someone is being healed by a medic or a dispenser. 
	TFCond_OnFire = ( 1 << 22 ),	// Toggled when a player is on fire. 
	TFCond_Overhealed = ( 1 << 23 ),	// Toggled when a player has >100% health. 
	TFCond_Jarated = ( 1 << 24 ),	// Toggled when a player is hit with a Sniper's Jarate. 
	TFCond_Bleeding = ( 1 << 25 ),	// Toggled when a player is taking bleeding damage. 
	TFCond_DefenseBuffed = ( 1 << 26 ),	// Toggled when a player is within range of an activated Battalion's Backup. 
	TFCond_Milked = ( 1 << 27 ),	// Player was hit with a jar of Mad Milk. 
	TFCond_MegaHeal = ( 1 << 28 ),	// Player is under the effect of Quick-Fix charge. 
	TFCond_RegenBuffed = ( 1 << 29 ),	// Toggled when a player is within a Concheror's range. 
	TFCond_MarkedForDeath = ( 1 << 30 ),	// Player is marked for death by a Fan O'War hit. Effects are similar to TFCond_Jarated. 
	TFCond_NoHealingDamageBuff = ( 1 << 31 ),	// Unknown what this is used for.
	TFCondEx_SpeedBuffAlly = ( 1 << 0 ),		// Toggled when a player gets hit with the disciplinary action. 
	TFCondEx_HalloweenCritCandy = ( 1 << 1 ),		// Only for Scream Fortress event maps that drop crit candy. 
	TFCondEx_CritCanteen = ( 1 << 2 ),		// Player is getting a crit boost from a MVM canteen.
	TFCondEx_CritDemoCharge = ( 1 << 3 ),		// From demo's shield
	TFCondEx_CritHype = ( 1 << 4 ),		// Soda Popper crits. 
	TFCondEx_CritOnFirstBlood = ( 1 << 5 ),		// Arena first blood crit buff. 
	TFCondEx_CritOnWin = ( 1 << 6 ),		// End of round crits. 
	TFCondEx_CritOnFlagCapture = ( 1 << 7 ),		// CTF intelligence capture crits. 
	TFCondEx_CritOnKill = ( 1 << 8 ),		// Unknown what this is for. 
	TFCondEx_RestrictToMelee = ( 1 << 9 ),		// Unknown what this is for. 
	TFCondEx_DefenseBuffNoCritBlock = ( 1 << 10 ),	// MvM Buff.
	TFCondEx_Reprogrammed = ( 1 << 11 ),	// MvM Bot has been reprogrammed.
	TFCondEx_PyroCrits = ( 1 << 12 ),	// Player is getting crits from the Mmmph charge. 
	TFCondEx_PyroHeal = ( 1 << 13 ),	// Player is being healed from the Mmmph charge. 
	TFCondEx_FocusBuff = ( 1 << 14 ),	// Player is getting a focus buff.
	TFCondEx_DisguisedRemoved = ( 1 << 15 ),	// Disguised remove from a bot.
	TFCondEx_MarkedForDeathSilent = ( 1 << 16 ),	// Player is under the effects of the Escape Plan/Equalizer or GRU.
	TFCondEx_DisguisedAsDispenser = ( 1 << 17 ),	// Bot is disguised as dispenser.
	TFCondEx_InKart = ( 1 << 18 ),	// MvM bot is being sapped.
	TFCondEx_UberchargedHidden = ( 1 << 19 ),	// MvM Related
	TFCondEx_UberchargedCanteen = ( 1 << 20 ),	// Player is receiving UberCharge from a canteen.
	TFCondEx_HalloweenBombHead = ( 1 << 21 ),	// Player has a bomb on their head from Merasmus.
	TFCondEx_HalloweenThriller = ( 1 << 22 ),	// Players are forced to dance from Merasmus.
	TFCondEx_BulletCharge = ( 1 << 26 ),	// Player is receiving 75% reduced damage from bullets.
	TFCondEx_ExplosiveCharge = ( 1 << 27 ),	// Player is receiving 75% reduced damage from explosives.
	TFCondEx_FireCharge = ( 1 << 28 ),	// Player is receiving 75% reduced damage from fire.
	TFCondEx_BulletResistance = ( 1 << 29 ),	// Player is receiving 10% reduced damage from bullets.
	TFCondEx_ExplosiveResistance = ( 1 << 30 ),	// Player is receiving 10% reduced damage from explosives.
	TFCondEx_FireResistance = ( 1 << 31 ),	// Player is receiving 10% reduced damage from fire.
	TFCondEx2_Stealthed = ( 1 << 0 ),
	TFCondEx2_MedigunDebuff = ( 1 << 1 ),
	TFCondEx2_StealthedUserBuffFade = ( 1 << 2 ),
	TFCondEx2_BulletImmune = ( 1 << 3 ),
	TFCondEx2_BlastImmune = ( 1 << 4 ),
	TFCondEx2_FireImmune = ( 1 << 5 ),
	TFCondEx2_PreventDeath = ( 1 << 6 ),
	TFCondEx2_MVMBotRadiowave = ( 1 << 7 ),
	TFCondEx2_HalloweenSpeedBoost = ( 1 << 8 ),		// Wheel has granted player speed boost.
	TFCondEx2_HalloweenQuickHeal = ( 1 << 9 ),		// Wheel has granted player quick heal.
	TFCondEx2_HalloweenGiant = ( 1 << 10 ),	// Wheel has granted player giant mode.
	TFCondEx2_HalloweenTiny = ( 1 << 11 ),	// Wheel has granted player tiny mode.
	TFCondEx2_HalloweenInHell = ( 1 << 12 ),	// Wheel has granted player in hell mode.
	TFCondEx2_HalloweenGhostMode = ( 1 << 13 ),	// Wheel has granted player ghost mode.
	TFCondEx2_Parachute = ( 1 << 16 ),	// Player has deployed the BASE Jumper.
	TFCondEx2_BlastJumping = ( 1 << 17 ),	// Player has sticky or rocket jumped.
	TFCond_MiniCrits = ( TFCond_Buffed | TFCond_CritCola ),
	TFCond_IgnoreStates = ( TFCond_Ubercharged | TFCond_Bonked ),
	TFCondEx_IgnoreStates = ( TFCondEx_PyroHeal )
};

enum e_tf_cond
{
	TF_COND_INVALID = -1,
	TF_COND_AIMING,
	TF_COND_ZOOMED,
	TF_COND_DISGUISING,
	TF_COND_DISGUISED,
	TF_COND_STEALTHED,
	TF_COND_INVULNERABLE,
	TF_COND_TELEPORTED,
	TF_COND_TAUNTING,
	TF_COND_INVULNERABLE_WEARINGOFF,
	TF_COND_STEALTHED_BLINK,
	TF_COND_SELECTED_TO_TELEPORT,
	TF_COND_CRITBOOSTED,
	TF_COND_TMPDAMAGEBONUS,
	TF_COND_FEIGN_DEATH,
	TF_COND_PHASE,
	TF_COND_STUNNED,
	TF_COND_OFFENSEBUFF,
	TF_COND_SHIELD_CHARGE,
	TF_COND_DEMO_BUFF,
	TF_COND_ENERGY_BUFF,
	TF_COND_RADIUSHEAL,
	TF_COND_HEALTH_BUFF,
	TF_COND_BURNING,
	TF_COND_HEALTH_OVERHEALED,
	TF_COND_URINE,
	TF_COND_BLEEDING,
	TF_COND_DEFENSEBUFF,
	TF_COND_MAD_MILK,
	TF_COND_MEGAHEAL,
	TF_COND_REGENONDAMAGEBUFF,
	TF_COND_MARKEDFORDEATH,
	TF_COND_NOHEALINGDAMAGEBUFF,
	TF_COND_SPEED_BOOST,
	TF_COND_CRITBOOSTED_PUMPKIN,
	TF_COND_CRITBOOSTED_USER_BUFF,
	TF_COND_CRITBOOSTED_DEMO_CHARGE,
	TF_COND_SODAPOPPER_HYPE,
	TF_COND_CRITBOOSTED_FIRST_BLOOD,
	TF_COND_CRITBOOSTED_BONUS_TIME,
	TF_COND_CRITBOOSTED_CTF_CAPTURE,
	TF_COND_CRITBOOSTED_ON_KILL,
	TF_COND_CANNOT_SWITCH_FROM_MELEE,
	TF_COND_DEFENSEBUFF_NO_CRIT_BLOCK,
	TF_COND_REPROGRAMMED,
	TF_COND_CRITBOOSTED_RAGE_BUFF,
	TF_COND_DEFENSEBUFF_HIGH,
	TF_COND_SNIPERCHARGE_RAGE_BUFF,
	TF_COND_DISGUISE_WEARINGOFF,
	TF_COND_MARKEDFORDEATH_SILENT,
	TF_COND_DISGUISED_AS_DISPENSER,
	TF_COND_SAPPED,
	TF_COND_INVULNERABLE_HIDE_UNLESS_DAMAGE,
	TF_COND_INVULNERABLE_USER_BUFF,
	TF_COND_HALLOWEEN_BOMB_HEAD,
	TF_COND_HALLOWEEN_THRILLER,
	TF_COND_RADIUSHEAL_ON_DAMAGE,
	TF_COND_CRITBOOSTED_CARD_EFFECT,
	TF_COND_INVULNERABLE_CARD_EFFECT,
	TF_COND_MEDIGUN_UBER_BULLET_RESIST,
	TF_COND_MEDIGUN_UBER_BLAST_RESIST,
	TF_COND_MEDIGUN_UBER_FIRE_RESIST,
	TF_COND_MEDIGUN_SMALL_BULLET_RESIST,
	TF_COND_MEDIGUN_SMALL_BLAST_RESIST,
	TF_COND_MEDIGUN_SMALL_FIRE_RESIST,
	TF_COND_STEALTHED_USER_BUFF,
	TF_COND_MEDIGUN_DEBUFF,
	TF_COND_STEALTHED_USER_BUFF_FADING,
	TF_COND_BULLET_IMMUNE,
	TF_COND_BLAST_IMMUNE,
	TF_COND_FIRE_IMMUNE,
	TF_COND_PREVENT_DEATH,
	TF_COND_MVM_BOT_STUN_RADIOWAVE,
	TF_COND_HALLOWEEN_SPEED_BOOST,
	TF_COND_HALLOWEEN_QUICK_HEAL,
	TF_COND_HALLOWEEN_GIANT,
	TF_COND_HALLOWEEN_TINY,
	TF_COND_HALLOWEEN_IN_HELL,
	TF_COND_HALLOWEEN_GHOST_MODE,
	TF_COND_MINICRITBOOSTED_ON_KILL,
	TF_COND_OBSCURED_SMOKE,
	TF_COND_PARACHUTE_ACTIVE,
	TF_COND_BLASTJUMPING,
	TF_COND_HALLOWEEN_KART,
	TF_COND_HALLOWEEN_KART_DASH,
	TF_COND_BALLOON_HEAD,
	TF_COND_MELEE_ONLY,
	TF_COND_SWIMMING_CURSE,
	TF_COND_FREEZE_INPUT,
	TF_COND_HALLOWEEN_KART_CAGE,
	TF_COND_DONOTUSE_0,
	TF_COND_RUNE_STRENGTH,
	TF_COND_RUNE_HASTE,
	TF_COND_RUNE_REGEN,
	TF_COND_RUNE_RESIST,
	TF_COND_RUNE_VAMPIRE,
	TF_COND_RUNE_REFLECT,
	TF_COND_RUNE_PRECISION,
	TF_COND_RUNE_AGILITY,
	TF_COND_GRAPPLINGHOOK,
	TF_COND_GRAPPLINGHOOK_SAFEFALL,
	TF_COND_GRAPPLINGHOOK_LATCHED,
	TF_COND_GRAPPLINGHOOK_BLEEDING,
	TF_COND_AFTERBURN_IMMUNE,
	TF_COND_RUNE_KNOCKOUT,
	TF_COND_RUNE_IMBALANCE,
	TF_COND_CRITBOOSTED_RUNE_TEMP,
	TF_COND_PASSTIME_INTERCEPTION,
	TF_COND_SWIMMING_NO_EFFECTS,
	TF_COND_PURGATORY,
	TF_COND_RUNE_KING,
	TF_COND_RUNE_PLAGUE,
	TF_COND_RUNE_SUPERNOVA,
	TF_COND_PLAGUE,
	TF_COND_KING_BUFFED,
	TF_COND_TEAM_GLOWS,
	TF_COND_KNOCKED_INTO_AIR,
	TF_COND_COMPETITIVE_WINNER,
	TF_COND_COMPETITIVE_LOSER,
	TF_COND_HEALING_DEBUFF,
	TF_COND_PASSTIME_PENALTY_DEBUFF,
	TF_COND_GRAPPLED_TO_PLAYER,
	TF_COND_GRAPPLED_BY_PLAYER,
	TF_COND_PARACHUTE_DEPLOYED,
	TF_COND_GAS,
	TF_COND_BURNING_PYRO,
	TF_COND_ROCKETPACK,
	TF_COND_LOST_FOOTING,
	TF_COND_AIR_CURRENT,
	TF_COND_HALLOWEEN_HELL_HEAL,
	TF_COND_POWERUPMODE_DOMINANT
};

class i_net_channel_info {
public:
	enum {
		GENERIC = 0,
		LOCALPLAYER,
		OTHERPLAYERS,
		ENTITIES,
		SOUNDS,
		EVENTS,
		USERMESSAGES,
		ENTMESSAGES,
		VOICE,
		STRINGTABLE,
		MOVE,
		STRINGCMD,
		SIGNON,
		TOTAL,
	};

	virtual const char* get_name( void ) const = 0;
	virtual const char* get_address( void ) const = 0;
	virtual float get_time( void ) const = 0;
	virtual float get_time_connected( void ) const = 0;
	virtual int get_buffer_size( void ) const = 0;
	virtual int get_data_rate( void ) const = 0;
	virtual bool is_loopback( void ) const = 0;
	virtual bool is_timing_out( void ) const = 0;
	virtual bool is_playback( void ) const = 0;
	virtual float get_latency( int flow ) const = 0;
	virtual float get_avg_latency( int flow ) const = 0;
	virtual float get_avg_loss( int flow ) const = 0;
	virtual float get_avg_choke( int flow ) const = 0;
	virtual float get_data_pata( int flow ) const = 0;
	virtual float get_avg_packets( int flow ) const = 0;
	virtual int get_total_data( int flow ) const = 0;
	virtual int get_sequence_nr( int flow ) const = 0;
	virtual bool is_valid_packet( int flow, int frame_number ) const = 0;
	virtual float get_packet_time( int flow, int frame_number ) const = 0;
	virtual int get_packet_bytes( int flow, int frame_number, int group ) const = 0;
	virtual bool get_stream_progress( int flow, int* received, int* total ) const = 0;
	virtual float get_time_since_last_received( void ) const = 0;
	virtual	float get_command_interpolation_amount( int flow, int frame_number ) const = 0;
	virtual void get_packet_responseLatency( int flow, int frame_number, int* latency_msecs, int* choke ) const = 0;
	virtual void get_remote_framerate( float* frame_time, float* frame_time_std_deviation ) const = 0;
	virtual float get_timeout_seconds( ) const = 0;
};

class i_net_channel : public i_net_channel_info {
public:
	virtual ~i_net_channel( void ) { };
	virtual void set_data_rate( float rate ) = 0;
	virtual bool register_message( void* msg ) = 0;
	virtual bool start_streaming( unsigned int challenge_nr ) = 0;
	virtual void reset_streaming( void ) = 0;
	virtual void set_timeout( float seconds ) = 0;
	virtual void set_demo_recorder( void* recorder ) = 0;
	virtual void set_challenge_nr( unsigned int chnr ) = 0;
	virtual void reset( void ) = 0;
	virtual void clear( void ) = 0;
	virtual void shutdown( const char* reason ) = 0;
	virtual void process_layback( void ) = 0;
	virtual bool process_stream( void ) = 0;
	virtual void process_packet( struct netpacket_s* packet, bool has_header ) = 0;
	virtual bool send_net_msg( void* msg, bool force_reliable = false, bool voice = false ) = 0;
	virtual bool send_data( void* msg, bool reliable = true) = 0;
	virtual bool send_file( const char* filename, unsigned int transfer_id ) = 0;
	virtual void deny_file( const char* filename, unsigned int transfer_id ) = 0;
	virtual void request_file_old( const char* filename, unsigned int transfer_id ) = 0;
	virtual void set_choked( void ) = 0;
	virtual int send_datagram( void* data ) = 0;
	virtual bool transmit( bool only_reliable = false ) = 0;
	virtual const void* get_remote_address( void ) const = 0;
	virtual void* get_msg_handler( void ) const = 0;
	virtual int get_drop_number( void ) const = 0;
	virtual int	get_socket( void ) const = 0;
	virtual unsigned int get_challenge_nr( void ) const = 0;
	virtual void get_sequence_data( int& out_sequence_nr, int& in_sequence_nr, int& out_sequence_nr_ack ) = 0;
	virtual void set_sequence_data( int out_sequence_nr, int in_sequence_nr, int out_sequence_nr_ack ) = 0;
	virtual void update_message_stats( int msg_group, int bits ) = 0;
	virtual bool can_packet( void ) const = 0;
	virtual bool is_overflowed( void ) const = 0;
	virtual bool is_timed_out( void ) const = 0;
	virtual bool has_pending_reliable_data( void ) = 0;
	virtual void set_file_transmission_mode( bool background_mode ) = 0;
	virtual void set_compression_mode( bool use_compression ) = 0;
	virtual unsigned int request_file( const char* filename ) = 0;
	virtual float get_time_since_last_received( void ) const = 0;
	virtual void set_max_buffer_size( bool reliable, int bytes, bool voice = false ) = 0;
	virtual bool is_null( ) const = 0;
	virtual int get_num_bits_written( bool reliable ) = 0;
	virtual void set_interpolation_amount( float interpolation_amount ) = 0;
	virtual void set_remote_frametime( float frame_time, float frame_time_std_deviation ) = 0;
	virtual void set_max_routable_payload_size( int split_size ) = 0;
	virtual int get_max_routable_payload_size( ) = 0;
	virtual int get_protocol_version( ) = 0;
};

typedef void* file_handle_t;

typedef struct net_adr_s {
public:
	unsigned char m_ip[ 4 ];
	unsigned short m_port;
} netadr_t;

class c_net_channel : public i_net_channel {
public:
	typedef struct data_fragments_s {
		file_handle_t m_file;				// open file handle
		char m_filename[ 260 ];		// filename
		char* m_buffer;					// if NULL it's a file
		unsigned int m_bytes;				// size in BYTEs
		unsigned int m_bits;				// size in bits
		unsigned int m_transfer_id;		// only for files
		bool m_is_compressed;				// true if data is bzip compressed
		unsigned int m_uncompressed_size; // full size in BYTEs
		bool m_as_tcp;						// send as TCP stream
		int m_num_fragments;				// number of total fragments
		int m_acked_fragments;				// number of fragments send & acknowledged
		int m_pending_fragments;			// number of fragments send, but not acknowledged yet
	} data_fragments_t;

	struct sub_channel_s {
		int m_start_fraggment[ 2 ];
		int m_num_fragments[ 2 ];
		int m_send_seq_nr;
		int m_state;
		int m_index;

		void free( ) {
			m_state = 0;
			m_send_seq_nr = -1;

			for ( int i = 0; i < 2; i++ ) {
				m_num_fragments[ i ] = 0;
				m_start_fraggment[ i ] = -1;
			}
		}
	};

	typedef struct netframe_s {
		float m_time;
		int m_size;
		float m_latency;
		float m_avg_latency;
		bool m_valid;
		int m_choked;
		int m_dropped;
		float m_interpolation_amount;
		unsigned short m_msg_groups[ i_net_channel_info::TOTAL ];
	} netframe_t;

	typedef struct {
		float m_next_compute;
		float m_avg_bytes_per_sec;
		float m_avg_packets_per_sec;
		float m_avg_loss;
		float m_avg_choke;
		float m_avg_latency;
		float m_latency;
		int m_total_packets;
		int m_total_bytes;
		int m_current_index;
		netframe_t m_frames[ 64 ];
		netframe_t* m_current_frame;
	} netflow_t;

public:
	bool m_processing_messages;
	bool m_should_delete;
	int m_out_sequence_nr;
	int m_in_sequence_nr;
	int m_out_sequence_nr_ack;
	int m_out_reliable_state;
	int m_in_reliable_state;
	int m_choked_packets;
	int m_socket;
	int m_stream_socket;
	unsigned int m_max_reliable_payload_size;
	netadr_t m_remote_address;
	float m_last_received;
	double m_connect_time;
	int m_rate;
	double m_clear_time;
	data_fragments_t m_receive_list[ 2 ];
	sub_channel_s m_sub_channels[ 8 ];
	unsigned int m_file_request_counter;
	bool m_file_background_tranmission;
	bool m_use_compression;
	bool m_stream_active;
	int m_stream_type;
	int m_stream_seq_nr;
	int m_stream_length;
	int m_stream_received;
	netflow_t m_data_flow[ 2 ];
	int m_msg_stats[ i_net_channel_info::TOTAL ];
	int m_packet_drop;
	char m_name[ 32 ];
	unsigned int m_challeng_nr;
	float m_timeout;
	void* m_message_handler;
	int m_queued_packets;
	float m_interpolation_amount;
	float m_remote_frame_time;
	float m_remote_frame_time_std_deviation;
	int m_max_routable_payload_size;
	int m_split_packet_sequence;
};

typedef struct weapon_data_t {
	int m_damage;
	int m_bullets_per_shot;
	float m_range;
	float m_spread;
	float m_punch_angle;
	float m_time_fire_delay;
	float m_time_idle;
	float m_time_idle_empty;
	float m_time_reload_start;
	float m_time_reload;
	bool m_draw_crosshair;
	int m_projectile;
	int m_ammo_per_shot;
	float m_projectile_speed;
	float m_smack_delay;
	bool m_use_rapid_fire_crits;
} weapon_data;

#define MAX_WEAPON_STRING 80
class key_values;

class file_weapon_info_t {
public:
	file_weapon_info_t( );
	virtual void parse( key_values* key_values_data, const char* weapon_name );

public:
	bool m_parsed_script;
	bool m_loaded_hud_elements;
	char m_class_name[ MAX_WEAPON_STRING ];
	char m_print_name[ MAX_WEAPON_STRING ];
	char m_view_model[ MAX_WEAPON_STRING ];
	char m_world_model[ MAX_WEAPON_STRING ];
	char m_animation_prefix[ 16 ];
	int m_slot;
	int m_position;
	int m_max_clip1;
	int m_max_clip2;
	int m_default_clip1;
	int m_default_clip2;
	int m_weight;
	int m_rumble_effect;
	bool m_auto_switch_to;
	bool m_auto_switch_from;
	int m_flags;
	char m_ammo1[ 32 ];
	char m_ammo2[ 32 ];
	char m_shoot_sounds[ 16 ][ MAX_WEAPON_STRING ];
	int m_ammo_type;
	int m_ammo2_type;
	bool m_melee_weapon;
	bool m_built_right_handed;
	bool m_allow_flipping;
	int m_sprite_count;
	void* m_icon_active;
	void* m_icon_inactive;
	void* m_icon_ammo;
	void* m_icon_ammo2;
	void* m_icon_crosshair;
	void* m_icon_autoaim;
	void* m_icon_zoomed_crosshair;
	void* m_icon_zoomed_autoaim;
	void* m_icon_small;
	bool m_show_usage_hint;
};

class c_tf_weapon_info : public file_weapon_info_t {
public:
	c_tf_weapon_info( );
	~c_tf_weapon_info( );

	virtual void parse( key_values* key_values_data, const char* weapon_name );

	weapon_data_t const& get_weapon_data( int weapon ) const {
		return m_weapon_data[ weapon ];
	}

public:
	weapon_data_t m_weapon_data[ 2 ];
	int m_weapon_type;
	bool m_grenade;
	float m_damage_radius;
	float m_primer_time;
	bool m_lower_weapon;
	bool m_suppress_gren_timer;
	bool m_has_team_skins_viewmodel;
	bool m_has_team_skins_worldmodel;
	char m_muzzle_flash_model[ 128 ];
	float m_muzzle_flash_model_duration;
	char m_muzzle_flash_particle_effect[ 128 ];
	char m_tracer_effect[ 128 ];
	bool m_do_instant_eject_brass;
	char m_brass_model[ 128 ];
	char m_explosionSound[ 128 ];
	char m_explosionEffect[ 128 ];
	char m_explosion_player_effect[ 128 ];
	char m_explosion_water_effect[ 128 ];
	bool m_dont_drop;
};

class i_net_message {
public:
	virtual ~i_net_message( ) { };
	virtual void set_net_channel( i_net_channel* netchan ) = 0;
	virtual void set_reliable( bool state ) = 0;
	virtual bool process( void ) = 0;
	virtual bool read_from_buffer( bf_read& buffer ) = 0;
	virtual bool write_to_buffer( bf_write& buffer ) = 0;
	virtual bool is_reliable( void ) const = 0;
	virtual int get_type( void ) const = 0;
	virtual int get_group( void ) const = 0;
	virtual const char* get_name( void ) const = 0;
	virtual i_net_channel* get_net_channel( void ) const = 0;
	virtual const char* to_string( void ) const = 0;
};

class c_net_message : public i_net_message {
public:
	c_net_message( ) {
		m_reliable = true;
		m_net_channel = nullptr;
	}

	virtual ~c_net_message( ) { };
	virtual int get_group( ) const { return i_net_channel_info::GENERIC; }
	i_net_channel* get_net_channel( ) const { return m_net_channel; }
	virtual void set_reliable( bool state ) { m_reliable = state; };
	virtual bool is_reliable( ) const { return m_reliable; };
	virtual void set_net_channel( i_net_channel* netchan ) { m_net_channel = netchan; }
	virtual bool process( ) { return false; }; // no handler set

protected:
	bool m_reliable;          // true if message should be send reliable
	i_net_channel* m_net_channel; // netchannel this message is from/for
};

class net_stringcmd : public c_net_message
{
public:
	bool read_from_buffer( bf_read& buffer );
	bool write_to_buffer( bf_write& buffer );
	const char* to_string( ) const;
	int get_type( ) const { return 4; }
	const char* get_name( ) const { return "net_StringCmd"; }
	void* m_message_handler;

	int	get_group( ) const { return 12; }

	net_stringcmd( ) { m_command = NULL; };
	net_stringcmd( const char* cmd ) { m_command = cmd; };

public:
	const char* m_command;	// execute this command
private:
	char		m_command_buffer[ 1024 ];	// buffer for received messages
};

class clc_move : public c_net_message {
public:
	bool read_from_buffer( bf_read& buffer );
	bool write_to_buffer( bf_write& buffer );
	const char* to_string( ) const;
	int get_type( ) const { return 9; }
	const char* get_name( ) const { return "clc_Move"; }
	void* m_message_handler;
	int get_group( ) const { return i_net_channel::MOVE; }
	clc_move( ) { m_reliable = false; }

public:
	int m_backup_commands;
	int m_new_commands;
	int m_length;
	bf_read m_data_in;
	bf_write m_data_out;
};

class c_clock_drift_mgr {
public:
	enum { NUM_CLOCKDRIFT_SAMPLES = 16 };
	float m_clock_offsets[ NUM_CLOCKDRIFT_SAMPLES ];
	int m_current_clock_offset;
	int m_server_tick;
	int	m_client_tick;
};

class c_client_state {
	byte m_pad[ 0x10 ];
public:
	c_net_channel* m_net_channel;
private:
	byte m_pad_[ 0x140 ];
public:
	c_clock_drift_mgr m_clock_drift_mgr;
	int m_delta_tick;
private:
	byte m_pad__[ 0x110 ];
public:
	int m_max_clients;
private:
	byte m_pad___[ 0x4860 ];
public:
	int m_old_tickcount;
	float m_tick_remainder;
	float m_frame_time;
	int m_last_out_going_command;
	int m_choked_commands;
	int m_last_command_ack;
};
namespace fnv_1a {
	template< typename S >
	struct fnv_internal;
	template< typename S >
	struct fnv1a;

	template< >
	struct fnv_internal< uint32_t > {
		constexpr static uint32_t default_offset_basis = 0x811C9DC5;
		constexpr static uint32_t prime = 0x01000193;
	};

	template< >
	struct fnv1a< uint32_t > : public fnv_internal< uint32_t > {
		constexpr static uint32_t hash(char const* string, const uint32_t val = default_offset_basis) {
			return (string[0] == '\0') ? val : hash(&string[1], (val ^ uint32_t(string[0])) * prime);
		}

		constexpr static uint32_t hash(wchar_t const* string, const uint32_t val = default_offset_basis) {
			return (string[0] == L'\0') ? val : hash(&string[1], (val ^ uint32_t(string[0])) * prime);
		}
	};
}

using fnv = fnv_1a::fnv1a< uint32_t >;

class c_clockdriftmgr
{
public:
	enum { NUM_CLOCKDRIFT_SAMPLES = 16 };
	float m_ClockOffsets[NUM_CLOCKDRIFT_SAMPLES];
	int m_iCurClockOffset;
	int m_nServerTick;
	int	m_nClientTick;
};

class c_clientstate
{
public:
	char pad0[0x10];
	void* m_netchannel;
	char pad1[0x140];
	c_clockdriftmgr m_clockdriftmanager;
	int m_deltatick;
	char pad2[0x110];
	int m_maxclients;
	char pad3[0x486C];
	int lastoutgoingcommand;
	int chokedcommands;
	int last_command_ack;
};

struct cplane_t {
	vector m_normal;
	float m_dist;
	std::byte m_type;
	std::byte m_signbits;
	std::byte m_pad[ 2 ];
};

class __declspec( align( 16 ) )vector_aligned : public vector {
public:
	inline vector_aligned( void ) { };

	inline vector_aligned( float x, float y, float z ) {
		this->set( x, y, z );
	}

	explicit vector_aligned( const vector& other ) {
		this->set( other.m_x, other.m_y, other.m_z );
	}

	vector_aligned& operator=( const vector& other ) {
		this->set( other.m_x, other.m_y, other.m_z );
		return *this;
	}

	float w;
};

struct ray_t {
	vector_aligned m_start;
	vector_aligned m_delta;
	vector_aligned m_start_offset;
	vector_aligned m_extents;
	bool m_is_ray;
	bool m_is_swept;

	void init( vector const& start, vector const& end ) {
		m_delta = end - start;
		m_is_swept = ( m_delta.length_sqr( ) != 0 );
		m_extents.set( );
		m_is_ray = true;
		m_start_offset.set( );
		m_start = start;
	}

	void init( vector const& start, vector const& end, vector const& mins, vector const& maxs ) {
		m_delta = end - start;
		m_is_swept = ( m_delta.length_sqr( ) != 0 );
		m_extents = maxs - mins;
		m_extents *= 0.5f;
		m_is_ray = ( m_extents.length_sqr( ) < 1e-6 );
		m_start_offset = mins + maxs;
		m_start_offset *= 0.5f;
		m_start = start + m_start_offset;
		m_start_offset *= -1.0f;
	}

	vector inv_delta( ) const {
		vector inv_delta = vector( );

		for ( int axis = 0; axis < 3; ++axis ) {
			if ( m_delta[ axis ] != 0.0f )
				inv_delta[ axis ] = 1.0f / m_delta[ axis ];

			else
				inv_delta[ axis ] = FLT_MAX;
		}

		return inv_delta;
	}
};

#define DISPSURF_FLAG_SURFACE		( 1 << 0 )
#define DISPSURF_FLAG_WALKABLE		( 1 << 1 )
#define DISPSURF_FLAG_BUILDABLE		( 1 << 2 )
#define DISPSURF_FLAG_SURFPROP1		( 1 << 3 )
#define DISPSURF_FLAG_SURFPROP2		( 1 << 4 )

class c_base_trace {
public:
	bool is_disp_surface( void ) { return ( ( m_disp_flags & DISPSURF_FLAG_SURFACE ) != 0 ); }
	bool is_disp_surface_walkable( void ) { return ( ( m_disp_flags & DISPSURF_FLAG_WALKABLE ) != 0 ); }
	bool is_disp_surface_buildable( void ) { return ( ( m_disp_flags & DISPSURF_FLAG_BUILDABLE ) != 0 ); }
	bool is_disp_surface_prop1( void ) { return ( ( m_disp_flags & DISPSURF_FLAG_SURFPROP1 ) != 0 ); }
	bool is_disp_surface_prop2( void ) { return ( ( m_disp_flags & DISPSURF_FLAG_SURFPROP2 ) != 0 ); }

public:
	vector m_start_position;
	vector m_end_position;
	cplane_t m_plane;
	float m_fraction;
	int m_contents;
	unsigned short m_disp_flags;
	bool m_allsolid;
	bool m_startsolid;
};

struct csurface_t {
	const char* m_name;
	short m_surface_props;
	unsigned short m_flags;
};

class c_base_entity;

class c_game_trace : public c_base_trace {
public:
	float m_fractionleftsolid;
	csurface_t m_surface;
	int m_hitgroup;
	short m_physicsbone;
	c_base_entity* m_ent;
	int m_hitbox;

	bool did_hit_world( ) const {
		return m_ent == NULL;
	}

	bool did_hit_non_world_entity( ) const {
		return m_ent != NULL && !did_hit_world( );
	}

	bool did_hit( ) const {
		return m_fraction < 1 || m_allsolid || m_startsolid;
	}
};

enum trace_type_t {
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

class c_trace_filter {
public:
	virtual bool should_hit_entity( i_handle_entity* server_entity, int contents_mask ) = 0;
	virtual trace_type_t get_trace_type( ) const = 0;
};

class c_trace_filter_entities_only : public c_trace_filter {
public:
	virtual bool should_hit_entity( i_handle_entity* server_entity, int contents_mask ) override {
		return true;
	}

	virtual trace_type_t get_trace_type( ) const override {
		return TRACE_ENTITIES_ONLY;
	}
};

class c_trace_filter_world_only : public c_trace_filter {
public:
	virtual bool should_hit_entity( i_handle_entity* server_entity, int contents_mask ) override {
		return false;
	}

	virtual trace_type_t get_trace_type( ) const override {
		return TRACE_WORLD_ONLY;
	}
};

class c_trace_filter_world_and_props_only : public c_trace_filter {
public:
	virtual bool should_hit_entity( i_handle_entity* server_entity, int contents_mask ) override {
		return false;
	}

	virtual trace_type_t get_trace_type( ) const override {
		return TRACE_EVERYTHING;
	}
};

class c_trace_filter_hit_all : public c_trace_filter {
public:
	virtual bool should_hit_entity( i_handle_entity* server_entity, int contents_mask ) override {
		return true;
	}

	virtual trace_type_t get_trace_type( ) const override {
		return TRACE_EVERYTHING;
	}
};

class c_trace_filter_hitscan : public c_trace_filter {
public:
	virtual bool should_hit_entity( i_handle_entity* server_entity, int contents_mask );

	virtual trace_type_t get_trace_type( ) const override {
		return TRACE_EVERYTHING;
	}

	i_client_entity* m_skip = nullptr;
};

class i_engine_trace {
public:
	inline void trace_ray( const ray_t& ray, unsigned int mask, c_trace_filter* trace_filter, c_game_trace* game_trace ) {
		typedef void( __thiscall* trace_ray_fn )( i_engine_trace*, const ray_t&, unsigned int, c_trace_filter*, c_game_trace* );
		return util::get_virtual< trace_ray_fn >( this, 4u )( this, ray, mask, trace_filter, game_trace );
	}
};

enum tf_weapon_type {
	TF_WEAPON_NONE = 0,
	TF_WEAPON_BAT,
	TF_WEAPON_BAT_WOOD,
	TF_WEAPON_BOTTLE,
	TF_WEAPON_FIREAXE,
	TF_WEAPON_CLUB,
	TF_WEAPON_CROWBAR,
	TF_WEAPON_KNIFE,
	TF_WEAPON_FISTS,
	TF_WEAPON_SHOVEL,
	TF_WEAPON_WRENCH,
	TF_WEAPON_BONESAW,
	TF_WEAPON_SHOTGUN_PRIMARY,
	TF_WEAPON_SHOTGUN_SOLDIER,
	TF_WEAPON_SHOTGUN_HWG,
	TF_WEAPON_SHOTGUN_PYRO,
	TF_WEAPON_SCATTERGUN,
	TF_WEAPON_SNIPERRIFLE,
	TF_WEAPON_MINIGUN,
	TF_WEAPON_SMG,
	TF_WEAPON_SYRINGEGUN_MEDIC,
	TF_WEAPON_TRANQ,
	TF_WEAPON_ROCKETLAUNCHER,
	TF_WEAPON_GRENADELAUNCHER,
	TF_WEAPON_PIPEBOMBLAUNCHER,
	TF_WEAPON_FLAMETHROWER,
	TF_WEAPON_GRENADE_NORMAL,
	TF_WEAPON_GRENADE_CONCUSSION,
	TF_WEAPON_GRENADE_NAIL,
	TF_WEAPON_GRENADE_MIRV,
	TF_WEAPON_GRENADE_MIRV_DEMOMAN,
	TF_WEAPON_GRENADE_NAPALM,
	TF_WEAPON_GRENADE_GAS,
	TF_WEAPON_GRENADE_EMP,
	TF_WEAPON_GRENADE_CALTROP,
	TF_WEAPON_GRENADE_PIPEBOMB,
	TF_WEAPON_GRENADE_SMOKE_BOMB,
	TF_WEAPON_GRENADE_HEAL,
	TF_WEAPON_GRENADE_STUNBALL,
	TF_WEAPON_GRENADE_JAR,
	TF_WEAPON_GRENADE_JAR_MILK,
	TF_WEAPON_PISTOL,
	TF_WEAPON_PISTOL_SCOUT,
	TF_WEAPON_REVOLVER,
	TF_WEAPON_NAILGUN,
	TF_WEAPON_PDA,
	TF_WEAPON_PDA_ENGINEER_BUILD,
	TF_WEAPON_PDA_ENGINEER_DESTROY,
	TF_WEAPON_PDA_SPY,
	TF_WEAPON_BUILDER,
	TF_WEAPON_MEDIGUN,
	TF_WEAPON_GRENADE_MIRVBOMB,
	TF_WEAPON_FLAMETHROWER_ROCKET,
	TF_WEAPON_GRENADE_DEMOMAN,
	TF_WEAPON_SENTRY_BULLET,
	TF_WEAPON_SENTRY_ROCKET,
	TF_WEAPON_DISPENSER,
	TF_WEAPON_INVIS,
	TF_WEAPON_FLAREGUN,
	TF_WEAPON_LUNCHBOX,
	TF_WEAPON_JAR,
	TF_WEAPON_COMPOUND_BOW,
	TF_WEAPON_BUFF_ITEM,
	TF_WEAPON_PUMPKIN_BOMB,
	TF_WEAPON_SWORD,
	TF_WEAPON_ROCKETLAUNCHER_DIRECTHIT,
	TF_WEAPON_LIFELINE,
	TF_WEAPON_LASER_POINTER,
	TF_WEAPON_DISPENSER_GUN,
	TF_WEAPON_SENTRY_REVENGE,
	TF_WEAPON_JAR_MILK,
	TF_WEAPON_HANDGUN_SCOUT_PRIMARY,
	TF_WEAPON_BAT_FISH,
	TF_WEAPON_CROSSBOW,
	TF_WEAPON_STICKBOMB,
	TF_WEAPON_HANDGUN_SCOUT_SECONDARY,
	TF_WEAPON_SODA_POPPER,
	TF_WEAPON_SNIPERRIFLE_DECAP,
	TF_WEAPON_RAYGUN,
	TF_WEAPON_PARTICLE_CANNON,
	TF_WEAPON_MECHANICAL_ARM,
	TF_WEAPON_DRG_POMSON,
	TF_WEAPON_BAT_GIFTWRAP,
	TF_WEAPON_GRENADE_ORNAMENT_BALL,
	TF_WEAPON_FLAREGUN_REVENGE,
	TF_WEAPON_PEP_BRAWLER_BLASTER,
	TF_WEAPON_CLEAVER,
	TF_WEAPON_GRENADE_CLEAVER,
	TF_WEAPON_STICKY_BALL_LAUNCHER,
	TF_WEAPON_GRENADE_STICKY_BALL,
	TF_WEAPON_SHOTGUN_BUILDING_RESCUE,
	TF_WEAPON_CANNON,
	TF_WEAPON_THROWABLE,
	TF_WEAPON_GRENADE_THROWABLE,
	TF_WEAPON_PDA_SPY_BUILD,
	TF_WEAPON_GRENADE_WATERBALLOON,
	TF_WEAPON_HARVESTER_SAW,
	TF_WEAPON_SPELLBOOK,
	TF_WEAPON_SPELLBOOK_PROJECTILE,
	TF_WEAPON_SNIPERRIFLE_CLASSIC,
	TF_WEAPON_PARACHUTE,
	TF_WEAPON_GRAPPLINGHOOK,
	TF_WEAPON_PASSTIME_GUN,
	TF_WEAPON_CHARGED_SMG,
	TF_WEAPON_BREAKABLE_SIGN,
	TF_WEAPON_ROCKETPACK,
	TF_WEAPON_SLAP,
	TF_WEAPON_JAR_GAS,
	TF_WEAPON_GRENADE_JAR_GAS,
	TF_WEAPON_FLAME_BALL,

	TF_WEAPON_COUNT
};

#pragma warning (disable : 26495)


struct mstudiobbox_t {
	int bone;
	int group;
	vector bbmin;
	vector bbmax;
	int szhitboxnameindex;
	vector angle;
	float rad;
	uint8_t pad[0x10];
};

struct mstudiohitboxset_t {
	int sznameindex;
	inline char* const name(void) const { return ((char*)this) + sznameindex; }
	int numhitboxes;
	int hitboxindex;
	mstudiobbox_t* hitbox(int i) const { return (mstudiobbox_t*)(((BYTE*)this) + hitboxindex) + i; };
};

struct studiohdr_t
{
	unsigned char        pad00[ 12 ];
	char                name[ 64 ];
	unsigned char        pad01[ 80 ];
	int                    numbones;
	int                    boneindex;
	unsigned char        pad02[ 12 ];
	int                    hitboxsetindex;
	unsigned char        pad03[ 228 ];

	mstudiohitboxset_t* hitbox_set( int i ) const {
		return (mstudiohitboxset_t*)(((unsigned char*)this) + hitboxsetindex) + i;
	};

	mstudiobbox_t* hitbox( int i, int set ) const {
		const mstudiohitboxset_t* s = hitbox_set( set );
		if (!s)
			return 0;

		return s->hitbox(i);
	};

	int            iHitboxCount(int set) const
	{
		const mstudiohitboxset_t* s = hitbox_set(set);
		if (!s)
			return 0;

		return s->numhitboxes;
	};
};

class iv_model_info {
public:
	inline model_t* get_model( int index ) {
		typedef model_t* ( __thiscall* get_model_fn )( iv_model_info*, int );
		return util::get_virtual< get_model_fn >( this, 1u )( this, index );
	}

	inline const char* get_model_name( const model_t* model ) {
		typedef const char* ( __thiscall* get_model_name_fn )( iv_model_info*, const model_t* );
		return util::get_virtual< get_model_name_fn >( this, 3u )( this, model );
	}

	inline studiohdr_t* get_studio_model( const model_t* model ) {
		typedef studiohdr_t* ( __thiscall* get_studio_model_fn )( iv_model_info*, const model_t*);
		return util::get_virtual< get_studio_model_fn >( this, 28u )( this, model );
	}
};

enum tf_hitboxes {
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_LOWER_NECK,
	HITBOX_PELVIS,
	HITBOX_BODY,
	HITBOX_THORAX,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX
};

class i_con_var;
class c_command;

#define FCVAR_NONE				0 
#define FCVAR_UNREGISTERED		( 1 << 0 )
#define FCVAR_DEVELOPMENTONLY	( 1 << 1 )
#define FCVAR_GAMEDLL			( 1 << 2 )
#define FCVAR_CLIENTDLL			( 1 << 3 )
#define FCVAR_HIDDEN			( 1 << 4 )
#define FCVAR_PROTECTED			( 1 << 5 )
#define FCVAR_SPONLY			( 1 << 6 )
#define	FCVAR_ARCHIVE			( 1 << 7 )
#define	FCVAR_NOTIFY			( 1 << 8 )
#define	FCVAR_USERINFO			( 1 << 9 )
#define FCVAR_CHEAT				( 1 << 14 )
#define FCVAR_PRINTABLEONLY		( 1 << 10 )
#define FCVAR_UNLOGGED			( 1 << 11 )
#define FCVAR_NEVER_AS_STRING	( 1 << 12 )
#define FCVAR_REPLICATED		( 1 << 13 )
#define FCVAR_DEMO				( 1 << 16 )
#define FCVAR_DONTRECORD		( 1 << 17 )
#define FCVAR_RELOAD_MATERIALS	( 1 << 20 )
#define FCVAR_RELOAD_TEXTURES	( 1 << 21 )
#define FCVAR_NOT_CONNECTED		( 1 << 22 )
#define FCVAR_MATERIAL_SYSTEM_THREAD ( 1 << 23 )
#define FCVAR_ARCHIVE_XBOX		( 1 << 24 )
#define FCVAR_ACCESSIBLE_FROM_THREADS	( 1 << 25 )
#define FCVAR_SERVER_CAN_EXECUTE	( 1 << 28 )
#define FCVAR_SERVER_CANNOT_QUERY	( 1 << 29 )
#define FCVAR_CLIENTCMD_CAN_EXECUTE	( 1 << 30 )
#define FCVAR_EXEC_DESPITE_DEFAULT	( 1 << 31 )
#define FCVAR_INTERNAL_USE		( 1 << 15 )
#define FCVAR_ALLOWED_IN_COMPETITIVE	( 1 << 18 )
#define FCVAR_MATERIAL_THREAD_MASK ( FCVAR_RELOAD_MATERIALS | FCVAR_RELOAD_TEXTURES | FCVAR_MATERIAL_SYSTEM_THREAD )

typedef void( *fn_change_callback_t )( i_con_var* var, const char* old_value, float old_value_ );

class i_con_var {
public:
	virtual void set_value( const char* value ) = 0;
	virtual void set_value( float value ) = 0;
	virtual void set_value( int value ) = 0;
	virtual const char* get_name( void ) const = 0;
	virtual bool is_flag_set( int flag ) const = 0;
};

class con_var;
class c_command;
class con_command;
class con_command_base;
struct characterset_t;

using c_utl_string = std::string;

class i_con_command_base_accessor {
public:
	virtual bool register_con_command_base( con_command_base* var ) = 0;
};

typedef void ( *fn_command_callback_void_t )( void );
typedef void ( *fn_command_callback_t )( const c_command& command );

#define COMMAND_COMPLETION_MAXITEMS 64
#define COMMAND_COMPLETION_ITEM_LENGTH 64

typedef int ( *fn_command_completion_callback )( const char* partial, char commands[ COMMAND_COMPLETION_MAXITEMS ][ COMMAND_COMPLETION_ITEM_LENGTH ] );

class i_command_callback {
public:
	virtual void command_callback( const c_command& command ) = 0;
};

class i_command_completion_callback {
public:
	virtual void pad0( ) = 0;
};

struct c_var_dll_identifier_t;

class con_command_base {
public:
	virtual ~con_command_base( void );
	virtual	bool is_command( void ) const;
	virtual bool is_flag_set( int flag ) const;
	virtual void add_flags( int flags );
	virtual const char* get_name( void ) const;
	virtual const char* get_help_text( void ) const;
	virtual bool is_registered( void ) const;
	virtual c_var_dll_identifier_t get_dll_identifier( ) const;
	virtual void create_base( const char* name, const char* help_string = 0, int flags = 0 );

	con_command_base* m_next;
	bool m_registered;
	const char* m_name;
	const char* m_help_string;
	int m_flags;

protected:
	static con_command_base* s_con_command_bases;
	static i_con_command_base_accessor* s_accessor;
};

class c_command {
public:
	enum
	{
		COMMAND_MAX_ARGC = 64,
		COMMAND_MAX_LENGTH = 512,
	};

	int	m_nArgc;
	int	 m_nArgv0Size;
	char m_pArgSBuffer[COMMAND_MAX_LENGTH];
	char m_pArgvBuffer[COMMAND_MAX_LENGTH];
	const char* m_ppArgv[COMMAND_MAX_ARGC];
};

class con_command : public con_command_base {
public:
	typedef con_command_base base_class;
	virtual ~con_command( void );
	virtual	bool is_command( void ) const;
	virtual void pad( );
	virtual bool can_auto_complete( void );
	virtual void dispatch( const c_command& command );

private:
	union {
		fn_command_callback_void_t m_fn_command_callback_v1;
		fn_command_callback_t m_fn_command_callback;
		i_command_callback* m_command_callback;
	};

	union {
		fn_command_completion_callback m_fn_completion_callback;
		i_command_completion_callback* m_command_completion_callback;
	};

	bool m_has_completion_callback : 1;
	bool m_using_new_command_callback : 1;
	bool m_using_command_callback_interface : 1;
};

class con_var : public con_command_base, public i_con_var {
public:
	virtual ~con_var( void );
	virtual bool is_flag_set( int flag ) const;
	virtual const char* get_help_text( void ) const;
	virtual bool is_registered( void ) const;
	virtual const char* get_name( void ) const;
	virtual void add_flags( int flags );
	virtual	bool is_command( void ) const;
	virtual void set_value( const char* value );
	virtual void set_value( float value );
	virtual void set_value( int value );
	virtual void internal_set_value( const char* value );
	virtual void internal_set_float_value( float new_value, bool force = false );
	virtual void internal_set_int_value( int value );
	virtual bool clamp_value( float& value );
	virtual void change_string_value( const char* temp_val, float old_value );
	virtual void init( );

	inline float get_float( void ) const;
	inline int get_int( void ) const;
	inline bool	get_bool( ) const { return !!get_int( ); }
	inline char const* get_string( void ) const;

private:
	con_var* m_parent;
	const char* m_default_value;
	char* m_string;
	int m_string_length;
	float m_float_value;
	int m_int_value;
	bool m_has_min;
	float m_min_value;
	bool m_has_max;
	float m_max_value;
	bool m_has_comp_min;
	float m_comp_min_value;
	bool m_has_comp_max;
	float m_comp_max_value;
	bool m_competitive_restrictions;
	fn_change_callback_t m_fn_change_callback;
};

inline float con_var::get_float( void ) const {
	return m_parent->m_float_value;
}

inline int con_var::get_int( void ) const {
	return m_parent->m_int_value;
}

inline const char* con_var::get_string( void ) const {
	if ( m_flags & FCVAR_NEVER_AS_STRING )
		return "FCVAR_NEVER_AS_STRING";

	return ( m_parent->m_string ) ? m_parent->m_string : "";
}

class i_console_display_func {
public:
	virtual void color_print( const color& clr, const char* message ) = 0;
	virtual void print( const char* message ) = 0;
	virtual void d_print( const char* message ) = 0;
};

class i_base_interface {
public:
	virtual	~i_base_interface( ) { }
};

typedef void* ( *create_interface_fn )( const char* name, int* return_code );
typedef void* ( *instantiate_interface_fn )( );

enum init_return_val_t {
	INIT_FAILED = 0,
	INIT_OK,
	INIT_LAST_VAL,
};

class i_app_system {
public:
	virtual bool connect( create_interface_fn factory ) = 0;
	virtual void disconnect( ) = 0;
	virtual void* query_interface( const char* interface_name ) = 0;
	virtual init_return_val_t init( ) = 0;
	virtual void shutdown( ) = 0;
};

class i_cvar_query : public i_app_system {
public:
	virtual bool are_con_vars_linkable( const con_var* child, const con_var* parent ) = 0;
};

class i_cvar : public i_app_system {
public:
	virtual c_var_dll_identifier_t allocate_dll_identifier( ) = 0;
	virtual void register_con_command( con_command_base* command_base ) = 0;
	virtual void unregister_con_command( con_command_base* command_base ) = 0;
	virtual void unregister_con_commands( c_var_dll_identifier_t id ) = 0;
	virtual const char* get_command_line_value( const char* variable_name ) = 0;
	virtual con_command_base* find_command_base( const char* name ) = 0;
	virtual const con_command_base* find_command_base( const char* name ) const = 0;
	virtual con_var* find_var( const char* var_name ) = 0;
	virtual const con_var* find_var( const char* var_name ) const = 0;
	virtual con_command* find_command( const char* name ) = 0;
	virtual const con_command* find_command( const char* name ) const = 0;
	virtual con_command_base* get_commands( void ) = 0;
	virtual const con_command_base* get_commands( void ) const = 0;
	virtual void install_global_change_callback( fn_change_callback_t callback ) = 0;
	virtual void remove_global_change_callback( fn_change_callback_t callback ) = 0;
	virtual void call_global_change_callbacks( con_var* var, const char* old_string, float old_value ) = 0;
	virtual void install_console_display_func( i_console_display_func* display_func ) = 0;
	virtual void remove_console_display_func( i_console_display_func* display_func ) = 0;
	virtual void console_color_printf( const color& clr, const char* format, ... ) const = 0;
	virtual void console_printf( const char* format, ... ) const = 0;
	virtual void console_d_printf( const char* format, ... ) const = 0;
	virtual void revert_flagged_con_vars( int flag ) = 0;
	virtual void install_c_var_query( i_cvar_query* query ) = 0;
	virtual bool is_material_thread_set_allowed( ) const = 0;
	virtual void queue_material_thread_set_value( con_var* con_var, const char* value ) = 0;
	virtual void queue_material_thread_set_value( con_var* con_var, int value ) = 0;
	virtual void queue_material_thread_set_value( con_var* con_var, float value ) = 0;
	virtual bool has_queued_material_thread_con_var_sets( ) const = 0;
	virtual int process_queued_material_thread_con_var_sets( ) = 0;
};

enum e_tf_weapons {
	Scout_m_Scattergun = 13,
	Scout_m_ScattergunR = 200,
	Scout_m_ForceANature = 45,
	Scout_m_TheShortstop = 220,
	Scout_m_TheSodaPopper = 448,
	Scout_m_FestiveScattergun = 669,
	Scout_m_BabyFacesBlaster = 772,
	Scout_m_SilverBotkillerScattergunMkI = 799,
	Scout_m_GoldBotkillerScattergunMkI = 808,
	Scout_m_RustBotkillerScattergunMkI = 888,
	Scout_m_BloodBotkillerScattergunMkI = 897,
	Scout_m_CarbonadoBotkillerScattergunMkI = 906,
	Scout_m_DiamondBotkillerScattergunMkI = 915,
	Scout_m_SilverBotkillerScattergunMkII = 964,
	Scout_m_GoldBotkillerScattergunMkII = 973,
	Scout_m_FestiveForceANature = 1078,
	Scout_m_TheBackScatter = 1103,
	Scout_m_NightTerror = 15002,
	Scout_m_TartanTorpedo = 15015,
	Scout_m_CountryCrusher = 15021,
	Scout_m_BackcountryBlaster = 15029,
	Scout_m_SpruceDeuce = 15036,
	Scout_m_CurrentEvent = 15053,
	Scout_m_MacabreWeb = 15065,
	Scout_m_Nutcracker = 15069,
	Scout_m_BlueMew = 15106,
	Scout_m_FlowerPower = 15107,
	Scout_m_ShottoHell = 15108,
	Scout_m_CoffinNail = 15131,
	Scout_m_KillerBee = 15151,
	Scout_m_Corsair = 15157,
	Scout_s_ScoutsPistol = 23,
	Scout_s_PistolR = 209,
	Scout_s_BonkAtomicPunch = 46,
	Scout_s_VintageLugermorph = 160,
	Scout_s_CritaCola = 163,
	Scout_s_MadMilk = 222,
	Scout_s_Lugermorph = 294,
	Scout_s_TheWinger = 449,
	Scout_s_PrettyBoysPocketPistol = 773,
	Scout_s_TheFlyingGuillotine = 812,
	Scout_s_TheFlyingGuillotineG = 833,
	Scout_s_MutatedMilk = 1121,
	Scout_s_FestiveBonk = 1145,
	Scout_s_RedRockRoscoe = 15013,
	Scout_s_HomemadeHeater = 15018,
	Scout_s_HickoryHolepuncher = 15035,
	Scout_s_LocalHero = 15041,
	Scout_s_BlackDahlia = 15046,
	Scout_s_SandstoneSpecial = 15056,
	Scout_s_MacabreWeb = 15060,
	Scout_s_Nutcracker = 15061,
	Scout_s_BlueMew = 15100,
	Scout_s_BrainCandy = 15101,
	Scout_s_ShottoHell = 15102,
	Scout_s_DressedToKill = 15126,
	Scout_s_Blitzkrieg = 15148,
	Scout_s_TheCAPPER = 30666,
	Scout_t_Bat = 0,
	Scout_t_BatR = 190,
	Scout_t_TheSandman = 44,
	Scout_t_TheHolyMackerel = 221,
	Scout_t_TheCandyCane = 317,
	Scout_t_TheBostonBasher = 325,
	Scout_t_SunonaStick = 349,
	Scout_t_TheFanOWar = 355,
	Scout_t_TheAtomizer = 450,
	Scout_t_ThreeRuneBlade = 452,
	Scout_t_TheConscientiousObjector = 474,
	Scout_t_UnarmedCombat = 572,
	Scout_t_TheWrapAssassin = 648,
	Scout_t_FestiveBat = 660,
	Scout_t_TheFreedomStaff = 880,
	Scout_t_TheBatOuttaHell = 939,
	Scout_t_TheMemoryMaker = 954,
	Scout_t_FestiveHolyMackerel = 999,
	Scout_t_TheHamShank = 1013,
	Scout_t_TheNecroSmasher = 1123,
	Scout_t_TheCrossingGuard = 1127,
	Scout_t_Batsaber = 30667,
	Scout_t_PrinnyMachete = 30758,
	Soldier_m_RocketLauncher = 18,
	Soldier_m_RocketLauncherR = 205,
	Soldier_m_TheDirectHit = 127,
	Soldier_m_TheBlackBox = 228,
	Soldier_m_RocketJumper = 237,
	Soldier_m_TheLibertyLauncher = 414,
	Soldier_m_TheCowMangler5000 = 441,
	Soldier_m_TheOriginal = 513,
	Soldier_m_FestiveRocketLauncher = 658,
	Soldier_m_TheBeggarsBazooka = 730,
	Soldier_m_SilverBotkillerRocketLauncherMkI = 800,
	Soldier_m_GoldBotkillerRocketLauncherMkI = 809,
	Soldier_m_RustBotkillerRocketLauncherMkI = 889,
	Soldier_m_BloodBotkillerRocketLauncherMkI = 898,
	Soldier_m_CarbonadoBotkillerRocketLauncherMkI = 907,
	Soldier_m_DiamondBotkillerRocketLauncherMkI = 916,
	Soldier_m_SilverBotkillerRocketLauncherMkII = 965,
	Soldier_m_GoldBotkillerRocketLauncherMkII = 974,
	Soldier_m_FestiveBlackBox = 1085,
	Soldier_m_TheAirStrike = 1104,
	Soldier_m_WoodlandWarrior = 15006,
	Soldier_m_SandCannon = 15014,
	Soldier_m_AmericanPastoral = 15028,
	Soldier_m_SmalltownBringdown = 15043,
	Soldier_m_ShellShocker = 15052,
	Soldier_m_AquaMarine = 15057,
	Soldier_m_Autumn = 15081,
	Soldier_m_BlueMew = 15104,
	Soldier_m_BrainCandy = 15105,
	Soldier_m_CoffinNail = 15129,
	Soldier_m_HighRollers = 15130,
	Soldier_m_Warhawk = 15150,
	Soldier_s_SoldiersShotgun = 10,
	Soldier_s_ShotgunR = 199,
	Soldier_s_TheBuffBanner = 129,
	Soldier_s_Gunboats = 133,
	Soldier_s_TheBattalionsBackup = 226,
	Soldier_s_TheConcheror = 354,
	Soldier_s_TheReserveShooter = 415,
	Soldier_s_TheRighteousBison = 442,
	Soldier_s_TheMantreads = 444,
	Soldier_s_FestiveBuffBanner = 1001,
	Soldier_s_TheBASEJumper = 1101,
	Soldier_s_FestiveShotgun = 1141,
	Soldier_s_PanicAttack = 1153,
	Soldier_s_BackwoodsBoomstick = 15003,
	Soldier_s_RusticRuiner = 15016,
	Soldier_s_CivicDuty = 15044,
	Soldier_s_LightningRod = 15047,
	Soldier_s_Autumn = 15085,
	Soldier_s_FlowerPower = 15109,
	Soldier_s_CoffinNail = 15132,
	Soldier_s_DressedtoKill = 15133,
	Soldier_s_RedBear = 15152,
	Soldier_t_Shovel = 6,
	Soldier_t_ShovelR = 196,
	Soldier_t_TheEqualizer = 128,
	Soldier_t_ThePainTrain = 154,
	Soldier_t_TheHalfZatoichi = 357,
	Soldier_t_TheMarketGardener = 416,
	Soldier_t_TheDisciplinaryAction = 447,
	Soldier_t_TheConscientiousObjector = 474,
	Soldier_t_TheEscapePlan = 775,
	Soldier_t_TheFreedomStaff = 880,
	Soldier_t_TheBatOuttaHell = 939,
	Soldier_t_TheMemoryMaker = 954,
	Soldier_t_TheHamShank = 1013,
	Soldier_t_TheNecroSmasher = 1123,
	Soldier_t_TheCrossingGuard = 1127,
	Soldier_t_PrinnyMachete = 30758,
	Pyro_m_FlameThrower = 21,
	Pyro_m_FlameThrowerR = 208,
	Pyro_m_TheBackburner = 40,
	Pyro_m_TheDegreaser = 215,
	Pyro_m_ThePhlogistinator = 594,
	Pyro_m_FestiveFlameThrower = 659,
	Pyro_m_TheRainblower = 741,
	Pyro_m_SilverBotkillerFlameThrowerMkI = 798,
	Pyro_m_GoldBotkillerFlameThrowerMkI = 807,
	Pyro_m_RustBotkillerFlameThrowerMkI = 887,
	Pyro_m_BloodBotkillerFlameThrowerMkI = 896,
	Pyro_m_CarbonadoBotkillerFlameThrowerMkI = 905,
	Pyro_m_DiamondBotkillerFlameThrowerMkI = 914,
	Pyro_m_SilverBotkillerFlameThrowerMkII = 963,
	Pyro_m_GoldBotkillerFlameThrowerMkII = 972,
	Pyro_m_FestiveBackburner = 1146,
	Pyro_m_DragonsFury = 1178,
	Pyro_m_ForestFire = 15005,
	Pyro_m_BarnBurner = 15017,
	Pyro_m_BovineBlazemaker = 15030,
	Pyro_m_EarthSkyandFire = 15034,
	Pyro_m_FlashFryer = 15049,
	Pyro_m_TurbineTorcher = 15054,
	Pyro_m_Autumn = 15066,
	Pyro_m_PumpkinPatch = 15067,
	Pyro_m_Nutcracker = 15068,
	Pyro_m_Balloonicorn = 15089,
	Pyro_m_Rainbow = 15090,
	Pyro_m_CoffinNail = 15115,
	Pyro_m_Warhawk = 15141,
	Pyro_m_NostromoNapalmer = 30474,
	Pyro_s_PyrosShotgun = 12,
	Pyro_s_ShotgunR = 199,
	Pyro_s_TheFlareGun = 39,
	Pyro_s_TheDetonator = 351,
	Pyro_s_TheReserveShooter = 415,
	Pyro_s_TheManmelter = 595,
	Pyro_s_TheScorchShot = 740,
	Pyro_s_FestiveFlareGun = 1081,
	Pyro_s_FestiveShotgun = 1141,
	Pyro_s_PanicAttack = 1153,
	Pyro_s_ThermalThruster = 1179,
	Pyro_s_GasPasser = 1180,
	Pyro_s_BackwoodsBoomstick = 15003,
	Pyro_s_RusticRuiner = 15016,
	Pyro_s_CivicDuty = 15044,
	Pyro_s_LightningRod = 15047,
	Pyro_s_Autumn = 15085,
	Pyro_s_FlowerPower = 15109,
	Pyro_s_CoffinNail = 15132,
	Pyro_s_DressedtoKill = 15133,
	Pyro_s_RedBear = 15152,
	Pyro_t_FireAxe = 2,
	Pyro_t_FireAxeR = 192,
	Pyro_t_TheAxtinguisher = 38,
	Pyro_t_Homewrecker = 153,
	Pyro_t_ThePowerjack = 214,
	Pyro_t_TheBackScratcher = 326,
	Pyro_t_SharpenedVolcanoFragment = 348,
	Pyro_t_ThePostalPummeler = 457,
	Pyro_t_TheMaul = 466,
	Pyro_t_TheConscientiousObjector = 474,
	Pyro_t_TheThirdDegree = 593,
	Pyro_t_TheLollichop = 739,
	Pyro_t_NeonAnnihilator = 813,
	Pyro_t_NeonAnnihilatorG = 834,
	Pyro_t_TheFreedomStaff = 880,
	Pyro_t_TheBatOuttaHell = 939,
	Pyro_t_TheMemoryMaker = 954,
	Pyro_t_TheFestiveAxtinguisher = 1000,
	Pyro_t_TheHamShank = 1013,
	Pyro_t_TheNecroSmasher = 1123,
	Pyro_t_TheCrossingGuard = 1127,
	Pyro_t_HotHand = 1181,
	Pyro_t_PrinnyMachete = 30758,
	Demoman_m_GrenadeLauncher = 19,
	Demoman_m_GrenadeLauncherR = 206,
	Demoman_m_TheLochnLoad = 308,
	Demoman_m_AliBabasWeeBooties = 405,
	Demoman_m_TheBootlegger = 608,
	Demoman_m_TheLooseCannon = 996,
	Demoman_m_FestiveGrenadeLauncher = 1007,
	Demoman_m_TheBASEJumper = 1101,
	Demoman_m_TheIronBomber = 1151,
	Demoman_m_Autumn = 15077,
	Demoman_m_MacabreWeb = 15079,
	Demoman_m_Rainbow = 15091,
	Demoman_m_SweetDreams = 15092,
	Demoman_m_CoffinNail = 15116,
	Demoman_m_TopShelf = 15117,
	Demoman_m_Warhawk = 15142,
	Demoman_m_ButcherBird = 15158,
	Demoman_s_StickybombLauncher = 20,
	Demoman_s_StickybombLauncherR = 207,
	Demoman_s_TheScottishResistance = 130,
	Demoman_s_TheCharginTarge = 131,
	Demoman_s_StickyJumper = 265,
	Demoman_s_TheSplendidScreen = 406,
	Demoman_s_FestiveStickybombLauncher = 661,
	Demoman_s_SilverBotkillerStickybombLauncherMkI = 797,
	Demoman_s_GoldBotkillerStickybombLauncherMkI = 806,
	Demoman_s_RustBotkillerStickybombLauncherMkI = 886,
	Demoman_s_BloodBotkillerStickybombLauncherMkI = 895,
	Demoman_s_CarbonadoBotkillerStickybombLauncherMkI = 904,
	Demoman_s_DiamondBotkillerStickybombLauncherMkI = 913,
	Demoman_s_SilverBotkillerStickybombLauncherMkII = 962,
	Demoman_s_GoldBotkillerStickybombLauncherMkII = 971,
	Demoman_s_TheTideTurner = 1099,
	Demoman_s_FestiveTarge = 1144,
	Demoman_s_TheQuickiebombLauncher = 1150,
	Demoman_s_SuddenFlurry = 15009,
	Demoman_s_CarpetBomber = 15012,
	Demoman_s_BlastedBombardier = 15024,
	Demoman_s_RooftopWrangler = 15038,
	Demoman_s_LiquidAsset = 15045,
	Demoman_s_PinkElephant = 15048,
	Demoman_s_Autumn = 15082,
	Demoman_s_PumpkinPatch = 15083,
	Demoman_s_MacabreWeb = 15084,
	Demoman_s_SweetDreams = 15113,
	Demoman_s_CoffinNail = 15137,
	Demoman_s_DressedtoKill = 15138,
	Demoman_s_Blitzkrieg = 15155,
	Demoman_t_Bottle = 1,
	Demoman_t_BottleR = 191,
	Demoman_t_TheEyelander = 132,
	Demoman_t_ThePainTrain = 154,
	Demoman_t_TheScotsmansSkullcutter = 172,
	Demoman_t_HorselessHeadlessHorsemannsHeadtaker = 266,
	Demoman_t_UllapoolCaber = 307,
	Demoman_t_TheClaidheamhMor = 327,
	Demoman_t_TheHalfZatoichi = 357,
	Demoman_t_ThePersianPersuader = 404,
	Demoman_t_TheConscientiousObjector = 474,
	Demoman_t_NessiesNineIron = 482,
	Demoman_t_TheScottishHandshake = 609,
	Demoman_t_TheFreedomStaff = 880,
	Demoman_t_TheBatOuttaHell = 939,
	Demoman_t_TheMemoryMaker = 954,
	Demoman_t_TheHamShank = 1013,
	Demoman_t_FestiveEyelander = 1082,
	Demoman_t_TheNecroSmasher = 1123,
	Demoman_t_TheCrossingGuard = 1127,
	Demoman_t_PrinnyMachete = 30758,
	Heavy_m_Minigun = 15,
	Heavy_m_MinigunR = 202,
	Heavy_m_Natascha = 41,
	Heavy_m_IronCurtain = 298,
	Heavy_m_TheBrassBeast = 312,
	Heavy_m_Tomislav = 424,
	Heavy_m_FestiveMinigun = 654,
	Heavy_m_SilverBotkillerMinigunMkI = 793,
	Heavy_m_GoldBotkillerMinigunMkI = 802,
	Heavy_m_TheHuoLongHeater = 811,
	Heavy_m_TheHuoLongHeaterG = 832,
	Heavy_m_Deflector_mvm = 850,
	Heavy_m_RustBotkillerMinigunMkI = 882,
	Heavy_m_BloodBotkillerMinigunMkI = 891,
	Heavy_m_CarbonadoBotkillerMinigunMkI = 900,
	Heavy_m_DiamondBotkillerMinigunMkI = 909,
	Heavy_m_SilverBotkillerMinigunMkII = 958,
	Heavy_m_GoldBotkillerMinigunMkII = 967,
	Heavy_m_KingoftheJungle = 15004,
	Heavy_m_IronWood = 15020,
	Heavy_m_AntiqueAnnihilator = 15026,
	Heavy_m_WarRoom = 15031,
	Heavy_m_CitizenPain = 15040,
	Heavy_m_BrickHouse = 15055,
	Heavy_m_MacabreWeb = 15086,
	Heavy_m_PumpkinPatch = 15087,
	Heavy_m_Nutcracker = 15088,
	Heavy_m_BrainCandy = 15098,
	Heavy_m_MisterCuddles = 15099,
	Heavy_m_CoffinNail = 15123,
	Heavy_m_DressedtoKill = 15124,
	Heavy_m_TopShelf = 15125,
	Heavy_m_ButcherBird = 15147,
	Heavy_s_HeavysShotgun = 11,
	Heavy_s_ShotgunR = 199,
	Heavy_s_Sandvich = 42,
	Heavy_s_TheDalokohsBar = 159,
	Heavy_s_TheBuffaloSteakSandvich = 311,
	Heavy_s_TheFamilyBusiness = 425,
	Heavy_s_Fishcake = 433,
	Heavy_s_RoboSandvich = 863,
	Heavy_s_FestiveSandvich = 1002,
	Heavy_s_FestiveShotgun = 1141,
	Heavy_s_PanicAttack = 1153,
	Heavy_s_SecondBanana = 1190,
	Heavy_s_BackwoodsBoomstick = 15003,
	Heavy_s_RusticRuiner = 15016,
	Heavy_s_CivicDuty = 15044,
	Heavy_s_LightningRod = 15047,
	Heavy_s_Autumn = 15085,
	Heavy_s_FlowerPower = 15109,
	Heavy_s_CoffinNail = 15132,
	Heavy_s_DressedtoKill = 15133,
	Heavy_s_RedBear = 15152,
	Heavy_t_Fists = 5,
	Heavy_t_FistsR = 195,
	Heavy_t_TheKillingGlovesofBoxing = 43,
	Heavy_t_GlovesofRunningUrgently = 239,
	Heavy_t_WarriorsSpirit = 310,
	Heavy_t_FistsofSteel = 331,
	Heavy_t_TheEvictionNotice = 426,
	Heavy_t_TheConscientiousObjector = 474,
	Heavy_t_ApocoFists = 587,
	Heavy_t_TheHolidayPunch = 656,
	Heavy_t_TheFreedomStaff = 880,
	Heavy_t_TheBatOuttaHell = 939,
	Heavy_t_TheMemoryMaker = 954,
	Heavy_t_TheHamShank = 1013,
	Heavy_t_FestiveGlovesofRunningUrgently = 1084,
	Heavy_t_TheBreadBite = 1100,
	Heavy_t_TheNecroSmasher = 1123,
	Heavy_t_TheCrossingGuard = 1127,
	Heavy_t_GlovesofRunningUrgentlyMvM = 1184,
	Heavy_t_PrinnyMachete = 30758,
	Engi_m_EngineersShotgun = 9,
	Engi_m_ShotgunR = 199,
	Engi_m_TheFrontierJustice = 141,
	Engi_m_TheWidowmaker = 527,
	Engi_m_ThePomson6000 = 588,
	Engi_m_TheRescueRanger = 997,
	Engi_m_FestiveFrontierJustice = 1004,
	Engi_m_FestiveShotgun = 1141,
	Engi_m_PanicAttack = 1153,
	Engi_m_BackwoodsBoomstick = 15003,
	Engi_m_RusticRuiner = 15016,
	Engi_m_CivicDuty = 15044,
	Engi_m_LightningRod = 15047,
	Engi_m_Autumn = 15085,
	Engi_m_FlowerPower = 15109,
	Engi_m_CoffinNail = 15132,
	Engi_m_DressedtoKill = 15133,
	Engi_m_RedBear = 15152,
	Engi_s_EngineersPistol = 22,
	Engi_s_PistolR = 209,
	Engi_s_TheWrangler = 140,
	Engi_s_VintageLugermorph = 160,
	Engi_s_Lugermorph = 294,
	Engi_s_TheShortCircuit = 528,
	Engi_s_FestiveWrangler = 1086,
	Engi_s_RedRockRoscoe = 15013,
	Engi_s_HomemadeHeater = 15018,
	Engi_s_HickoryHolepuncher = 15035,
	Engi_s_LocalHero = 15041,
	Engi_s_BlackDahlia = 15046,
	Engi_s_SandstoneSpecial = 15056,
	Engi_s_MacabreWeb = 15060,
	Engi_s_Nutcracker = 15061,
	Engi_s_BlueMew = 15100,
	Engi_s_BrainCandy = 15101,
	Engi_s_ShottoHell = 15102,
	Engi_s_DressedToKill = 15126,
	Engi_s_Blitzkrieg = 15148,
	Engi_s_TheCAPPER = 30666,
	Engi_s_TheGigarCounter = 30668,
	Engi_t_Wrench = 7,
	Engi_t_WrenchR = 197,
	Engi_t_TheGunslinger = 142,
	Engi_t_TheSouthernHospitality = 155,
	Engi_t_GoldenWrench = 169,
	Engi_t_TheJag = 329,
	Engi_t_TheEurekaEffect = 589,
	Engi_t_FestiveWrench = 662,
	Engi_t_SilverBotkillerWrenchMkI = 795,
	Engi_t_GoldBotkillerWrenchMkI = 804,
	Engi_t_RustBotkillerWrenchMkI = 884,
	Engi_t_BloodBotkillerWrenchMkI = 893,
	Engi_t_CarbonadoBotkillerWrenchMkI = 902,
	Engi_t_DiamondBotkillerWrenchMkI = 911,
	Engi_t_SilverBotkillerWrenchMkII = 960,
	Engi_t_GoldBotkillerWrenchMkII = 969,
	Engi_t_TheNecroSmasher = 1123,
	Engi_t_Nutcracker = 15073,
	Engi_t_Autumn = 15074,
	Engi_t_Boneyard = 15075,
	Engi_t_DressedtoKill = 15139,
	Engi_t_TopShelf = 15140,
	Engi_t_TorquedtoHell = 15114,
	Engi_t_Airwolf = 15156,
	Engi_t_PrinnyMachete = 30758,
	Engi_p_ConstructionPDA = 25,
	Engi_p_ConstructionPDAR = 737,
	Engi_p_DestructionPDA = 26,
	Engi_p_PDA = 28,
	Medic_m_SyringeGun = 17,
	Medic_m_SyringeGunR = 204,
	Medic_m_TheBlutsauger = 36,
	Medic_m_CrusadersCrossbow = 305,
	Medic_m_TheOverdose = 412,
	Medic_m_FestiveCrusadersCrossbow = 1079,
	Medic_s_MediGun = 29,
	Medic_s_MediGunR = 211,
	Medic_s_TheKritzkrieg = 35,
	Medic_s_TheQuickFix = 411,
	Medic_s_FestiveMediGun = 663,
	Medic_s_SilverBotkillerMediGunMkI = 796,
	Medic_s_GoldBotkillerMediGunMkI = 805,
	Medic_s_RustBotkillerMediGunMkI = 885,
	Medic_s_BloodBotkillerMediGunMkI = 894,
	Medic_s_CarbonadoBotkillerMediGunMkI = 903,
	Medic_s_DiamondBotkillerMediGunMkI = 912,
	Medic_s_SilverBotkillerMediGunMkII = 961,
	Medic_s_GoldBotkillerMediGunMkII = 970,
	Medic_s_TheVaccinator = 998,
	Medic_s_MaskedMender = 15008,
	Medic_s_WrappedReviver = 15010,
	Medic_s_ReclaimedReanimator = 15025,
	Medic_s_CivilServant = 15039,
	Medic_s_SparkofLife = 15050,
	Medic_s_Wildwood = 15078,
	Medic_s_FlowerPower = 15097,
	Medic_s_DressedToKill = 15121,
	Medic_s_HighRollers = 15122,
	Medic_s_CoffinNail = 15123,
	Medic_s_Blitzkrieg = 15145,
	Medic_s_Corsair = 15146,
	Medic_t_Bonesaw = 8,
	Medic_t_BonesawR = 198,
	Medic_t_TheUbersaw = 37,
	Medic_t_TheVitaSaw = 173,
	Medic_t_Amputator = 304,
	Medic_t_TheSolemnVow = 413,
	Medic_t_TheConscientiousObjector = 474,
	Medic_t_TheFreedomStaff = 880,
	Medic_t_TheBatOuttaHell = 939,
	Medic_t_TheMemoryMaker = 954,
	Medic_t_FestiveUbersaw = 1003,
	Medic_t_TheHamShank = 1013,
	Medic_t_TheNecroSmasher = 1123,
	Medic_t_TheCrossingGuard = 1127,
	Medic_t_FestiveBonesaw = 1143,
	Medic_t_PrinnyMachete = 30758,
	Sniper_m_SniperRifle = 14,
	Sniper_m_SniperRifleR = 201,
	Sniper_m_TheHuntsman = 56,
	Sniper_m_TheSydneySleeper = 230,
	Sniper_m_TheBazaarBargain = 402,
	Sniper_m_TheMachina = 526,
	Sniper_m_FestiveSniperRifle = 664,
	Sniper_m_TheHitmansHeatmaker = 752,
	Sniper_m_SilverBotkillerSniperRifleMkI = 792,
	Sniper_m_GoldBotkillerSniperRifleMkI = 801,
	Sniper_m_TheAWPerHand = 851,
	Sniper_m_RustBotkillerSniperRifleMkI = 881,
	Sniper_m_BloodBotkillerSniperRifleMkI = 890,
	Sniper_m_CarbonadoBotkillerSniperRifleMkI = 899,
	Sniper_m_DiamondBotkillerSniperRifleMkI = 908,
	Sniper_m_SilverBotkillerSniperRifleMkII = 957,
	Sniper_m_GoldBotkillerSniperRifleMkII = 966,
	Sniper_m_FestiveHuntsman = 1005,
	Sniper_m_TheFortifiedCompound = 1092,
	Sniper_m_TheClassic = 1098,
	Sniper_m_NightOwl = 15000,
	Sniper_m_PurpleRange = 15007,
	Sniper_m_LumberFromDownUnder = 15019,
	Sniper_m_ShotintheDark = 15023,
	Sniper_m_Bogtrotter = 15033,
	Sniper_m_Thunderbolt = 15059,
	Sniper_m_PumpkinPatch = 15070,
	Sniper_m_Boneyard = 15071,
	Sniper_m_Wildwood = 15072,
	Sniper_m_Balloonicorn = 15111,
	Sniper_m_Rainbow = 15112,
	Sniper_m_CoffinNail = 15135,
	Sniper_m_DressedtoKill = 15136,
	Sniper_m_Airwolf = 15154,
	Sniper_m_ShootingStar = 30665,
	Sniper_s_SMG = 16,
	Sniper_s_SMGR = 203,
	Sniper_s_TheRazorback = 57,
	Sniper_s_Jarate = 58,
	Sniper_s_DarwinsDangerShield = 231,
	Sniper_s_CozyCamper = 642,
	Sniper_s_TheCleanersCarbine = 751,
	Sniper_s_FestiveJarate = 1083,
	Sniper_s_TheSelfAwareBeautyMark = 1105,
	Sniper_s_FestiveSMG = 1149,
	Sniper_s_WoodsyWidowmaker = 15001,
	Sniper_s_PlaidPotshotter = 15022,
	Sniper_s_TreadplateTormenter = 15032,
	Sniper_s_TeamSprayer = 15037,
	Sniper_s_LowProfile = 15058,
	Sniper_s_Wildwood = 15076,
	Sniper_s_BlueMew = 15110,
	Sniper_s_HighRollers = 15134,
	Sniper_s_Blitzkrieg = 15153,
	Sniper_t_Kukri = 3,
	Sniper_t_KukriR = 193,
	Sniper_t_TheTribalmansShiv = 171,
	Sniper_t_TheBushwacka = 232,
	Sniper_t_TheShahanshah = 401,
	Sniper_t_TheConscientiousObjector = 474,
	Sniper_t_TheFreedomStaff = 880,
	Sniper_t_TheBatOuttaHell = 939,
	Sniper_t_TheMemoryMaker = 954,
	Sniper_t_TheHamShank = 1013,
	Sniper_t_TheNecroSmasher = 1123,
	Sniper_t_TheCrossingGuard = 1127,
	Sniper_t_PrinnyMachete = 30758,
	Spy_m_Revolver = 24,
	Spy_m_RevolverR = 210,
	Spy_m_TheAmbassador = 61,
	Spy_m_BigKill = 161,
	Spy_m_LEtranger = 224,
	Spy_m_TheEnforcer = 460,
	Spy_m_TheDiamondback = 525,
	Spy_m_FestiveAmbassador = 1006,
	Spy_m_FestiveRevolver = 1142,
	Spy_m_PsychedelicSlugger = 15011,
	Spy_m_OldCountry = 15027,
	Spy_m_Mayor = 15042,
	Spy_m_DeadReckoner = 15051,
	Spy_m_Boneyard = 15062,
	Spy_m_Wildwood = 15063,
	Spy_m_MacabreWeb = 15064,
	Spy_m_FlowerPower = 15103,
	Spy_m_TopShelf = 15128,
	Spy_m_CoffinNail = 15129,
	Spy_m_Blitzkrieg = 15149,
	Spy_s_Sapper = 735,
	Spy_s_SapperR = 736,
	Spy_s_TheRedTapeRecorder = 810,
	Spy_s_TheRedTapeRecorderG = 831,
	Spy_s_TheApSapG = 933,
	Spy_s_FestiveSapper = 1080,
	Spy_s_TheSnackAttack = 1102,
	Spy_t_Knife = 4,
	Spy_t_KnifeR = 194,
	Spy_t_YourEternalReward = 225,
	Spy_t_ConniversKunai = 356,
	Spy_t_TheBigEarner = 461,
	Spy_t_TheWangaPrick = 574,
	Spy_t_TheSharpDresser = 638,
	Spy_t_TheSpycicle = 649,
	Spy_t_FestiveKnife = 665,
	Spy_t_TheBlackRose = 727,
	Spy_t_SilverBotkillerKnifeMkI = 794,
	Spy_t_GoldBotkillerKnifeMkI = 803,
	Spy_t_RustBotkillerKnifeMkI = 883,
	Spy_t_BloodBotkillerKnifeMkI = 892,
	Spy_t_CarbonadoBotkillerKnifeMkI = 901,
	Spy_t_DiamondBotkillerKnifeMkI = 910,
	Spy_t_SilverBotkillerKnifeMkII = 959,
	Spy_t_GoldBotkillerKnifeMkII = 968,
	Spy_t_Boneyard = 15062,
	Spy_t_BlueMew = 15094,
	Spy_t_BrainCandy = 15095,
	Spy_t_StabbedtoHell = 15096,
	Spy_t_DressedtoKill = 15118,
	Spy_t_TopShelf = 15119,
	Spy_t_Blitzkrieg = 15143,
	Spy_t_Airwolf = 15144,
	Spy_t_PrinnyMachete = 30758,
	Spy_d_DisguiseKitPDA = 27,
	Spy_w_InvisWatch = 30,
	Spy_w_InvisWatchR = 212,
	Spy_w_TheDeadRinger = 59,
	Spy_w_TheCloakandDagger = 60,
	Spy_w_EnthusiastsTimepiece = 297,
	Spy_w_TheQuackenbirdt = 947,
	Misc_t_FryingPan = 264,
	Misc_t_GoldFryingPan = 1071,
	Misc_t_Saxxy = 423,
};

struct vcollide_t;

enum {
	COLLIDE_POLY = 0,
	COLLIDE_MOPP = 1,
	COLLIDE_BALL = 2,
	COLLIDE_VIRTUAL = 3,
};

class i_phys_collide {
public:
	virtual ~i_phys_collide( ) { }
	virtual void* create_surface_manager( short& ) const = 0;
	virtual void get_all_ledges( void* ledges ) const = 0;
	virtual unsigned int get_serialization_size( ) const = 0;
	virtual unsigned int serialize_to_buffer( char* dest, bool swap = false ) const = 0;
	virtual int get_vcollide_index( ) const = 0;
	virtual vector get_mass_center( ) const = 0;
	virtual void set_mass_center( const vector& mass_center ) = 0;
	virtual vector get_orthographic_areas( ) const = 0;
	virtual void set_orthographic_areas( const vector& areas ) = 0;
	virtual float get_sphere_radius( ) const = 0;
	virtual void output_debug_info( ) const = 0;
};

#define LEAFMAP_HAS_CUBEMAP					0x0001
#define LEAFMAP_HAS_SINGLE_VERTEX_SPAN		0x0002
#define LEAFMAP_HAS_MULTIPLE_VERTEX_SPANS	0x0004

struct leafmap_t {
	void* m_leaf;
	unsigned short m_vert_count;
	byte m_flags;
	byte m_span_count;
	unsigned short m_start_vert[ 8 ];

	void set_has_cubemap( ) {
		this->m_flags = LEAFMAP_HAS_CUBEMAP;
	}

	void set_single_vertex_span( int start_vert_index, int vert_count_in ) {
		this->m_flags = 0;
		this->m_flags |= LEAFMAP_HAS_SINGLE_VERTEX_SPAN;
		this->m_start_vert[ 0 ] = start_vert_index;
		this->m_vert_count = vert_count_in;
	}

	int max_spans( ) {
		return sizeof( m_start_vert ) - sizeof( m_start_vert[ 0 ] );
	}
	const byte* get_spans( ) const {
		return reinterpret_cast< const byte*>( &m_start_vert[ 1 ] );
	}
	byte* get_spans() {
		return reinterpret_cast< byte* >( &m_start_vert[ 1 ] );
	}

	void set_rle_spans( int start_vert_index, int span_count_in, byte* spans ) {
		m_flags = 0;

		if ( span_count_in > max_spans( ) )
			return;

		if ( span_count_in == 1 ) {
			set_single_vertex_span( start_vert_index, spans[ 0 ] );
			return;
		}

		m_flags |= LEAFMAP_HAS_MULTIPLE_VERTEX_SPANS;
		m_start_vert[ 0 ] = start_vert_index;
		m_vert_count = 0;
		m_span_count = span_count_in;

		byte* span_out = get_spans( );

		for ( int i = 0; i < span_count_in; i++ ) {
			span_out[ i ] = spans[ i ];

			if ( !( i & 1 ) ) {
				m_vert_count += spans[ i ];
			}
		}
	}

	inline bool has_spans( ) const { return ( m_flags & ( LEAFMAP_HAS_SINGLE_VERTEX_SPAN | LEAFMAP_HAS_MULTIPLE_VERTEX_SPANS ) ) ? true : false; }
	inline bool has_cubemap( ) const { return ( m_flags & LEAFMAP_HAS_CUBEMAP ) ? true : false; }
	inline bool has_single_vertex_span( ) const { return ( m_flags & LEAFMAP_HAS_SINGLE_VERTEX_SPAN ) ? true : false; }
	inline bool has_rle_spans( ) const { return ( m_flags & LEAFMAP_HAS_MULTIPLE_VERTEX_SPANS ) ? true : false; }
};


struct collidemap_t {
	int m_leaf_count;
	leafmap_t m_leafmap[ 1 ];
};

class c_phys_collide : public i_phys_collide {
public:
	static c_phys_collide* unserialize_from_buffer( const char* buffer, unsigned int size, int index, bool swap = false );
	virtual const void* get_compact_surface( ) const { return NULL; }
	virtual vector get_orthographic_areas( ) const { return vector( 1.0f, 1.0f, 1.0f ); }
	virtual float get_sphere_radius( ) const { return 0; }
	virtual void compute_orthographic_areas( float epsilon ) {}
	virtual void set_orthographic_areas( const vector& areas ) {}
	virtual const collidemap_t* get_collide_map( ) const { return NULL; }
};

#define METERS_PER_INCH					( 0.0254f )
#define CUBIC_METERS_PER_CUBIC_INCH		( METERS_PER_INCH*METERS_PER_INCH*METERS_PER_INCH )
#define POUNDS_PER_KG	( 2.2f )
#define KG_PER_POUND	( 1.0f / POUNDS_PER_KG )
#define LBS2KG( x )		( ( x ) * KG_PER_POUND )
#define KG2LBS( x )		( ( x ) * POUNDS_PER_KG )

const float vphysics_min_mass = 0.1f;
const float vphysics_max_mass = 5e4f;

class i_physics_object {
public:
	virtual ~i_physics_object( void ) { }
	virtual bool is_static( ) const = 0;
	virtual bool is_asleep( ) const = 0;
	virtual bool is_trigger( ) const = 0;
	virtual bool is_fluid( ) const = 0;
	virtual bool is_hinged( ) const = 0;
	virtual bool is_collision_enabled( ) const = 0;
	virtual bool is_gravity_enabled( ) const = 0;
	virtual bool is_drag_enabled( ) const = 0;
	virtual bool is_motion_enabled( ) const = 0;
	virtual bool is_moveable( ) const = 0;
	virtual bool is_attached_to_constraint( bool external_only ) const = 0;
	virtual void enable_collisions( bool enable ) = 0;
	virtual void enable_gravity( bool enable ) = 0;
	virtual void enable_drag( bool enable ) = 0;
	virtual void enable_motion( bool enable ) = 0;
	virtual void set_game_data( void* game_data ) = 0;
	virtual void* get_game_data( void ) const = 0;
	virtual void set_game_flags( unsigned short user_flags ) = 0;
	virtual unsigned short get_game_flags( void ) const = 0;
	virtual void set_game_index( unsigned short game_index ) = 0;
	virtual unsigned short get_game_index( void ) const = 0;
	virtual void set_callback_flags( unsigned short callbackflags ) = 0;
	virtual unsigned short get_callback_flags( void ) const = 0;
	virtual void wake( void ) = 0;
	virtual void sleep( void ) = 0;
	virtual void recheck_collision_filter( ) = 0;
	virtual void recheck_contact_points( ) = 0;
	virtual void set_mass( float mass ) = 0;
	virtual float get_mass( void ) const = 0;
	virtual float get_inv_mass( void ) const = 0;
	virtual vector get_inertia( void ) const = 0;
	virtual vector get_inv_inertia( void ) const = 0;
	virtual void set_inertia( const vector& inertia ) = 0;
	virtual void set_damping( const float* speed, const float* rot ) = 0;
	virtual void get_damping( float* speed, float* rot ) const = 0;
	virtual void set_drag_coefficient( float* pDrag, float* angular_drag ) = 0;
	virtual void set_buoyancy_ratio( float ratio ) = 0;
	virtual int get_material_index( ) const = 0;
	virtual void set_material_index( int material_index ) = 0;
	virtual unsigned int get_contents( ) const = 0;
	virtual void set_contents( unsigned int contents ) = 0;
	virtual float get_sphere_radius( ) const = 0;
	virtual float get_energy( ) const = 0;
	virtual vector get_mass_center_local_space( ) const = 0;
	virtual void set_position( const vector& world_position, const vector& angles, bool is_teleport ) = 0;
	virtual void set_position_matrix( const matrix_3x4& matrix, bool is_teleport ) = 0;
	virtual void get_position( vector* world_position, vector* angles) const = 0;
	virtual void get_position_matrix( matrix_3x4* position_matrix ) const = 0;
	virtual void set_velocity( const vector* velocity, const vector* angular_velocity ) = 0;
	virtual void set_velocity_instantaneous( const vector* velocity, const vector* angular_velocity ) = 0;
	virtual void get_velocity( vector* velocity, vector* angular_velocity ) const = 0;
	virtual void add_velocity( const vector* velocity, const vector* angular_velocity ) = 0;
	virtual void get_velocity_at_point( const vector& world_position, vector* velocity ) const = 0;
	virtual void get_implicit_velocity( vector* velocity, vector* angular_velocity ) const = 0;
	virtual void local_to_world( vector* world_position, const vector& local_position ) const = 0;
	virtual void world_to_local( vector* local_position, const vector& world_position ) const = 0;
	virtual void local_to_world_vector( vector* world_vector, const vector& local_vector ) const = 0;
	virtual void world_to_local_vector( vector* local_vector, const vector& world_vector ) const = 0;
	virtual void apply_force_center( const vector& force_vector) = 0;
	virtual void apply_force_offset( const vector& force_vector, const vector& world_position ) = 0;
	virtual void apply_torque_center( const vector& torque ) = 0;
	virtual void calculate_force_offset( const vector& force_vector, const vector& world_position, vector* center_force, vector* center_torque ) const = 0;
	virtual void calculate_velocity_offset( const vector& force_vector, const vector& world_position, vector* center_velocity, vector* center_angular_velocity ) const = 0;
	virtual float calculate_linear_drag( const vector& unit_direction ) const = 0;
	virtual float calculate_angular_drag( const vector& object_space_rotation_axis ) const = 0;
	virtual bool get_contact_point( vector* contactPoint, i_physics_object** contact_object ) const = 0;
	virtual void set_shadow( float max_speed, float max_angular_speed, bool allow_physics_movement, bool allow_physics_rotation ) = 0;
	virtual void update_shadow( const vector& target_position, const vector& target_angles, bool temp_disable_gravity, float time_offset ) = 0;
	virtual int get_shadow_position( vector* position, vector* angles ) const = 0;
	virtual void* get_shadow_controller( void ) const = 0;
	virtual void remove_shadow_controller( ) = 0;
	virtual float compute_shadow_control( void* params, float seconds_to_arrival, float dt ) = 0;
	virtual const c_phys_collide* get_collide( void ) const = 0;
	virtual const char* get_name( ) const = 0;
	virtual void become_trigger( ) = 0;
	virtual void remove_trigger( ) = 0;
	virtual void become_hinged( int local_axis ) = 0;
	virtual void remove_hinged( ) = 0;
	virtual void* create_friction_snapshot( ) = 0;
	virtual void destroy_friction_snapshot( void* snapshot ) = 0;
	virtual void output_debug_info( ) const = 0;
};

class i_physics_environment;
class i_physics_surface_props;
class i_physics_constraint;
class i_physics_constraint_group;
class i_physics_fluid_controller;
class i_physics_spring;
class i_physics_vehicle_controller;
class i_convex_info;
class i_physics_object_pair_hash;
class i_physics_collision_set;
class i_physics_player_controller;
class i_physics_friction_snapshot;
struct ray_t;
struct constraint_ragdollparams_t;
struct constraint_hingeparams_t;
struct constraint_fixedparams_t;
struct constraint_ballsocketparams_t;
struct constraint_slidingparams_t;
struct constraint_pulleyparams_t;
struct constraint_lengthparams_t;
struct constraint_groupparams_t;
struct vehicleparams_t;
struct fluidparams_t;
struct springparams_t;

struct objectparams_t {
	vector* m_mass_center_override;
	float		m_mass;
	float		m_inertia;
	float		m_damping;
	float		m_rot_damping;
	float		m_rot_inertia_limit;
	const char* m_name;
	void* m_game_data;
	float		m_volume;
	float		m_drag_coefficient;
	bool		m_enable_collisions;
};

struct debugcollide_t;
class c_game_trace;
typedef c_game_trace trace_t;
struct physics_stats_t;
struct physics_performanceparams_t;
struct virtualmeshparams_t;
struct physsaveparams_t;
struct physrestoreparams_t;
struct physprerestoreparams_t;

enum phys_interface_id_t {
	PIID_UNKNOWN,
	PIID_IPHYSICSOBJECT,
	PIID_I_PHYSICS_FLUID_CONTROLLER,
	PIID_I_PHYSICS_SPRING,
	PIID_I_PHYSICS_CONSTRAINT_GROUP,
	PIID_I_PHYSICS_CONSTRAINT,
	PIID_I_PHYSICS_SHADOW_CONTROLLER,
	PIID_I_PHYSICS_PLAYER_CONTROLLER,
	PIID_I_PHYSICS_MOTION_CONTROLLER,
	PIID_I_PHYSICS_VEHICLE_CONTROLLER,
	PIID_I_PHYSICS_GAME_TRACE,
	PIID_NUM_TYPES
};

class i_save;
class i_restore;

class i_vphysics_debug_overlay {
public:
	virtual void add_entity_text_overlay( int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char* format, ... ) = 0;
	virtual void add_box_overlay( const vector& origin, const vector& mins, const vector& max, vector const& orientation, int r, int g, int b, int a, float duration ) = 0;
	virtual void add_triangle_overlay( const vector& p1, const vector& p2, const vector& p3, int r, int g, int b, int a, bool no_depth_test, float duration ) = 0;
	virtual void add_line_overlay( const vector& origin, const vector& dest, int r, int g, int b, bool no_depth_test, float duration ) = 0;
	virtual void add_text_overlay( const vector& origin, float duration, const char* format, ... ) = 0;
	virtual void add_text_overlay( const vector& origin, int line_offset, float duration, const char* format, ... ) = 0;
	virtual void add_screen_text_overlay( float x_pos, float y_pos, float duration, int r, int g, int b, int a, const char* text ) = 0;
	virtual void add_swept_box_overlay( const vector& start, const vector& end, const vector& mins, const vector& max, const vector& angles, int r, int g, int b, int a, float duration ) = 0;
	virtual void add_text_overlay_rgb( const vector& origin, int line_offset, float duration, float r, float g, float b, float alpha, const char* format, ... ) = 0;
};

class i_physics : public i_app_system {
public:
	virtual	i_physics_environment* create_environment( void ) = 0;
	virtual void destroy_environment( i_physics_environment* ) = 0;
	virtual i_physics_environment* get_active_environment_by_index( int index ) = 0;
	virtual i_physics_object_pair_hash* create_object_pair_hash( ) = 0;
	virtual void destroy_object_pair_hash( i_physics_object_pair_hash* hash ) = 0;
	virtual i_physics_collision_set* find_or_create_collision_set( unsigned int id, int max_element_count ) = 0;
	virtual i_physics_collision_set* find_collision_set( unsigned int id ) = 0;
	virtual void destroy_all_collision_sets( ) = 0;
};

class c_phys_convex;
class c_phys_polysoup;
class i_collision_query;
class i_vphysics_key_parser;
struct convertconvexparams_t;
class c_packed_physics_description;
class c_polyhedron;

struct truncatedcone_t {
	vector m_origin;
	vector m_normal;
	float m_h;
	float m_theta;
};

class i_physics_collision {
public:
	virtual ~i_physics_collision( void ) { }
	virtual c_phys_convex* convex_from_verts( vector** verts, int vert_count ) = 0;
	virtual c_phys_convex* convex_from_planes( float* planes, int plane_count, float merge_distance ) = 0;
	virtual float convex_volume( c_phys_convex* convex ) = 0;
	virtual float convex_surface_area( c_phys_convex* convex) = 0;
	virtual void set_convex_game_data( c_phys_convex* convex, unsigned int game_data ) = 0;
	virtual void convex_free( c_phys_convex* convex ) = 0;
	virtual c_phys_convex* bbox_to_convex( const vector& mins, const vector& maxs ) = 0;
	virtual c_phys_convex* convex_from_convex_polyhedron( const c_polyhedron& convex_polyhedron ) = 0;
	virtual void convexes_from_convex_polygon( const vector& poly_normal, const vector* points, int point_count, c_phys_convex** output ) = 0;
	virtual c_phys_polysoup* polysoup_create( void ) = 0;
	virtual void polysoup_destroy( c_phys_polysoup* soup) = 0;
	virtual void polysoup_add_triangle( c_phys_polysoup* soup, const vector& a, const vector& b, const vector& c, int material_index7bits ) = 0;
	virtual c_phys_collide* convert_polysoup_to_collide( c_phys_polysoup* soup, bool use_mopp ) = 0;
	virtual c_phys_collide* convert_convex_to_collide( c_phys_convex** convex, int convex_count ) = 0;
	virtual c_phys_collide* convert_convex_to_collide_params( c_phys_convex** convex, int convex_count, const convertconvexparams_t& convert_params ) = 0;
	virtual void destroy_collide( c_phys_collide* collide ) = 0;
	virtual int collide_size( c_phys_collide* collide ) = 0;
	virtual int collide_write( char* pDest, c_phys_collide* collide, bool swap = false ) = 0;
	virtual c_phys_collide* unserialize_collide( char* buffer, int size, int index ) = 0;
	virtual float collide_volume( c_phys_collide* collide ) = 0;
	virtual float collide_surface_area( c_phys_collide* collide ) = 0;
	virtual vector collide_get_extent( const c_phys_collide* collide, const vector& collide_origin, const vector& collide_angles, const vector& direction ) = 0;
	virtual void collide_get_aabb( vector* mins, vector* maxs, const c_phys_collide* collide, const vector& collide_origin, const vector& collide_angles ) = 0;
	virtual void collide_get_mass_center( c_phys_collide* collide, vector* out_mass_center ) = 0;
	virtual void collide_set_mass_center( c_phys_collide* collide, const vector& mass_center ) = 0;
	virtual vector collide_get_orthographic_areas( const c_phys_collide* collide ) = 0;
	virtual void collide_set_orthographic_areas( c_phys_collide* collide, const vector& areas ) = 0;
	virtual int collide_index( const c_phys_collide* collide ) = 0;
	virtual c_phys_collide* bbox_to_collide( const vector& mins, const vector& maxs ) = 0;
	virtual int get_convexes_used_in_collideable( const c_phys_collide* collideable, c_phys_convex** output_array, int output_array_limit ) = 0;
	virtual void trace_box( const vector& start, const vector& end, const vector& mins, const vector& maxs, const c_phys_collide* collide, const vector& collide_origin, const vector& collide_angles, trace_t* ptr ) = 0;
	virtual void trace_box( const ray_t& ray, const c_phys_collide* collide, const vector& collide_origin, const vector& collide_angles, trace_t* ptr ) = 0;
	virtual void trace_box( const ray_t& ray, unsigned int contents_mask, i_convex_info* convex_info, const c_phys_collide* collide, const vector& collide_origin, const vector& collide_angles, trace_t* ptr ) = 0;
	virtual void trace_collide( const vector& start, const vector& end, const c_phys_collide* pSweepCollide, const vector& sweepAngles, const c_phys_collide* pCollide, const vector& collideOrigin, const vector& collideAngles, trace_t* ptr) = 0;
	virtual bool is_box_intersecting_cone( const vector& box_abs_mins, const vector& box_abs_maxs, const truncatedcone_t& cone ) = 0;
	virtual void vcollide_load( vcollide_t* output, int solid_count, const char* buffer, int size, bool swap = false ) = 0;
	virtual void vcollide_unload( vcollide_t* vcollide ) = 0;
	virtual i_vphysics_key_parser* vphysics_key_parser_create( const char* key_data ) = 0;
	virtual void vphysics_key_parser_destroy( i_vphysics_key_parser* parser ) = 0;
	virtual int create_debug_mesh( c_phys_collide const* collision_model, vector** out_verts ) = 0;
	virtual void destroy_debug_mesh( int vert_count, vector* out_verts ) = 0;
	virtual i_collision_query* create_query_model( c_phys_collide* collide ) = 0;
	virtual void destroy_query_model( i_collision_query* query ) = 0;
	virtual i_physics_collision* thread_context_create( void ) = 0;
	virtual void thread_context_destroy( i_physics_collision* thread_contex ) = 0;
	virtual c_phys_collide* create_virtual_mesh( const virtualmeshparams_t& params ) = 0;
	virtual bool supports_virtual_mesh( ) = 0;
	virtual bool get_bbox_cache_size( int* cached_size, int* cached_count ) = 0;
	virtual c_polyhedron* polyhedron_from_convex( c_phys_convex* const convex, bool use_temp_polyhedron ) = 0;
	virtual void output_debug_info( const c_phys_collide* collide ) = 0;
	virtual unsigned int read_stat( int stat_id ) = 0;
};

class i_collision_query {
public:
	virtual ~i_collision_query( ) { }
	virtual int convex_count( void ) = 0;
	virtual int triangle_count( int convex_index ) = 0;
	virtual unsigned int get_game_data( int convex_index ) = 0;
	virtual void get_triangle_verts( int convex_index, int triangle_index, vector* verts ) = 0;
	virtual void set_triangle_verts( int convex_index, int triangle_index, const vector* verts ) = 0;
	virtual int get_triangle_material_index( int convex_index, int triangle_index ) = 0;
	virtual void set_triangle_material_index( int convex_index, int triangle_index, int index7bits ) = 0;
};

class i_physics_game_trace {
public:
	virtual void vehicle_trace_ray( const ray_t& ray, void* vehicle, trace_t* trace ) = 0;
	virtual	void vehicle_trace_ray_with_water( const ray_t& ray, void* vehicle, trace_t* trace ) = 0;
	virtual bool vehicle_point_in_water( const vector& point ) = 0;
};

class i_convex_info {
public:
	virtual unsigned int get_contents( int convex_game_data ) = 0;
};

class c_physics_event_handler;
class i_physics_collision_data {
public:
	virtual void get_surface_normal( vector& out ) = 0;
	virtual void get_contact_point( vector& out ) = 0;
	virtual void get_contact_speed( vector& out ) = 0;
};

struct vcollisionevent_t {
	i_physics_object* m_objects[ 2 ];
	int m_surface_props[ 2 ];
	bool m_is_collision;
	bool m_is_shadow_collision;
	float m_delta_collision_time;
	float m_collision_speed;
	i_physics_collision_data* m_internal_data;
};

class i_physics_collision_event {
public:
	virtual void pre_collision( vcollisionevent_t* event_ ) = 0;
	virtual void post_collision( vcollisionevent_t* event_ ) = 0;
	virtual void friction( i_physics_object* pObject, float energy, int surface_props, int surface_props_hit, i_physics_collision_data* data ) = 0;
	virtual void start_touch( i_physics_object* object, i_physics_object* object_, i_physics_collision_data* touch_data ) = 0;
	virtual void end_touch( i_physics_object* object, i_physics_object* object_, i_physics_collision_data* touch_data ) = 0;
	virtual void fluid_start_touch( i_physics_object* object, i_physics_fluid_controller* fluid ) = 0;
	virtual void fluid_end_touch( i_physics_object* object, i_physics_fluid_controller* fluid ) = 0;
	virtual void post_simulation_frame( ) = 0;
	virtual void object_enter_trigger( i_physics_object* trigger, i_physics_object* object ) { }
	virtual void object_leave_trigger( i_physics_object* trigger, i_physics_object* object ) { }
};

class i_physics_object_event {
public:
	virtual void object_wake( i_physics_object* object ) = 0;
	virtual void object_sleep( i_physics_object* object ) = 0;
};

class i_physics_constraint_event {
public:
	virtual void constraint_broken( i_physics_constraint* ) = 0;
};

struct hlshadowcontrol_params_t {
	vector m_target_position;
	vector m_target_rotation;
	float m_max_angular;
	float m_max_damp_angular;
	float m_max_speed;
	float m_max_damp_speed;
	float m_damp_factor;
	float m_teleport_distance;
};

class i_physics_shadow_controller {
public:
	virtual ~i_physics_shadow_controller( void ) { }

	virtual void update( const vector& position, const vector& angles, float time_offset ) = 0;
	virtual void max_speed( float max_speed, float maxangular_speed ) = 0;
	virtual void step_up( float height ) = 0;
	virtual void set_teleport_distance( float teleport_distance ) = 0;
	virtual bool allows_translation( ) = 0;
	virtual bool allows_rotation( ) = 0;
	virtual void set_physically_controlled( bool is_physically_controlled ) = 0;
	virtual bool is_physically_controlled( ) = 0;
	virtual void get_last_impulse(vector* out ) = 0;
	virtual void use_shadow_material(bool use_shadow_material ) = 0;
	virtual void object_material_changed(int material_index ) = 0;
	virtual float get_target_position( vector* position_out, vector* angles_out ) = 0;
	virtual float get_teleport_distance( void ) = 0;
	virtual void get_max_speed( float* max_speed_out, float* max_angular_speed_out ) = 0;
};

class c_physics_sim_object;
class i_physics_motion_controller;

class i_motion_event {
public:
	enum simresult_e { IM_NOTHING = 0, SIM_LOCAL_ACCELERATION, SIM_LOCAL_FORCE, SIM_GLOBAL_ACCELERATION, SIM_GLOBAL_FORCE };
	virtual simresult_e	simulate( i_physics_motion_controller* controller, i_physics_object* object, float delta_time, vector& linear, vector& angular ) = 0;
};

class i_physics_motion_controller {
public:
	virtual ~i_physics_motion_controller( void ) { }
	virtual void set_event_handler( i_motion_event* handler ) = 0;
	virtual void attach_object( i_physics_object* object, bool check_if_already_attached ) = 0;
	virtual void detach_object( i_physics_object* object ) = 0;
	virtual int count_objects( void ) = 0;
	virtual void get_objects( i_physics_object** object_list ) = 0;
	virtual void clear_objects( void ) = 0;
	virtual void wake_objects( void ) = 0;

	enum priority_t {
		LOW_PRIORITY = 0,
		MEDIUM_PRIORITY = 1,
		HIGH_PRIORITY = 2
	};

	virtual void set_priority( priority_t priority ) = 0;
};

class i_physics_collision_solver {
public:
	virtual int should_collide( i_physics_object* object, i_physics_object* object_, void* game_data, void* game_data_ ) = 0;
	virtual int should_solve_penetration( i_physics_object* object, i_physics_object* object_, void* game_data, void* game_data_, float dt ) = 0;
	virtual bool should_freeze_object( i_physics_object* object ) = 0;
	virtual int additional_collision_checks_this_tick( int current_checks_done ) = 0;
	virtual bool should_freeze_contacts( i_physics_object** object_list, int object_count ) = 0;
};

enum physics_trace_type_t {
	VPHYSICS_TRACE_EVERYTHING = 0,
	VPHYSICS_TRACE_STATIC_ONLY,
	VPHYSICS_TRACE_MOVING_ONLY,
	VPHYSICS_TRACE_TRIGGERS_ONLY,
	VPHYSICS_TRACE_STATIC_AND_MOVING,
};

class i_physics_trace_filter {
public:
	virtual bool should_hit_object( i_physics_object* object, int contents_mask ) = 0;
	virtual physics_trace_type_t get_trace_type( ) const = 0;
};

class i_physics_environment {
public:
	virtual ~i_physics_environment( void ) { }
	virtual void set_debug_overlay( create_interface_fn debug_overlay_factory ) = 0;
	virtual i_vphysics_debug_overlay* get_debug_overlay( void ) = 0;
	virtual void set_gravity( const vector& gravity_vector ) = 0;
	virtual void get_gravity( vector* gravity_vector ) const = 0;
	virtual void set_air_density( float density ) = 0;
	virtual float get_air_density( void ) const = 0;
	virtual i_physics_object* create_poly_object( const c_phys_collide* collision_model, int material_index, const vector& position, const vector& angles, objectparams_t* params ) = 0;
	virtual i_physics_object* create_poly_object_static( const c_phys_collide* collision_model, int material_index, const vector& position, const vector& angles, objectparams_t* params ) = 0;
	virtual i_physics_object* create_sphere_object( float radius, int material_index, const vector& position, const vector& angles, objectparams_t* params, bool is_static ) = 0;
	virtual void destroy_object( i_physics_object* ) = 0;
	virtual i_physics_fluid_controller* create_fluid_controller( i_physics_object* fluid_object, fluidparams_t* params ) = 0;
	virtual void destroy_fluid_controller( i_physics_fluid_controller* ) = 0;
	virtual i_physics_spring* create_spring( i_physics_object* object_start, i_physics_object* object_end, springparams_t* params ) = 0;
	virtual void destroy_spring( i_physics_spring* ) = 0;
	virtual i_physics_constraint* create_ragdoll_constraint( i_physics_object* reference_object, i_physics_object* attached_object, i_physics_constraint_group* group, const constraint_ragdollparams_t& ragdoll ) = 0;
	virtual i_physics_constraint* create_hinge_constraint( i_physics_object* reference_object, i_physics_object* attached_object, i_physics_constraint_group* group, const constraint_hingeparams_t& hinge ) = 0;
	virtual i_physics_constraint* create_fixed_constraint( i_physics_object* reference_object, i_physics_object* attached_object, i_physics_constraint_group* group, const constraint_fixedparams_t& fixed ) = 0;
	virtual i_physics_constraint* create_sliding_constraint( i_physics_object* reference_object, i_physics_object* attached_object, i_physics_constraint_group* group, const constraint_slidingparams_t& sliding ) = 0;
	virtual i_physics_constraint* create_ballsocket_constraint( i_physics_object* reference_object, i_physics_object* attached_object, i_physics_constraint_group* group, const constraint_ballsocketparams_t& ballsocket ) = 0;
	virtual i_physics_constraint* create_pulley_constraint( i_physics_object* reference_object, i_physics_object* attached_object, i_physics_constraint_group* group, const constraint_pulleyparams_t& pulley ) = 0;
	virtual i_physics_constraint* create_length_constraint( i_physics_object* reference_object, i_physics_object* attached_object, i_physics_constraint_group* group, const constraint_lengthparams_t& length ) = 0;
	virtual void destroy_constraint( i_physics_constraint* ) = 0;
	virtual i_physics_constraint_group* create_constraint_group( const constraint_groupparams_t& group_params ) = 0;
	virtual void destroy_constraint_group( i_physics_constraint_group* group ) = 0;
	virtual i_physics_shadow_controller* create_shadow_controller( i_physics_object* object, bool allow_translation, bool allow_rotation ) = 0;
	virtual void destroy_shadow_controller( i_physics_shadow_controller* ) = 0;
	virtual i_physics_player_controller* create_player_controller( i_physics_object* object ) = 0;
	virtual void destroy_player_controller( i_physics_player_controller* ) = 0;
	virtual i_physics_motion_controller* create_motion_controller( i_motion_event* handler ) = 0;
	virtual void destroy_motion_controller( i_physics_motion_controller* controller ) = 0;
	virtual i_physics_vehicle_controller* create_vehicle_controller( i_physics_object* vehicle_body_object, const vehicleparams_t& params, unsigned int nVehicleType, i_physics_game_trace* game_trace ) = 0;
	virtual void destroy_vehicle_controller(i_physics_vehicle_controller*) = 0;
	virtual void set_collision_solver( i_physics_collision_solver* solver ) = 0;
	virtual void simulate( float delta_time ) = 0;
	virtual bool is_in_simulation( ) const = 0;
	virtual float get_simulation_timestep( ) const = 0;
	virtual void set_simulation_timestep( float timestep ) = 0;
	virtual float get_simulation_time( ) const = 0;
	virtual void reset_simulation_clock( ) = 0;
	virtual float get_next_frame_time(void) const = 0;
	virtual void set_collision_event_handler( i_physics_collision_event* collision_events ) = 0;
	virtual void set_object_event_handler( i_physics_object_event* object_events ) = 0;
	virtual	void set_constraint_event_handler( i_physics_constraint_event* constraint_event ) = 0;
	virtual void set_quick_delete( bool quick ) = 0;
	virtual int get_active_object_count( ) const = 0;
	virtual void get_active_objects( i_physics_object** output_object_list ) const = 0;
	virtual const i_physics_object** get_object_list( int* output_object_count ) const = 0;
	virtual bool transfer_object( i_physics_object* object, i_physics_environment* destination_environment ) = 0;
	virtual void cleanup_delete_list( void ) = 0;
	virtual void enable_delete_queue( bool enable ) = 0;
	virtual bool save( const physsaveparams_t& params ) = 0;
	virtual void pre_restore( const physprerestoreparams_t& params ) = 0;
	virtual bool restore( const physrestoreparams_t& params ) = 0;
	virtual void post_restore( ) = 0;
	virtual bool is_collision_model_used( c_phys_collide* collide ) const = 0;
	virtual void trace_ray( const ray_t& ray, unsigned int mask, i_physics_trace_filter* trace_filter, trace_t* trace ) = 0;
	virtual void sweep_collideable( const c_phys_collide* collide, const vector& abs_start, const vector& abs_end, const vector& angles, unsigned int mask, i_physics_trace_filter* trace_filter, trace_t* trace ) = 0;
	virtual void get_performance_settings( physics_performanceparams_t* output ) const = 0;
	virtual void set_performance_settings( const physics_performanceparams_t* settings ) = 0;
	virtual void read_stats( physics_stats_t* output ) = 0;
	virtual void clear_stats( ) = 0;
	virtual unsigned int get_object_serialize_size( i_physics_object* object ) const = 0;
	virtual void serialize_object_to_buffer( i_physics_object* object, unsigned char* buffer, unsigned int buffer_size ) = 0;
	virtual i_physics_object* unserialize_object_from_buffer( void* game_data, unsigned char* buffer, unsigned int buffer_size, bool enable_collisions ) = 0;
	virtual void enable_constraint_notify( bool enable ) = 0;
	virtual void debug_check_contacts( void ) = 0;
};

const objectparams_t g_phys_default_object_params = {
	NULL,
	1.0,
	1.0,
	0.1f,
	0.1f,
	0.05f,
	"DEFAULT",
	NULL,
	0.f,
	1.0f,
	true,
};

class c_physics_object : public i_physics_object {
public:
	void* m_game_data;
	void* m_object;
	const c_phys_collide* m_collide;
	i_physics_shadow_controller* m_shadow;
	vector m_drag_basis;
	vector m_angular_drag_basis;
	bool m_shadow_temp_gravity_disable : 5;
	bool m_has_touched_dynamic : 1;
	bool m_asleep_since_creation : 1;
	bool m_force_silent_delete : 1;
	unsigned char m_sleep_state : 2;
	unsigned char m_hinged_axis : 3;
	unsigned char m_collide_type : 3;
	unsigned short m_game_index;
	unsigned short m_material_index;
	unsigned short m_active_index;
	unsigned short m_callbacks;
	unsigned short m_game_flags;
	unsigned int m_contents_mask;
	float m_volume;
	float m_buoyancy_ratio;
	float m_drag_coefficient;
	float m_angular_drag_coefficient;
};

inline const float k_max_velocity = 2000.0f;
inline const float k_max_angular_velocity = 360.0f * 10.0f;

const float default_min_fricion_mass = 10.0f;
const float default_max_fricion_mass = 2500.0f;

struct physics_performanceparams_t {
	int m_max_collisions_per_object_per_timestep;
	int m_max_collision_checks_per_timestep;
	float m_max_velocity;
	float m_max_angular_velocity;
	float m_look_ahead_time_objects_vs_world;
	float m_look_ahead_time_objects_vs_object;
	float m_min_friction_mass;
	float m_max_friction_mass;

	void defaults( ) {
		this->m_max_collisions_per_object_per_timestep = 6;
		this->m_max_collision_checks_per_timestep = 250;
		this->m_max_velocity = k_max_velocity;
		this->m_max_angular_velocity = k_max_angular_velocity;
		this->m_look_ahead_time_objects_vs_world = 1.0f;
		this->m_look_ahead_time_objects_vs_object = 0.5f;
		this->m_min_friction_mass = default_min_fricion_mass;
		this->m_max_friction_mass = default_max_fricion_mass;
	}
};

enum projectile_type_t {
	TF_PROJECTILE_NONE,
	TF_PROJECTILE_BULLET,
	TF_PROJECTILE_ROCKET,
	TF_PROJECTILE_PIPEBOMB,
	TF_PROJECTILE_PIPEBOMB_REMOTE,
	TF_PROJECTILE_SYRINGE,
	TF_PROJECTILE_FLARE,
	TF_PROJECTILE_JAR,
	TF_PROJECTILE_ARROW,
	TF_PROJECTILE_FLAME_ROCKET,
	TF_PROJECTILE_JAR_MILK,
	TF_PROJECTILE_HEALING_BOLT,
	TF_PROJECTILE_ENERGY_BALL,
	TF_PROJECTILE_ENERGY_RING,
	TF_PROJECTILE_PIPEBOMB_PRACTICE,
	TF_PROJECTILE_CLEAVER,
	TF_PROJECTILE_STICKY_BALL,
	TF_PROJECTILE_CANNONBALL,
	TF_PROJECTILE_BUILDING_REPAIR_BOLT,
	TF_PROJECTILE_FESTIVE_ARROW,
	TF_PROJECTILE_THROWABLE,
	TF_PROJECTILE_SPELL,
	TF_PROJECTILE_FESTIVE_JAR,
	TF_PROJECTILE_FESTIVE_HEALING_BOLT,
	TF_PROJECTILE_BREADMONSTER_JARATE,
	TF_PROJECTILE_BREADMONSTER_MADMILK,
	TF_PROJECTILE_GRAPPLINGHOOK,
	TF_PROJECTILE_SENTRY_ROCKET,
	TF_PROJECTILE_BREAD_MONSTER,
	TF_PROJECTILE_JAR_GAS,
	TF_PROJECTILE_BALLOFFIRE,
	TF_NUM_PROJECTILES
};

enum {
	PARTITION_ENGINE_SOLID_EDICTS = (1 << 0),		// every edict_t that isn't SOLID_TRIGGER or SOLID_NOT (and static props)
	PARTITION_ENGINE_TRIGGER_EDICTS = (1 << 1),		// every edict_t that IS SOLID_TRIGGER
	PARTITION_CLIENT_SOLID_EDICTS = (1 << 2),
	PARTITION_CLIENT_RESPONSIVE_EDICTS = (1 << 3),		// these are client-side only objects that respond to being forces, etc.
	PARTITION_ENGINE_NON_STATIC_EDICTS = (1 << 4),		// everything in solid & trigger except the static props, includes SOLID_NOTs
	PARTITION_CLIENT_STATIC_PROPS = (1 << 5),
	PARTITION_ENGINE_STATIC_PROPS = (1 << 6),
	PARTITION_CLIENT_NON_STATIC_EDICTS = (1 << 7),		// everything except the static props
};

#define MAX_SPHERE_QUERY 256

class c_entity_sphere_query {
public:
	c_entity_sphere_query( const vector& center, const float radius, const int flag_mask = 0, const int partition_mask = PARTITION_CLIENT_NON_STATIC_EDICTS ) {
		typedef void( __thiscall* fn )( void*, const vector&, float, int, int );
		static auto function = util::find_signature< fn >( "client.dll", "55 8B EC 83 EC 14 D9 45 0C" );
		function( this, center, radius, flag_mask, partition_mask );
	}

	c_base_entity* get_current_entity( ) {
		return ( m_list_index < m_list_count ) ? m_list[ m_list_index ] : nullptr;
	}

	void next_entity( ) {
		m_list_index++;
	}

private:
	int m_list_index, m_list_count;
	c_base_entity* m_list[ MAX_SPHERE_QUERY ];
};

struct overlay_text_t;

class iv_debug_overlay {
public:
	virtual void add_entity_text_overlay( int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char* format, ... ) = 0;
	virtual void add_box_overlay( const vector& origin, const vector& mins, const vector& maxs, vector const& orientation, int r, int g, int b, int a, float duration ) = 0;
	virtual void add_triangle_overlay( const vector& p1, const vector& p2, const vector& p3, int r, int g, int b, int a, bool no_depth_test, float duration ) = 0;
	virtual void add_line_overlay( const vector& origin, const vector& dest, int r, int g, int b, bool no_depth_test, float duration ) = 0;
	virtual void add_text_overlay( const vector& origin, float duration, const char* format, ... ) = 0;
	virtual void add_text_overlay( const vector& origin, int line_offset, float duration, const char* format, ... ) = 0;
	virtual void add_screen_text_overlay( float x_pos, float y_pos, float duration, int r, int g, int b, int a, const char* text ) = 0;
	virtual void add_swept_box_overlay( const vector& start, const vector& end, const vector& mins, const vector& maxs, const vector& angles, int r, int g, int b, int a, float duration ) = 0;
	virtual void add_grid_overlay( const vector& origin ) = 0;
	virtual int screen_position( const vector& point, vector& screen) = 0;
	virtual int screen_position( float x_pos, float y_pos, vector& screen) = 0;
	virtual overlay_text_t* get_first( void ) = 0;
	virtual overlay_text_t* get_next( overlay_text_t* current ) = 0;
	virtual void clear_dead_overlays( void ) = 0;
	virtual void clear_all_overlays( ) = 0;
	virtual void add_text_overlay_rgb( const vector& origin, int line_offset, float duration, float r, float g, float b, float alpha, const char* format, ... ) = 0;
	virtual void add_text_overlay_rgb( const vector& origin, int line_offset, float duration, int r, int g, int b, int a, const char* format, ... ) = 0;
	virtual void pad( ) = 0;
	virtual void add_line_overlay_alpha( const vector& origin, const vector& dest, int r, int g, int b, int a, bool no_depth_test, float duration ) = 0;
	virtual void add_box_overlay_2( const vector& origin, const vector& mins, const vector& maxs, vector const& orientation, const color& face_color, const color& edge_color, float duration ) = 0;

private:
	inline void add_text_overlay( const vector& origin, int line_offset, float duration, int r, int g, int b, int a, const char* format, ... ) { }
};

enum move_type_t
{
	MOVETYPE_NONE = 0,	// never moves
	MOVETYPE_ISOMETRIC,			// For players -- in TF2 commander view, etc.
	MOVETYPE_WALK,				// Player only - moving on the ground
	MOVETYPE_STEP,				// gravity, special edge handling -- monsters use this
	MOVETYPE_FLY,				// No gravity, but still collides with stuff
	MOVETYPE_FLYGRAVITY,		// flies through the air + is affected by gravity
	MOVETYPE_VPHYSICS,			// uses VPHYSICS for simulation
	MOVETYPE_PUSH,				// no clip to world, push and crush
	MOVETYPE_NOCLIP,			// No gravity, no collisions, still do velocity/avelocity
	MOVETYPE_LADDER,			// Used by players only when going onto a ladder
	MOVETYPE_OBSERVER,			// Observer movement, depends on player's observer mode
	MOVETYPE_CUSTOM,			// Allows the entity to describe its own physics

	MOVETYPE_LAST = MOVETYPE_CUSTOM,

	MOVETYPE_MAX_BITS = 4
};

class c_panel {
public:
	inline const char* get_name( unsigned int vgui_panel )
	{
		typedef const char* ( __thiscall* fn )( PVOID, unsigned int );
		return util::get_virtual<fn>( this, 36 )( this, vgui_panel );
	}
};

typedef unsigned short model_instance_handle_t;
struct stuido_data_t;
struct studio_decal_handle_t;

struct draw_model_state_t
{
	studiohdr_t* studio_hdr;
	stuido_data_t* studio_data;
	i_client_renderable* renderable;
	const matrix_3x4* model_to_world;
	studio_decal_handle_t* decals;
	int draw_flags;
	int lod;
};

struct model_render_info_t
{
	vector origin;
	vector angles;
	i_client_renderable* renderable;
	const model_t* model;
	const matrix_3x4* model_to_world;
	const matrix_3x4* lighting_offset;
	const vector* lighting_origin;
	int flags;
	int ent_index;
	int skin;
	int body;
	int hitbox_set;
	model_instance_handle_t mdl_instance;

	model_render_info_t()
	{
		model_to_world = NULL;
		lighting_offset = NULL;
		lighting_origin = NULL;
	}
};

class iv_model_renderer
{
public:
	virtual int		draw_model(int flags,
		void* renderable,
		model_instance_handle_t instance,
		int entity_index,
		const model_t* model,
		vector const& origin,
		vector const& angles,
		int skin,
		int body,
		int hitbox_set,
		const matrix_3x4* model_to_world = NULL,
		const matrix_3x4* light_offset = NULL) = 0;

	virtual void	forced_material_override(i_material* material, int nOverrideType = 0) = 0;

};

#define TEXTURE_GROUP_LIGHTMAP						"Lightmaps"
#define TEXTURE_GROUP_WORLD							"World textures"
#define TEXTURE_GROUP_MODEL							"Model textures"
#define TEXTURE_GROUP_VGUI							"VGUI textures"
#define TEXTURE_GROUP_PARTICLE						"Particle textures"
#define TEXTURE_GROUP_DECAL							"Decal textures"
#define TEXTURE_GROUP_SKYBOX						"SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				"ClientEffect textures"
#define TEXTURE_GROUP_OTHER							"Other textures"
#define TEXTURE_GROUP_PRECACHED						"Precached"				// TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP						"CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"
#define TEXTURE_GROUP_RUNTIME_COMPOSITE				"Runtime Composite"
#define TEXTURE_GROUP_UNACCOUNTED					"Unaccounted textures"	// Textures that weren't assigned a texture group.

#define STUDIO_NONE						0x00000000
#define STUDIO_RENDER					0x00000001
#define STUDIO_VIEWXFORMATTACHMENTS		0x00000002
#define STUDIO_DRAWTRANSLUCENTSUBMODELS 0x00000004
#define STUDIO_TWOPASS					0x00000008
#define STUDIO_STATIC_LIGHTING			0x00000010
#define STUDIO_WIREFRAME				0x00000020
#define STUDIO_ITEM_BLINK				0x00000040
#define STUDIO_NOSHADOWS				0x00000080
#define STUDIO_WIREFRAME_VCOLLIDE		0x00000100
#define STUDIO_NO_OVERRIDE_FOR_ATTACH	0x00000200

// Not a studio flag, but used to flag when we want studio stats
#define STUDIO_GENERATE_STATS			0x01000000

// Not a studio flag, but used to flag model as using shadow depth material override
#define STUDIO_SSAODEPTHTEXTURE			0x08000000

// Not a studio flag, but used to flag model as using shadow depth material override
#define STUDIO_SHADOWDEPTHTEXTURE		0x40000000

// Not a studio flag, but used to flag model as a non-sorting brush model
#define STUDIO_TRANSPARENCY				0x80000000

#define CREATERENDERTARGETFLAGS_HDR				0x00000001
#define CREATERENDERTARGETFLAGS_AUTOMIPMAP		0x00000002
#define CREATERENDERTARGETFLAGS_UNFILTERABLE_OK 0x00000004

enum clear_flags_t
{
	VIEW_CLEAR_COLOR = 0x1,
	VIEW_CLEAR_DEPTH = 0x2,
	VIEW_CLEAR_FULL_TARGET = 0x4,
	VIEW_NO_DRAW = 0x8,
	VIEW_CLEAR_OBEY_STENCIL = 0x10, // Draws a quad allowing stencil test to clear through portals
	VIEW_CLEAR_STENCIL = 0x20,
};

class i_mat_render_context;
class i_view_render;
class iv_material_system
{
public:
	e_image_format get_back_buffer_format( ) {
		typedef e_image_format( __thiscall* fn )( iv_material_system* );
		return util::get_virtual<fn>( this, 37u )( this );
	}

	i_material* create_material( const char* mat, key_values* vmt ) {
		typedef i_material* ( __thiscall* fn )( iv_material_system*, const char*, key_values* );
		return util::get_virtual<fn>( this, 72u )( this, mat, vmt );
	}

	i_material* find_material(char const* mat, const char* group, bool complain = true, const char* prefix = NULL) {
		typedef i_material* (__thiscall* fn)(PVOID, const char*, const char*, bool, const char*);
		return util::get_virtual<fn>( this, 73u )(this, mat, group, complain, prefix);
	}

	i_texture* find_texture( char const* texture_name, const char* texture_group_name, bool complain = true, int additional_creation_flags = 0 ) {
		typedef i_texture* ( __thiscall* fn )( iv_material_system*, const char*, const char*, bool, int );
		return util::get_virtual<fn>( this, 81u )( this, texture_name, texture_group_name, complain, additional_creation_flags );
	}

	void begin_render_target_allocation( ) {
		typedef void( __thiscall* fn )( iv_material_system* );
		return util::get_virtual<fn>( this, 84u )( this );
	}

	void end_render_target_allocation( ) {
		typedef void( __thiscall* fn )( iv_material_system* );
		return util::get_virtual<fn>( this, 85u )( this );
	}

	i_texture* create_named_render_target_texture_ex( const char* rt_name, int w, int h, render_target_size_mode_t size_mode, e_image_format format, 
													  material_render_target_depth_t depth = MATERIAL_RT_DEPTH_SHARED, 
													  unsigned int texture_flags = TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT, unsigned int render_target_flags = 0 ) {
		typedef i_texture* ( __thiscall* fn )( iv_material_system*, const char*, int, int, render_target_size_mode_t, e_image_format, material_render_target_depth_t,
											   unsigned int, unsigned int );
		return util::get_virtual<fn>( this, 88u )( this, rt_name, w, h, size_mode, format, depth, texture_flags, render_target_flags );
	}

	i_mat_render_context* get_render_context( ) {
		typedef i_mat_render_context* ( __thiscall* fn )( iv_material_system* );
		return util::get_virtual<fn>( this, 100u )( this );
	}
};

enum light_type_t
{
	MATERIAL_LIGHT_DISABLE = 0,
	MATERIAL_LIGHT_POINT,
	MATERIAL_LIGHT_DIRECTIONAL,
	MATERIAL_LIGHT_SPOT,
};

struct light_desc_t
{
	light_type_t m_Type;
	vector m_Color;
	vector m_Position;
	vector m_Direction;
	float  m_Range;
	float m_Falloff;
	float m_Attenuation0;
	float m_Attenuation1;
	float m_Attenuation2;
	float m_Theta;
	float m_Phi;
	float m_ThetaDot;
	float m_PhiDot;
	unsigned int m_Flags;
	float OneOver_ThetaDot_Minus_PhiDot;
	float m_RangeSquared;
};

struct morph_weight_t;
struct material_primitive_type_t;
struct material_non_interactive_mode_t;
struct material_matrix_mode_t;
struct material_index_format_t;
struct i_mesh;
enum material_height_clip_mode_t
{
	MATERIAL_HEIGHTCLIPMODE_DISABLE,
	MATERIAL_HEIGHTCLIPMODE_RENDER_ABOVE_HEIGHT,
	MATERIAL_HEIGHTCLIPMODE_RENDER_BELOW_HEIGHT
};
struct material_fog_mode_t;
enum material_cull_mode_t
{
	MATERIAL_CULLMODE_CCW,	// this culls polygons with counterclockwise winding
	MATERIAL_CULLMODE_CW	// this culls polygons with clockwise winding
};

struct i_vertex_buffer;
struct i_morph;
struct i_index_buffer;
struct i_call_queue;
struct i_async_texture_operation_receiver;
struct flashlight_state_t;
struct deformation_base_t;
struct color_correction_handle_t;
struct vmatrix;
struct vector_4d;

enum stencil_operation_t
{
	STENCILOPERATION_KEEP = 1,
	STENCILOPERATION_ZERO = 2,
	STENCILOPERATION_REPLACE = 3,
	STENCILOPERATION_INCRSAT = 4,
	STENCILOPERATION_DECRSAT = 5,
	STENCILOPERATION_INVERT = 6,
	STENCILOPERATION_INCR = 7,
	STENCILOPERATION_DECR = 8,
	STENCILOPERATION_FORCE_DWORD = 0x7fffffff
};

enum stencil_comparison_function_t
{
	STENCILCOMPARISONFUNCTION_NEVER = 1,
	STENCILCOMPARISONFUNCTION_LESS = 2,
	STENCILCOMPARISONFUNCTION_EQUAL = 3,
	STENCILCOMPARISONFUNCTION_LESSEQUAL = 4,
	STENCILCOMPARISONFUNCTION_GREATER = 5,
	STENCILCOMPARISONFUNCTION_NOTEQUAL = 6,
	STENCILCOMPARISONFUNCTION_GREATEREQUAL = 7,
	STENCILCOMPARISONFUNCTION_ALWAYS = 8,
	STENCILCOMPARISONFUNCTION_FORCE_DWORD = 0x7fffffff
};

class i_ref_counted
{
public:
	virtual int add_ref( ) = 0;
	virtual int release( ) = 0;
};

class i_mat_render_context : public i_ref_counted
{
public:
	virtual void begin_render( ) = 0;
	virtual void end_render( ) = 0;
	virtual void flush( bool flush_hardware = false ) = 0;
	virtual void bind_local_cubemap( i_texture* p_texture ) = 0;
	virtual void set_render_target( i_texture* p_texture ) = 0;
	virtual i_texture* get_render_target( void ) = 0;
	virtual void get_render_target_dimensions( int& width, int& height ) const = 0;
	virtual void bind( i_material* material, void* proxy_data = 0 ) = 0;
	virtual void bind_lightmap_page( int lightmap_page_id ) = 0;
	virtual void depth_range( float z_near, float z_far ) = 0;
	virtual void clear_buffers( bool b_clear_color, bool b_clear_depth, bool b_clear_stencil = false ) = 0;
	virtual void read_pixels( int x, int y, int width, int height, unsigned char* data, e_image_format dst_format ) = 0;
	virtual void set_ambient_light( float r, float g, float b ) = 0;
	virtual void set_light( int light_num, const light_desc_t& desc ) = 0;
	virtual void set_ambient_light_cube( vector_4d cube[ 6 ] ) = 0;
	virtual void copy_render_target_to_texture( i_texture* p_texture ) = 0;
	virtual void set_frame_buffer_copy_texture( i_texture* p_texture, int texture_index = 0 ) = 0;
	virtual i_texture* get_frame_buffer_copy_texture( int texture_index ) = 0;
	virtual void matrix_mode( material_matrix_mode_t matrix_mode ) = 0;
	virtual void push_matrix( void ) = 0;
	virtual void pop_matrix( void ) = 0;
	virtual void load_matrix( vmatrix const& matrix ) = 0;
	virtual void load_matrix( matrix_3x4 const& matrix ) = 0;
	virtual void mult_matrix( vmatrix const& matrix ) = 0;
	virtual void mult_matrix( matrix_3x4 const& matrix ) = 0;
	virtual void mult_matrix_local( vmatrix const& matrix ) = 0;
	virtual void mult_matrix_local( matrix_3x4 const& matrix ) = 0;
	virtual void get_matrix( material_matrix_mode_t matrix_mode, vmatrix* matrix ) = 0;
	virtual void get_matrix( material_matrix_mode_t matrix_mode, matrix_3x4* matrix ) = 0;
	virtual void load_identity( void ) = 0;
	virtual void ortho( double left, double top, double right, double bottom, double z_near, double z_far ) = 0;
	virtual void perspective_x( double fovx, double aspect, double z_near, double z_far ) = 0;
	virtual void pick_matrix( int x, int y, int width, int height ) = 0;
	virtual void rotate( float angle, float x, float y, float z ) = 0;
	virtual void translate( float x, float y, float z ) = 0;
	virtual void scale( float x, float y, float z ) = 0;
	virtual void viewport( int x, int y, int width, int height ) = 0;
	virtual void get_viewport( int& x, int& y, int& width, int& height ) const = 0;
	virtual void cull_mode( material_cull_mode_t cull_mode ) = 0;
	virtual void set_height_clip_mode( material_height_clip_mode_t n_height_clip_mode ) = 0;
	virtual void set_height_clip_z( float z ) = 0;
	virtual void fog_mode( material_fog_mode_t fog_mode ) = 0;
	virtual void fog_start( float f_start ) = 0;
	virtual void fog_end( float f_end ) = 0;
	virtual void set_fog_z( float fog_z ) = 0;
	virtual material_fog_mode_t get_fog_mode( void ) = 0;
	virtual void fog_color3f( float r, float g, float b ) = 0;
	virtual void fog_color3fv( float const* rgb ) = 0;
	virtual void fog_color3ub( unsigned char r, unsigned char g, unsigned char b ) = 0;
	virtual void fog_color3ubv( unsigned char const* rgb ) = 0;
	virtual void get_fog_color( unsigned char* rgb ) = 0;
	virtual void set_num_bone_weights( int num_bones ) = 0;
	virtual i_mesh* create_static_mesh( vertex_format_t fmt, const char* p_texture_budget_group, i_material* p_material = NULL ) = 0;
	virtual void destroy_static_mesh( i_mesh* mesh ) = 0;
	virtual i_mesh* get_dynamic_mesh( bool buffered = true, i_mesh* p_vertex_override = 0, i_mesh* p_index_override = 0, i_material* p_auto_bind = 0 ) = 0;
	virtual i_vertex_buffer* create_static_vertex_buffer( vertex_format_t fmt, int n_vertex_count, const char* p_texture_budget_group ) = 0;
	virtual i_index_buffer* create_static_index_buffer( material_index_format_t fmt, int n_index_count, const char* p_texture_budget_group ) = 0;
	virtual void destroy_vertex_buffer( i_vertex_buffer* ) = 0;
	virtual void destroy_index_buffer( i_index_buffer* ) = 0;
	virtual i_vertex_buffer* get_dynamic_vertex_buffer( int stream_id, vertex_format_t vertex_format, bool b_buffered = true ) = 0;
	virtual i_index_buffer* get_dynamic_index_buffer( material_index_format_t fmt, bool b_buffered = true ) = 0;
	virtual void bind_vertex_buffer( int stream_id, i_vertex_buffer* p_vertex_buffer, int n_offset_in_bytes, int n_first_vertex, int n_vertex_count, vertex_format_t fmt, int n_repetitions = 1 ) = 0;
	virtual void bind_index_buffer( i_index_buffer* p_index_buffer, int n_offset_in_bytes ) = 0;
	virtual void draw( material_primitive_type_t primitive_type, int first_index, int num_indices ) = 0;
	virtual int  selection_mode( bool selection_mode ) = 0;
	virtual void selection_buffer( unsigned int* p_buffer, int size ) = 0;
	virtual void clear_selection_names( ) = 0;
	virtual void load_selection_name( int name ) = 0;
	virtual void push_selection_name( int name ) = 0;
	virtual void pop_selection_name( ) = 0;
	virtual void clear_color3ub( unsigned char r, unsigned char g, unsigned char b ) = 0;
	virtual void clear_color4ub( unsigned char r, unsigned char g, unsigned char b, unsigned char a ) = 0;
	virtual void override_depth_enable( bool b_enable, bool b_depth_enable ) = 0;
	virtual void draw_screen_space_quad( i_material* p_material ) = 0;
	virtual void sync_token( const char* p_token ) = 0;
	virtual float compute_pixel_width_of_sphere( const vector& origin, float fl_radius ) = 0;
	virtual occlusion_query_object_handle_t create_occlusion_query_object( void ) = 0;
	virtual void destroy_occlusion_query_object( occlusion_query_object_handle_t ) = 0;
	virtual void begin_occlusion_query_drawing( occlusion_query_object_handle_t ) = 0;
	virtual void end_occlusion_query_drawing( occlusion_query_object_handle_t ) = 0;
	virtual int occlusion_query_get_num_pixels_rendered( occlusion_query_object_handle_t ) = 0;
	virtual void set_flashlight_mode( bool b_enable ) = 0;
	virtual void set_flashlight_state( const flashlight_state_t& state, const vmatrix& world_to_texture ) = 0;
	virtual material_height_clip_mode_t get_height_clip_mode( ) = 0;
	virtual float compute_pixel_diameter_of_sphere( const vector& vec_abs_origin, float fl_radius ) = 0;
	virtual void enable_user_clip_transform_override( bool b_enable ) = 0;
	virtual void user_clip_transform( const vmatrix& world_to_view ) = 0;
	virtual bool get_flashlight_mode( ) const = 0;
	virtual void reset_occlusion_query_object( occlusion_query_object_handle_t ) = 0;
	virtual void unused3( ) {}
	virtual i_morph* create_morph( morph_format_t format, const char* p_debug_name ) = 0;
	virtual void destroy_morph( i_morph* p_morph ) = 0;
	virtual void bind_morph( i_morph* p_morph ) = 0;
	virtual void set_flex_weights( int n_first_weight, int n_count, const morph_weight_t* p_weights ) = 0;
	virtual void unused4( ) {};
	virtual void unused5( ) {};
	virtual void unused6( ) {};
	virtual void unused7( ) {};
	virtual void unused8( ) {};
	virtual void read_pixels_and_stretch( rect_t* p_src_rect, rect_t* p_dst_rect, unsigned char* p_buffer, e_image_format dst_format, int n_dst_stride ) = 0;
	virtual void get_window_size( int& width, int& height ) const = 0;
	virtual void draw_screen_space_rectangle(
		i_material* p_material,
		int dest_x, int dest_y,
		int width, int height,
		float src_texture_x0, float src_texture_y0,
		float src_texture_x1, float src_texture_y1,
		int src_texture_width, int src_texture_height,
		void* p_client_renderable = NULL,
		int n_x_dice = 1,
		int n_y_dice = 1 ) = 0;
	virtual void load_bone_matrix( int bone_index, const matrix_3x4& matrix ) = 0;
	virtual void push_render_target_and_viewport( ) = 0;
	virtual void push_render_target_and_viewport( i_texture* p_texture ) = 0;
	virtual void push_render_target_and_viewport( i_texture* p_texture, int view_x, int view_y, int view_w, int view_h ) = 0;
	virtual void push_render_target_and_viewport( i_texture* p_texture, i_texture* p_depth_texture, int view_x, int view_y, int view_w, int view_h ) = 0;
	virtual void pop_render_target_and_viewport( ) = 0;
	virtual void bind_lightmap_texture( i_texture* p_lightmap_texture ) = 0;
	virtual void copy_render_target_to_texture_ex( i_texture* p_texture, int render_target_id, rect_t* p_src_rect, rect_t* p_dst_rect = NULL ) = 0;
	virtual void copy_texture_to_render_target_ex( int render_target_id, i_texture* p_texture, rect_t* p_src_rect, rect_t* p_dst_rect = NULL ) = 0;
	virtual void perspective_off_center_x( double fov_x, double aspect, double z_near, double z_far, double bottom, double top, double left, double right ) = 0;
	virtual void set_float_rendering_parameter( int parm_number, float value ) = 0;
	virtual void set_int_rendering_parameter( int parm_number, int value ) = 0;
	virtual void set_vector_rendering_parameter( int parm_number, const vector& value ) = 0;
	virtual void set_stencil_enable( bool on_off ) = 0;
	virtual void set_stencil_fail_operation( stencil_operation_t op ) = 0;
	virtual void set_stencil_z_fail_operation( stencil_operation_t op ) = 0;
	virtual void set_stencil_pass_operation( stencil_operation_t op ) = 0;
	virtual void set_stencil_compare_function( stencil_comparison_function_t cmp_fn ) = 0;
	virtual void set_stencil_reference_value( int ref ) = 0;
	virtual void set_stencil_test_mask( uint32_t mask ) = 0;
	virtual void set_stencil_write_mask( uint32_t mask ) = 0;
	virtual void clear_stencil_buffer_rectangle( int xmin, int ymin, int xmax, int ymax, int value ) = 0;
	virtual void set_render_target_ex( int render_target_id, i_texture* p_texture ) = 0;
	virtual void push_custom_clip_plane( const float* p_plane ) = 0;
	virtual void pop_custom_clip_plane( ) = 0;
	virtual void get_max_to_render( i_mesh* p_mesh, bool b_max_until_flush, int* p_max_verts, int* p_max_indices ) = 0;
	virtual int get_max_vertices_to_render( i_material* p_material ) = 0;
	virtual int get_max_indices_to_render( ) = 0;
	virtual void disable_all_local_lights( ) = 0;
	virtual int compare_material_combos( i_material* p_material1, i_material* p_material2, int light_map_id1, int light_map_id2 ) = 0;
	virtual i_mesh* get_flex_mesh( ) = 0;
	virtual void set_flashlight_state_ex( const flashlight_state_t& state, const vmatrix& world_to_texture, i_texture* p_flashlight_depth_texture ) = 0;
	virtual i_texture* get_local_cubemap( ) = 0;
	virtual void clear_buffers_obey_stencil( bool b_clear_color, bool b_clear_depth ) = 0;
	virtual bool enable_clipping( bool b_enable ) = 0;
	virtual void get_fog_distances( float* f_start, float* f_end, float* f_fog_z ) = 0;
	virtual void begin_pix_event( unsigned long color, const char* sz_name ) = 0;
	virtual void end_pix_event( ) = 0;
	virtual void set_pix_marker( unsigned long color, const char* sz_name ) = 0;
	virtual void begin_batch( i_mesh* p_indices ) = 0;
	virtual void bind_batch( i_mesh* p_vertices, i_material* p_auto_bind = NULL ) = 0;
	virtual void draw_batch( int first_index, int num_indices ) = 0;
	virtual void end_batch( ) = 0;
	virtual i_call_queue* get_call_queue( ) = 0;
	virtual void get_world_space_camera_position( vector* p_camera_pos ) = 0;
	virtual void get_world_space_camera_vectors( vector* p_vec_forward, vector* p_vec_right, vector* p_vec_up ) = 0;
	virtual void reset_tone_mapping_scale( float mono_scale ) = 0;
	virtual void set_goal_tone_mapping_scale( float mono_scale ) = 0;
	virtual void turn_on_tone_mapping( ) = 0;
	virtual void set_tone_mapping_scale_linear( const vector& scale ) = 0;
	virtual vector get_tone_mapping_scale_linear( ) = 0;
	virtual void set_shadow_depth_bias_factors( float f_slope_scale_depth_bias, float f_depth_bias ) = 0;
	virtual void perform_full_screen_stencil_operation( ) = 0;
	virtual void set_lighting_origin( vector v_lighting_origin ) = 0;
	virtual void set_scissor_rect( int n_left, int n_top, int n_right, int n_bottom, bool b_enable_scissor ) = 0;
	virtual void begin_morph_accumulation( ) = 0;
	virtual void end_morph_accumulation( ) = 0;
	virtual void accumulate_morph( i_morph* p_morph, int n_morph_count, const morph_weight_t* p_weights ) = 0;
	virtual void push_deformation( const deformation_base_t* deformation ) = 0;
	virtual void pop_deformation( ) = 0;
	virtual int get_num_active_deformations( ) const = 0;
	virtual bool get_morph_accumulator_tex_coord( vector_2d* p_tex_coord, i_morph* p_morph, int n_vertex ) = 0;
	virtual i_mesh* get_dynamic_mesh_ex( vertex_format_t vertex_format, bool b_buffered = true, i_mesh* p_vertex_override = 0, i_mesh* p_index_override = 0, i_material* p_auto_bind = 0 ) = 0;
	virtual void fog_max_density( float fl_max_density ) = 0;
	virtual i_material* get_current_material( ) = 0;
	virtual int get_current_num_bones( ) const = 0;
	virtual void* get_current_proxy( ) = 0;
	virtual void enable_color_correction( bool b_enable ) = 0;
	virtual color_correction_handle_t add_lookup( const char* p_name ) = 0;
	virtual bool remove_lookup( color_correction_handle_t handle ) = 0;
	virtual void lock_lookup( color_correction_handle_t handle ) = 0;
	virtual void load_lookup( color_correction_handle_t handle, const char* p_lookup_name ) = 0;
	virtual void unlock_lookup( color_correction_handle_t handle ) = 0;
	virtual void set_lookup_weight( color_correction_handle_t handle, float fl_weight ) = 0;
	virtual void reset_lookup_weights( ) = 0;
	virtual void set_resetable( color_correction_handle_t handle, bool b_resetable ) = 0;
	virtual void set_full_screen_depth_texture_validity_flag( bool b_is_valid ) = 0;
	virtual void set_non_interactive_pacifier_texture( i_texture* p_texture, float fl_normalized_x, float fl_normalized_y, float fl_normalized_size ) = 0;
	virtual void set_non_interactive_temp_fullscreen_buffer( i_texture* p_texture, material_non_interactive_mode_t mode ) = 0;
	virtual void enable_non_interactive_mode( material_non_interactive_mode_t mode ) = 0;
	virtual void refresh_front_buffer_non_interactive( ) = 0;
	virtual void* lock_render_data( int n_size_in_bytes ) = 0;
	virtual void unlock_render_data( void* p_data ) = 0;
	virtual void add_ref_render_data( ) = 0;
	virtual void release_render_data( ) = 0;
	virtual bool is_render_data( const void* p_data ) const = 0;
	virtual void printf_va( char* fmt, va_list vargs ) = 0;
	virtual void printf( const char* fmt, ... ) = 0;
	virtual float knob( char* knob_name, float* set_value = NULL ) = 0;
	virtual void override_alpha_write_enable( bool b_enable, bool b_alpha_write_enable ) = 0;
	virtual void override_color_write_enable( bool b_override_enable, bool b_color_write_enable ) = 0;
	virtual void clear_buffers_obey_stencil_ex( bool b_clear_color, bool b_clear_alpha, bool b_clear_depth ) = 0;
	virtual void async_create_texture_from_render_target( i_texture* p_src_rt, const char* p_dst_name, e_image_format dst_fmt, bool b_gen_mips, int n_additional_creation_flags, i_async_texture_operation_receiver* p_recipient, void* p_extra_args ) = 0;
};

enum types_t
{
	TYPE_NONE = 0,
	TYPE_STRING,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_PTR,
	TYPE_WSTRING,
	TYPE_COLOR,
	TYPE_UINT64,
	TYPE_NUMTYPES,
};

class key_values {
public:
	int m_key_name;
	char* m_char;
	wchar_t* m_wchar;

	union {
		int m_int;
		float m_float;
		void* m_void;
		unsigned char m_color[ 4 ];
	};

	char m_data_type;
	char m_has_escape_sequences;
	char m_evaluate_conditionals;
	char unused[ 1 ];

	key_values* m_peer;
	key_values* m_sub;
	key_values* m_chain;

	bool load_from_buffer( char const* resource_name, const char* buffer, void* file_system = 0, const char* path_id = 0 );
	void initialize( char* name );
	key_values( const char* name );
	key_values* find_key( const char* key_name, bool b_create = false );

	int get_int( const char* key_name, int default_value = 0 );
	unsigned long long get_uint64( const char* key_name, unsigned long long default_value = 0 );
	float get_float( const char* key_name, float default_value = 0.0f );
	const char* get_string( const char* key_name, const char* default_value = "" );
	const wchar_t* get_wstring( const char* key_name, const wchar_t* default_value = L"" );
	void* get_ptr( const char* key_name, void* default_value = ( void* )0 );
	bool get_bool( const char* key_name, bool default_value = false );
	color get_color( const char* key_name );
	const char* get_name( );
	bool is_empty( const char* key_name );

	void set_wstring( const char* key_name, const wchar_t* value );
	void set_string( const char* key_name, const char* value );
	void set_int( const char* key_name, int value );
	void set_uint64( const char* key_name, unsigned long long value );
	void set_float( const char* key_name, float value );
	void set_ptr( const char* key_name, void* value );
	void set_color( const char* key_name, color value );
	void set_bool( const char* key_name, bool value ) { set_int( key_name, value ? 1 : 0 ); }
};

#define STEAMWORKS_STRUCT_RETURN_0( return_type, function_name )	\
		virtual void function_name( return_type& ret ) = 0;			\
		inline return_type function_name( )	{						\
			return_type ret;										\
			this->function_name( ret );								\
			return ret;												\
		}

enum e_universe;

class c_steam_id {
public:
	uint64_t to_uint64( ) const {
		return m_steam_id.m_all_64_bits;
	}

	union steam_id_t {
		struct steam_id_component_t {
			uint32_t m_account_id : 32;
			unsigned int m_account_instance : 20;
			unsigned int m_account_type : 4;
			e_universe m_universe : 8;
		} m_comp;

		uint64_t m_all_64_bits;
	} m_steam_id;
};

class i_steam_user {
public:
	virtual int32_t get_steam_user( ) = 0;
	virtual bool logged_on( ) = 0;
	STEAMWORKS_STRUCT_RETURN_0( c_steam_id, get_steam_id )
};

enum e_account_type;

class i_steam_client {
public:
	virtual int32_t create_steam_pipe( ) = 0;
	virtual bool release_steam_pipe( int32_t steam_pipe ) = 0;
	virtual int32_t connect_to_global_user( int32_t steam_pipe ) = 0;
	virtual int32_t create_local_user( int32_t* steam_pipe, e_account_type account_type ) = 0;
	virtual void release_user( int32_t steam_pipe, int32_t user ) = 0;
	virtual i_steam_user* get_steam_user( int32_t steam_user, int32_t steam_pipe, const char* version ) = 0;
};

#define GESTURE_SLOT_INVALID	-1

#define ANIM_LAYER_ACTIVE		0x0001
#define ANIM_LAYER_AUTOKILL		0x0002
#define ANIM_LAYER_KILLME		0x0004
#define ANIM_LAYER_DONTRESTORE	0x0008
#define ANIM_LAYER_CHECKACCESS	0x0010
#define ANIM_LAYER_DYING		0x0020
enum activity;
class c_studio_hdr;

enum player_anim_event_t {
	PLAYERANIMEVENT_ATTACK_PRIMARY,
	PLAYERANIMEVENT_ATTACK_SECONDARY,
	PLAYERANIMEVENT_ATTACK_GRENADE,
	PLAYERANIMEVENT_RELOAD,
	PLAYERANIMEVENT_RELOAD_LOOP,
	PLAYERANIMEVENT_RELOAD_END,
	PLAYERANIMEVENT_JUMP,
	PLAYERANIMEVENT_SWIM,
	PLAYERANIMEVENT_DIE,
	PLAYERANIMEVENT_FLINCH_CHEST,
	PLAYERANIMEVENT_FLINCH_HEAD,
	PLAYERANIMEVENT_FLINCH_LEFTARM,
	PLAYERANIMEVENT_FLINCH_RIGHTARM,
	PLAYERANIMEVENT_FLINCH_LEFTLEG,
	PLAYERANIMEVENT_FLINCH_RIGHTLEG,
	PLAYERANIMEVENT_DOUBLEJUMP,

	// Cancel.
	PLAYERANIMEVENT_CANCEL,
	PLAYERANIMEVENT_SPAWN,

	// Snap to current yaw exactly
	PLAYERANIMEVENT_SNAP_YAW,

	PLAYERANIMEVENT_CUSTOM,				// Used to play specific activities
	PLAYERANIMEVENT_CUSTOM_GESTURE,
	PLAYERANIMEVENT_CUSTOM_SEQUENCE,	// Used to play specific sequences
	PLAYERANIMEVENT_CUSTOM_GESTURE_SEQUENCE,

	// TF Specific. Here until there's a derived game solution to this.
	PLAYERANIMEVENT_ATTACK_PRE,
	PLAYERANIMEVENT_ATTACK_POST,
	PLAYERANIMEVENT_GRENADE1_DRAW,
	PLAYERANIMEVENT_GRENADE2_DRAW,
	PLAYERANIMEVENT_GRENADE1_THROW,
	PLAYERANIMEVENT_GRENADE2_THROW,
	PLAYERANIMEVENT_VOICE_COMMAND_GESTURE,
	PLAYERANIMEVENT_DOUBLEJUMP_CROUCH,
	PLAYERANIMEVENT_STUN_BEGIN,
	PLAYERANIMEVENT_STUN_MIDDLE,
	PLAYERANIMEVENT_STUN_END,
	PLAYERANIMEVENT_PASSTIME_THROW_BEGIN,
	PLAYERANIMEVENT_PASSTIME_THROW_MIDDLE,
	PLAYERANIMEVENT_PASSTIME_THROW_END,
	PLAYERANIMEVENT_PASSTIME_THROW_CANCEL,

	PLAYERANIMEVENT_ATTACK_PRIMARY_SUPER,

	PLAYERANIMEVENT_COUNT
};

class c_animation_layer {
public:
	int		m_flags;
	bool	m_sequence_finished;
	bool	m_looping;
	int		m_sequence;
	float	m_cycle;
	float	m_prev_cycle;
	float	m_weight;
	float	m_playback_rate;
	float	m_blend_in;
	float	m_blend_out;
	float	m_kill_rate;
	float	m_kill_delay;
	float	m_layer_animtime;
	float	m_layer_fade_outtime;

	activity m_n_activity;

	int	m_n_priority;
	int m_n_order;

	bool is_active( ) { return ( ( m_flags & ANIM_LAYER_ACTIVE ) != 0 ); }
	bool is_autokill( ) { return ( ( m_flags & ANIM_LAYER_AUTOKILL ) != 0 ); }
	bool is_kill_me( ) { return ( ( m_flags & ANIM_LAYER_KILLME ) != 0 ); }
	bool is_autoramp( ) { return ( m_blend_in != 0.0 || m_blend_out != 0.0 ); }
	void kill_me( ) { m_flags |= ANIM_LAYER_KILLME; }
	void dying( ) { m_flags |= ANIM_LAYER_DYING; }
	bool is_dying( ) { return ( ( m_flags & ANIM_LAYER_DYING ) != 0 ); }
	void dead( ) { m_flags &= ~ANIM_LAYER_DYING; }

	float m_fl_last_event_check;
	float m_fl_last_access;

	// Network state changes get forwarded here.
	void* m_p_owner_entity;
};

struct gesture_slot_t {
	int				 m_iGestureSlot;
	activity		 m_iActivity;
	bool			 m_bAutoKill;
	bool			 m_bActive;
	c_animation_layer* m_pAnimLayer;
};

struct multi_player_pose_data_t {
	int			m_iMoveX;
	int			m_iMoveY;
	int			m_iAimYaw;
	int			m_iAimPitch;
	int			m_iBodyHeight;
	int			m_iMoveYaw;
	int			m_iMoveScale;

	float		m_flEstimateYaw;
	float		m_flLastAimTurnTime;

	void Init( ) {
		m_iMoveX = 0;
		m_iMoveY = 0;
		m_iAimYaw = 0;
		m_iAimPitch = 0;
		m_iBodyHeight = 0;
		m_iMoveYaw = 0;
		m_iMoveScale = 0;
		m_flEstimateYaw = 0.0f;
		m_flLastAimTurnTime = 0.0f;
	}
};

struct debug_player_anim_data_t {
	float	m_flVelocity;
	float	m_flAimPitch;
	float	m_flAimYaw;
	float	m_flBodyHeight;
	vector_2d m_vecMoveYaw;

	void Init( ) {
		m_flVelocity = 0.0f;
		m_flAimPitch = 0.0f;
		m_flAimYaw = 0.0f;
		m_flBodyHeight = 0.0f;
		m_vecMoveYaw.set( );
	}
};

struct multi_player_movement_data_t {
	// Set speeds to -1 if they are not used.
	float m_walk_speed;
	float m_run_speed;
	float m_sprint_speed;
	float m_body_yaw_rate;
};

typedef enum {
	LEGANIM_9WAY,	// Legs use a 9-way blend, with "move_x" and "move_y" pose parameters.
	LEGANIM_8WAY,	// Legs use an 8-way blend with "move_yaw" pose param.
	LEGANIM_GOLDSRC	// Legs always point in the direction he's running and the torso rotates.
} leg_anim_type_t;

#define ACTIVITY_NOT_AVAILABLE		-1

class c_multi_player_anim_state {
public:
	virtual				~c_multi_player_anim_state( ) = 0;
	virtual void		clear_animation_state( ) = 0;
	virtual void		do_animation_event( player_anim_event_t event, int n_data = 0 ) = 0;
	virtual activity	calc_main_activity( ) = 0;
	virtual void		update( float eye_yaw, float eye_pitch ) = 0;
	virtual void		release( ) = 0;
	virtual activity	translate_activity( activity act_desired ) = 0;
	virtual void		set_run_speed( float fl_speed ) { m_movement_data.m_run_speed = fl_speed; }
	virtual void		set_walk_speed( float fl_speed ) { m_movement_data.m_walk_speed = fl_speed; }
	virtual void		set_sprint_speed( float fl_speed ) { m_movement_data.m_sprint_speed = fl_speed; }
	virtual void		show_debug_info( ) = 0;
	virtual void		debug_show_anim_state( int i_start_line ) = 0;

	activity get_current_main_activity( ) { return m_current_main_sequence_activity; }

	bool m_force_aim_yaw;

	virtual void init( c_base_entity* p_player, multi_player_movement_data_t& movement_data ) = 0;
	c_base_player* get_base_player( ) { return m_player; }

	virtual int select_weighted_sequence( activity activity ) = 0;
	virtual void restart_main_sequence( ) = 0;
	virtual void get_outer_abs_velocity( vector& vel ) = 0;
	virtual bool handle_jumping( activity& ideal_activity ) = 0;
	virtual bool handle_ducking( activity& ideal_activity ) = 0;
	virtual bool handle_moving( activity& ideal_activity ) = 0;
	virtual bool handle_swimming( activity& ideal_activity ) = 0;
	virtual bool handle_dying( activity& ideal_activity ) = 0;

	void* m_gesture_slots;

	virtual void	restart_gesture( int i_gesture_slot, activity i_gesture_activity, bool b_auto_kill = true ) = 0;
	virtual float	get_gesture_playback_rate( ) = 0;
	virtual void	play_flinch_gesture( activity i_activity ) = 0;
	virtual float	calc_movement_speed( bool* b_is_moving ) = 0;
	virtual float	calc_movement_playback_rate( bool* b_is_moving ) = 0;
	virtual void	compute_pose_param_move_yaw( c_studio_hdr* p_studio_hdr ) = 0;
	virtual void	compute_pose_param_aim_pitch( c_studio_hdr* p_studio_hdr ) = 0;
	virtual void	compute_pose_param_aim_yaw( c_studio_hdr* p_studio_hdr ) = 0;
	virtual void	estimate_yaw( ) = 0;
	virtual float	get_current_max_ground_speed( ) = 0;
	virtual void	compute_sequences( c_studio_hdr* p_studio_hdr ) = 0;
	virtual bool	should_update_anim_state( ) = 0;

	c_base_player* m_player;
	vector m_ang_render;

	bool					m_pose_parameter_init;
	multi_player_pose_data_t	m_pose_parameter_data;
	debug_player_anim_data_t	m_debug_anim_data;

	bool m_current_feet_yaw_initialized;
	float m_last_animation_state_clear_time;

	float m_eye_yaw;
	float m_eye_pitch;
	float m_goal_feet_yaw;
	float m_current_feet_yaw;
	float m_last_aim_turn_time;

	multi_player_movement_data_t m_movement_data;

	bool	m_jumping;
	float	m_jump_start_time;
	bool	m_first_jump_frame;
	bool	m_in_swim;
	bool	m_first_swim_frame;
	bool	m_dying;
	bool	m_first_dying_frame;

	activity m_current_main_sequence_activity;
	int m_specific_main_sequence;

	c_base_combat_weapon* m_active_weapon;

	float m_last_ground_speed_update_time;
	float m_iv_max_ground_speed;
	float m_max_ground_speed;

	int m_movement_sequence;
	leg_anim_type_t m_leg_anim_type;
};

class c_tf_player;
class c_tf_player_anim_state : public c_multi_player_anim_state {
public:
	c_tf_player* get_tf_player( ) { return m_tf_player; }

	virtual void		clear_animation_state( ) = 0;
	virtual activity	translate_activity( activity act_desired ) = 0;
	virtual void		update( float eye_yaw, float eye_pitch ) = 0;
	virtual void		check_stun_animation( ) = 0;
	virtual activity	calc_main_activity( ) = 0;
	virtual void		compute_pose_param_aim_yaw( c_studio_hdr* p_studio_hdr ) = 0;
	virtual float		get_current_max_ground_speed( ) = 0;
	virtual float		get_gesture_playback_rate( ) = 0;
	virtual bool		should_update_anim_state( ) = 0;
	virtual void		get_outer_abs_velocity( vector& vel ) = 0;
	virtual void		restart_gesture( int i_gesture_slot, activity i_gesture_activity, bool b_auto_kill = true ) = 0;
	void				set_render_angles( const vector& angles ) { m_ang_render = angles; }

	c_tf_player* m_tf_player;
	bool		 m_in_air_walk;
	float		 m_hold_deployed_pose_until_time;
	float		 m_taunt_move_x;
	float		 m_taunt_move_y;
	float		 m_vehicle_lean_vel;
	float		 m_vehicle_lean_pos;
	vector		 m_smoothed_up;
};

enum {
	EF_BONEMERGE = 0x001,
	EF_BRIGHTLIGHT = 0x002,
	EF_DIMLIGHT = 0x004,
	EF_NOINTERP = 0x008,
	EF_NOSHADOW = 0x010,
	EF_NODRAW = 0x020,
	EF_NORECEIVESHADOW = 0x040,
	EF_BONEMERGE_FASTCULL = 0x080,
	EF_ITEM_BLINK = 0x100,
	EF_PARENT_ANIMATES = 0x200,
	EF_MAX_BITS = 10
};

class i_studio_render;
class c_base_entity;

struct fire_bullets_info_t {
	fire_bullets_info_t( ) {
		m_shots = 1;
		m_spread.set( );
		m_distance = 8192;
		m_tracer_freq = 4;
		m_damage = 0;
		m_player_damage = 0;
		m_attacker = NULL;
		m_flags = 0;
		m_additional_ignore_ent = NULL;
		m_damage_force_scale = 1.0f;
		m_primary_attack = true;
		m_use_server_random_seed = false;
	}

	fire_bullets_info_t( int shots, const vector& src, const vector& dir, const vector& spread, float distance, int ammo_type, bool primary_attack = true ) {
		m_shots = shots;
		m_src = src;
		m_dir_shooting = dir;
		m_spread = spread;
		m_distance = distance;
		m_iAmmoType = ammo_type;
		m_tracer_freq = 4;
		m_damage = 0;
		m_player_damage = 0;
		m_attacker = NULL;
		m_flags = 0;
		m_additional_ignore_ent = NULL;
		m_damage_force_scale = 1.0f;
		m_primary_attack = primary_attack;
		m_use_server_random_seed = false;
	}

	int m_shots;
	vector m_src;
	vector m_dir_shooting;
	vector m_spread;
	float m_distance;
	int m_iAmmoType;
	int m_tracer_freq;
	float m_damage;
	int m_player_damage;
	int m_flags;
	float m_damage_force_scale;
	c_base_entity* m_attacker;
	c_base_entity* m_additional_ignore_ent;
	bool m_primary_attack;
	bool m_use_server_random_seed;
};