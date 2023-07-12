#include "models.h"

bool c_models::is_rendering( ) {
	return m_rendering;
}

bool c_models::is_used_material( i_material* material ) {
	return ( material == m_flat_material 
		|| material == m_shaded_material
		|| material == m_fresnel_material
		|| material == m_overlay_material );
}

bool c_models::is_entity_rendered( c_base_entity* entity ) {
	if ( !entity || entity->is_dormant( ) )
		return false;

	if ( entity->is_player( ) ) {
		if ( config->m_models.m_player_two_models ) {
			return ( m_rendered_entities.find( entity ) != m_rendered_entities.end( ) && m_rendered_entities[ entity ] == 2 );
		}
		else {
			return m_rendered_entities.find( entity ) != m_rendered_entities.end( );
		}
	}

	else if ( entity->is_building( ) ) {
		if ( config->m_models.m_building_two_models ) {
			return ( m_rendered_entities.find( entity ) != m_rendered_entities.end( ) && m_rendered_entities[ entity ] == 2 );
		}
		else {
			return m_rendered_entities.find( entity ) != m_rendered_entities.end( );
		}
	}

	else if ( entity->is_projectile( ) ) {
		if ( config->m_models.m_projectile_two_models ) {
			return ( m_rendered_entities.find( entity ) != m_rendered_entities.end( ) && m_rendered_entities[ entity ] == 2 );
		}
		else {
			return m_rendered_entities.find( entity ) != m_rendered_entities.end( );
		}
	}

	else if ( entity->is_health( ) ) {
		if ( config->m_models.m_world_two_models ) {
			return ( m_rendered_entities.find( entity ) != m_rendered_entities.end( ) && m_rendered_entities[ entity ] == 2 );
		}
		else {
			return m_rendered_entities.find( entity ) != m_rendered_entities.end( );
		}
	}

	else if ( entity->is_ammo( ) ) {
		if ( config->m_models.m_world_two_models ) {
			return ( m_rendered_entities.find( entity ) != m_rendered_entities.end( ) && m_rendered_entities[ entity ] == 2 );
		}
		else {
			return m_rendered_entities.find( entity ) != m_rendered_entities.end( );
		}
	}

	else {
		if ( config->m_models.m_player_two_models ) {
			return ( m_rendered_entities.find( entity ) != m_rendered_entities.end( ) && m_rendered_entities[ entity ] == 2 );
		}
		else {
			return m_rendered_entities.find( entity ) != m_rendered_entities.end( );
		}
	}
}

