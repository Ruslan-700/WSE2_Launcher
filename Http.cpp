#include "Http.h"
#include <windows.h>
#include <winhttp.h>
#include <fstream>
#include <vector>
#pragma comment(lib, "winhttp.lib")

#define HTTP_ABORTED_ERROR "aborted"

namespace
{
	struct Handle
	{
		HINTERNET Value = nullptr;
		~Handle() { if (Value) WinHttpCloseHandle(Value); }
		operator HINTERNET() const { return Value; }
	};

	std::string DescribeLastError(const char* Stage)
	{
		return std::string(Stage) + " failed (WinHTTP error " + std::to_string(GetLastError()) + ")";
	}

	// Receives the response body in chunks; returning false aborts the transfer.
	using SinkCallback = std::function<bool(const char* Data, unsigned long Size)>;

	bool Receive(const std::wstring& Url, const SinkCallback& Sink, const Http::ProgressCallback& Progress, std::string& OutError)
	{
		WCHAR HostName[256] = L"", UrlPath[2048] = L"", ExtraInfo[2048] = L"";
		URL_COMPONENTS Components = {};
		Components.dwStructSize = sizeof(Components);
		Components.lpszHostName = HostName;
		Components.dwHostNameLength = ARRAYSIZE(HostName);
		Components.lpszUrlPath = UrlPath;
		Components.dwUrlPathLength = ARRAYSIZE(UrlPath);
		Components.lpszExtraInfo = ExtraInfo;
		Components.dwExtraInfoLength = ARRAYSIZE(ExtraInfo);
		if (!WinHttpCrackUrl(Url.c_str(), 0, 0, &Components)) { OutError = DescribeLastError("WinHttpCrackUrl"); return false; }

		Handle Session;
		Session.Value = WinHttpOpen(L"WSE2Launcher", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
		if (!Session) { OutError = DescribeLastError("WinHttpOpen"); return false; }

		// Older systems still default to TLS 1.0, which GitHub refuses.
		DWORD SecureProtocols = WINHTTP_FLAG_SECURE_PROTOCOL_TLS1 | WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_1 | WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_2;
		WinHttpSetOption(Session, WINHTTP_OPTION_SECURE_PROTOCOLS, &SecureProtocols, sizeof(SecureProtocols));
		WinHttpSetTimeouts(Session, 15000, 15000, 30000, 30000);

		Handle Connection;
		Connection.Value = WinHttpConnect(Session, HostName, Components.nPort, 0);
		if (!Connection) { OutError = DescribeLastError("WinHttpConnect"); return false; }

		std::wstring Target = UrlPath;
		Target += ExtraInfo;
		DWORD RequestFlags = (Components.nScheme == INTERNET_SCHEME_HTTPS) ? WINHTTP_FLAG_SECURE : 0;
		Handle Request;
		Request.Value = WinHttpOpenRequest(Connection, L"GET", Target.c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, RequestFlags);
		if (!Request) { OutError = DescribeLastError("WinHttpOpenRequest"); return false; }

		WinHttpAddRequestHeaders(Request, L"Accept: application/vnd.github+json\r\n", (DWORD)-1, WINHTTP_ADDREQ_FLAG_ADD);

		if (!WinHttpSendRequest(Request, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) { OutError = DescribeLastError("WinHttpSendRequest"); return false; }
		if (!WinHttpReceiveResponse(Request, NULL)) { OutError = DescribeLastError("WinHttpReceiveResponse"); return false; }

		DWORD StatusCode = 0, StatusCodeSize = sizeof(StatusCode);
		if (!WinHttpQueryHeaders(Request, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &StatusCode, &StatusCodeSize, WINHTTP_NO_HEADER_INDEX)) { OutError = DescribeLastError("WinHttpQueryHeaders"); return false; }
		if (StatusCode != 200) { OutError = "server answered HTTP " + std::to_string(StatusCode); return false; }

		uint64_t TotalSize = 0;
		WCHAR ContentLength[32] = L"";
		DWORD ContentLengthSize = sizeof(ContentLength);
		if (WinHttpQueryHeaders(Request, WINHTTP_QUERY_CONTENT_LENGTH, WINHTTP_HEADER_NAME_BY_INDEX, ContentLength, &ContentLengthSize, WINHTTP_NO_HEADER_INDEX))
			TotalSize = _wcstoui64(ContentLength, nullptr, 10);

		std::vector<char> Buffer(64 * 1024);
		uint64_t Downloaded = 0;
		if (Progress && !Progress(0, TotalSize)) { OutError = HTTP_ABORTED_ERROR; return false; }
		for (;;) {
			DWORD BytesRead = 0;
			if (!WinHttpReadData(Request, Buffer.data(), (DWORD)Buffer.size(), &BytesRead)) { OutError = DescribeLastError("WinHttpReadData"); return false; }
			if (BytesRead == 0) break;
			if (!Sink(Buffer.data(), BytesRead)) { OutError = "could not write the downloaded data"; return false; }
			Downloaded += BytesRead;
			if (Progress && !Progress(Downloaded, TotalSize)) { OutError = HTTP_ABORTED_ERROR; return false; }
		}
		if (TotalSize != 0 && Downloaded != TotalSize) { OutError = "connection closed before the whole file was received"; return false; }

		return true;
	}
}

bool Http::Get(const std::wstring& Url, std::string& OutBody, std::string& OutError)
{
	OutBody.clear();
	return Receive(Url, [&OutBody](const char* Data, unsigned long Size) { OutBody.append(Data, Size); return true; }, nullptr, OutError);
}

bool Http::DownloadToFile(const std::wstring& Url, const std::wstring& DestinationPath, const ProgressCallback& Progress, std::string& OutError)
{
	std::ofstream File(DestinationPath, std::ios::binary | std::ios::trunc);
	if (!File.good()) { OutError = "could not create the temporary file"; return false; }

	bool Result = Receive(Url, [&File](const char* Data, unsigned long Size) { File.write(Data, Size); return File.good(); }, Progress, OutError);
	File.close();
	if (!Result) DeleteFileW(DestinationPath.c_str());
	return Result;
}

bool Http::WasAborted(const std::string& Error)
{
	return Error == HTTP_ABORTED_ERROR;
}
