#include "outlines.h"
#include "../models/models.h"

bool c_outlines::is_rendering( ) {
	return m_rendering;
}

bool c_outlines::is_used_material( i_material* material ) {
	return material == m_material_glow_color;
}

bool c_outlines::is_entity_rendered( c_base_entity* entity ) {
	if ( !entity || entity->is_dormant( ) )
		return false;

	return m_rendered_entities.find( entity ) != m_rendered_entities.end( );
}

void c_outlines::init_materials( ) {
	if ( !m_material_glow_color ) {
		m_material_glow_color = ctx->m_material_system->find_material( ( "dev/glow_color" ), "Other textures" );
		m_material_glow_color->increment_reference_count( );
	}

	if ( !m_rt_full_frame ) {
		m_rt_full_frame = ctx->m_material_system->find_texture( ( "_rt_FullFrameFB" ), "RenderTargets" );
		m_rt_full_frame->increment_reference_count( );
	}

	if ( !m_render_buffer1 ) {
		m_render_buffer1 = ctx->m_material_system->create_named_render_target_texture_ex(
			( "glow_buffer_1" ), m_rt_full_frame->get_actual_width( ), m_rt_full_frame->get_actual_height( ),
			RT_SIZE_LITERAL, IMAGE_FORMAT_RGB888, MATERIAL_RT_DEPTH_SHARED,
			TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT | TEXTUREFLAGS_EIGHTBITALPHA, CREATERENDERTARGETFLAGS_HDR );
		m_render_buffer1->increment_reference_count( );
	}

	if ( !m_render_buffer2 ) {
		m_render_buffer2 = ctx->m_material_system->create_named_render_target_texture_ex(
			( "glow_buffer_2" ), m_rt_full_frame->get_actual_width( ), m_rt_full_frame->get_actual_height( ),
			RT_SIZE_LITERAL, IMAGE_FORMAT_RGB888, MATERIAL_RT_DEPTH_SHARED,
			TEXTUREFLAGS_CLAMPS | TEXTUREFLAGS_CLAMPT | TEXTUREFLAGS_EIGHTBITALPHA, CREATERENDERTARGETFLAGS_HDR );
		m_render_buffer2->increment_reference_count( );
	}

	if ( !m_material_blur_x ) {
		if ( !m_material_blur_x_vmt ) {
			m_material_blur_x_vmt = new key_values( "BlurFilterX" );
			m_material_blur_x_vmt->set_string( "$basetexture", "glow_buffer_1" );
			m_material_blur_x_vmt->set_string( "$wireframe", "0" );
		}
		m_material_blur_x = ctx->m_material_system->create_material( "m_pMatBlurX", m_material_blur_x_vmt );
	}

	if ( !m_material_blur_x_wireframe ) {
		if ( !m_material_blur_x_wireframe_vmt ) {
			m_material_blur_x_wireframe_vmt = new key_values( "BlurFilterX" );
			m_material_blur_x_wireframe_vmt->set_string( "$basetexture", "glow_buffer_1" );
			m_material_blur_x_wireframe_vmt->set_string( "$wireframe", "1" );
		}
		m_material_blur_x_wireframe = ctx->m_material_system->create_material( "m_pMatBlurXwf", m_material_blur_x_wireframe_vmt );
	}

	if ( !m_material_blur_y ) {
		if ( !m_material_blur_y_vmt ) {
			m_material_blur_y_vmt = new key_values( "BlurFilterY" );
			m_material_blur_y_vmt->set_string( "$basetexture", "glow_buffer_2" );
			m_material_blur_y_vmt->set_string( "$wireframe", "0" );
		}
		m_material_blur_y = ctx->m_material_system->create_material( "m_pMatBlurY", m_material_blur_y_vmt );
	}

	if ( !m_material_blur_y_wireframe ) {
		if ( !m_material_blur_y_wireframe_vmt ) {
			m_material_blur_y_wireframe_vmt = new key_values( "BlurFilterY" );
			m_material_blur_y_wireframe_vmt->set_string( "$basetexture", "glow_buffer_2" );
			m_material_blur_y_wireframe_vmt->set_string( "$wireframe", "1" );
		}
		m_material_blur_y_wireframe = ctx->m_material_system->create_material( "m_pMatBlurYwf", m_material_blur_y_wireframe_vmt );
	}

	if ( !m_material_halo ) {
		if ( !m_material_halo_vmt ) {
			m_material_halo_vmt = new key_values( "UnlitGeneric" );
			m_material_halo_vmt->set_string( "$basetexture", "glow_buffer_1" );
			m_material_halo_vmt->set_string( "$wireframe", "0" );
			m_material_halo_vmt->set_string( "$additive", "1" );
		}
		m_material_halo = ctx->m_material_system->create_material( "m_pMatHaloAddToScreen", m_material_halo_vmt );
	}
}

