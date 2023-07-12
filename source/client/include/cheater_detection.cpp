#include "util.h"
#include <wininet.h>

bool util::download_file(const std::string& url, const std::string& output_file_path) {
	HINTERNET h_internet = InternetOpenA("FireFoxMyBlackMen", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (h_internet == NULL) {
		return false;
	}

	HINTERNET h_connection = InternetOpenUrlA(h_internet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
	if (h_connection == NULL) {
		InternetCloseHandle(h_internet);
		return false;
	}

	std::ofstream output_file(output_file_path, std::ios::binary);
	if (!output_file) {
		InternetCloseHandle(h_connection);
		InternetCloseHandle(h_internet);
		return false;
	}

	constexpr int buffer_size = 4096;
	char buffer[buffer_size];
	DWORD bytes_read = 0;

	while (InternetReadFile(h_connection, buffer, buffer_size, &bytes_read) && bytes_read > 0) {
		output_file.write(buffer, bytes_read);
	}

	output_file.close();
	InternetCloseHandle(h_connection);
	InternetCloseHandle(h_internet);

	return true;
}

std::string util::download_data(const std::string& url) {
	HINTERNET hInternet = InternetOpenA("FireFox", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (hInternet == NULL) {
		return "Invalid";
	}

	HINTERNET hConnection = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
	if (hConnection == NULL) {
		InternetCloseHandle(hInternet);
		return "Invalid";
	}

	std::stringstream contentStream{};
	constexpr int bufferSize = 4096;
	char buffer[bufferSize];
	DWORD bytesRead = 0;

	while (InternetReadFile(hConnection, buffer, bufferSize, &bytesRead) && bytesRead > 0)
		contentStream.write(buffer, bytesRead);

	std::string content = contentStream.str();

	InternetCloseHandle(hConnection);
	InternetCloseHandle(hInternet);

	return content;
}