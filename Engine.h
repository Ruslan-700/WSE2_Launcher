#pragma once
#include "Global.h"
#include <windows.h>

class Class_Engine {
public:
	void Start();
	~Class_Engine();
private:
	std::shared_ptr<sf::RenderWindow> Window_Main = nullptr, Window_Options = nullptr;
	std::shared_ptr<tgui::Panel> Panel_Main = nullptr, Panel_Options = nullptr;
	tgui::Gui GUI_Main, GUI_Options;
	tgui::ComboBox::Ptr ComboBoxModule;
	void Initialize();
	void Initialize_UI_Main();
	void Initialize_UI_Options();
	void Runtime();
	void Interact_Main();
	void Interact_Options();
	void LaunchGame(ExeType);
	void Button_Launch_onClick();
	void Button_Launch_Dedicated_onClick();
	void Button_Options_onClick();
	void RefreshModulesList();
	void SetWindowTransparency();
	void UpdateTextures();
	void UpdateText();
	void InitializeTextButton(tgui::Button::Ptr);
	void ReadCurrentUserPath();
	void ReadCurrentLanguage();
	void ReadLocalizationFiles();
	void BuildLanguagesList();
	void ChangeLanguage();
	void Close();
	void CancelChanges();
	void UpdateModPreviewImage();
	void FillMissingLocalizationKeys();
	void MoveWindow_Main();
	void MoveWindow_Options();
	void ReadWSE2Version();
	void SetLastModule();
	void FTPThread();
	void FTPDownloadContent(std::string);
	void DisplayErrorMessageMain(std::string);
	void DisplayErrorMessageOptions(std::string);
	void CreateDefaultRglConfig();
	bool UpdateOptions();
	bool ApplyOptions();
	bool FTPThread_IsRunning = false;
	bool IsCurrentVersionOlderThan(std::wstring);
	FTPDownloadState Current_FTPDownloadState = FTPDownloadState_None;
	FTPCommand Current_FTPCommand = FTPCommand_None;
	std::future<void> FTPThread_future;
	sf::Ftp FTP;
	bool WSE2IsInstalled = false;
	std::string GetLanguageNameById(std::string);
	std::string GetLocalizedTextEntry(std::string);
	std::wstring GetLastModule();
	std::wstring WSE2VersionWithDots = L"";
	std::wstring WSE2Version = L"";
	std::string GetCurrentModule();
	std::vector<std::string> Modules;
	sf::Texture Texture_Options, Texture_MainBackground, Texture_OptionsBackground, Texture_ModPreview, Texture_Close, Texture_CloseDown, Texture_Minimize, Texture_MinimizeDown, Texture_Button, Texture_Button_Hover, Texture_Button_Down, Texture_Combobox, Texture_Combobox_Arrow;
	std::map<std::string, std::string> Options;
	std::map<std::string, std::string> LocalizedText;
	tgui::Font Font_Latin, Font_Universal;
	std::string CurrentLanguage = "en", PreviousLanguage = "en";
	int MoveBar_X = -1, MoveBar_Y = 0, Options_MoveBar_X = -1, Options_MoveBar_Y = 0;
	CHAR CurentDocumentsPath[MAX_PATH] = "";
	CHAR CurentAppdataPath[MAX_PATH] = "";
};