void c_outlines::remove_materials( ) {
	if ( m_material_glow_color ) {
		m_material_glow_color->decrement_reference_count( );
		//m_material_glow_color->delete_if_unreferenced( );
		m_material_glow_color = nullptr;
	}

	if ( m_rt_full_frame ) {
		m_rt_full_frame->decrement_reference_count( );
		//m_rt_full_frame->delete_if_unreferenced( );
		m_rt_full_frame = nullptr;
	}

	if ( m_render_buffer1 ) {
		m_render_buffer1->decrement_reference_count( );
		//m_render_buffer1->delete_if_unreferenced( );
		m_render_buffer1 = nullptr;
	}

	if ( m_render_buffer2 ) {
		m_render_buffer2->decrement_reference_count( );
		//m_render_buffer2->delete_if_unreferenced( );
		m_render_buffer2 = nullptr;
	}

	if ( m_material_blur_x ) {
		m_material_blur_x->decrement_reference_count( );
		//m_material_blur_x->delete_if_unreferenced( );
		m_material_blur_x = nullptr;
		m_material_blur_x_vmt = nullptr;
	}

	if ( m_material_blur_x_wireframe ) {
		m_material_blur_x_wireframe->decrement_reference_count( );
		//m_material_blur_x_wireframe->delete_if_unreferenced( );
		m_material_blur_x_wireframe = nullptr;
		m_material_blur_x_wireframe_vmt = nullptr;
	}

	if ( m_material_blur_y ) {
		m_material_blur_y->decrement_reference_count( );
		//m_material_blur_y->delete_if_unreferenced( );
		m_material_blur_y = nullptr;
		m_material_blur_y_vmt = nullptr;
	}

	if ( m_material_blur_y_wireframe ) {
		m_material_blur_y_wireframe->decrement_reference_count( );
		//m_material_blur_y_wireframe->delete_if_unreferenced( );
		m_material_blur_y_wireframe = nullptr;
		m_material_blur_y_wireframe_vmt = nullptr;
	}

	if ( m_material_halo ) {
		m_material_halo->decrement_reference_count( );
		//m_material_halo->delete_if_unreferenced( );
		m_material_halo = nullptr;
		m_material_halo_vmt = nullptr;
	}
}

void c_outlines::draw_entity( c_base_entity* entity, bool drawing_models ) {
	m_rendering = true;
	if ( !entity || entity->is_dormant( ) )
		return;

	if ( !drawing_models )
		m_drawing_glow = true;

	entity->draw_model( STUDIO_RENDER | STUDIO_NOSHADOWS );

	if ( drawing_models )
		m_rendered_entities[ entity ] = true;

	if ( !drawing_models )
		m_drawing_glow = false;

	m_rendering = false;
}

