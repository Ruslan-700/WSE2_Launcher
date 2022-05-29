#include "Engine.h"

void Class_Engine::FTPThread()
{
	if (CurentAppdataPath == "") return;
	sf::Ftp::Response ConnectionResponse, LoginResponse, FileResponse, AliveResponse;
	ConnectionResponse = FTP.connect("ftp.fianna.ru", 2121, sf::seconds(10));
	if (!ConnectionResponse.isOk()) return;
	LoginResponse = FTP.login("WSE2", "WSE2");
	if (!LoginResponse.isOk()) return;
	FileResponse = FTP.download("\\version.txt", std::string(CurentAppdataPath) + u8"\\Mount&Blade Warband WSE2");
	if (!FileResponse.isOk()) return;
	std::ifstream File_version(std::string(CurentAppdataPath) + std::string("\\Mount&Blade Warband WSE2\\version.txt"));
	std::string Line = "";
	std::wstring FTP_Version = L"";
	if (File_version.good())
	{
		try { std::getline(File_version, Line); } catch (const std::exception& Exception) { DisplayErrorMessageMain("Error (unhandled exception in FTPThread) - ''" + std::string(Exception.what()) + "''. "); return; }
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> Converter;
		FTP_Version = Converter.from_bytes(Line);
		File_version.close();
		std::remove(std::string(std::string(CurentAppdataPath) + "\\Mount&Blade Warband WSE2\\version.txt").c_str());
	}
	else return;
	struct stat StatBuffer;
	WSE2IsInstalled = (stat(std::string("mb_warband_wse2.exe").c_str(), &StatBuffer) == 0);
	while (Current_FTPCommand != FTPCommand_Stop) {
		AliveResponse = FTP.sendCommand("FEAT");
		if (!AliveResponse.isOk()) return;
		FTP.keepAlive();
		tgui::Button::Ptr Button_FTP = GUI_Main.get<tgui::Button>("Button_FTP");
		tgui::Label::Ptr Label_FTP = GUI_Main.get<tgui::Label>("Label_FTP");  
		if (Current_FTPDownloadState != FTPDownloadState_Updated && WSE2IsInstalled && !IsCurrentVersionOlderThan(FTP_Version)) {
			Current_FTPDownloadState = FTPDownloadState_Updated;
			Button_FTP->setVisible(false);
			Label_FTP->setVisible(true);
			TGUIWidgetPropertyChangeRequests.push_back(Class_TGUIWidgetPropertyChangeRequest(&GUI_Main, TGUIWidget_TGUILabel, "Label_FTP", GetLocalizedTextEntry("ui_version_is_up_to_date")));
			Label_FTP->setPosition("23%", "40%");
		}
		if (Current_FTPDownloadState != FTPDownloadState_WaitingUpdate && WSE2IsInstalled && IsCurrentVersionOlderThan(FTP_Version)) {
			Current_FTPDownloadState = FTPDownloadState_WaitingUpdate;
			Button_FTP->setVisible(true);
			Label_FTP->setVisible(true);
			TGUIWidgetPropertyChangeRequests.push_back(Class_TGUIWidgetPropertyChangeRequest(&GUI_Main, TGUIWidget_TGUIButton, "Button_FTP", GetLocalizedTextEntry("ui_update_wse2")));
			TGUIWidgetPropertyChangeRequests.push_back(Class_TGUIWidgetPropertyChangeRequest(&GUI_Main, TGUIWidget_TGUILabel, "Label_FTP", GetLocalizedTextEntry("ui_newer_version_available")));
			Label_FTP->setPosition("23%", "32%");
		}
		if (Current_FTPDownloadState != FTPDownloadState_WaitingInstall && !WSE2IsInstalled) {
			Current_FTPDownloadState = FTPDownloadState_WaitingInstall;
			Button_FTP->setVisible(true);
			Label_FTP->setVisible(true);
			TGUIWidgetPropertyChangeRequests.push_back(Class_TGUIWidgetPropertyChangeRequest(&GUI_Main, TGUIWidget_TGUIButton, "Button_FTP", GetLocalizedTextEntry("ui_install_wse2")));
			TGUIWidgetPropertyChangeRequests.push_back(Class_TGUIWidgetPropertyChangeRequest(&GUI_Main, TGUIWidget_TGUILabel, "Label_FTP", GetLocalizedTextEntry("ui_wse2_not_installed")));
			Label_FTP->setPosition("23%", "32%");
		}

		if (Current_FTPCommand == FTPCommand_DownloadAllFiles) {
			Current_FTPCommand = FTPCommand_None;
			TGUIWidgetPropertyChangeRequests.push_back(Class_TGUIWidgetPropertyChangeRequest(&GUI_Main, TGUIWidget_TGUIButton, "Button_FTP", GetLocalizedTextEntry("ui_please_wait")));

			Current_FTPDownloadState = FTPDownloadState_Downloading;
			sf::Ftp::ListingResponse ListingResponse = FTP.getDirectoryListing();
			if (!ListingResponse.isOk()) return;
			for (size_t i = 0; i < ListingResponse.getListing().size(); i++) FTPDownloadContent(ListingResponse.getListing()[i]);

			WSE2Version = FTP_Version;
			WSE2VersionWithDots = WSE2Version;
			for (size_t i = 1; i < 4; i++)  WSE2VersionWithDots.insert(i * 2 - 1, L".");
			tgui::Label::Ptr Label_WSE2Version = GUI_Main.get<tgui::Label>("Label_WSE2Version");
			if (WSE2VersionWithDots != L"") Label_WSE2Version->setText(L"WSE2 ver. " + WSE2VersionWithDots); TGUIWidgetPropertyChangeRequests.push_back(Class_TGUIWidgetPropertyChangeRequest(&GUI_Main, TGUIWidget_TGUILabel, "Label_FTP", "WSE2 ver. " + std::string(WSE2VersionWithDots)));
			WSE2IsInstalled = true;
			Current_FTPDownloadState = FTPDownloadState_Updated;
			Button_FTP->setVisible(false);
			Label_FTP->setVisible(true);
			Label_FTP->setText(GetLocalizedTextEntry("ui_version_is_up_to_date"));
			Label_FTP->setPosition("23%", "40%");
			HKEY Key;
			RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\MountAndBladeWarbandKeys", 0, KEY_WRITE, &Key);
			RegSetValueExW(Key, L"wse2_version", 0, REG_SZ, (LPBYTE)WSE2Version.c_str(), wcslen(WSE2Version.c_str()) * sizeof(wchar_t));
		}
	}

}

