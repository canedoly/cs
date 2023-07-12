#include "esp.h"
#include "../backtrack/backtrack.h"
#include "../cheat_detection/cheat_detection.h"

void c_esp::run( ) {
	if ( !ctx->m_local_player || ctx->m_engine_vgui->is_game_ui_visible( ) )
		return;

	render_players( );
	render_buildings( );
	render_worlds( );
}

bool c_esp::compute_bounding_box( c_base_entity* entity, rect_t& bounding_box ) {
	const auto& mins = entity->m_mins( );
	const auto& maxs = entity->m_maxs( );

	std::array< vector, 8 > points = {
		vector( mins.m_x, mins.m_y, mins.m_z ),
		vector( mins.m_x, maxs.m_y, mins.m_z ),
		vector( maxs.m_x, maxs.m_y, mins.m_z ),
		vector( maxs.m_x, mins.m_y, mins.m_z ),
		vector( maxs.m_x, maxs.m_y, maxs.m_z ),
		vector( mins.m_x, maxs.m_y, maxs.m_z ),
		vector( mins.m_x, mins.m_y, maxs.m_z ),
		vector( maxs.m_x, mins.m_y, maxs.m_z )
	};

	auto& transform = entity->renderable_to_world_transform( );

	if ( entity && entity == ctx->m_local_player ) {
		auto angles = ctx->m_engine_client->get_view_angles( );
		angles.m_x = angles.m_z = 0.0f;
		math::angle_matrix( angles, transform );
		math::matrix_set_column( entity->get_render_origin( ), 3, transform );
	}

	auto left = std::numeric_limits< float >::max( );
	auto top = std::numeric_limits< float >::max( );
	auto right = std::numeric_limits< float >::lowest( );
	auto bottom = std::numeric_limits< float >::lowest( );

	std::array< vector, 8 > screen;

	for ( std::size_t i = 0; i < 8; i++ ) {
		if ( !tf2::world_to_screen( math::vector_transform( points.at( i ), transform ), screen.at( i ) ) )
			return false;

		left = std::min( left, screen.at( i ).m_x );
		top = std::min( top, screen.at( i ).m_y );
		right = std::max( right, screen.at( i ).m_x );
		bottom = std::max( bottom, screen.at( i ).m_y );
	}

	auto x_ = left;
	auto y_ = top;
	auto w_ = right - left;
	auto h_ = bottom - top;

	if ( entity->is_player( ) ) {
		x_ += ( ( right - left ) / 8.0f );
		w_ -= ( ( ( right - left ) / 8.0f ) * 2.0f );
	}

	bounding_box.m_x = static_cast< int >( x_ );
	bounding_box.m_y = static_cast< int >( y_ );
	bounding_box.m_w = static_cast< int >( w_ );
	bounding_box.m_h = static_cast< int >( h_ );

	return true;
}

