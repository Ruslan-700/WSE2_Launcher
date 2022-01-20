#pragma once
#include "Global.h"

class Class_Engine {
public:
	void Start();
	sf::RenderWindow* Window;
	tgui::Gui GUI;
	void Initialize();
	void Runtime();
	void Interact();
	std::shared_ptr<tgui::Panel> Panel_Main;
	tgui::ComboBox::Ptr ComboBoxModule;
	void LaunchGame(ExeType);
	void Button_Launch_onClick();
	void Button_Launch_Dedicated_onClick();
	void RefreshModulesList();
	std::vector<std::string> Modules;
};
