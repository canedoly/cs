#pragma once
#include "../../include/tf2.h"
#include "../backtrack/backtrack.h"

class c_melee
{
private:
	struct c_target
	{
		 float m_dst = 0.f;
		 int m_priority = 0;
		 c_backtrack::backtrack_record_t m_record;
		 c_base_player* m_player = {};
	};

	c_target best_target = {};
	bool can_backstab(const vector& source, const vector& destination, vector wsc_delta);

public:
	void run(c_user_cmd* cmd);
};

inline c_melee* melee = new c_melee;