void c_esp::render_players( ) {
	if ( !config->m_esp.m_players_enabled )
		return;

	for ( const auto& player : ctx->players ) {
		if ( !player || !player->is_alive( ) || ( player->is_dormant( ) && ctx->m_globals->m_current_time - ctx->m_far_esp_t[ player ] > config->m_esp.m_far_esp_fade_t ) )
			continue;

		if ( !player->is_enemy( ) && config->m_esp.m_player_enemy && !player->is_player_on_friend_list( ) && !player->is_local_player( ) )
			continue;

		if ( !ctx->m_input->cam_is_third_person( ) && player == ctx->m_local_player )
			continue;

		auto esp_color = color( 0, 0, 0 );
		if ( config->m_esp.m_player_team_color )
			esp_color = player->is_enemy( ) ? color( 255, 150, 50 ) : color( 50, 255, 50 );

		else
			esp_color = player->m_team_num( ) == TF_TEAM_RED ? color( 215, 60, 60 ) : ( player->m_team_num( ) == TF_TEAM_BLU ? color( 0, 200, 255 ) : color( 0, 0, 0 ) );

		if ( player->is_player_on_friend_list( ) || player->is_local_player( ) )
			esp_color = color( 150, 50, 255 );

		if ( config->m_esp.m_player_arrows && player->is_enemy( ) ) {
			if ( !player->is_entity_on_screen( ) )
				render_player_arrow( player, esp_color );
		}

		rect_t bbox = { };
		if ( !compute_bounding_box( player, bbox) )
			continue;

		const rect_t& bounding_box = const_cast<rect_t&>(bbox); // jod bless performancer

		auto dormant_color = color( 255, 255, 255 );

		if ( player->is_dormant( ) )
			dormant_color = color( 170, 170, 170 );

		if ( config->m_esp.m_player_box ) {
			render->outlined_rect( bounding_box.m_x, bounding_box.m_y, bounding_box.m_w, bounding_box.m_h, esp_color );
			render->outlined_rect( bounding_box.m_x - 1, bounding_box.m_y - 1, bounding_box.m_w + 2, bounding_box.m_h + 2, color( 0, 0, 0, 200 ) );
			render->outlined_rect( bounding_box.m_x + 1, bounding_box.m_y + 1, bounding_box.m_w - 2, bounding_box.m_h - 2, color( 0, 0, 0, 200 ) );
		}

		if ( config->m_esp.m_player_health ) {
			if ( player_health[ player->entindex( ) ] < 0 || player_health[ player->entindex( ) ] > player->get_max_health( ) )
				player_health[ player->entindex( ) ] = player->m_health( );

			float& health_anim = player_health[ player->entindex( ) ];

			if ( health_anim > player->m_health( ) ) {
				if ( player->get_max_health( ) < 451 )
					health_anim -= ( player->get_max_health( ) * 2 ) * ctx->m_globals->m_frame_time;
				else
					health_anim -= ( player->get_max_health( ) * 2 ) * ctx->m_globals->m_frame_time * player->get_max_health( ) / 300.f;
			}
			else
				health_anim = player->m_health( );

			auto health_bar_height = static_cast< float >( bounding_box.m_h ) * math::get_fraction( health_anim, player->get_max_health( ), 0.0f );
			auto render_height = ( bounding_box.m_y + ( bounding_box.m_h - health_bar_height ) ) + ( health_anim < player->get_max_health( ) ? 1 : 0 );
			render->filled_rect( bounding_box.m_x - 6, bounding_box.m_y - 1, 4, bounding_box.m_h + 2, color( 0, 0, 0, 180 ) );
			render->filled_rect( bounding_box.m_x - 5, render_height, 2, health_bar_height, tf2::get_health_color( player->m_health( ), player->get_max_health( ) ) );
			if ( player->m_health( ) < player->get_max_health( ) ) {
				render->outlined_text( bounding_box.m_x - 6, render_height - 3, ALIGN_RIGHT, ctx->m_verdana_narrow.m_font, color( 255, 255, 255 ), L"%i", player->m_health( ) );
			}
		}

		if ( config->m_esp.m_player_flags ) {
			int y = bounding_box.m_y - 2;
			int text_offset = 0;

			if ( player->is_dormant( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 220, 240, 170 ), "DORMANT" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_overhealed( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 150, 255, 150 ), "+%i HP", player->m_health( ) - player->get_max_health( ) );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_cloaked( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 200, 200, 200 ), "CLOAKED" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_invulnerable( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 110, 255 ), "UBERCHARGE" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_crit_boosted( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 150, 255 ), "CRIT BOOSTED" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_stunned( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 150, 150, 150 ), "SLOWED" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_slowed( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 150, 150, 150 ), player->m_player_class( ) == CLASS_HEAVY ? "REVVED" : "SLOWED" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_bonked( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 144, 110 ), "BONKED" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_zoomed( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 50, 200, 255 ), "ZOOMED" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_taunting( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 200, 100, 255 ), "TAUNTING" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_marked_for_death( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 200, 255, 50 ), "MARKED" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_in_battalions_range( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 128, 128, 255 ), "BATTALIONS" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_in_concheror_range( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 255, 150 ), "CONCHEROR" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_in_buff_banner_range( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 150, 255 ), "BUFF BANNER" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_mini_crit_boosted( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 150, 255 ), "MINI CRIT" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_covered_in_milk( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 255, 255 ), "MAD MILK" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_bleeding( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 50, 50 ), "BLEEDING" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_bullet_charged( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 110, 255 ), "BULLET CHARGE" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			else if ( player->is_bullet_resistant( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 160, 255 ), "BULLET RESISTANT" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_explosive_charged( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 110, 255 ), "EXPLOSIVE CHARGE" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			else if ( player->is_explosive_resistant( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 160, 255 ), "EXPLOSIVE RESISTANT" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			if ( player->is_fire_charged( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 110, 255 ), "FIRE CHARGE" );
				text_offset += ctx->m_small_fonts.m_tall;
			}

			else if ( player->is_fire_resistant( ) ) {
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, y + text_offset, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 160, 255 ), "FIRE RESISTANT" );
				text_offset += ctx->m_small_fonts.m_tall;
			}
		}

		if ( config->m_esp.m_player_name ) {
			player_info_t info = { };
			if ( ctx->m_engine_client->get_player_info( player->entindex( ), &info ) ) {
				if ( player->is_player_on_friend_list( ) )
					render->outlined_text( bounding_box.m_x + ( bounding_box.m_w * 0.5f ), bounding_box.m_y - ctx->m_verdana_narrow.m_tall - 12, ALIGN_CENTERHORIZONTAL, ctx->m_verdana_narrow.m_font, color( 0, 200, 255 ), "FRIEND" );
				else if ( tf2::is_a_cheater_unoptimized( info.m_friends_id ) )
					render->outlined_text( bounding_box.m_x + ( bounding_box.m_w * 0.5f ), bounding_box.m_y - ctx->m_verdana_narrow.m_tall - 12, ALIGN_CENTERHORIZONTAL, ctx->m_verdana_narrow.m_font, color( 255, 50, 50 ), "CHEATER" );
				else if (cheat_detection->m_suspects[player->entindex()].m_marked)
					render->outlined_text(bounding_box.m_x + (bounding_box.m_w * 0.5f), bounding_box.m_y - ctx->m_verdana_narrow.m_tall - 12, ALIGN_CENTERHORIZONTAL, ctx->m_verdana_narrow.m_font, color(200, 120, 50), "SUSPECT");
				render->outlined_text( bounding_box.m_x + ( bounding_box.m_w * 0.5f ), bounding_box.m_y - ctx->m_verdana_narrow.m_tall - 2, ALIGN_CENTERHORIZONTAL, ctx->m_verdana_narrow.m_font, dormant_color, util::utf_to_wide( info.m_name ).c_str( ) );
			}
		}

		if ( config->m_esp.m_player_weapon ) {
			if ( player->get_active_weapon( ) )
				render->outlined_text( bounding_box.m_x + ( bounding_box.m_w * 0.5f ), bounding_box.m_y + bounding_box.m_h, ALIGN_CENTERHORIZONTAL, ctx->m_small_fonts.m_font, dormant_color, player->get_weapon_name( ) );
		}
	}
}

