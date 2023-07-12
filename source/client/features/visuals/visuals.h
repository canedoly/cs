#pragma once
#include "../../include/ctx.h"
#include "../../hooks/hooks.h"

class c_visuals {
private:
	int m_vote_yes = 0, m_vote_no = 0;
public:
	void draw_indicators( );
	void trace_projectile_path( );
	void visualize_stickies_path( );
	void draw_hitboxes( c_base_player* player, const model_t* model, matrix_3x4* bones, const color& face_col, const color& edge_col, float time );
	void draw_server_hitboxes( );
	void draw_camera_outline( );

	bool m_vote_in_progress = false;
	void vote_revealer_register_event(c_game_event* event);
	void vote_revealer_register_message(int message, bf_read& data);

	rect_t camera_position = { 30, 30, 300, 200 };
	i_texture* camera_texture;
	i_material* camera_material;
	key_values* camera_material_vmt;
};

inline c_visuals* visuals = new c_visuals;