void c_outlines::draw_glow_on_entities( ) {
	if ( ctx->m_engine_vgui->is_game_ui_visible( ) || !ctx->m_engine_client->is_in_game( ) )
		return;

	int w = ctx->m_screen_width;
	int h = ctx->m_screen_height;

	if ( w < 1 || h < 1 || w > 4096 || h > 2160 )
		return;

	const auto& context = ctx->m_material_system->get_render_context( );
	if ( !context )
		return;

	if ( i_material_var* bloom = m_material_blur_y->find_var( "$bloomamount", NULL, false ) ) {
		bloom->set_int_value( config->m_outlines.m_blur_scale );
	}

	//if ( !models->m_has_stencil ) {
		context->clear_buffers( false, false, false );
		context->set_stencil_enable( true );
		context->set_stencil_compare_function( STENCILCOMPARISONFUNCTION_ALWAYS );
		context->set_stencil_pass_operation( config->m_models.m_rendering_order ? STENCILOPERATION_KEEP : STENCILOPERATION_REPLACE );
		context->set_stencil_fail_operation( STENCILOPERATION_KEEP );
		context->set_stencil_z_fail_operation( config->m_models.m_rendering_order ? STENCILOPERATION_KEEP : STENCILOPERATION_REPLACE );
		context->set_stencil_reference_value( 1 );
		context->set_stencil_write_mask( 0xFF );
		context->set_stencil_test_mask( 0x0 );
	//}

	ctx->m_render_view->set_color_modulation( 1.0f, 1.0f, 1.0f );
	ctx->m_render_view->set_blend( 1.0f );

	if ( config->m_outlines.m_player_outlines ) {
		for ( const auto& player : ctx->players ) {
			if ( !player || !player->is_alive( ) || player->is_dormant( ) || ( !player->is_enemy( ) && config->m_outlines.m_player_enemy_only && !player->is_player_on_friend_list( ) && !player->is_local_player( ) ) )
				continue;

			if ( !player->is_entity_on_screen( ) )
				continue;

			color glow_color = player->m_team_num( ) == TF_TEAM_RED ? color( 255, 55, 55, 255 ) : color( 0, 200, 255, 255 );
			if ( player->is_player_on_friend_list( ) || player->is_local_player( ) ) {
				glow_color = color( 150, 50, 255 );
			}

			m_glow_entities.push_back( { player, glow_color, config->m_outlines.m_player_alpha } );
			if ( !models->is_entity_rendered( player ) )
				draw_entity( player, true );

			auto attachment = player->get_move_child( );
			for ( int i = 0; i < 32; i++ ) {
				if ( !attachment || attachment->is_dormant( ) )
					continue;

				if ( attachment->get_client_class( )->m_class_id == class_id_t::CTFWearable ) {
					m_glow_entities.push_back( { attachment, glow_color, config->m_outlines.m_player_alpha } );
					if ( !models->is_entity_rendered( attachment ) )
						draw_entity( attachment, true );
				}

				attachment = attachment->next_move_peer( );
			}

			const auto& weapon = player->get_active_weapon( );

			if ( weapon && !weapon->is_dormant( ) ) {
				m_glow_entities.push_back( { weapon, glow_color, config->m_outlines.m_player_alpha } );
				if ( !models->is_entity_rendered( weapon ) )
					draw_entity( weapon, true );
			}
		}
	}

	if ( config->m_outlines.m_building_outlines ) {
		for ( const auto& building : ctx->buildings ) {
			const auto& builder = ctx->m_entity_list->get_client_entity_from_handle( building->m_builder( ) )->as<c_base_player>( );
			if ( !building || building->m_placing( ) || building->is_dormant( ) || ( !building->is_enemy( ) && config->m_outlines.m_building_enemy_only && builder && !builder->is_player_on_friend_list( ) && !builder->is_local_player( ) ) || !building->m_health( ) )
				continue;

			if ( !building->is_entity_on_screen( ) )
				continue;

			color glow_color = building->m_team_num( ) == TF_TEAM_RED ? color( 255, 55, 55, 255 ) : color( 0, 200, 255, 255 );
			if ( builder && ( builder->is_player_on_friend_list( ) || builder->is_local_player( ) ) ) {
				glow_color = color( 150, 50, 255 );
			}

			m_glow_entities.push_back( { building, glow_color, config->m_outlines.m_building_alpha } );
			if ( !models->is_entity_rendered( building ) )
				draw_entity( building, true );
		}
	}

	if ( config->m_outlines.m_world_outlines ) {
		for ( const auto& health : ctx->healthpacks ) {
			if ( !health || health->is_dormant( ) )
				continue;

			if ( !health->is_entity_on_screen( ) )
				continue;

			color glow_color = color( 55, 200, 55, 128 );

			m_glow_entities.push_back( { health, glow_color, config->m_outlines.m_world_alpha } );
			if ( !models->is_entity_rendered( health ) )
				draw_entity( health, true );
		}

		for ( const auto& ammo : ctx->ammopacks ) {
			if ( !ammo || ammo->is_dormant( ) )
				continue;

			if ( !ammo->is_entity_on_screen( ) )
				continue;

			color glow_color = color( 200, 200, 200, 128 );

			m_glow_entities.push_back( { ammo, glow_color, config->m_outlines.m_world_alpha } );
			if ( !models->is_entity_rendered( ammo ) )
				draw_entity( ammo, true );
		}
	}

	if ( config->m_outlines.m_projectile_outlines ) {
		for ( const auto& projectile : ctx->projectiles ) {
			const auto& thrower = ctx->m_entity_list->get_client_entity_from_handle( projectile->m_thrower( ) )->as<c_base_player>( );
			if ( !projectile || projectile->is_dormant( ) || ( !projectile->is_enemy( ) && config->m_outlines.m_projectile_enemy_only && thrower && !thrower->is_player_on_friend_list( ) && !thrower->is_local_player( ) ) )
				continue;

			if ( !projectile->is_entity_on_screen( ) )
				continue;

			color glow_color = projectile->m_team_num( ) == TF_TEAM_RED ? color( 255, 55, 55, 255 ) : color( 0, 200, 255, 255 );
			if ( thrower && ( thrower->is_player_on_friend_list( ) || thrower->is_local_player( ) ) ) {
				glow_color = color( 150, 50, 255 );
			}

			m_glow_entities.push_back( { projectile, glow_color, config->m_outlines.m_projectile_alpha } );
			if ( !models->is_entity_rendered( projectile ) )
				draw_entity( projectile, true );
		}
	}

	context->set_stencil_enable( false );
	if ( m_glow_entities.empty( ) )
		return;

	ctx->m_model_renderer->forced_material_override( m_material_glow_color );

	context->push_render_target_and_viewport( ); {
		if ( m_render_buffer1 ) context->set_render_target( m_render_buffer1 );
		context->viewport( 0, 0, w, h );
		context->clear_color4ub( 0, 0, 0, 0 );
		context->clear_buffers( true, false, false );

		for ( const auto& glow_entity : m_glow_entities ) {
			ctx->m_render_view->set_color_modulation( glow_entity.m_color );
			ctx->m_render_view->set_blend( glow_entity.alpha );

			draw_entity( glow_entity.m_entity, false );
		}

	} context->pop_render_target_and_viewport( );

	if ( config->m_outlines.m_blur_outline ) {
		context->push_render_target_and_viewport( ); {
			context->viewport( 0, 0, w, h );

			context->set_render_target( m_render_buffer2 );
			context->draw_screen_space_rectangle( m_material_blur_x, 0, 0, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );

			context->set_render_target( m_render_buffer1 );
			context->draw_screen_space_rectangle( m_material_blur_y, 0, 0, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
		} context->pop_render_target_and_viewport( );
	}

	context->set_stencil_enable( true );
	if ( !models->m_has_stencil ) {
		context->set_stencil_compare_function( STENCILCOMPARISONFUNCTION_EQUAL );
		context->set_stencil_pass_operation( STENCILOPERATION_KEEP );
		context->set_stencil_fail_operation( STENCILOPERATION_KEEP );
		context->set_stencil_z_fail_operation( STENCILOPERATION_KEEP );
		context->set_stencil_reference_value( 0 );
		context->set_stencil_write_mask( 0x0 );
		context->set_stencil_test_mask( 0xFF );
	}

	if ( config->m_outlines.m_stencil_outline )
	{
		context->draw_screen_space_rectangle( m_material_halo, -config->m_outlines.m_stencil_scale, -config->m_outlines.m_stencil_scale, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
		context->draw_screen_space_rectangle( m_material_halo, -config->m_outlines.m_stencil_scale, 0, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
		context->draw_screen_space_rectangle( m_material_halo, 0, -config->m_outlines.m_stencil_scale, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
		context->draw_screen_space_rectangle( m_material_halo, 0, config->m_outlines.m_stencil_scale, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
		context->draw_screen_space_rectangle( m_material_halo, config->m_outlines.m_stencil_scale, config->m_outlines.m_stencil_scale, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
		context->draw_screen_space_rectangle( m_material_halo, config->m_outlines.m_stencil_scale, 0, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
		context->draw_screen_space_rectangle( m_material_halo, config->m_outlines.m_stencil_scale, -config->m_outlines.m_stencil_scale, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
		context->draw_screen_space_rectangle( m_material_halo, -config->m_outlines.m_stencil_scale, config->m_outlines.m_stencil_scale, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
	}

	if ( config->m_outlines.m_blur_outline ) {
		context->draw_screen_space_rectangle( m_material_halo, 0, 0, w, h, 0.0f, 0.0f, w - 1, h - 1, w, h );
	}

	context->set_stencil_enable( false );
	ctx->m_model_renderer->forced_material_override( nullptr );
	ctx->m_render_view->set_color_modulation( 1.0f, 1.0f, 1.0f );
	ctx->m_render_view->set_blend( 1.0f );
}

void c_outlines::render( ) {
	if ( !m_rendered_entities.empty( ) )
		m_rendered_entities.clear( );

	if ( !m_glow_entities.empty( ) )
		m_glow_entities.clear( );

	if ( !ctx->m_local_player || ctx->m_engine_vgui->is_game_ui_visible( ) )
		return;

	if ( !config->m_outlines.m_enabled )
		return;

	if ( !GetModuleHandleA( "materialsystem.dll" ) )
		return;

	if ( ctx->m_drawing_projectile_camera )
		return;

	draw_glow_on_entities( );

	ctx->m_render_view->set_color_modulation( { 255, 255, 255, 255 } );
	ctx->m_render_view->set_blend( 1.0f );
	ctx->m_model_renderer->forced_material_override( nullptr );
}