void c_esp::render_buildings( ) {
	if ( !config->m_esp.m_buildings_enabled )
		return;

	for ( const auto& building : ctx->buildings ) {
		if ( !building || building->is_dormant( ) || building->m_health( ) <= 0 )
			continue;

		rect_t bbox = { };
		if ( !compute_bounding_box( building, bbox) )
			continue;

		const rect_t& bounding_box = const_cast<rect_t&>(bbox); // jod bless performancer

		const auto& builder = ctx->m_entity_list->get_client_entity_from_handle( building->m_builder( ) )->as<c_base_player>( );
		if ( !building->is_enemy( ) && config->m_esp.m_building_enemy && builder && !builder->is_player_on_friend_list( ) && !builder->is_local_player( ) )
			continue;

		auto esp_color = color( 0, 0, 0 );

		if ( config->m_esp.m_player_team_color )
			esp_color = building->is_enemy( ) ? color( 255, 150, 50 ) : color( 50, 255, 50 );
		else
			esp_color = building->m_team_num( ) == TF_TEAM_RED ? color( 255, 50, 50 ) : ( building->m_team_num( ) == TF_TEAM_BLU ? color( 0, 200, 255 ) : color( 0, 0, 0 ) );

		if ( builder && ( builder->is_player_on_friend_list( ) || builder->is_local_player( ) ) )
			esp_color = color( 150, 50, 255 );

		if ( config->m_esp.m_building_box ) {
			render->outlined_rect( bounding_box.m_x, bounding_box.m_y, bounding_box.m_w, bounding_box.m_h, esp_color );
			render->outlined_rect( bounding_box.m_x - 1, bounding_box.m_y - 1, bounding_box.m_w + 2, bounding_box.m_h + 2, color( 0, 0, 0, 200 ) );
			render->outlined_rect( bounding_box.m_x + 1, bounding_box.m_y + 1, bounding_box.m_w - 2, bounding_box.m_h - 2, color( 0, 0, 0, 200 ) );
		}

		if ( config->m_esp.m_building_health ) {
			if ( building_health[ building->entindex( ) ] < 0 || building_health[ building->entindex( ) ] > building->m_max_health( ) )
			{
				building_health[ building->entindex( ) ] = building->m_health( );
			}
			float& health_anim = building_health[ building->entindex( ) ];

			if ( health_anim > building->m_health( ) )
			{
				if ( building->m_max_health( ) < 216 )
					health_anim -= ( building->m_max_health( ) * 2 ) * ctx->m_globals->m_frame_time;
				else
					health_anim -= ( building->m_max_health( ) * 2 ) * ctx->m_globals->m_frame_time * building->m_max_health( ) / 216.f;
			}
			else
			{
				health_anim = building->m_health( );
			}

			auto health_bar_height = static_cast< float >( bounding_box.m_h ) * math::get_fraction( health_anim, building->m_max_health( ), 0.0f );
			auto render_height = bounding_box.m_y + ( bounding_box.m_h - health_bar_height ) + ( health_anim < building->m_max_health( ) ? 1 : 0 );
			render->filled_rect( bounding_box.m_x - 6, bounding_box.m_y - 1, 4, bounding_box.m_h + 2, color( 0, 0, 0, 200 ) );
			render->filled_rect( bounding_box.m_x - 5, render_height, 2, health_bar_height, tf2::get_health_color( building->m_health( ), building->m_max_health( ) ) );
			if ( building->m_health( ) < building->m_max_health( ) ) {
				render->outlined_text( bounding_box.m_x - 6, render_height - 3, ALIGN_RIGHT, ctx->m_verdana_narrow.m_font, color( 255, 255, 255 ), L"%i", building->m_health( ) );
			}
		}

		if ( config->m_esp.m_building_flags ) {
			int text_offset = 0;
			if ( building->is_teleporter_and_recharging( ) ) {
				float recharge_time = building->m_recharge_time( ) - ctx->m_globals->m_current_time + 0.05f;

				if ( recharge_time > 0 ) {
					render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, bounding_box.m_y - 2, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 255, 255 ), "RECHARGES IN: %.1f", recharge_time );
					text_offset += ctx->m_small_fonts.m_tall;
				}
			}

			if ( building->m_upgrade_level( ) )
				render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, bounding_box.m_y + text_offset - 2, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 255, 255 ), "LEVEL: %i", building->m_upgrade_level( ) );
		}

		if ( config->m_esp.m_building_name ) {
			render->outlined_text( bounding_box.m_x + ( bounding_box.m_w * 0.5f ), bounding_box.m_y - ctx->m_verdana_narrow.m_tall, ALIGN_CENTERHORIZONTAL, ctx->m_verdana_narrow.m_font, color( 255, 255, 255 ), building->get_object_name( ) );
		}
	}
}

