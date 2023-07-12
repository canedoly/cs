#pragma once
#include "../../include/tf2.h"
#include "../backtrack/backtrack.h"

struct shot_info_t {
	vector m_pos = { };
	c_base_entity* m_entity = nullptr;
	bool m_found = false;
	bool m_require_scope = false;
	bool m_headshot = false;
	float m_sim_time = -1.f;
	int m_choked_packets = 0;
	c_backtrack::backtrack_record_t record;

	shot_info_t(const vector& m_pos, c_base_entity* m_entity, bool m_found, bool m_require_scope, bool m_headshot, float m_sim_time, int m_choked_packets, const c_backtrack::backtrack_record_t& record)
		: m_pos(m_pos), m_entity(m_entity), m_found(m_found), m_require_scope(m_require_scope), m_headshot(m_headshot), m_sim_time(m_sim_time), m_choked_packets(m_choked_packets), record(record)
	{
	}

	shot_info_t() = default;
};

class c_hitscan {
public:
	void run( c_user_cmd* cmd );
	c_base_player* closest_to_crosshair = nullptr;
private:
	struct target_t {
		c_base_entity* m_entity = nullptr;
		float m_fov = 0.0f;
		float m_distance = 0.f;
		int m_priority = 0;
	};

	std::vector<c_hitscan::target_t> get_best_targets();
	std::vector<vector> generate_points_for_hitbox(c_base_player* player, int hitbox, matrix_3x4* backtrack_matrix, model_t* model);
	shot_info_t handle_hvh_classes( target_t target );
	shot_info_t handle_headshot_weapons( target_t target );
	shot_info_t handle_other( target_t target );
	shot_info_t handle_buildings(target_t target);
	void handle_tap_fire( shot_info_t info, c_user_cmd* cmd );
};

inline c_hitscan* hitscan = new c_hitscan;