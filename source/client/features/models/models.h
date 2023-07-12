#pragma once
#include "../../include/tf2.h"
#include <unordered_map>

class c_models {
public:
	bool m_rendering = false;
	std::unordered_map<c_base_entity*, int> m_rendered_entities;
	std::unordered_map<c_base_entity*, int> m_rendered_weapons;

	void draw_entity_and_attachments( c_base_entity* entity, bool overlay, color color, float alpha );
	void draw_occluded_and_unoccluded_model( c_base_entity* entity, i_material* material, color color, float alpha, bool ignorez, bool overlay );
	void draw_occluded_and_unoccluded_models( c_base_entity* entity, i_material* material_occluded, color color_occluded, float alpha_occluded, bool overlay_occluded, i_material* material_unoccluded, color color_unoccluded, float alpha_unoccluded, bool overlay_unoccluded );
	void render_players( );
	void render_buildings( );
	void render_world( );

	bool m_has_stencil = false;
	bool m_has_second_stencil = false;
	key_values* m_flat_material_vmt;
	key_values* m_shaded_material_vmt;
	key_values* m_fresnel_material_vmt;
	key_values* m_overlay_material_vmt;

	i_material* m_flat_material;
	i_material* m_shaded_material;
	i_material* m_fresnel_material;
	i_material* m_overlay_material;
	void init_materials( );
	void remove_materials( );
	bool is_rendering( );
	bool is_used_material( i_material* material );
	bool is_entity_rendered( c_base_entity* entity );
	void render( );
};

inline c_models* models = new c_models;