void c_models::init_materials( ) {

	if ( !m_flat_material ) {
		if ( !m_flat_material_vmt ) {
			m_flat_material_vmt = new key_values( "UnlitGeneric" );
			m_flat_material_vmt->set_string( "$basetexture", "vgui/white_additive" );
		}

		m_flat_material = ctx->m_material_system->create_material( "m_flat_material", m_flat_material_vmt );
		m_flat_material->increment_reference_count( );
	}

	if ( !m_shaded_material ) {
		if ( !m_shaded_material_vmt ) {
			m_shaded_material_vmt = new key_values( "VertexLitGeneric" );
			m_shaded_material_vmt->set_string( "$basetexture", "vgui/white_additive" );
			m_shaded_material_vmt->set_string( "$bumpmap", "vgui/white_additive" );
			m_shaded_material_vmt->set_string( "$halflambert", "1" );
			m_shaded_material_vmt->set_string( "$selfillum", "1" );
			m_shaded_material_vmt->set_string( "$selfillumfresnel", "1" );
			m_shaded_material_vmt->set_string( "$selfillumfresnelminmaxexp", "[-0.25 1 1]" );
		}

		m_shaded_material = ctx->m_material_system->create_material( "m_shaded_material", m_shaded_material_vmt );
		m_shaded_material->increment_reference_count( );
	}

	if ( !m_fresnel_material ) {
		if ( !m_fresnel_material_vmt ) {
			m_fresnel_material_vmt = new key_values( "VertexLitGeneric" );
			m_fresnel_material_vmt->set_string( "$basetexture", "vgui/white_additive" );
			m_fresnel_material_vmt->set_string( "$bumpmap", "models/player/shared/shared_normal" );
			m_fresnel_material_vmt->set_string( "$color2", "[35 35 35]" );
			m_fresnel_material_vmt->set_string( "$selfillum", "1" );
			m_fresnel_material_vmt->set_string( "$selfillumfresnel", "1" );
			m_fresnel_material_vmt->set_string( "$selfillumfresnelminmaxexp", "[-0.22 0.22 0.18]" );
			m_fresnel_material_vmt->set_string( "$selfillumtint", "[0.04 0.03 0.06]" );
		}

		m_fresnel_material = ctx->m_material_system->create_material( "m_fresnel_material", m_fresnel_material_vmt );
		m_fresnel_material->increment_reference_count( );
	}

	if ( !m_overlay_material ) {
		if ( !m_overlay_material_vmt ) {
			m_overlay_material_vmt = new key_values( "VertexLitGeneric" );
			m_overlay_material_vmt->set_string( "$basetexture", "models/player/shared/ice_player" );
			m_overlay_material_vmt->set_string( "$bumpmap", "models/player/shared/shared_normal" );
			m_overlay_material_vmt->set_string( "$translucent", "1" );
			m_overlay_material_vmt->set_string( "$additive", "1" );
			m_overlay_material_vmt->set_string( "$phong", "1" );
			m_overlay_material_vmt->set_string( "$phongfresnelranges", "[0 0.5 1]" );
			m_overlay_material_vmt->set_string( "$phongtint", "[0 0 0]" );
			m_overlay_material_vmt->set_string( "$envmap", "skybox/sky_dustbowl_01" );
			m_overlay_material_vmt->set_string( "$envmapfresnel", "1" );
			m_overlay_material_vmt->set_string( "$envmaptint", "[1 1 1]" );
			m_overlay_material_vmt->set_string( "$selfillum", "1" );
			m_overlay_material_vmt->set_string( "$selfillumtint", "[0 0 0]" );
			m_overlay_material_vmt->set_string( "$wireframe", "0" );
			m_overlay_material_vmt->set_string( "$cloakPassEnabled", "1" );
		}

		m_overlay_material = ctx->m_material_system->create_material( "m_overlay_material", m_overlay_material_vmt );
		m_overlay_material->increment_reference_count( );
	}
}

void c_models::remove_materials( ) {
	if ( m_flat_material ) {
		m_flat_material->decrement_reference_count( );
		m_flat_material->delete_if_unreferenced( );
		m_flat_material = nullptr;
		m_flat_material_vmt = nullptr;
	}

	if ( m_shaded_material ) {
		m_shaded_material->decrement_reference_count( );
		m_shaded_material->delete_if_unreferenced( );
		m_shaded_material = nullptr;
		m_shaded_material_vmt = nullptr;
	}

	if ( m_fresnel_material ) {
		m_fresnel_material->decrement_reference_count( );
		m_fresnel_material->delete_if_unreferenced( );
		m_fresnel_material = nullptr;
		m_fresnel_material_vmt = nullptr;
	}

	if ( m_overlay_material ) {
		m_overlay_material->decrement_reference_count( );
		m_overlay_material->delete_if_unreferenced( );
		m_overlay_material = nullptr;
		m_overlay_material_vmt = nullptr;
	}
}

