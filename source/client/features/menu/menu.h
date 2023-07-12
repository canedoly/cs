#pragma once
#include "input/input.h"
#include "../../include/render.h"
#include "texture.h"

class c_menu {
	enum e_menu_tabs {
		TAB_AIM,
		TAB_VISUALS,
		TAB_HVH,
		TAB_MISC,
		TAB_EXPLOITS
	};

	enum e_aim_subtabs {
		SUBTAB_AIMBOT,
		SUBTAB_AUTOMATIONS,
	};

	enum e_visuals_subtabs {
		SUBTAB_ESP,
		SUBTAB_MODELS,
		SUBTAB_OUTLINES,
		SUBTAB_MISC_,
	};
	
	enum e_hvh_subtabs {
		SUBTAB_ANTIAIM,
		SUBTAB_FAKELAG
	};

	rect_t m_window = { 200, 200, 457, 483 };
	float m_fade_elapsed;
	float m_fade_alpha;
	float m_fade_time = 0.125f;

	int m_backup_left, m_backup_right, m_backup_top, m_backup_bottom;
	bool m_backup_clipping_disabled;

	e_menu_tabs m_current_tab = TAB_AIM;
	e_aim_subtabs m_aim_subtab = SUBTAB_AIMBOT;
	e_visuals_subtabs m_visuals_subtab = SUBTAB_ESP;
	e_hvh_subtabs m_hvh_subtab = SUBTAB_ANTIAIM;

	rect_t m_last_tab;
	rect_t m_last_subtab;
	rect_t m_last_group;

	bool m_typing = false;
	bool m_combobox_open = false;
	bool m_multi_combobox_open = false;
	bool m_rendering_group = false;
	int m_max_tabs = 5;
	int last_group_y = 0;
	bool menu_tab( std::string label, bool active );
	bool menu_subtab( std::string label, bool active );
	void menu_group_start( bool right, bool up, bool subtab );
	void menu_group( std::string label );
	bool button( std::string label, std::function<void( )> callback );
	bool check_box( std::string label, bool& var );
	bool slider_int( std::string label, int& var, int min, int max, int step = 1, const char* format = "%i" );
	bool slider_float( std::string label, float& var, float min, float max, float step = 1.f, const char* format = "%.2f" );
	bool text_box( std::string label, std::string& var );
	bool key_bind( std::string label, unsigned short& var );

	struct {
		int* m_var = nullptr;
		std::vector< const char* > m_items = { };
		rect_t m_area = { };
	} m_combo_info;
	bool combo_box( std::string label, int& var, std::vector< const char* > items );
	bool update_combo( );

	struct {
		std::string* m_label = nullptr;
		std::vector< std::pair<const char*, bool*> > m_items = { };
		rect_t m_area = { };
	} m_multi_combo_info;
	bool multi_combo_box( std::string label, std::vector< std::pair<const char*, bool*> > items );
	bool update_multi_combo( );

	void no_restrictions( ) {
		static con_var* sv_cheats = ctx->m_cvar->find_var( "sv_cheats" );
		if ( sv_cheats ) {
			sv_cheats->m_name = "sv_cheats_jw";
			sv_cheats->set_value( 1 );
		}
	}

	void kill_interp() {
		static con_var* sv_client_min_interp_ratio = ctx->m_cvar->find_var("sv_client_min_interp_ratio");
		static con_var* cl_interp_ratio = ctx->m_cvar->find_var("sv_client_min_interp_ratio");

		if (sv_client_min_interp_ratio) {
			sv_client_min_interp_ratio->m_name = "sv_client_min_interp_ratio_jw";
			sv_client_min_interp_ratio->set_value(-1);
		}

		if (cl_interp_ratio) {
			cl_interp_ratio->m_name = "cl_interp_ratio_jw";
			cl_interp_ratio->set_value(0);
		}
	}

public:
	void save_config( );
	void dump_server_players();
	void load_config( );

private:
	bool test = false;
	bool test1 = false;
	bool test2 = false;
	bool test3 = false;
	int test_int = 23;
	int test_int2 = 4;
	int test_int3 = 1;
	float test_float = 0.65f;
	float test_float2 = 0.24f;
	uint16_t test_key = 0x0;
	uint16_t test_key2 = 0x0;
	std::string test_string = "String";
	std::string test_string2 = "String";
public:
	bool m_open = false;

	void* backup_ecx = nullptr;
	void* backup_edx = nullptr;

	void press_sound();
	void render_window( std::string label, rect_t size, color background, color edge );
	void enable_clipping( rect_t size );
	void disable_clipping( );

	void run( );
	void reset( );
}; inline c_menu* menu = new c_menu;