void c_esp::render_worlds( ) {
	if ( config->m_esp.m_projectiles_enabled )
	{
		for ( const auto& projectile : ctx->projectiles ) {
			if ( !projectile )
				continue;

			if ( projectile->is_dormant( ) || ( projectile->estimate_abs_velocity( ).is_zero( ) && projectile->m_pipebomb_type() != TYPE_STICKY ) )
				continue;

			rect_t bbox = { };
			if ( !compute_bounding_box( projectile, bbox) )
				continue;

			const rect_t& bounding_box = const_cast<rect_t&>(bbox); // jod bless performancer

			const auto& thrower = ctx->m_entity_list->get_client_entity_from_handle( projectile->m_thrower( ) )->as<c_base_player>( );
			if ( thrower && thrower->is_enemy( ) && config->m_esp.m_projectile_enemy && !thrower->is_player_on_friend_list( ) && !thrower->is_local_player( ) )
				continue;

			auto esp_color = color( 0, 0, 0 );

			if ( config->m_esp.m_player_team_color )
				esp_color = projectile->is_enemy( ) ? color( 255, 150, 50 ) : color( 50, 255, 50 );
			else
				esp_color = projectile->m_team_num( ) == TF_TEAM_RED ? color( 255, 50, 50 ) : ( projectile->m_team_num( ) == TF_TEAM_BLU ? color( 0, 200, 255 ) : color( 0, 0, 0 ) );

			if ( thrower && ( thrower->is_player_on_friend_list( ) || thrower->is_local_player( ) ) )
				esp_color = color( 150, 50, 255 );

			if ( config->m_esp.m_projectile_box ) {
				render->outlined_rect( bounding_box.m_x, bounding_box.m_y, bounding_box.m_w, bounding_box.m_h, esp_color );
				render->outlined_rect( bounding_box.m_x - 1, bounding_box.m_y - 1, bounding_box.m_w + 2, bounding_box.m_h + 2, color( 0, 0, 0, 200 ) );
				render->outlined_rect( bounding_box.m_x + 1, bounding_box.m_y + 1, bounding_box.m_w - 2, bounding_box.m_h - 2, color( 0, 0, 0, 200 ) );
			}

			//todo: fix on medic crossbow arrows and test it on other projectiles
			/*if ( config->m_esp.m_projectile_flags ) {
				if ( projectile->m_critical( ) ) {
					render->outlined_text( bounding_box.m_x + bounding_box.m_w + 3, bounding_box.m_y - 2, ALIGN_DEFAULT, ctx->m_small_fonts.m_font, color( 255, 50, 50 ), "CRIT" );
				}
			}*/

			if ( config->m_esp.m_projectile_name )
				render->outlined_text( bounding_box.m_x + ( bounding_box.m_w * 0.5f ), bounding_box.m_y - ctx->m_verdana_narrow.m_tall, ALIGN_CENTERHORIZONTAL, ctx->m_verdana_narrow.m_font, color( 255, 255, 255 ), projectile->get_projectile_name( ) );

			if ( config->m_esp.m_projectile_distance ) {
				float distance = ctx->m_local_player->m_origin( ).dist_to( projectile->m_origin( ) ) * 0.01905f;
				render->outlined_text( bounding_box.m_x + ( bounding_box.m_w * 0.5f ), bounding_box.m_y + bounding_box.m_h, ALIGN_CENTERHORIZONTAL, ctx->m_small_fonts_medium.m_font, color( 255, 255, 255 ), "%im", ( int )distance );
			}
		}
	}

	if ( config->m_esp.m_world_enabled )
	{
		for ( const auto& ammo : ctx->ammopacks ) {
			if ( !ammo || ammo->is_dormant( ) )
				continue;

			rect_t bbox = { };
			if ( !compute_bounding_box( ammo, bbox) )
				continue;

			const rect_t& bounding_box = const_cast<rect_t&>(bbox); // jod bless performancer

			if ( config->m_esp.m_world_box ) {
				render->outlined_rect( bounding_box.m_x, bounding_box.m_y, bounding_box.m_w, bounding_box.m_h, color( 200, 200, 200 ) );
				render->outlined_rect( bounding_box.m_x - 1, bounding_box.m_y - 1, bounding_box.m_w + 2, bounding_box.m_h + 2, color( 0, 0, 0, 200 ) );
				render->outlined_rect( bounding_box.m_x + 1, bounding_box.m_y + 1, bounding_box.m_w - 2, bounding_box.m_h - 2, color( 0, 0, 0, 200 ) );
			}

			if ( config->m_esp.m_world_name )
				render->outlined_text( bounding_box.m_x + ( bounding_box.m_w * 0.5f ), bounding_box.m_y - ctx->m_verdana_narrow.m_tall, ALIGN_CENTERHORIZONTAL, ctx->m_verdana_narrow.m_font, color( 255, 255, 255 ), "Ammo" );

			if ( config->m_esp.m_world_distance ) {
				float distance = ctx->m_local_player->m_origin( ).dist_to( ammo->m_origin( ) ) * 0.01905f;
				render->outlined_text( bounding_box.m_x + ( bounding_box.m_w * 0.5f ), bounding_box.m_y + bounding_box.m_h, ALIGN_CENTERHORIZONTAL, ctx->m_small_fonts_medium.m_font, color( 255, 255, 255 ), "%im", ( int )distance );
			}
		}

		for ( const auto& health : ctx->healthpacks ) {
			if ( !health || health->is_dormant( ) )
				continue;

			rect_t bounding_box = { };
			if ( !compute_bounding_box( health, bounding_box ) )
				continue;

			if ( config->m_esp.m_world_box ) {
				render->outlined_rect( bounding_box.m_x, bounding_box.m_y, bounding_box.m_w, bounding_box.m_h, color( 55, 200, 55 ) );
				render->outlined_rect( bounding_box.m_x - 1, bounding_box.m_y - 1, bounding_box.m_w + 2, bounding_box.m_h + 2, color( 0, 0, 0, 200 ) );
				render->outlined_rect( bounding_box.m_x + 1, bounding_box.m_y + 1, bounding_box.m_w - 2, bounding_box.m_h - 2, color( 0, 0, 0, 200 ) );
			}

			if ( config->m_esp.m_world_name )
				render->outlined_text( bounding_box.m_x + ( bounding_box.m_w * 0.5f ), bounding_box.m_y - ctx->m_verdana_narrow.m_tall, ALIGN_CENTERHORIZONTAL, ctx->m_verdana_narrow.m_font, color( 255, 255, 255 ), "Health" );

			if ( config->m_esp.m_world_distance ) {
				float distance = ctx->m_local_player->m_origin( ).dist_to( health->m_origin( ) ) * 0.01905f;
				render->outlined_text( bounding_box.m_x + ( bounding_box.m_w * 0.5f ), bounding_box.m_y + bounding_box.m_h, ALIGN_CENTERHORIZONTAL, ctx->m_small_fonts_medium.m_font, color( 255, 255, 255 ), "%im", ( int )distance );
			}
		}
	}
}

