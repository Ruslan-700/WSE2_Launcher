#include "Engine.h"
#include <filesystem>

void Class_Engine::FTPThread()
{
	if (CurentAppdataPath[0] == '\0') return;
	sf::Ftp::Response ConnectionResponse, LoginResponse, FileResponse, AliveResponse;
	ConnectionResponse = FTP.connect(FTP_ADDRESS, FTP_PORT, sf::seconds(10));
	if (!ConnectionResponse.isOk()) return;
	LoginResponse = FTP.login(FTP_LOGIN, "");
	if (!LoginResponse.isOk()) return;
	FileResponse = FTP.download("/version.txt", std::string(CurentAppdataPath) + u8"\\" + MB_NAME);
	if (!FileResponse.isOk()) return;
	std::ifstream File_version(std::string(CurentAppdataPath) + MB_VERSION);
	std::string Line = "";
	std::wstring FTP_Version = L"";
	if (File_version.good())
	{
		try { std::getline(File_version, Line); } catch (const std::exception& Exception) { DisplayErrorMessageMain("Error (unhandled exception in FTPThread) - ''" + std::string(Exception.what()) + "''. "); return; }
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> Converter;
		FTP_Version = Converter.from_bytes(Line);
		File_version.close();
		std::remove(std::string(std::string(CurentAppdataPath) + MB_VERSION).c_str());
	}
	else return;
	struct stat StatBuffer;
	WSE2IsInstalled = (stat(std::string(EXECUTABLE).c_str(), &StatBuffer) == 0);
	auto lastKeepAlive = std::chrono::steady_clock::now() - std::chrono::seconds(30);
	while (Current_FTPCommand.load() != FTPCommand_Stop) {
		auto now = std::chrono::steady_clock::now();
		if (now - lastKeepAlive >= std::chrono::seconds(30)) {
			AliveResponse = FTP.sendCommand("FEAT");
			if (!AliveResponse.isOk()) return;
			FTP.keepAlive();
			lastKeepAlive = now;
		}

		if (Current_FTPDownloadState.load() != FTPDownloadState_Updated && WSE2IsInstalled && WSE2Version.length() == 4 && !IsCurrentVersionOlderThan(FTP_Version)) {
			Current_FTPDownloadState.store(FTPDownloadState_Updated);
			std::lock_guard<std::mutex> lock(FTPThread_Mutex);
			tgui::Button::Ptr Button_FTP = GUI_Main.get<tgui::Button>("Button_FTP");
			tgui::Label::Ptr Label_FTP = GUI_Main.get<tgui::Label>("Label_FTP");
			Button_FTP->setVisible(false);
			Label_FTP->setVisible(true);
			Label_FTP->setText(GetLocalizedTextEntry("ui_version_is_up_to_date"));
			Label_FTP->setPosition("23%", "43%");
		}
		if (Current_FTPDownloadState.load() != FTPDownloadState_WaitingUpdate && WSE2IsInstalled && IsCurrentVersionOlderThan(FTP_Version)) {
			Current_FTPDownloadState.store(FTPDownloadState_WaitingUpdate);
			std::lock_guard<std::mutex> lock(FTPThread_Mutex);
			tgui::Button::Ptr Button_FTP = GUI_Main.get<tgui::Button>("Button_FTP");
			tgui::Label::Ptr Label_FTP = GUI_Main.get<tgui::Label>("Label_FTP");
			Button_FTP->setVisible(true);
			Label_FTP->setVisible(true);
			Button_FTP->setText(GetLocalizedTextEntry("ui_update_wse2"));
			Label_FTP->setText(GetLocalizedTextEntry("ui_newer_version_available"));
			Label_FTP->setPosition("23%", "35%");
		}
		if (Current_FTPDownloadState.load() != FTPDownloadState_WaitingInstall && !WSE2IsInstalled) {
			Current_FTPDownloadState.store(FTPDownloadState_WaitingInstall);
			std::lock_guard<std::mutex> lock(FTPThread_Mutex);
			tgui::Button::Ptr Button_FTP = GUI_Main.get<tgui::Button>("Button_FTP");
			tgui::Label::Ptr Label_FTP = GUI_Main.get<tgui::Label>("Label_FTP");
			Button_FTP->setVisible(true);
			Label_FTP->setVisible(true);
			Button_FTP->setText(GetLocalizedTextEntry("ui_install_wse2"));
			Label_FTP->setText(GetLocalizedTextEntry("ui_wse2_not_installed"));
			Label_FTP->setPosition("23%", "35%");
		}

		FTPCommand expectedDownload = FTPCommand_DownloadAllFiles;
		if (Current_FTPCommand.compare_exchange_strong(expectedDownload, FTPCommand_None)) {
			{
				std::lock_guard<std::mutex> lock(FTPThread_Mutex);
				tgui::Button::Ptr Button_FTP = GUI_Main.get<tgui::Button>("Button_FTP");
				Button_FTP->setText(GetLocalizedTextEntry("ui_please_wait"));
			}

			Current_FTPDownloadState.store(FTPDownloadState_Downloading);
			sf::Ftp::ListingResponse ListingResponse = FTP.getDirectoryListing();
			bool downloadOk = ListingResponse.isOk();
			if (downloadOk) {
				for (size_t i = 0; i < ListingResponse.getListing().size(); i++) {
					if (Current_FTPCommand.load() == FTPCommand_Stop) { downloadOk = false; break; }
					if (!FTPDownloadContent(ListingResponse.getListing()[i])) { downloadOk = false; break; }
				}
			}

			if (downloadOk) {
				WSE2Version = FTP_Version;
				WSE2VersionWithDots = WSE2Version;
				for (size_t i = 1; i < 4; i++)  WSE2VersionWithDots.insert(i * 2 - 1, L".");
				{
					std::lock_guard<std::mutex> lock(FTPThread_Mutex);
					tgui::Label::Ptr Label_WSE2Version = GUI_Main.get<tgui::Label>("Label_WSE2Version");
					tgui::Button::Ptr Button_FTP = GUI_Main.get<tgui::Button>("Button_FTP");
					tgui::Label::Ptr Label_FTP = GUI_Main.get<tgui::Label>("Label_FTP");
					if (WSE2VersionWithDots != L"") Label_WSE2Version->setText(wstring_Converter.to_bytes(L"WSE2 ver. " + WSE2VersionWithDots));
					WSE2IsInstalled = true;
					Current_FTPDownloadState.store(FTPDownloadState_Updated);
					Button_FTP->setVisible(false);
					Label_FTP->setVisible(true);
					Label_FTP->setText(GetLocalizedTextEntry("ui_version_is_up_to_date"));
					Label_FTP->setPosition("23%", "43%");
				}
				HKEY Key;
				if (RegOpenKeyExW(HKEY_CURRENT_USER, REGISTRY_KEY, 0, KEY_WRITE, &Key) == ERROR_SUCCESS) {
					RegSetValueExW(Key, L"wse2_version", 0, REG_SZ, (LPBYTE)WSE2Version.c_str(), (DWORD)((WSE2Version.length() + 1) * sizeof(wchar_t)));
					RegCloseKey(Key);
				}
			}
			else {
				Current_FTPDownloadState.store(FTPDownloadState_None);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

}

bool Class_Engine::IsCurrentVersionOlderThan(std::wstring NewVersion)
{
	if (WSE2Version.length() < 4 || NewVersion.length() < 4) return false;
	if (WSE2Version[0] < NewVersion[0] || (WSE2Version[0] <= NewVersion[0] && WSE2Version[1] < NewVersion[1]) || (WSE2Version[0] <= NewVersion[0] && WSE2Version[1] <= NewVersion[1] && WSE2Version[2] < NewVersion[2]) || (WSE2Version[0] <= NewVersion[0] && WSE2Version[1] <= NewVersion[1] && WSE2Version[2] <= NewVersion[2] && WSE2Version[3] < NewVersion[3])) return true;
	return false;
}

bool Class_Engine::FTPDownloadContent(std::string Name)
{
	if (Current_FTPCommand.load() == FTPCommand_Stop) return false;
	if (Name == "." || Name == "..") return true;

	if (FTP.changeDirectory(Name).isOk()) {
		sf::Ftp::ListingResponse ListingResponse = FTP.getDirectoryListing();
		if (!ListingResponse.isOk()) {
			FTP.parentDirectory();
			return false;
		}
		bool ok = true;
		for (size_t i = 0; i < ListingResponse.getListing().size(); i++) {
			if (Current_FTPCommand.load() == FTPCommand_Stop) { ok = false; break; }
			if (!FTPDownloadContent(ListingResponse.getListing()[i])) { ok = false; break; }
		}
		FTP.parentDirectory();
		return ok;
	}

	if (Name == "version.txt") return true;

	sf::Ftp::DirectoryResponse FTPWorkingDirectory = FTP.getWorkingDirectory();
	if (!FTPWorkingDirectory.isOk()) return false;

	std::string remoteDir = FTPWorkingDirectory.getDirectory();
	std::string localDir = (remoteDir != "/") ? std::string(remoteDir + "/").erase(0, 1) : std::string(remoteDir).erase(0, 1);

	{
		std::lock_guard<std::mutex> lock(FTPThread_Mutex);
		tgui::Label::Ptr Label_FTP = GUI_Main.get<tgui::Label>("Label_FTP");
		Label_FTP->setText(GetLocalizedTextEntry(u8"ui_downloading_") + Name);
	}

	try {
		if (!localDir.empty()) std::filesystem::create_directories(localDir);
	}
	catch (const std::exception&) {
		return false;
	}

	return FTP.download(Name, localDir).isOk();
}