void c_models::draw_entity_and_attachments( c_base_entity* entity, bool overlay, color color, float alpha ) {
	if ( !entity || entity->is_dormant( ) )
		return;

	m_rendering = true;
	entity->draw_model( STUDIO_RENDER );

	if ( overlay ) {
		if ( i_material_var* $phongtint = m_overlay_material->find_var( "$phongtint", nullptr, false ) )
			$phongtint->set_vec_value( ( float )color.m_r / 255.f, ( float )color.m_g / 255.f, ( float )color.m_b / 255.f );

		if ( i_material_var* $envmaptint = m_overlay_material->find_var( "$envmaptint", nullptr, false ) )
			$envmaptint->set_vec_value( ( float )color.m_r / 255.f, ( float )color.m_g / 255.f, ( float )color.m_b / 255.f );

		if ( i_material_var* $phongfresnelranges = m_overlay_material->find_var( "$phongfresnelranges", nullptr, false ) )
			$phongfresnelranges->set_vec_value( 0, 1.f, 2.f );

		m_overlay_material->set_material_var_flag( MATERIAL_VAR_WIREFRAME, false );

		ctx->m_render_view->set_blend( alpha );
		ctx->m_model_renderer->forced_material_override( m_overlay_material );
		entity->draw_model( STUDIO_RENDER );
	}

	if ( entity->is_player( ) && entity->as<c_base_player>( )->is_alive( ) ) {
		const auto& weapon = entity->as<c_base_player>( )->get_active_weapon( );

		if ( weapon && !weapon->is_dormant( ) ) {
			if ( weapon->should_draw( ) ) {
				weapon->draw_model( STUDIO_RENDER );
				m_rendered_weapons[ weapon ]++;
			}
		}
	}
	
	m_rendered_entities[ entity ]++;
	m_rendering = false;
}

void c_models::draw_occluded_and_unoccluded_model( c_base_entity* entity, i_material* material, color color, float alpha, bool ignorez, bool overlay ) {
	if ( !entity || !entity->should_draw( ) )
	{
		return;
	}

	auto context = ctx->m_material_system->get_render_context( );
	if ( !context )
		return;

	context->clear_buffers( false, false, false );

	context->set_stencil_enable( true );

	ctx->m_model_renderer->forced_material_override( material ? material : nullptr );
	if (material) material->increment_reference_count();

	context->set_stencil_compare_function( STENCILCOMPARISONFUNCTION_ALWAYS );
	context->set_stencil_pass_operation( config->m_models.m_rendering_order ? STENCILOPERATION_KEEP : STENCILOPERATION_REPLACE );
	context->set_stencil_fail_operation( STENCILOPERATION_KEEP );
	context->set_stencil_z_fail_operation( config->m_models.m_rendering_order ? STENCILOPERATION_KEEP : STENCILOPERATION_REPLACE );
	context->set_stencil_reference_value( 1 );
	context->set_stencil_write_mask( 0xFF );
	context->set_stencil_test_mask( 0x0 );

	if ( material ) {
		ctx->m_render_view->set_color_modulation( color );
		ctx->m_render_view->set_blend( alpha );
	}
	else {
		ctx->m_render_view->set_color_modulation( 1.0f, 1.0f, 1.0f );
		ctx->m_render_view->set_blend( 1.0f );
	}
	
	if ( ignorez )
		context->depth_range( 0.0f, 0.2f );

	draw_entity_and_attachments( entity, overlay, color, alpha );
	context->depth_range( 0.0f, 1.0f );

	context->set_stencil_enable( false );
	ctx->m_model_renderer->forced_material_override( nullptr );
	ctx->m_render_view->set_color_modulation( 1.0f, 1.0f, 1.0f );
	ctx->m_render_view->set_blend( 1.0f );
}

