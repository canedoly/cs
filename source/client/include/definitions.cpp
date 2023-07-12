#include "entities.h"
#include "ctx.h"

#define NETMSG_TYPE_BITS 6
#define NUM_NEW_COMMAND_BITS 4
#define NUM_BACKUP_COMMAND_BITS 3

const char* clc_move::to_string( void ) const {
    return "CLC_Move";
}

bool clc_move::write_to_buffer( bf_write& buffer ) {
    buffer.WriteUBitLong( get_type( ), NETMSG_TYPE_BITS);
    m_length = m_data_out.GetNumBitsWritten( );

    buffer.WriteUBitLong(m_new_commands, NUM_NEW_COMMAND_BITS );
    buffer.WriteUBitLong(m_backup_commands, NUM_BACKUP_COMMAND_BITS );

    buffer.WriteWord( m_length );

    return buffer.WriteBits( m_data_out.GetData( ), m_length );
}

bool clc_move::read_from_buffer( bf_read& buffer ) {
    m_new_commands = buffer.ReadUBitLong( NUM_NEW_COMMAND_BITS );
    m_backup_commands = buffer.ReadUBitLong( NUM_BACKUP_COMMAND_BITS );
    m_length = buffer.ReadWord( );
    m_data_in = buffer;
    return buffer.SeekRelative( m_length );
}

bool net_stringcmd::write_to_buffer( bf_write& buffer )
{
	buffer.WriteUBitLong( get_type( ), 6 );
	return buffer.WriteString( m_command ? m_command : " NET_StringCmd NULL" );
}

bool net_stringcmd::read_from_buffer( bf_read& buffer )
{
	m_command = m_command_buffer;
	return buffer.ReadString( m_command_buffer, sizeof( m_command_buffer ) );
}

const char* net_stringcmd::to_string( void ) const
{
	return "STRINGCMD";
}

bool c_trace_filter_hitscan::should_hit_entity( i_handle_entity* server_entity, int contents_mask ) {
	auto entity = reinterpret_cast< i_client_entity* >( server_entity );

	switch ( entity->get_client_class( )->m_class_id ) {
		case class_id_t::CFuncAreaPortalWindow:
		case class_id_t::CFuncRespawnRoomVisualizer:
		case class_id_t::CSniperDot: return false;
		default: return ( entity != this->m_skip );
	}
}

#include <stringapiset.h>
#include <string>

#pragma warning (disable : 6031)
#pragma warning (disable : 4244)

#define Q_ARRAYSIZE(A) (sizeof(A)/sizeof((A)[0]))

int UnicodeToUTF8( const wchar_t* unicode, char* ansi, int ansiBufferSize )
{
	int result = WideCharToMultiByte( CP_UTF8, 0, unicode, -1, ansi, ansiBufferSize, NULL, NULL );
	ansi[ ansiBufferSize - 1 ] = 0;
	return result;
}

int UTF8ToUnicode( const char* ansi, wchar_t* unicode, int unicodeBufferSizeInBytes )
{
	int chars = MultiByteToWideChar( CP_UTF8, 0, ansi, -1, unicode, unicodeBufferSizeInBytes / sizeof( wchar_t ) );
	unicode[ ( unicodeBufferSizeInBytes / sizeof( wchar_t ) ) - 1 ] = 0;
	return chars;
}

bool key_values::load_from_buffer( char const* resource_name, const char* buffer, void* file_system, const char* path_id )
{
	static auto FN = util::find_signature<DWORD>( "client.dll", "55 8B EC 83 EC 38 53 8B 5D 0C" );
	return reinterpret_cast< int( __thiscall* )( key_values*, char const*, const char*, void*, const char* ) >( FN )( this, resource_name, buffer, file_system, path_id );
}

void key_values::initialize( char* name )
{
	static auto FN = util::find_signature<DWORD>( "engine.dll", "FF 15 ? ? ? ? 83 C4 08 89 06 8B C6" ) - 0x42;
	reinterpret_cast< key_values* ( __thiscall* )( key_values*, char* ) >( FN )( this, name );
}

key_values::key_values( const char* name )
{
	char _name[ 128 ];
	sprintf_s( _name, sizeof( _name ), name );
	this->initialize( ( char* )_name );
}

key_values* key_values::find_key( const char* keyName, bool bCreate )
{
	static auto FN = util::find_signature<DWORD>( "client.dll", "55 8B EC 81 EC ? ? ? ? 56 8B 75 08 57 8B F9 85 F6 0F 84 ? ? ? ? 80 3E 00 0F 84" );
	return reinterpret_cast< key_values * ( __thiscall* )( key_values*, const char*, bool ) >( FN )( this, keyName, bCreate );
}


int key_values::get_int( const char* keyName, int defaultValue )
{
	key_values* dat = find_key( keyName, false );
	if ( dat )
	{
		switch ( dat->m_data_type )
		{
			case TYPE_STRING:
				return atoi( dat->m_char );
			case TYPE_WSTRING:
				return _wtoi( dat->m_wchar );
			case TYPE_FLOAT:
				return ( int )dat->m_float;
			case TYPE_UINT64:
				return 0;
			case TYPE_INT:
			case TYPE_PTR:
			default:
				return dat->m_int;
		};
	}
	return defaultValue;
}

