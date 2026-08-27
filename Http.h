#pragma once
#include <string>
#include <functional>
#include <cstdint>

// Minimal HTTPS client built on WinHTTP. SFML's sf::Http speaks plain HTTP only,
// so GitHub (HTTPS-only) is unreachable through it.
namespace Http
{
	// Called while the body is being received. Total is 0 when the server sends no
	// Content-Length. Return false to abort the transfer.
	using ProgressCallback = std::function<bool(uint64_t Downloaded, uint64_t Total)>;

	bool Get(const std::wstring& Url, std::string& OutBody, std::string& OutError);
	bool DownloadToFile(const std::wstring& Url, const std::wstring& DestinationPath, const ProgressCallback& Progress, std::string& OutError);

	// True when the last failure was caused by the progress callback returning false.
	bool WasAborted(const std::string& Error);
}
