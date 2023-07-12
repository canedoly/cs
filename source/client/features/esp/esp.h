#pragma once
#include "../../include/tf2.h"

class c_esp {
public:
	void run( );

private:
	bool compute_bounding_box( c_base_entity* entity, rect_t& bounding_box );
	void render_players( );
	void render_buildings( );
	void render_worlds( );
	void render_player_arrow( c_base_player* player, color clr );

	std::array<float, 4096> player_health = { };
	std::array<float, 4096> building_health = { };
};

inline c_esp* esp = new c_esp;