unsigned long long key_values::get_uint64( const char* keyName, unsigned long long defaultValue )
{
	key_values* dat = find_key( keyName, false );
	if ( dat )
	{
		switch ( dat->m_data_type )
		{
			case TYPE_STRING:
				return ( unsigned long long )_atoi64( dat->m_char );
			case TYPE_WSTRING:
				return _wtoi64( dat->m_wchar );
			case TYPE_FLOAT:
				return ( int )dat->m_float;
			case TYPE_UINT64:
				return *( ( unsigned long long* )dat->m_char );
			case TYPE_INT:
			case TYPE_PTR:
			default:
				return dat->m_int;
		};
	}
	return defaultValue;
}

float key_values::get_float( const char* keyName, float defaultValue )
{
	key_values* dat = find_key( keyName, false );
	if ( dat )
	{
		switch ( dat->m_data_type )
		{
			case TYPE_STRING:
				return ( float )atof( dat->m_char );
			case TYPE_WSTRING:
				return ( float )_wtof( dat->m_wchar );
			case TYPE_FLOAT:
				return dat->m_float;
			case TYPE_INT:
				return ( float )dat->m_int;
			case TYPE_UINT64:
				return ( float )( *( ( unsigned long long* )dat->m_char ) );
			case TYPE_PTR:
			default:
				return 0.0f;
		};
	}
	return defaultValue;
}

const char* key_values::get_string( const char* keyName, const char* defaultValue )
{
	key_values* dat = find_key( keyName, false );
	if ( dat )
	{
		char buf[ 64 ];
		switch ( dat->m_data_type )
		{
			case TYPE_FLOAT:
				snprintf( buf, sizeof( buf ), "%f", dat->m_float );
				set_string( keyName, buf );
				break;
			case TYPE_PTR:
				snprintf( buf, sizeof( buf ), "%lld", ( int64_t )( size_t )dat->m_void );
				set_string( keyName, buf );
				break;
			case TYPE_INT:
				snprintf( buf, sizeof( buf ), "%d", dat->m_int );
				set_string( keyName, buf );
				break;
			case TYPE_UINT64:
				snprintf( buf, sizeof( buf ), "%lld", *( ( unsigned long long* )( dat->m_char ) ) );
				set_string( keyName, buf );
				break;
			case TYPE_WSTRING:
			{
				char wideBuf[ 512 ];
				int result = UnicodeToUTF8( dat->m_wchar, wideBuf, 512 );
				if ( result )
				{
					set_string( keyName, wideBuf );
				}
				else
				{
					return defaultValue;
				}
				break;
			}
			case TYPE_STRING:
				break;
			default:
				return defaultValue;
		};

		return dat->m_char;
	}
	return defaultValue;
}

const wchar_t* key_values::get_wstring( const char* keyName, const wchar_t* defaultValue )
{
	key_values* dat = find_key( keyName, false );
	if ( dat )
	{
		wchar_t wbuf[ 64 ];
		switch ( dat->m_data_type )
		{
			case TYPE_FLOAT:
				swprintf( wbuf, Q_ARRAYSIZE( wbuf ), L"%f", dat->m_float );
				set_wstring( keyName, wbuf );
				break;
			case TYPE_PTR:
				swprintf( wbuf, Q_ARRAYSIZE( wbuf ), L"%lld", ( int64_t )( size_t )dat->m_void );
				set_wstring( keyName, wbuf );
				break;
			case TYPE_INT:
				swprintf( wbuf, Q_ARRAYSIZE( wbuf ), L"%d", dat->m_int );
				set_wstring( keyName, wbuf );
				break;
			case TYPE_UINT64:
			{
				swprintf( wbuf, Q_ARRAYSIZE( wbuf ), L"%lld", *( ( unsigned long long* )( dat->m_char ) ) );
				set_wstring( keyName, wbuf );
			}
			break;

			case TYPE_WSTRING:
				break;
			case TYPE_STRING:
			{
				int bufSize = strlen( dat->m_char ) + 1;
				wchar_t* pWBuf = new wchar_t[ bufSize ];
				int result = UTF8ToUnicode( dat->m_char, pWBuf, bufSize * sizeof( wchar_t ) );
				if ( result >= 0 )
				{
					set_wstring( keyName, pWBuf );
				}
				else
				{
					delete[ ] pWBuf;
					return defaultValue;
				}
				delete[ ] pWBuf;
				break;
			}
			default:
				return defaultValue;
		};

		return ( const wchar_t* )dat->m_wchar;
	}
	return defaultValue;
}

