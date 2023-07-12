#include "input.h"

bool c_input::in_area( int x, int y, int w, int h )
{
	if ( mouse_x >= x && mouse_x <= x + w && mouse_y >= y && mouse_y <= y + h )
	{
		return true;
	}

	return false;
}

void c_input::update( )
{
	for ( int n = 0; n < 256; n++ )
	{
		if ( GetKeyState( n ) & 0x8000 )
		{
			if ( keys[ n ] == PRESSED )
				keys[ n ] = HELD;

			else if ( keys[ n ] != HELD )
				keys[ n ] = PRESSED;
		}

		else keys[ n ] = NONE;
	}

	ctx->m_surface->get_cursor_pos( mouse_x, mouse_y );
}

bool c_input::is_pressed( short key )
{
	if ( prevent_inputs )
	{
		return false;

	}

	return ( keys[ key ] == PRESSED );
}

bool c_input::is_held( short key )
{
	return ( keys[ key ] == HELD );
}

#include <chrono>

bool c_input::is_pressed_and_held( short key )
{
	key_state_e key_state = keys[ key ];

	static std::chrono::time_point<std::chrono::steady_clock> start[ 256 ] = { std::chrono::steady_clock::now( ) };

	if ( key_state == PRESSED )
	{
		start[ key ] = std::chrono::steady_clock::now( );
		return true;
	}

	if ( key_state == HELD && std::chrono::duration_cast< std::chrono::milliseconds >(
		std::chrono::steady_clock::now( ) - start[ key ] ).count( ) > 400 )
		return true;

	return false;
}

void c_input::drag( int& x, int& y, int w, int h, int offsety )
{
	static POINT delta;
	static bool drag = false;
	static bool move = false;
	bool held = is_held( VK_LBUTTON );
	bool pressed = is_pressed( VK_LBUTTON );

	auto mousex = mouse_x;
	auto mousey = mouse_y;

	if ( ( mousex > x && mousex < x + w && mousey > y - offsety && mousey < y - offsety + h ) )
	{
		if ( pressed ) {
			ctx->m_surface->play_sound( "ui/buttonclick.wav" );
		}
		else if ( held ) {
			drag = true;

			if ( !move )
			{
				delta.x = mousex - x;
				delta.y = mousey - y;
				move = true;
			}
		}
	}

	if ( drag )
	{
		x = std::clamp( mousex - ( int )delta.x, 0, ctx->m_screen_width - 457 );
		y = std::clamp( mousey - ( int )delta.y, 0, ctx->m_screen_height - 451 );
	}

	if ( !held )
	{
		drag = false;
		move = false;
	}
}

bool c_input::area_pressed( int x, int y, int w, int h )
{
	static POINT delta;
	static bool heldInArea = false;
	bool held = is_held( VK_LBUTTON );

	auto mousex = mouse_x;
	auto mousey = mouse_y;

	if ( ( mousex > x && mousex < x + w && mousey > y && mousey < y + h ) && held )
	{
		heldInArea = true;
	}

	if ( !held )
	{
		heldInArea = false;
	}

	return heldInArea;
}

void c_input::null_key( short key )
{
	keys[ key ] = key_state_e::NONE;
}

bool c_input::in_focus( )
{
	static HWND hwGame = 0;

	while ( !hwGame )
	{
		hwGame = FindWindowA( 0, "Team Fortress 2" );
		return false;
	}

	return ( GetForegroundWindow( ) == hwGame );
}