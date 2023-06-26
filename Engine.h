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
	std::mutex FTPThread_Mutex;
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
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> wstring_Converter;
};

#if defined WFAS
#define MB_NAME "Mount&Blade WFaS WSE2"
#define REGISTRY_KEY L"SOFTWARE\\MountAndBladeWarbandWFASKeys"
#define EXECUTABLE "mb_wfas_wse2.exe"
#define EXECUTABLE_DEDICATED "mb_wfas_wse2_dedicated.exe"
#define FTP_LOGIN "WSE2_WFaS"
#else
#define MB_NAME "Mount&Blade Warband WSE2"
#define REGISTRY_KEY L"SOFTWARE\\MountAndBladeWarbandKeys"
#define EXECUTABLE "mb_warband_wse2.exe"
#define EXECUTABLE_DEDICATED "mb_warband_wse2_dedicated.exe"
#define FTP_LOGIN "WSE2"
#endif

#define MB_NAME_PATH "/" MB_NAME
#define RGL_CONFIG "/" MB_NAME "/rgl_config.ini"
#define RGL_CONFIG_TEMP "/" MB_NAME "/rgl_config_temp.ini"
#define MB_LANGUAGE "\\" MB_NAME "\\language.txt"
#define MB_VERSION "\\" MB_NAME "\\version.txt"
#define FTP_ADDRESS "ftp.fianna.ru"
#define FTP_PORT 2121
