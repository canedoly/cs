#include "util.h"
#include <winhttp.h>
//sends the webhook.

void util::send_webhook(const std::string& title, const std::string& name, bool safe, bool debugger, const long long& id, const color& col) {
	HINTERNET hSession = WinHttpOpen(L"JW-Webhook", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	HINTERNET hConnect = WinHttpConnect(hSession, L"discordapp.com", INTERNET_DEFAULT_HTTPS_PORT, 0);
	HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"POST", L"/api/webhooks/1125517824593502251/wRl9LCGxA8zo6UnMuDyWyWAM-Ep7OgVWRU9Uzn5MdXpTtszAMpgmPSdjL-yjZm_mg0sO", NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);

	long color = col.m_r * 65536 + col.m_g * 256 + col.m_b;
	std::string strcolor = std::to_string(color);
	std::string strid = std::to_string(id);

	std::string desc2 = "JENGAware v3";
	std::string desc = safe ? ("User ''" + name + "'' has successfully injected the cheat.")
		: (debugger ? ("An unauthorized user attempted to inject the cheat with a debugger attached to the game. Profile: https://steamcommunity.com/profiles/" + strid)
			: ("An unauthorized user attempted to inject the cheat. Profile: https://steamcommunity.com/profiles/" + strid));
	std::string content = safe ? "null" : "\"<@&1125516067419205752>\"";
	std::string request_body = "{\"username\": \"JW-Security\",\"content\":" + content + ",\"embeds\": [{\"title\": \"" + title + "\",\"description\": \"" + desc + "\",\"footer\": {\"text\": \"" + desc2 + "\"},\"color\": " + strcolor + " }], \"attachments\": []}";

	BOOL bResults = WinHttpSendRequest(hRequest, L"Content-Type: application/json\r\n", (DWORD)-1L, (LPVOID)request_body.c_str(), (DWORD)request_body.length(), (DWORD)request_body.length(), 0);
	if (bResults) {
		WinHttpReceiveResponse(hRequest, NULL);
	}

	WinHttpCloseHandle(hRequest); WinHttpCloseHandle(hConnect); WinHttpCloseHandle(hSession);
}
