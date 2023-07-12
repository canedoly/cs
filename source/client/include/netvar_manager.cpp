#include "netvar_manager.h"
#include "ctx.h"

int c_netvar_manager::get_netvar( const char* class_, const char* net_var ) {
	auto classes = ctx->m_client->get_all_classes( );

	for ( auto current_node = classes; current_node; current_node = current_node->m_next ) {
		if ( std::string_view( class_ ).compare( current_node->m_network_name ) == 0 )
			return this->get_offset( current_node->m_recv_table, net_var );
	}

	return 0;
}

int c_netvar_manager::get_offset( recv_table* table, const char* net_var ) {
	for ( int i = 0; i < table->m_props_count; i++ ) {
		auto prop = table->m_props[ i ];

		if ( std::string_view( prop.m_prop_name ).compare( net_var ) == 0 )
			return prop.m_offset;

		if ( auto data_table = prop.m_data_table ) {
			if ( auto offset = this->get_offset( data_table, net_var ) )
				return offset + prop.m_offset;
		}
	}

	return 0;
}