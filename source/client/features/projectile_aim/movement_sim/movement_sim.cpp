#include "movement_sim.h"

#define DIST_EPSILON 0.03125f

static c_user_cmd dummy_cmd = { };

class c_player_data_backup {
private:
	vector m_origin = { };
	vector m_velocity = { };
	vector m_base_velocity = { };
	vector m_view_offset = { };
	int m_ground_entity = 0;
	int m_flags = 0;
	float m_duck_time = 0.0f;
	float m_duck_jump_time = 0.0f;
	bool m_ducked = false;
	bool m_ducking = false;
	bool m_in_duck_jump = false;
	float m_model_scale = 0.0f;

public:
	inline void store( c_base_player* player ) {
		this->m_origin = player->m_origin( );
		this->m_velocity = player->m_velocity( );
		this->m_base_velocity = player->m_base_velocity( );
		this->m_view_offset = player->m_view_offset( );
		this->m_ground_entity = player->m_ground_entity( );
		this->m_flags = player->m_flags( );
		this->m_duck_time = player->m_duck_time( );
		this->m_duck_jump_time = player->m_duck_jump_time( );
		this->m_ducked = player->m_ducked( );
		this->m_ducking = player->m_ducking( );
		this->m_in_duck_jump = player->m_in_duck_jump( );
		this->m_model_scale = player->m_model_scale( );
	}

	inline void restore( c_base_player* player ) {
		player->m_origin( ) = this->m_origin;
		player->m_velocity( ) = this->m_velocity;
		player->m_base_velocity( ) = this->m_base_velocity;
		player->m_view_offset( ) = this->m_view_offset;
		player->m_ground_entity( ) = this->m_ground_entity;
		player->m_flags( ) = this->m_flags;
		player->m_duck_time( ) = this->m_duck_time;
		player->m_duck_jump_time( ) = this->m_duck_jump_time;
		player->m_ducked( ) = this->m_ducked;
		player->m_ducking( ) = this->m_ducking;
		player->m_in_duck_jump( ) = this->m_in_duck_jump;
		player->m_model_scale( ) = this->m_model_scale;
	}
};

static c_player_data_backup player_data_backup;

bool c_movement_sim::init( c_base_player* player ) {
	if ( !player || !player->is_alive( ) )
		return false;

	m_positions.clear( );

	m_player = player;
	m_player->m_current_command( ) = &dummy_cmd;

	player_data_backup.store( m_player);

	m_old_in_prediction = ctx->m_prediction->m_in_prediction;
	m_old_first_time_predicted = ctx->m_prediction->m_first_time_predicted;
	m_old_frame_time = ctx->m_globals->m_frame_time;

	if ( player->m_flags( ) & FL_DUCKING ) {
		player->m_flags( ) &= ~FL_DUCKING;
		player->m_ducked( ) = true;
		player->m_duck_time( ) = 0.0f;
		player->m_duck_jump_time( ) = 0.0f;
		player->m_ducking( ) = false;
		player->m_in_duck_jump( ) = false;
	}

	if ( player != ctx->m_local_player )
		player->m_ground_entity( ) = 0;

	player->m_model_scale() -= DIST_EPSILON;

	if ( player->m_flags( ) & FL_ONGROUND )
		player->m_origin( ).m_z += DIST_EPSILON;

	if ( fabsf( player->m_velocity( ).m_x ) < 0.01f )
		player->m_velocity().m_x = 0.015f;

	if ( fabsf( player->m_velocity( ).m_y ) < 0.01f )
		player->m_velocity().m_y = 0.015f;

	setup_move_data( m_player, &m_move_data );
	compute_turn_speed( m_player, &m_move_data );

	if (player->m_velocity().length() > 0.f && config->m_projectile_aim.m_hitchance > ( math::remap_val_clamped( fabsf(movement_sim->m_turn_speed) , 0, player->m_flags() & FL_ONGROUND ? 1.08f : 7.5f, 100.0f, 25.0f) * math::remap_val_clamped(player->m_origin().dist_to(ctx->m_local_player->m_origin()), 450.0f, 3000.0f, 1.0f, 0.2f))) {
		restore( );
		return false;
	}

	return true;
}

void c_movement_sim::restore( ) {
	if ( !m_player )
		return;

	m_player->m_current_command( ) = nullptr;

	player_data_backup.restore( m_player );

	ctx->m_prediction->m_in_prediction = m_old_in_prediction;
	ctx->m_prediction->m_first_time_predicted = m_old_first_time_predicted;
	ctx->m_globals->m_frame_time = m_old_frame_time;

	m_player = nullptr;

	memset( &m_move_data, 0, sizeof( c_move_data ) );
	memset( &player_data_backup, 0, sizeof( c_player_data_backup ) );
}

