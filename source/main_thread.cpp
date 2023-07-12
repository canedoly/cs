#include "client/client.h"

__forceinline DWORD __stdcall main_thread( _In_ LPVOID parameters ) {
	client->attach( );

#ifndef JW_RELEASE_BUILD
	while (!client->m_unauthorized && !config->m_settings.m_detach_key.is_held())
		std::this_thread::sleep_for(std::chrono::milliseconds(175));
#else
	while (!client->m_unauthorized)
		std::this_thread::sleep_for(std::chrono::milliseconds(175));
#endif

	client->detach( );
	FreeLibraryAndExitThread( static_cast< HMODULE >( parameters ), EXIT_SUCCESS );
}

BOOL __stdcall DllMain( _In_ HINSTANCE dll_instance, _In_ DWORD reason_for_call, _In_ LPVOID reserved ) {
	DisableThreadLibraryCalls( dll_instance );

	if ( reason_for_call == DLL_PROCESS_ATTACH ) {
		if ( const auto thread_handle = CreateThread( nullptr, 0, main_thread, dll_instance, 0, nullptr ) )
			CloseHandle( thread_handle );
	}

	return TRUE;
}