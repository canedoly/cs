#pragma once
#include "ctx.h"

enum e_string_align { ALIGN_DEFAULT, ALIGN_CENTER, ALIGN_CENTERHORIZONTAL, ALIGN_CENTERVERTICAL, ALIGN_RIGHT };
class c_render {
public:
	void reload_fonts( ) {
		ctx->m_surface->set_font_glyph_set( ctx->m_tahoma_narrow.m_font = ctx->m_surface->create_font( ), ctx->m_tahoma_narrow.m_name, ctx->m_tahoma_narrow.m_tall, ctx->m_tahoma_narrow.m_weight, 0, 0, ctx->m_tahoma_narrow.m_flags );
		ctx->m_surface->set_font_glyph_set( ctx->m_tahoma_wide.m_font = ctx->m_surface->create_font( ), ctx->m_tahoma_wide.m_name, ctx->m_tahoma_wide.m_tall, ctx->m_tahoma_wide.m_weight, 0, 0, ctx->m_tahoma_wide.m_flags );
		ctx->m_surface->set_font_glyph_set( ctx->m_tahoma_big.m_font = ctx->m_surface->create_font( ), ctx->m_tahoma_big.m_name, ctx->m_tahoma_big.m_tall, ctx->m_tahoma_big.m_weight, 0, 0, ctx->m_tahoma_big.m_flags );
		ctx->m_surface->set_font_glyph_set( ctx->m_tahoma_bold.m_font = ctx->m_surface->create_font( ), ctx->m_tahoma_bold.m_name, ctx->m_tahoma_bold.m_tall, ctx->m_tahoma_bold.m_weight, 0, 0, ctx->m_tahoma_bold.m_flags );
		ctx->m_surface->set_font_glyph_set( ctx->m_verdana_narrow.m_font = ctx->m_surface->create_font( ), ctx->m_verdana_narrow.m_name, ctx->m_verdana_narrow.m_tall, ctx->m_verdana_narrow.m_weight, 0, 0, ctx->m_verdana_narrow.m_flags );
		ctx->m_surface->set_font_glyph_set( ctx->m_small_fonts.m_font = ctx->m_surface->create_font( ), ctx->m_small_fonts.m_name, ctx->m_small_fonts.m_tall, ctx->m_small_fonts.m_weight, 0, 0, ctx->m_small_fonts.m_flags );
		ctx->m_surface->set_font_glyph_set( ctx->m_small_fonts_medium.m_font = ctx->m_surface->create_font( ), ctx->m_small_fonts_medium.m_name, ctx->m_small_fonts_medium.m_tall, ctx->m_small_fonts_medium.m_weight, 0, 0, ctx->m_small_fonts_medium.m_flags );
	}

	void filled_rect( int x, int y, int w, int h, const color& col ) {
		ctx->m_surface->draw_set_color( col );
		ctx->m_surface->draw_filled_rect( x, y, x + w, y + h );
	}

	void outlined_rect( int x, int y, int w, int h, const color& col ) {
		ctx->m_surface->draw_set_color( col );
		ctx->m_surface->draw_outlined_rect( x, y, x + w, y + h );
	}

	void gradient_rect( int x, int y, int w, int h, const color& col, const color& col_, bool horizontal ) {
		ctx->m_surface->draw_set_color( col );
		ctx->m_surface->draw_filled_rect_fade( x, y, x + w, y + h, 255, 0, horizontal );
		ctx->m_surface->draw_set_color( col_ );
		ctx->m_surface->draw_filled_rect_fade( x, y, x + w, y + h, 0, 255, horizontal );
	}

	void line( int x, int y, int x_, int y_, const color& col ) {
		ctx->m_surface->draw_set_color( col );
		ctx->m_surface->draw_line( x, y, x_, y_ );
	}

