#pragma once
#include "../../../include/ctx.h"

class c_input
{
public:
	enum key_state_e { NONE, PRESSED, HELD };
	key_state_e keys[ 256 ];

	int mouse_x, mouse_y; // Mouse X/Y

	bool prevent_inputs = false;
	char key_pressed = 0x0;
	int scroll = 0;
	bool hovered = false;

	void update( );
	void null_key( short key );
	bool is_pressed( short key );
	bool is_held( short key );
	bool is_pressed_and_held( short key );
	void drag( int& x, int& y, int w, int h, int offsetY );
	bool area_pressed( int x, int y, int w, int h );
	bool in_area( int x, int y, int w, int h );
	bool in_focus( );
};
inline c_input* input = new c_input;