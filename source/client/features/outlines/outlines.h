#pragma once
#include "../../include/tf2.h"
#include <unordered_map>

class c_outlines {
	bool m_rendering = false;

	struct glow_entity_t
	{
		c_base_entity* m_entity;
		color m_color;
		float alpha;
	};

	std::vector<glow_entity_t> m_glow_entities;
	std::unordered_map<c_base_entity*, int> m_rendered_entities;

	void draw_entity( c_base_entity* entity, bool drawing_models );
	void draw_glow_on_entities( );

public:
	bool m_drawing_glow = false;

	i_material* m_material_glow_color;
	i_texture* m_rt_full_frame;
	i_texture* m_render_buffer1;
	i_texture* m_render_buffer2;

	key_values* m_material_blur_x_wireframe_vmt;
	i_material* m_material_blur_x_wireframe;
	key_values* m_material_blur_x_vmt;
	i_material* m_material_blur_x;
	key_values* m_material_blur_y_wireframe_vmt;
	i_material* m_material_blur_y_wireframe;
	key_values* m_material_blur_y_vmt;
	i_material* m_material_blur_y;
	key_values* m_material_halo_vmt;
	i_material* m_material_halo;

	void init_materials( );
	void remove_materials( );
	bool is_rendering( );
	bool is_used_material( i_material* material );
	bool is_entity_rendered( c_base_entity* entity );
	void render( );
};

inline c_outlines* outlines = new c_outlines;