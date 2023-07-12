#pragma once
#include <array>
#include <vector>
#include "../../include/definitions.h"

class c_cheat_detection
{
public:
	void scan_players();

	struct c_suspect
	{
		int m_friends_id = 0;
		char* m_name;
		int m_strikes = 0;
		int m_fakelag_strikes = 0;
		bool m_marked = false;
		bool m_dumped = false;
		int m_next_fakelag = 0;
		int m_next_angle = 0;
		c_base_player* m_player = nullptr;
		int m_recharge_delay = 350;
		vector m_old_pos = {};
		vector m_old_velocity = {};
		vector m_old_angles = {};
		bool m_detected_thru_list = false;

		c_suspect(int m_friends_id, int m_strikes, int m_fakelag_strikes, bool m_marked, bool m_dumped, int m_next_fakelag, int m_next_angle,
			c_base_player* m_player, char* m_name, vector m_old_pos, vector m_old_velocity)
			: m_friends_id(m_friends_id), m_strikes(m_strikes), m_fakelag_strikes(m_fakelag_strikes), m_marked(m_marked), 
			m_dumped(m_dumped), m_next_fakelag(m_next_fakelag), m_next_angle(m_next_angle), m_player(m_player), m_name(m_name), m_old_pos(m_old_pos),
			m_old_velocity(m_old_velocity), m_old_angles(m_old_angles)
		{

		}

		c_suspect() = default;
	};

	std::array< c_suspect, 128u > m_suspects;
	void drop_to_file(c_suspect);

	void reset_suspects()
	{
		m_suspects.fill({});
	}

};

inline c_cheat_detection* cheat_detection = new c_cheat_detection;