void c_models::draw_occluded_and_unoccluded_models( c_base_entity* entity, i_material* material_occluded, color color_occluded, float alpha_occluded, bool overlay_occluded, i_material* material_unoccluded, color color_unoccluded, float alpha_unoccluded, bool overlay_unoccluded ) {
	if ( !entity || !entity->should_draw( ) )
		return;

	auto context = ctx->m_material_system->get_render_context( );
	if ( !context )
		return;

	context->clear_buffers( false, false, false );

	context->set_stencil_enable( true );
	ctx->m_model_renderer->forced_material_override( material_unoccluded ? material_unoccluded : nullptr );

	context->set_stencil_compare_function( STENCILCOMPARISONFUNCTION_ALWAYS );
	context->set_stencil_pass_operation( STENCILOPERATION_REPLACE );
	context->set_stencil_fail_operation( STENCILOPERATION_KEEP );
	context->set_stencil_z_fail_operation( STENCILOPERATION_KEEP );
	context->set_stencil_reference_value( 1 );
	context->set_stencil_write_mask( 0xFF );
	context->set_stencil_test_mask( 0x0 );

	if ( material_unoccluded ) {
		ctx->m_render_view->set_color_modulation( color_unoccluded );
		ctx->m_render_view->set_blend( alpha_unoccluded );
	}
	else {
		ctx->m_render_view->set_color_modulation( 1.0f, 1.0f, 1.0f );
		ctx->m_render_view->set_blend( 1.0f );
	}

	draw_entity_and_attachments( entity, overlay_unoccluded, color_unoccluded, alpha_unoccluded );

	ctx->m_model_renderer->forced_material_override( material_occluded ? material_occluded : nullptr );

	context->clear_buffers( false, false, false );
	context->set_stencil_compare_function( STENCILCOMPARISONFUNCTION_EQUAL );
	context->set_stencil_pass_operation( STENCILOPERATION_KEEP );
	context->set_stencil_fail_operation( STENCILOPERATION_KEEP );
	context->set_stencil_z_fail_operation( STENCILOPERATION_KEEP );
	context->set_stencil_reference_value( 0 );
	context->set_stencil_write_mask( 0x0 );
	context->set_stencil_test_mask( 0xFF );

	if ( material_occluded ) {
		ctx->m_render_view->set_color_modulation( color_occluded );
		ctx->m_render_view->set_blend( alpha_occluded );
	}
	else {
		ctx->m_render_view->set_color_modulation( 1.0f, 1.0f, 1.0f );
		ctx->m_render_view->set_blend( 1.0f );
	}

	context->depth_range( 0.0f, 0.2f );
	draw_entity_and_attachments( entity, overlay_occluded, color_occluded, alpha_occluded );
	context->depth_range( 0.0f, 1.0f );

	context->set_stencil_enable( false );
	ctx->m_model_renderer->forced_material_override( nullptr );
	ctx->m_render_view->set_color_modulation( 1.0f, 1.0f, 1.0f );
	ctx->m_render_view->set_blend( 1.0f );
}

