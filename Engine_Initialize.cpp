#include "Engine.h"

void Class_Engine::Initialize()
{
	Panel_Main = tgui::Panel::create();
	GUI_Main.add(Panel_Main, "Panel_Main");

	tgui::Label::Ptr Label_Title = tgui::Label::create("WSE2 Launcher");
	Label_Title->setTextSize(20);
	Label_Title->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	Label_Title->setOrigin(0.5, 0.5);
	Label_Title->setPosition("50%", "5%");

	Texture_Options.loadFromMemory(Image_Options, Image_Options_Length);

	tgui::Button::Ptr Button_Options = tgui::Button::create();
	Button_Options->getRenderer()->setBorders(tgui::Borders::Outline(1));
	Button_Options->getRenderer()->setBorderColor(tgui::Color::Black);
	Button_Options->getRenderer()->setTexture(Texture_Options);
	Button_Options->setOrigin(0.5, 0.5);
	Button_Options->setPosition("85%", "20%");
	Button_Options->setSize("5.5%", "7%");
	Button_Options->onClick(&Class_Engine::Button_Options_onClick, this);

	tgui::Label::Ptr Label_Module = tgui::Label::create("Module");
	Label_Module->setTextSize(14);
	Label_Module->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	Label_Module->setOrigin(0, 0.5);
	Label_Module->setPosition("5%", "20%");

	RefreshModulesList();

	ComboBoxModule = tgui::ComboBox::create();
	ComboBoxModule->setOrigin(0.5, 0.5);
	ComboBoxModule->setPosition("50%", "20%");
	ComboBoxModule->setSize("50%", "7%");

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

	tgui::Button::Ptr Button_Launch_Dedicated = tgui::Button::create("Launch game\n(dedicated server)");
	Button_Launch_Dedicated->getRenderer()->setBorders(tgui::Borders::Outline(2));
	Button_Launch_Dedicated->getRenderer()->setBorderColor(tgui::Color::Black);
	Button_Launch_Dedicated->setOrigin(0.5, 0.5);
	Button_Launch_Dedicated->setPosition("85%", "88%");
	Button_Launch_Dedicated->setSize("18%", "10%");
	Button_Launch_Dedicated->onClick(&Class_Engine::Button_Launch_Dedicated_onClick, this);

	tgui::Label::Ptr Label_Message1 = tgui::Label::create(" ");
	Label_Message1->setTextSize(10);
	Label_Message1->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	Label_Message1->setOrigin(0.5, 0.5);
	Label_Message1->setPosition("50%", "78%");

	Panel_Main->add(Button_Launch, "Button_Connect");
	Panel_Main->add(Button_Options, "Button_Options");
	Panel_Main->add(Button_Launch_Dedicated, "Button_Launch_Dedicated");
	Panel_Main->add(Label_Module, "Label_Module");
	Panel_Main->add(Label_Title, "Label_Title");
	Panel_Main->add(Label_Message1, "Label_Message1");
	Panel_Main->add(ComboBoxModule, "ComboBoxModule");
}