	/*void outlined_line( int x, int y, int x_, int y_, int outline, color col ) {
		ctx->m_surface->draw_set_color( col );
		for ( int i = 0; i < outline * 1.5f; i++ ) {
			ctx->m_surface->draw_line( x + ( 0.1f * i ), y, x_ + ( 0.1f * i ), y_ );
			ctx->m_surface->draw_line( x - ( 0.1f * i ), y, x_ - ( 0.1f * i ), y_ );
		}
		ctx->m_surface->draw_set_color( color( 0, 0, 0 ) );
		for ( int i = 0; i < outline; i++ ) {
			ctx->m_surface->draw_line( x - ( 1.5f + 0.1f * i ), y, x_ - ( 1.5f + 0.1f * i ), y_ );
		}
		for ( int i = 0; i < outline * 1.4f; i++ ) {
			ctx->m_surface->draw_line( x + ( 1.5f + 0.1f * i ), y, x_ + ( 1.5f + 0.1f * i ), y_ );
		}
	}*/

	void text( int x, int y, e_string_align align, DWORD font, const color& col, const char* str, ... ) {
		if ( !str )
			return;

		va_list va_alist;
		char cbuffer[ 1024 ] = { '\0' };
		wchar_t wstr[ 1024 ] = { '\0' };

		va_start( va_alist, str );
		vsprintf_s( cbuffer, str, va_alist );
		va_end( va_alist );

		wsprintfW( wstr, L"%hs", cbuffer );

		switch ( align ) {
			case ALIGN_DEFAULT: break;
			case ALIGN_CENTER: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				x -= ( w * 0.5f );
				y -= ( h * 0.5f );
				break;
			}

			case ALIGN_CENTERHORIZONTAL: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				x -= ( w * 0.5f );
				break;
			}