void* key_values::get_ptr( const char* keyName, void* defaultValue )
{
	key_values* dat = find_key( keyName, false );
	if ( dat )
	{
		switch ( dat->m_data_type )
		{
			case TYPE_PTR:
				return dat->m_void;

			case TYPE_WSTRING:
			case TYPE_STRING:
			case TYPE_FLOAT:
			case TYPE_INT:
			case TYPE_UINT64:
			default:
				return NULL;
		};
	}
	return defaultValue;
}

bool key_values::get_bool( const char* keyName, bool defaultValue )
{
	if ( find_key( keyName ) )
	{
		/*if (optGotDefault)
			(*optGotDefault) = false;*/

		return 0 != get_int( keyName, 0 );
	}

	/*if (optGotDefault)
		(*optGotDefault) = true;*/

	return defaultValue;
}

color key_values::get_color( const char* keyName )
{
	color color{ 0, 0, 0, 0 };
	key_values* dat = find_key( keyName, false );
	if ( dat )
	{
		if ( dat->m_data_type == TYPE_COLOR )
		{
			color.m_r = dat->m_color[ 0 ];
			color.m_g = dat->m_color[ 1 ];
			color.m_b = dat->m_color[ 2 ];
			color.m_a = dat->m_color[ 3 ];
		}
		else if ( dat->m_data_type == TYPE_FLOAT )
		{
			color.m_r = dat->m_float;
		}
		else if ( dat->m_data_type == TYPE_INT )
		{
			color.m_r = dat->m_int;
		}
		else if ( dat->m_data_type == TYPE_STRING )
		{
			float a = 0.0f, b = 0.0f, c = 0.0f, d = 0.0f;
			sscanf_s( dat->m_char, "%f %f %f %f", &a, &b, &c, &d );
			color.m_r = ( unsigned char )a;
			color.m_g = ( unsigned char )b;
			color.m_b = ( unsigned char )c;
			color.m_a = ( unsigned char )d;
		}
	}
	return color;
}

const char* key_values::get_name( )
{
	static auto FN = reinterpret_cast< const char* ( __thiscall* )( key_values* ) >( util::find_signature<DWORD>( "client.dll", "FF 31 FF 15 ? ? ? ? 83 C4" ) );
	return FN( this );
}

bool key_values::is_empty( const char* keyName )
{
	key_values* dat = find_key( keyName, false );
	if ( !dat )
		return true;

	if ( dat->m_data_type == TYPE_NONE && dat->m_sub == NULL )
		return true;

	return false;
}


void key_values::set_wstring( const char* keyName, const wchar_t* value )
{
	key_values* dat = find_key( keyName, true );
	if ( dat )
	{
		delete[ ] dat->m_wchar;
		delete[ ] dat->m_char;
		dat->m_char = NULL;

		if ( !value )
		{
			value = L"";
		}

		int len = wcslen( value );
		dat->m_wchar = new wchar_t[ len + 1 ];
		memcpy( dat->m_wchar, value, ( len + 1 ) * sizeof( wchar_t ) );

		dat->m_data_type = TYPE_WSTRING;
	}
}

void key_values::set_string( const char* keyName, const char* value )
{
	key_values* dat = find_key( keyName, true );

	if ( dat )
	{
		if ( dat->m_data_type == TYPE_STRING && dat->m_char == value )
		{
			return;
		}

		delete[ ] dat->m_char;
		delete[ ] dat->m_wchar;
		dat->m_wchar = NULL;

		if ( !value )
		{
			value = "";
		}

		int len = strlen( value );
		dat->m_char = new char[ len + 1 ];
		memcpy( dat->m_char, value, len + 1 );

		dat->m_data_type = TYPE_STRING;
	}
}

void key_values::set_int( const char* keyName, int value )
{
	key_values* dat = find_key( keyName, true );

	if ( dat )
	{
		dat->m_int = value;
		dat->m_data_type = TYPE_INT;
	}
}

void key_values::set_uint64( const char* keyName, unsigned long long value )
{
	key_values* dat = find_key( keyName, true );

	if ( dat )
	{
		delete[ ] dat->m_char;
		delete[ ] dat->m_wchar;
		dat->m_wchar = NULL;

		dat->m_char = new char[ sizeof( unsigned long long ) ];
		*( ( unsigned long long* )dat->m_char ) = value;
		dat->m_data_type = TYPE_UINT64;
	}
}

void key_values::set_float( const char* keyName, float value )
{
	key_values* dat = find_key( keyName, true );

	if ( dat )
	{
		dat->m_float = value;
		dat->m_data_type = TYPE_FLOAT;
	}
}

void key_values::set_ptr( const char* keyName, void* value )
{
	key_values* dat = find_key( keyName, true );

	if ( dat )
	{
		dat->m_void = value;
		dat->m_data_type = TYPE_PTR;
	}
}

void key_values::set_color( const char* keyName, color value )
{
	key_values* dat = find_key( keyName, true );

	if ( dat )
	{
		dat->m_data_type = TYPE_COLOR;
		dat->m_color[ 0 ] = value.m_r;
		dat->m_color[ 1 ] = value.m_g;
		dat->m_color[ 2 ] = value.m_b;
		dat->m_color[ 3 ] = value.m_a;
	}
}