void c_models::render_players( ) {
	if ( !config->m_models.m_player_models )
		return;

	i_material* material = nullptr;
	i_material* material_occluded = nullptr;
	i_material* material_unoccluded = nullptr;

	if ( config->m_models.m_player_two_models ) {

		switch ( config->m_models.m_player_model_occluded ) {
			case FLAT: {
				material_occluded = m_flat_material;
				break;
			}
			case SHADED: {
				material_occluded = m_shaded_material;
				break;
			}
			case FRESNEL: {
				material_occluded = m_fresnel_material;
				break;
			}
			default: break;
		}

		switch ( config->m_models.m_player_model_unoccluded ) {
			case FLAT: {
				material_unoccluded = m_flat_material;
				break;
			}
			case SHADED: {
				material_unoccluded = m_shaded_material;
				break;
			}
			case FRESNEL: {
				material_unoccluded = m_fresnel_material;
				break;
			}
			default: break;
		}
	}
	else {
		switch ( config->m_models.m_player_model ) {
			case FLAT: {
				material = m_flat_material;
				break;
			}
			case SHADED: {
				material = m_shaded_material;
				break;
			}
			case FRESNEL: {
				material = m_fresnel_material;
				break;
			}
			default: break;
		}
	}

	for ( const auto& player : ctx->players ) {
		if ( player->is_dormant( ) || ( !player->is_enemy( ) && config->m_models.m_player_enemy_only && !player->is_player_on_friend_list( ) && !player->is_local_player( ) ) )
			continue;

		if ( !player->is_entity_on_screen( ) )
			continue;

		//color occluded = player->m_team_num( ) == TF_TEAM_RED ? color( 165, 57, 43, 128 ) : color( 48, 54, 160, 128 );
		//color unoccluded = player->m_team_num( ) == TF_TEAM_RED ? color( 255, 120, 100, 128 ) : color( 105, 115, 255, 128 );
		color occluded = player->m_team_num( ) == TF_TEAM_RED ? color( 128, 25, 25, 128 ) : color( 0, 100, 128, 128 );
		color unoccluded = player->m_team_num( ) == TF_TEAM_RED ? color( 255, 55, 55, 128 ) : color( 0, 200, 255, 128 );
		if ( player->is_player_on_friend_list( ) || player->is_local_player( ) ) {
			occluded = color( 75, 25, 128 );
			unoccluded = color( 150, 50, 255 );
		}

		if ( config->m_models.m_player_two_models )
			draw_occluded_and_unoccluded_models( player, material_occluded, occluded, config->m_models.m_player_alpha_occluded, config->m_models.m_player_overlay_occluded,
												 material_unoccluded, unoccluded, config->m_models.m_player_alpha_unoccluded, config->m_models.m_player_overlay_unoccluded );
		else
			draw_occluded_and_unoccluded_model( player, material, unoccluded, config->m_models.m_player_alpha, config->m_models.m_player_ignorez, config->m_models.m_player_overlay );

		if ( player->is_alive( ) ) {
			auto attachment = player->get_move_child( );

			for ( int i = 0; i < 32; i++ ) {
				if ( !attachment || attachment->is_dormant( ) )
					continue;

				if ( config->m_models.m_player_two_models )
					draw_occluded_and_unoccluded_models( attachment, material_occluded, occluded, config->m_models.m_player_alpha_occluded, config->m_models.m_player_overlay_occluded,
														 material_unoccluded, unoccluded, config->m_models.m_player_alpha_unoccluded, config->m_models.m_player_overlay_unoccluded );
				else
					draw_occluded_and_unoccluded_model( attachment, material, unoccluded, config->m_models.m_player_alpha, config->m_models.m_player_ignorez, config->m_models.m_player_overlay );

				attachment = attachment->next_move_peer( );
			}
		}
	}
}

void c_models::render_buildings( ) {
	if ( !config->m_models.m_building_models )
		return;

	i_material* material = nullptr;
	i_material* material_occluded = nullptr;
	i_material* material_unoccluded = nullptr;

	if ( config->m_models.m_building_two_models ) {

		switch ( config->m_models.m_building_model_occluded ) {
			case FLAT: {
				material_occluded = m_flat_material;
				break;
			}
			case SHADED: {
				material_occluded = m_shaded_material;
				break;
			}
			case FRESNEL: {
				material_occluded = m_fresnel_material;
				break;
			}
			default: break;
		}

		switch ( config->m_models.m_building_model_unoccluded ) {
			case FLAT: {
				material_unoccluded = m_flat_material;
				break;
			}
			case SHADED: {
				material_unoccluded = m_shaded_material;
				break;
			}
			case FRESNEL: {
				material_unoccluded = m_fresnel_material;
				break;
			}
			default: break;
		}
	}
	else {
		switch ( config->m_models.m_building_model ) {
			case FLAT: {
				material = m_flat_material;
				break;
			}
			case SHADED: {
				material = m_shaded_material;
				break;
			}
			case FRESNEL: {
				material = m_fresnel_material;
				break;
			}
			default: break;
		}
	}

	for ( const auto& building : ctx->buildings ) {
		const auto& builder = ctx->m_entity_list->get_client_entity_from_handle( building->m_builder( ) )->as<c_base_player>( );
		if ( !building || building->m_placing( ) || building->is_dormant( ) || ( !building->is_enemy( ) && config->m_models.m_building_enemy_only && builder && !builder->is_player_on_friend_list( ) && !builder->is_local_player( ) ) || !building->m_health( ) )
			continue;

		if ( !building->is_entity_on_screen( ) )
			continue;

		color occluded = building->m_team_num( ) == TF_TEAM_RED ? color( 128, 25, 25, 128 ) : color( 0, 100, 128, 128 );
		color unoccluded = building->m_team_num( ) == TF_TEAM_RED ? color( 255, 55, 55, 128 ) : color( 0, 200, 255, 128 );
		if ( builder && ( builder->is_player_on_friend_list( ) || builder->is_local_player( ) ) ) {
			occluded = color( 75, 25, 128 );
			unoccluded = color( 150, 50, 255 );
		}

		if ( config->m_models.m_building_two_models )
			draw_occluded_and_unoccluded_models( building, material_occluded, occluded, config->m_models.m_building_alpha_occluded, config->m_models.m_building_overlay_occluded,
												 material_unoccluded, unoccluded, config->m_models.m_building_alpha_unoccluded, config->m_models.m_building_overlay_unoccluded );
		else
			draw_occluded_and_unoccluded_model( building, material, unoccluded, config->m_models.m_building_alpha, config->m_models.m_building_ignorez, config->m_models.m_building_overlay );
	}
}