			case ALIGN_CENTERVERTICAL: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				y -= ( h * 0.5f );
				break;
			}

			case ALIGN_RIGHT: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				x -= ( w );
				break;
			}
		}

		ctx->m_surface->draw_set_text_pos( x, y );
		ctx->m_surface->draw_set_text_font( font );
		ctx->m_surface->draw_set_text_color( col );
		ctx->m_surface->draw_print_text( wstr, wcslen( wstr ) );
	}

	void text( int x, int y, e_string_align align, DWORD font, const color& col, const wchar_t* str, ... ) {
		if ( !str )
			return;

		va_list va_alist;
		wchar_t wstr[1024] = { '\0' };

		va_start( va_alist, str );
		vswprintf_s( wstr, str, va_alist );
		va_end( va_alist );

		switch ( align ) {
			case ALIGN_DEFAULT: break;
			case ALIGN_CENTER: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				x -= ( w * 0.5f );
				y -= ( h * 0.5f );
				break;
			}

			case ALIGN_CENTERHORIZONTAL: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				x -= ( w * 0.5f );
				break;
			}

			case ALIGN_CENTERVERTICAL: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				y -= ( h * 0.5f );
				break;
			}

			case ALIGN_RIGHT: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				x -= ( w );
				break;
			}
		}

		ctx->m_surface->draw_set_text_pos( x, y );
		ctx->m_surface->draw_set_text_font( font );
		ctx->m_surface->draw_set_text_color( col );
		ctx->m_surface->draw_print_text( wstr, wcslen( wstr ) );
	}

	void outlined_text( int x, int y, e_string_align align, DWORD font, const color& col, const char* str, ... ) {
		if ( !str )
			return;

		va_list va_alist;
		char cbuffer[ 1024 ] = { '\0' };
		wchar_t wstr[ 1024 ] = { '\0' };

		va_start( va_alist, str );
		vsprintf_s( cbuffer, str, va_alist );
		va_end( va_alist );

		wsprintfW( wstr, L"%hs", cbuffer );

		switch ( align ) {
			case ALIGN_DEFAULT: break;
			case ALIGN_CENTER: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				x -= ( w * 0.5f );
				y -= ( h * 0.5f );
				break;
			}

			case ALIGN_CENTERHORIZONTAL: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				x -= ( w * 0.5f );
				break;
			}

			case ALIGN_CENTERVERTICAL: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				y -= ( h * 0.5f );
				break;
			}

			case ALIGN_RIGHT: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				x -= ( w );
				break;
			}
		}

		ctx->m_surface->draw_set_text_color( color( 0, 0, 0 ) );
		ctx->m_surface->draw_set_text_font( font );
		{
			ctx->m_surface->draw_set_text_pos( x - 1, y );
			ctx->m_surface->draw_print_text( wstr, wcslen( wstr ) );

			ctx->m_surface->draw_set_text_pos( x + 1, y );
			ctx->m_surface->draw_print_text( wstr, wcslen( wstr ) );

			ctx->m_surface->draw_set_text_pos( x, y - 1 );
			ctx->m_surface->draw_print_text( wstr, wcslen( wstr ) );

			ctx->m_surface->draw_set_text_pos( x, y + 1 );
			ctx->m_surface->draw_print_text( wstr, wcslen( wstr ) );
		}
		ctx->m_surface->draw_set_text_color( col );
		ctx->m_surface->draw_set_text_pos( x, y );
		ctx->m_surface->draw_print_text( wstr, wcslen( wstr ) );
	}

	void outlined_text( int x, int y, e_string_align align, DWORD font, const color& col, const wchar_t* str, ... ) {
		if ( !str )
			return;

		va_list va_alist;
		wchar_t wstr[ 1024 ] = { '\0' };

		va_start( va_alist, str );
		vswprintf_s( wstr, str, va_alist );
		va_end( va_alist );

		switch ( align ) {
			case ALIGN_DEFAULT: break;
			case ALIGN_CENTER: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				x -= ( w * 0.5f );
				y -= ( h * 0.5f );
				break;
			}

			case ALIGN_CENTERHORIZONTAL: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				x -= ( w * 0.5f );
				break;
			}

			case ALIGN_CENTERVERTICAL: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				y -= ( h * 0.5f );
				break;
			}

			case ALIGN_RIGHT: {
				int w = 0, h = 0;
				ctx->m_surface->get_text_size( font, wstr, w, h );
				x -= ( w );
				break;
			}
		}

		ctx->m_surface->draw_set_text_color( color( 0, 0, 0 ) );
		ctx->m_surface->draw_set_text_font( font );
		{
			ctx->m_surface->draw_set_text_pos( x - 1, y );
			ctx->m_surface->draw_print_text( wstr, wcslen( wstr ) );

			ctx->m_surface->draw_set_text_pos( x + 1, y );
			ctx->m_surface->draw_print_text( wstr, wcslen( wstr ) );

			ctx->m_surface->draw_set_text_pos( x, y - 1 );
			ctx->m_surface->draw_print_text( wstr, wcslen( wstr ) );

			ctx->m_surface->draw_set_text_pos( x, y + 1 );
			ctx->m_surface->draw_print_text( wstr, wcslen( wstr ) );
		}
		ctx->m_surface->draw_set_text_color( col );
		ctx->m_surface->draw_set_text_pos( x, y );
		ctx->m_surface->draw_print_text( wstr, wcslen( wstr ) );
	}

	inline void draw_texture_rect( int x, int y, int w, int h, int id, const color& clr ) {
		ctx->m_surface->draw_set_color( clr );
		ctx->m_surface->draw_set_texture( id );
		ctx->m_surface->draw_textured_rect( x, y, x + w, y + h );
	}

	std::vector<int> texture_ids;
	inline int create_array_texture( const unsigned char* array, int w, int h ) {
		int id = ctx->m_surface->create_new_texture_id( true );
		texture_ids.push_back( id );
		ctx->m_surface->draw_set_texture_rgba_ex( id, array, w, h, IMAGE_FORMAT_RGBA8888 );
		return id;
	}

	inline void delete_textures( ) {
		for ( int id : texture_ids )
			ctx->m_surface->delete_texture_by_id( id );
	}

	inline void draw_texture_polygon( int count, vertex_t* vertices, const color& clr ) {
		static int id = ctx->m_surface->create_new_texture_id( true );

		ctx->m_surface->draw_set_color( clr );
		ctx->m_surface->draw_set_texture( id );

		ctx->m_surface->draw_textured_polygon( count, vertices );
	}
};

inline c_render* render = new c_render;