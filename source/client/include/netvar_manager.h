#pragma once
#include "definitions.h"

class c_netvar_manager {
public:
	int get_netvar( const char* class_, const char* net_var );
	int get_offset( recv_table* table, const char* net_var );
};

inline c_netvar_manager* netvar_manager = new c_netvar_manager;

#define NETVAR( _name, type, table, name ) inline type &_name( ) { \
	static int offset = netvar_manager->get_netvar( table, name ); \
	return *reinterpret_cast< type* >( reinterpret_cast< uint32_t >( this ) + offset ); \
}