void c_models::render_world( ) {
	if ( config->m_models.m_world_models ) {
		i_material* material = nullptr;
		i_material* material_occluded = nullptr;
		i_material* material_unoccluded = nullptr;

		if ( config->m_models.m_world_two_models ) {

			switch ( config->m_models.m_world_model_occluded ) {
				case FLAT: {
					material_occluded = m_flat_material;
					break;
				}
				case SHADED: {
					material_occluded = m_shaded_material;
					break;
				}
				case FRESNEL: {
					material_occluded = m_fresnel_material;
					break;
				}
				default: break;
			}

			switch ( config->m_models.m_world_model_unoccluded ) {
				case FLAT: {
					material_unoccluded = m_flat_material;
					break;
				}
				case SHADED: {
					material_unoccluded = m_shaded_material;
					break;
				}
				case FRESNEL: {
					material_unoccluded = m_fresnel_material;
					break;
				}
				default: break;
			}
		}
		else {
			switch ( config->m_models.m_world_model ) {
				case FLAT: {
					material = m_flat_material;
					break;
				}
				case SHADED: {
					material = m_shaded_material;
					break;
				}
				case FRESNEL: {
					material = m_fresnel_material;
					break;
				}
				default: break;
			}
		}

		for ( const auto& health : ctx->healthpacks ) {
			if ( !health->is_entity_on_screen( ) )
				continue;

			color occluded = color( 25, 120, 25, 128 );
			color unoccluded = color( 55, 200, 55, 128 );

			if ( config->m_models.m_world_two_models )
				draw_occluded_and_unoccluded_models( health, material_occluded, occluded, config->m_models.m_world_alpha_occluded, config->m_models.m_world_overlay_occluded
													 , material_unoccluded, unoccluded, config->m_models.m_world_alpha_unoccluded, config->m_models.m_world_overlay_unoccluded );
			else
				draw_occluded_and_unoccluded_model( health, material, unoccluded, config->m_models.m_world_alpha, config->m_models.m_world_ignorez, config->m_models.m_world_overlay );
		}

		for ( const auto& ammo : ctx->ammopacks ) {
			if ( !ammo->is_entity_on_screen( ) )
				continue;

			color occluded = color( 128, 128, 128, 128 );
			color unoccluded = color( 200, 200, 200, 128 );

			if ( config->m_models.m_world_two_models )
				draw_occluded_and_unoccluded_models( ammo, material_occluded, occluded, config->m_models.m_world_alpha_occluded, config->m_models.m_world_overlay_occluded
													 , material_unoccluded, unoccluded, config->m_models.m_world_alpha_unoccluded, config->m_models.m_world_overlay_unoccluded );
			else
				draw_occluded_and_unoccluded_model( ammo, material, unoccluded, config->m_models.m_world_alpha, config->m_models.m_world_ignorez, config->m_models.m_world_overlay );
		}
	}

	if ( config->m_models.m_projectile_models ) {
		i_material* material = nullptr;
		i_material* material_occluded = nullptr;
		i_material* material_unoccluded = nullptr;

		if ( config->m_models.m_projectile_two_models ) {

			switch ( config->m_models.m_projectile_model_occluded ) {
				case FLAT: {
					material_occluded = m_flat_material;
					break;
				}
				case SHADED: {
					material_occluded = m_shaded_material;
					break;
				}
				case FRESNEL: {
					material_occluded = m_fresnel_material;
					break;
				}
				default: break;
			}

			switch ( config->m_models.m_projectile_model_unoccluded ) {
				case FLAT: {
					material_unoccluded = m_flat_material;
					break;
				}
				case SHADED: {
					material_unoccluded = m_shaded_material;
					break;
				}
				case FRESNEL: {
					material_unoccluded = m_fresnel_material;
					break;
				}
				default: break;
			}
		}
		else {
			switch ( config->m_models.m_projectile_model ) {
				case FLAT: {
					material = m_flat_material;
					break;
				}
				case SHADED: {
					material = m_shaded_material;
					break;
				}
				case FRESNEL: {
					material = m_fresnel_material;
					break;
				}
				default: break;
			}
		}

		for ( const auto& projectile : ctx->projectiles ) {
			const auto& thrower = ctx->m_entity_list->get_client_entity_from_handle( projectile->m_thrower( ) )->as<c_base_player>( );
			if ( !projectile->is_enemy( ) && config->m_models.m_projectile_enemy_only && thrower && !thrower->is_player_on_friend_list( ) && !thrower->is_local_player( ) )
				continue;

			if ( !projectile->is_entity_on_screen( ) )
				continue;

			color occluded = projectile->m_team_num( ) == TF_TEAM_RED ? color( 128, 25, 25, 128 ) : color( 0, 100, 128, 128 );
			color unoccluded = projectile->m_team_num( ) == TF_TEAM_RED ? color( 255, 55, 55, 128 ) : color( 0, 200, 255, 128 );
			if ( thrower && ( thrower->is_player_on_friend_list( ) || thrower->is_local_player( ) ) ) {
				occluded = color( 75, 25, 128 );
				unoccluded = color( 150, 50, 255 );
			}

			if ( config->m_models.m_projectile_two_models )
				draw_occluded_and_unoccluded_models( projectile, material_occluded, occluded, config->m_models.m_projectile_alpha_occluded, config->m_models.m_projectile_overlay_occluded
													 , material_unoccluded, unoccluded, config->m_models.m_projectile_alpha_unoccluded, config->m_models.m_projectile_overlay_unoccluded );
			else
				draw_occluded_and_unoccluded_model( projectile, material, unoccluded, config->m_models.m_projectile_alpha, config->m_models.m_projectile_ignorez, config->m_models.m_projectile_overlay );
		}
	}
}

void c_models::render( ) {
	if ( !m_rendered_entities.empty( ) )
		m_rendered_entities.clear( );

	if ( !m_rendered_weapons.empty( ) )
		m_rendered_weapons.clear( );
	
	if ( !ctx->m_local_player || ctx->m_engine_vgui->is_game_ui_visible( ) )
		return;

	if ( !config->m_models.m_enabled )
		return;

	if ( !GetModuleHandleA( "materialsystem.dll" ) )
		return;

	m_has_stencil = false;
	m_has_second_stencil = false;

	render_players( );
	render_buildings( );
	render_world( );

	ctx->m_render_view->set_color_modulation( { 255, 255, 255, 255 } );
	ctx->m_render_view->set_blend( 1.0f );
	ctx->m_model_renderer->forced_material_override( nullptr );
}