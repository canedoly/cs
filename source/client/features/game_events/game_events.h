#pragma once
#include "../../include/ctx.h"

class c_game_events : public c_game_event_listener
{
public:
	void fire_game_event(c_game_event* event) override;
	void init();
	void exit();
};

inline c_game_events* game_events = new c_game_events;