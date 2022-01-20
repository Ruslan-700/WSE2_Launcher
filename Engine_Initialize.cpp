#include "Engine.h"

void Class_Engine::Initialize()
{
	Panel_Main = tgui::Panel::create();
	GUI.add(Panel_Main, "Panel_Main");

	tgui::Label::Ptr Label_Title = tgui::Label::create("WSE2 Launcher");
	Label_Title->setTextSize(20);
	Label_Title->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	Label_Title->setOrigin(0.5, 0.5);
	Label_Title->setPosition("50%", "5%");

	tgui::Label::Ptr Label_Module = tgui::Label::create("Module");
	Label_Module->setTextSize(14);
	Label_Module->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	Label_Module->setOrigin(0, 0.5);
	Label_Module->setPosition("5%", "20%");

	RefreshModulesList();

	ComboBoxModule = tgui::ComboBox::create();
	ComboBoxModule->setOrigin(0.5, 0.5);
	ComboBoxModule->setPosition("60%", "20%");
	ComboBoxModule->setSize("60%", "7%");

	for (size_t i = 0; i < Modules.size(); i++)
	{
		ComboBoxModule->addItem(Modules[i], Modules[i]);
	}

	ComboBoxModule->setItemsToDisplay(5);
	ComboBoxModule->setSelectedItemByIndex(0);

	tgui::Button::Ptr Button_Launch = tgui::Button::create("Launch game");
	Button_Launch->getRenderer()->setBorders(tgui::Borders::Outline(2));
	Button_Launch->getRenderer()->setBorderColor(tgui::Color::Black);
	Button_Launch->setOrigin(0.5, 0.5);
	Button_Launch->setPosition("40%", "88%");
	Button_Launch->setSize("60%", "10%");
	Button_Launch->onClick(&Class_Engine::Button_Launch_onClick, this);

	tgui::Button::Ptr Button_Launch_Dedicated = tgui::Button::create("Launch dedicated\nserver");
	Button_Launch_Dedicated->getRenderer()->setBorders(tgui::Borders::Outline(2));
	Button_Launch_Dedicated->getRenderer()->setBorderColor(tgui::Color::Black);
	Button_Launch_Dedicated->setOrigin(0.5, 0.5);
	Button_Launch_Dedicated->setPosition("85%", "88%");
	Button_Launch_Dedicated->setSize("18%", "10%");
	Button_Launch_Dedicated->onClick(&Class_Engine::Button_Launch_Dedicated_onClick, this);

	Panel_Main->add(Button_Launch, "Button_Connect");
	Panel_Main->add(Button_Launch_Dedicated, "Button_Launch_Dedicated");
	Panel_Main->add(Label_Module, "Label_Title");
	Panel_Main->add(Label_Title, "Label_Title");
	Panel_Main->add(ComboBoxModule, "ComboBoxModule");
}
