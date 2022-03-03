#pragma once
#include "Global.h"

class Class_Engine {
public:
	void Start();
	std::shared_ptr<sf::RenderWindow> Window_Main = nullptr, Window_Options = nullptr;
	std::shared_ptr<tgui::Panel> Panel_Main = nullptr, Panel_Options = nullptr;
	tgui::Gui GUI_Main, GUI_Options;
	tgui::ComboBox::Ptr ComboBoxModule;
	void Initialize();
	void Runtime();
	void Interact_Main();
	void Interact_Options();
	void LaunchGame(ExeType);
	void Button_Launch_onClick();
	void Button_Launch_Dedicated_onClick();
	void Button_Options_onClick();
	void RefreshModulesList();
	bool UpdateOptions();
	bool ApplyOptions();
	std::string CurrentModule();
	std::vector<std::string> Modules;
	sf::Texture Texture_Options;
	std::map<std::string, std::string> Options;
	CHAR CurentUserDocuments[MAX_PATH];
};
