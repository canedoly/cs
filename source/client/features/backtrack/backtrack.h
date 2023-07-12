#pragma once
#include "../../include/tf2.h"
#include <deque>

class c_backtrack
{
public:

	struct backtrack_record_t
	{
		vector m_origin = {};
		vector m_angles = {};
		vector m_mins = {};
		vector m_maxs = {};
		vector m_velocity = {};
		vector m_world_space_center = {};
		matrix_3x4 m_bones[128] = {};
		model_t* m_model = nullptr;

		float m_simulation_time = 0.f;
		float m_cycle = 0.f;

		bool m_is_breaking_lagcomp = false;
		int m_choked_packets = 0;
		bool m_is_fake_lagging = false;

		backtrack_record_t() = default;
	};

	struct seq
	{
		int m_reliable;
		int m_sequence;
		float m_servertime;
	};
	std::deque<seq> sequences;

	bool is_tick_valid(float simulation_time);
	void save_lag_comp();
	void update_sequences();
	void add_latency(void* netchan, float latency);
	c_backtrack::backtrack_record_t best_last_tick(int ent_idx);
	c_backtrack::backtrack_record_t best_first_tick(int ent_idx);
	std::deque<backtrack_record_t> m_records[65] = {};

};

inline c_backtrack* backtrack = new c_backtrack;