vector c_movement_sim::run_tick( ) {
	if ( !m_player )
		return vector( );

	ctx->m_prediction->m_in_prediction = true;
	ctx->m_prediction->m_first_time_predicted = false;
	ctx->m_globals->m_frame_time = ctx->m_prediction->m_engine_paused ? 0.0f : TICK_INTERVAL;

	if ( config->m_projectile_aim.m_turn_prediction ) {
		if (m_player->m_flags() & FL_ONGROUND)
			m_move_data.m_view_angles.m_y += m_turn_speed;
		else
			m_move_data.m_view_angles.m_y = math::normalize_angle(m_move_data.m_view_angles.m_y + m_turn_speed);

		if ( !( m_player->m_flags( ) & FL_ONGROUND ) ) {
			m_move_data.m_forward_move = 0.0f;
			m_move_data.m_side_move = math::normalize_angle( m_turn_speed ) < 0.0f ? 450.0f : -450.0f;
		}

		else {
			m_move_data.m_forward_move = m_old_forward_move;
			m_move_data.m_side_move = m_old_side_move;
		}
	}

	ctx->m_game_movement->process_movement( m_player, &m_move_data );

	m_time_stamp = ctx->m_engine_client->time( );
	m_positions.emplace_back( get_origin( ) );

	return this->get_origin( );
}

void c_movement_sim::setup_move_data( c_base_player* player, c_move_data* move_data ) {
	if ( !player || !move_data )
		return;

	move_data->m_first_run_of_functions = false;
	move_data->m_game_code_moved_player = false;
	move_data->m_player_handle = player->as< i_handle_entity >( )->get_ref_e_handle( );
	move_data->m_velocity = player->m_velocity( );
	move_data->m_abs_origin = player->m_origin( );

	move_data->m_view_angles = vector( 0.0f, math::direction_to_angles( move_data->m_velocity ).m_y, 0.0f );

	auto forward = vector( ), right = vector( );
	math::angle_vectors( move_data->m_view_angles, &forward, &right, nullptr );

	move_data->m_forward_move = ( move_data->m_velocity.m_y - right.m_y / right.m_x * move_data->m_velocity.m_x ) / ( forward.m_y - right.m_y / right.m_x * forward.m_x );
	move_data->m_side_move = ( move_data->m_velocity.m_x - forward.m_x * move_data->m_forward_move ) / right.m_x;

	m_old_forward_move = move_data->m_forward_move;
	m_old_side_move = move_data->m_side_move;
}

void c_movement_sim::compute_turn_speed( c_base_player *player, c_move_data* move_data ) {
	m_turn_speed = 0.0f;
	auto compare_yaw = move_data->m_view_angles.m_y;

	for ( const auto& direction : m_directions[ player ] ) {
		m_turn_speed += math::normalize_angle( compare_yaw - math::direction_to_angles( direction ).m_y );
		compare_yaw = math::direction_to_angles( direction ).m_y;
	}

	m_turn_speed /= m_directions[ player ].size( );
	if (player->m_flags() & FL_ONGROUND)
		m_turn_speed = std::clamp(m_turn_speed / 2, -1.08f, 1.08f);
	else
		m_turn_speed = std::clamp(m_turn_speed, -7.5f, 7.5f);
}

void c_movement_sim::fill_directions( ) {
	for ( const auto& player : ctx->players ) {
		if ( !player || player->is_dormant( ) || !player->is_player( ) || !player->is_alive( ) )
			continue;

		if (m_ground_state[player] != (player->m_flags() & FL_ONGROUND))
			m_directions[player].clear();

		m_directions[ player ].push_front( player->m_velocity( ) );
		m_ground_state[ player ] = ( player->m_flags( ) & FL_ONGROUND );

		while ( m_directions[ player ].size( ) > static_cast< size_t >( TIME_TO_TICKS( config->m_projectile_aim.m_sample_time ) ) )
			m_directions[ player ].pop_back( );
	}
}

void c_movement_sim::draw_path( ) {
	if ( !config->m_projectile_aim.m_draw_prediction_path || m_positions.empty( ) || ( ctx->m_engine_client->time( ) > m_time_stamp + 5.0f ) )
		return;

	for ( auto i = 1u; i < m_positions.size( ); i++ ) {
		const auto& start = m_positions[ i - 1 ];
		const auto& end = m_positions[ i ];

		auto start_screen = vector( ), end_screen = vector( );

		if ( !tf2::world_to_screen( start, start_screen ) || !tf2::world_to_screen( end, end_screen ) )
			continue;

		auto alpha = static_cast< int >( math::remap_val_clamped( ctx->m_engine_client->time( ) - m_time_stamp, 4.0f, 5.0f, 255.0f, 0.0f ) );

		if ( ( i % 5 ) == 0 ) {
			auto rotated = math::get_rotated_position( end, math::direction_to_angles( start - end ).m_y + 90.0f, 10.0f ), rotated_screen = vector( );

			if ( !tf2::world_to_screen( rotated, rotated_screen ) )
				continue;

			render->line( start_screen.m_x, start_screen.m_y, rotated_screen.m_x, rotated_screen.m_y, color( 235, 235, 235, alpha ) );
		}

		render->line( start_screen.m_x, start_screen.m_y, end_screen.m_x, end_screen.m_y, color( 235, 65, 65, alpha ) );
	}
}