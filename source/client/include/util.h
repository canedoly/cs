#pragma once

// shut up, visual studio, i do not care.
#pragma warning ( disable : 6385 )
#pragma warning ( disable : 26451 )
#pragma warning ( disable : 26495 )
#pragma warning ( disable : 26498 )
#pragma warning ( disable : 26812 )

// Define this before releasing the cheat. This removes developer only features.
//#define JW_RELEASE_BUILD

#include <windows.h>
#include <thread>
#include <chrono>
#include <cstdint>
#include <array>
#include <algorithm>
#include <string>
#include <string_view>
#include <intrin.h>
#include <map>
#include <functional>
#include <sstream>
#include <fstream>
#include <winternl.h>
#include "json.h"

#undef BOOLAPI
#undef SECURITY_FLAG_IGNORE_CERT_DATE_INVALID
#undef SECURITY_FLAG_IGNORE_CERT_CN_INVALID


#pragma comment( lib, "winhttp.lib" )
#pragma comment( lib, "Wininet.lib" )
#pragma warning ( disable : 6385 )

class color {
public:
	color( int r, int g, int b, int a = 255 ) {
		m_r = r; m_g = g; m_b = b; m_a = a;
	}

	uint8_t m_r, m_g, m_b, m_a;
};

class c_base_entity;
class vector;
class c_user_cmd;

#undef min
#undef max

namespace util {
	template < typename T >
	inline T get_virtual( void* base, const std::uint16_t index ) {
		return ( *static_cast< T** >( base ) )[ index ];
	}

	template < typename T >
	inline T get_interface( const char* module_name, const char* interface_name ) {
		typedef void* ( *create_interface_fn )( const char* name, int* return_code );

		if ( const auto module_handle = GetModuleHandleA( module_name ) ) {
			if ( const auto create_interface = reinterpret_cast< create_interface_fn >( GetProcAddress( module_handle, "CreateInterface" ) ) )
				return reinterpret_cast< T >( create_interface( interface_name, nullptr ) );
		}

		return nullptr;
	}

	template < typename T, const std::uint16_t offset = 0u >
	inline T find_signature( const char* module_name, const char* signature ) {
		if ( const auto module_handle = GetModuleHandleA( module_name ) ) {
			static auto signature_to_byte = [ ]( const char* signature ) {
				auto bytes = std::vector< int >{ };
				auto start = const_cast< char* >( signature );
				auto end = const_cast< char* >( signature ) + strlen( signature );

				for ( auto current = start; current < end; ++current ) {
					if ( *current == '?' ) {
						++current;

						if ( *current == '?' )
							++current;

						bytes.push_back( -1 );
					}

					else bytes.push_back( strtoul( current, &current, 16 ) );
				}

				return bytes;
			};

			auto dos_header = reinterpret_cast< PIMAGE_DOS_HEADER >( module_handle );
			auto nt_headers = reinterpret_cast< PIMAGE_NT_HEADERS >( reinterpret_cast< std::uint8_t* >( module_handle ) + dos_header->e_lfanew );

			auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
			auto pattern_bytes = signature_to_byte( signature );
			auto scan_bytes = reinterpret_cast< std::uint8_t* >( module_handle );

			auto s = pattern_bytes.size( );
			auto d = pattern_bytes.data( );

			for ( auto i = 0ul; i < size_of_image - s; ++i ) {
				bool found = true;

				for ( auto j = 0ul; j < s; ++j ) {
					if ( scan_bytes[ i + j ] != d[ j ] && d[ j ] != -1 ) {
						found = false;
						break;
					}
				}

				if ( found )
					return reinterpret_cast< T >( &scan_bytes[ i ] + offset );
			}
		}

		return 0;
	}

	inline std::wstring utf_to_wide( const std::string_view& str ) {
		auto count = MultiByteToWideChar( CP_UTF8, 0, str.data( ), str.length( ), NULL, 0 );
		std::wstring wstr( count, 0 );
		MultiByteToWideChar( CP_UTF8, 0, str.data(), str.length(), &wstr[ 0 ], count );
		return wstr;
	}

	inline bool is_window_in_focus( ) {
		static HWND hwGame = 0;

		while ( !hwGame ) {
			hwGame = FindWindowW( 0, ( L"Team Fortress 2" ) );
			return false;
		}

		return ( GetForegroundWindow( ) == hwGame );
	}
	
	inline bool is_debugger_present()
	{
		// windows stuff can be bypassed really easily
		PPEB peb = (PEB*)(__readfsdword(0x30)); //x86
		if (peb->BeingDebugged == 1) return true;
		return false;
	}

	std::string download_data(const std::string& url);

	bool download_file(const std::string& url, const std::string& output_file_path);

	inline std::vector<int> split_by_new_line(const std::string& content) {
		std::vector<int> numbers;
		std::istringstream iss(content);

		std::string line;
		while (std::getline(iss, line)) {
			numbers.push_back(std::stoi(line));
		}

		return numbers;
	}

	inline std::vector< unsigned long long > m_downloaded_cheater_list = { 76561199109258156, 76561198886202948, 76561198181758350 };

	inline void extract_steam_ids_from_json(const std::string& path_to_file) {

		std::ifstream file(path_to_file);
		if (!file.is_open()) {
			return;
		}

		Json::Value root;
		Json::CharReaderBuilder builder;
		std::string errs;

		if (!Json::parseFromStream(builder, file, &root, &errs)) {
			file.close();
			return;
		}

		file.close();

		// this is stupid
		root = root["players"];
		for (const Json::Value& item : root) {
			util::m_downloaded_cheater_list.emplace_back(item["steamid"].asLargestUInt());
		}
	}

	inline void download_cheater_list()
	{
		std::vector<std::string> urls = {
			"https://trusted.roto.lol/v1/steamids",
		};

		for (size_t i = 1; i < urls.size(); i++)
		{
			std::string output = "Player" + std::to_string(i) + ".txt";
			if (download_file(urls[i], output))
			{
				if (i == 1)
				{
					extract_steam_ids_from_json(output);
				}
				else
				{
					std::ifstream input_file(output);
					if (input_file)
					{
						std::string file_content((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
						input_file.close();

						std::vector<int> numbers = split_by_new_line(file_content);

						for (int number : numbers) {
							m_downloaded_cheater_list.push_back(0x0110000100000000ULL + number);
						}
					}
				}
				std::remove(output.c_str()); // delete the file, we dont need it
			}
		}
	}
}