//pasted as fuck
void c_esp::render_player_arrow( c_base_player* player, color clr ) {
	if ( !player || player->is_dormant( ) )
		return;

	auto get_clockwise_angle = [ & ] ( const vector& view_angles, const vector& aim_angle ) -> float {
		vector angle, aim;
		math::angle_vectors( view_angles, &angle );
		math::angle_vectors( aim_angle, &aim );

		return -atan2f( angle.m_x * aim.m_y - angle.m_y * aim.m_x, angle.m_x * aim.m_x + angle.m_y * aim.m_y );
	};

	const vector angle_to = math::calculate_angle( ctx->m_local_player->m_origin( ), player->m_origin( ) );
	const float degrees = get_clockwise_angle( ctx->m_engine_client->get_view_angles( ), angle_to );
	
	const float x1 = ( ctx->m_screen_width * config->m_esp.m_arrows_screen_distance * ( config->m_esp.m_arrows_screen_shape ? ( ( float )ctx->m_screen_width / ( float )ctx->m_screen_height ) : 1.0f ) + 5.0f ) * cos( degrees - PI / 2 );
	const float y1 = ( ctx->m_screen_width * config->m_esp.m_arrows_screen_distance + 5.0f ) * sin( degrees - PI / 2 );
	const float x2 = ( ctx->m_screen_width * config->m_esp.m_arrows_screen_distance * ( config->m_esp.m_arrows_screen_shape ? ( ( float )ctx->m_screen_width / ( float )ctx->m_screen_height ) : 1.0f ) + 15.0f ) * cos( degrees - PI / 2 );
	const float y2 = ( ctx->m_screen_width * config->m_esp.m_arrows_screen_distance + 15.0f ) * sin( degrees - PI / 2 );

	const float arrow_angle = DEG_TO_RAD( 90.f );
	const float arrow_length = 25.f;

	const vector_2d line{ x2 - x1, y2 - y1 };
	const float length = line.length( );

	const float f_point_on_line = arrow_length / ( atanf( arrow_angle ) * length );
	const vector_2d point_on_line = vector_2d( x2, y2 ) + ( line * f_point_on_line * -1.0f );
	const vector_2d normal_vector{ -line.m_y, line.m_x };
	const vector_2d normal = vector_2d( arrow_length, arrow_length ) / ( length * 2 );

	const vector_2d rotation = normal * normal_vector;
	const vector_2d left = point_on_line + rotation;
	const vector_2d right = point_on_line - rotation;

	const float center_x = ctx->m_screen_width * 0.5f;
	const float center_y = ctx->m_screen_height * 0.5f;

	//outer
	render->line( center_x + left.m_x, center_y + left.m_y, center_x + right.m_x, center_y + right.m_y, clr );
	render->line( center_x + left.m_x, center_y + left.m_y, center_x + x2, center_y + y2, clr );
	render->line( center_x + right.m_x, center_y + right.m_y, center_x + x2, center_y + y2, clr );

	//inner
	render->line( center_x + left.m_x, center_y + left.m_y, center_x + ( point_on_line.m_x + ( x2 - point_on_line.m_x ) * 0.45f ),
				  center_y + ( point_on_line.m_y + ( y2 - point_on_line.m_y ) * 0.45f ), clr );

	render->line( center_x + right.m_x, center_y + right.m_y, center_x + ( point_on_line.m_x + ( x2 - point_on_line.m_x ) * 0.45f ),
				  center_y + ( point_on_line.m_y + ( y2 - point_on_line.m_y ) * 0.45f ), clr );

	render->line( center_x + x2, center_y + y2, center_x + ( point_on_line.m_x + ( x2 - point_on_line.m_x ) * 0.41f ),
				  center_y + ( point_on_line.m_y + ( y2 - point_on_line.m_y ) * 0.41f ), clr );

	//bottom triangle
	vertex_t triangle[ 3 ];
	triangle[ 0 ].init( { center_x + left.m_x, center_y + left.m_y } );
	triangle[ 1 ].init( { center_x + right.m_x, center_y + right.m_y } );
	triangle[ 2 ].init( { center_x + ( point_on_line.m_x + ( x2 - point_on_line.m_x ) * 0.41f ), center_y + ( point_on_line.m_y + ( y2 - point_on_line.m_y ) * 0.41f ) } );
	render->draw_texture_polygon( 3, triangle, { clr.m_r, clr.m_g, clr.m_b, 60 } );

	if ( config->m_esp.m_arrows_esp ) {
		float x = center_x + ( point_on_line.m_x + ( x2 - point_on_line.m_x ) * 0.45f );
		float y = center_y + ( point_on_line.m_y + ( y2 - point_on_line.m_y ) * 0.45f );

		if ( config->m_esp.m_player_name ) {
			player_info_t info = { };
			if ( ctx->m_engine_client->get_player_info( player->entindex( ), &info ) ) {
				if ( player->is_player_on_friend_list( ) )
					render->outlined_text( x + 1, y - 37, ALIGN_CENTERHORIZONTAL, ctx->m_verdana_narrow.m_font, color( 0, 200, 255 ), "FRIEND" );
				else if ( tf2::is_a_cheater_unoptimized( info.m_friends_id ) )
					render->outlined_text( x + 1, y - 37, ALIGN_CENTERHORIZONTAL, ctx->m_verdana_narrow.m_font, color( 255, 50, 50 ), "CHEATER" );
				else if ( cheat_detection->m_suspects[ player->entindex( ) ].m_marked )
					render->outlined_text( x + 1, y - 37, ALIGN_CENTERHORIZONTAL, ctx->m_verdana_narrow.m_font, color( 200, 120, 50 ), "SUSPECT" );
				render->outlined_text( x + 1, y - 27, ALIGN_CENTERHORIZONTAL, ctx->m_verdana_narrow.m_font, { 255, 255, 255, 255 }, util::utf_to_wide( info.m_name ).c_str( ) );
			}
		}

		if ( config->m_esp.m_player_health ) {
			if ( player_health[ player->entindex( ) ] < 0 || player_health[ player->entindex( ) ] > player->get_max_health( ) )
				player_health[ player->entindex( ) ] = player->m_health( );

			float& health_anim = player_health[ player->entindex( ) ];

			if ( health_anim > player->m_health( ) ) {
				if ( player->get_max_health( ) < 451 )
					health_anim -= ( player->get_max_health( ) * 2 ) * ctx->m_globals->m_frame_time;
				else
					health_anim -= ( player->get_max_health( ) * 2 ) * ctx->m_globals->m_frame_time * player->get_max_health( ) / 300.f;
			}
			else
				health_anim = player->m_health( );

			auto health_bar_height = static_cast< float >( arrow_length + 4 ) * math::get_fraction( health_anim, player->get_max_health( ), 0.0f );
			auto render_height = ( y - 14 + ( arrow_length + 4 - health_bar_height ) ) + ( health_anim < player->get_max_health( ) ? 1 : 0 );
			render->filled_rect( x - 16 - 2 - 1, y - 14 - 1, 4, arrow_length + 4 + 2, color( 0, 0, 0, 180 ) );
			render->filled_rect( x - 16 - 2, render_height, 2, health_bar_height, tf2::get_health_color( player->m_health( ), player->get_max_health( ) ) );
			if ( player->m_health( ) < player->get_max_health( ) ) {
				render->outlined_text( x - 16 - 2 - 1, render_height - 3, ALIGN_RIGHT, ctx->m_verdana_narrow.m_font, color( 255, 255, 255 ), L"%i", player->m_health( ) );
			}
		}

		if ( config->m_esp.m_player_weapon ) {
			if ( player->get_active_weapon( ) )
				render->outlined_text( x, y + 16, ALIGN_CENTERHORIZONTAL, ctx->m_small_fonts.m_font, { 255, 255, 255, 255 }, player->get_weapon_name( ) );
		}
	}
}