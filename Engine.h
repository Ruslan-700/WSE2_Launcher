#pragma once
#include "Global.h"
#include <windows.h>

class Class_Engine {
public:
	void Start();
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
	std::string GetLocalizedTextEntry(std::string);
	std::wstring GetLastModule();
	bool UpdateOptions();
	bool ApplyOptions();
	std::string CurrentModule();
	std::vector<std::string> Modules;
	sf::Texture Texture_Options, Texture_MainBackground, Texture_OptionsBackground, Texture_ModPreview, Texture_Close, Texture_CloseDown, Texture_Minimize, Texture_MinimizeDown;
	std::map<std::string, std::string> Options;
	std::map<std::string, std::string> LocalizedText;
	tgui::Font Font_Latin, Font_Universal;
	std::string CurrentLanguage = "en", PreviousLanguage = "en";
	CHAR CurentUserPath[MAX_PATH] = "";
};