bool Class_Engine::IsCurrentVersionOlderThan(std::wstring NewVersion)
{
	if (WSE2Version.length() < 4 || NewVersion.length() < 4) return false;
	if (WSE2Version[0] < NewVersion[0] || (WSE2Version[0] <= NewVersion[0] && WSE2Version[1] < NewVersion[1]) || (WSE2Version[0] <= NewVersion[0] && WSE2Version[1] <= NewVersion[1] && WSE2Version[2] < NewVersion[2]) || (WSE2Version[0] <= NewVersion[0] && WSE2Version[1] <= NewVersion[1] && WSE2Version[2] <= NewVersion[2] && WSE2Version[3] < NewVersion[3])) return true;
	return false;
}

void Class_Engine::FTPDownloadContent(std::string Name)
{
	if (Name.find('.') == std::string::npos) {
		FTP.changeDirectory(Name);
		sf::Ftp::ListingResponse ListingResponse = FTP.getDirectoryListing();
		if (!ListingResponse.isOk()) return;
		for (size_t i = 0; i < ListingResponse.getListing().size(); i++) FTPDownloadContent(ListingResponse.getListing()[i]);
		FTP.parentDirectory();
	}
	else {
		sf::Ftp::DirectoryResponse FTPWorkingDirectory = FTP.getWorkingDirectory();
		if (!FTPWorkingDirectory.isOk()) return;
		tgui::Label::Ptr Label_FTP = GUI_Main.get<tgui::Label>("Label_FTP");
		Label_FTP->setText(GetLocalizedTextEntry(u8"ui_downloading_") + Name);
		FTP.download(Name, FTPWorkingDirectory.getDirectory() != "/" ? std::string(FTPWorkingDirectory.getDirectory() + "/").erase(0, 1) : std::string(FTPWorkingDirectory.getDirectory()).erase(0, 1));
	}

}