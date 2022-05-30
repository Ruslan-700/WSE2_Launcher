#include "Engine.h"

void Class_Engine::Initialize_UI_Main()
{
	GUI_Main.setTarget(*Window_Main);

	Panel_Main = tgui::Panel::create();
	Panel_Main->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
	GUI_Main.add(Panel_Main, "Panel_Main");

	tgui::Label::Ptr Label_Message1 = tgui::Label::create(" ");
	Label_Message1->setTextSize(11);
	Label_Message1->setOrigin(0, 0);
	Label_Message1->setPosition("2%", "74%");
	Label_Message1->setSize("20%", "15%");
	Label_Message1->setAutoSize(1);
	Label_Message1->setMaximumTextWidth(270);
	Panel_Main->add(Label_Message1, "Label_Message1");

	tgui::Label::Ptr Label_CurrentModule = tgui::Label::create(" ");
	Label_CurrentModule->setOrigin(1, 0.5);
	Label_CurrentModule->setPosition("33%", "26%");
	Label_CurrentModule->getRenderer()->setTextColor(tgui::Color(105, 80, 54));
	Panel_Main->add(Label_CurrentModule, "Label_CurrentModule");

	tgui::Label::Ptr Label_WSE2Version = tgui::Label::create(u8"WSE2");
	Label_WSE2Version->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	Label_WSE2Version->setOrigin(0, 0.5);
	Label_WSE2Version->setPosition("74%", "19%");
	Label_WSE2Version->getRenderer()->setTextColor(tgui::Color(105, 80, 54));
	Panel_Main->add(Label_WSE2Version, "Label_WSE2Version");

	ComboBoxModule = tgui::ComboBox::create();
	ComboBoxModule->setOrigin(0.5, 0.5);
	ComboBoxModule->setPosition("64%", "26%");
	ComboBoxModule->setSize("60%", "6%");
	ComboBoxModule->setChangeItemOnScroll(true);
	ComboBoxModule->getRenderer()->setBorders(0);
	ComboBoxModule->getRenderer()->setPadding({ 5, 0, 0, 0 });
	ComboBoxModule->setItemsToDisplay(10);
	ComboBoxModule->onItemSelect([&] {Class_Engine::UpdateModPreviewImage(); SetLastModule(); });
	Panel_Main->add(ComboBoxModule, "ComboBoxModule");

	tgui::Label::Ptr Label_FTP = tgui::Label::create(u8" ");
	Label_FTP->setOrigin(0.5, 0.5);
	Label_FTP->getRenderer()->setTextColor(tgui::Color(105, 80, 54));
	Panel_Main->add(Label_FTP, "Label_FTP");
	Label_FTP->setVisible(false);

	tgui::Button::Ptr Button_FTP = tgui::Button::create(" ");
	InitializeTextButton(Button_FTP);
	Button_FTP->setPosition("23%", "39%");
	Button_FTP->setSize("30%", "12%");
	Panel_Main->add(Button_FTP, "Button_FTP");
	Button_FTP->setVisible(false);
	Button_FTP->onClick([&] {  Current_FTPCommand = FTPCommand_DownloadAllFiles; });

	tgui::Button::Ptr Button_Launch = tgui::Button::create(" ");
	InitializeTextButton(Button_Launch);
	Button_Launch->setPosition("23%", "47%");
	Button_Launch->setSize("30%", "12%");
	Button_Launch->onClick(&Class_Engine::Button_Launch_onClick, this);
	Panel_Main->add(Button_Launch, "Button_Launch");

	tgui::Button::Ptr Button_Launch_Dedicated = tgui::Button::create(" ");
	InitializeTextButton(Button_Launch_Dedicated);
	Button_Launch_Dedicated->setPosition("23%", "48%");
	Button_Launch_Dedicated->setSize("35%", "12%");
	Button_Launch_Dedicated->onClick(&Class_Engine::Button_Launch_Dedicated_onClick, this);
	Panel_Main->add(Button_Launch_Dedicated, "Button_Launch_Dedicated");
	Button_Launch_Dedicated->setEnabled(false);
	Button_Launch_Dedicated->setVisible(false);

	tgui::Button::Ptr Button_Options = tgui::Button::create(" ");
	InitializeTextButton(Button_Options);
	Button_Options->setPosition("23%", "55%");
	Button_Options->setSize("25%", "9%");
	Button_Options->onClick(&Class_Engine::Button_Options_onClick, this);
	Panel_Main->add(Button_Options, "Button_Options");

	tgui::Button::Ptr Button_Exit = tgui::Button::create(" ");
	InitializeTextButton(Button_Exit);
	Button_Exit->setPosition("23%", "63%");
	Button_Exit->setSize("25%", "8%");
	Button_Exit->onClick(&Class_Engine::Close, this);
	Panel_Main->add(Button_Exit, "Button_Exit");

	tgui::Picture::Ptr Picture_ModPreview = tgui::Picture::create();
	Picture_ModPreview->setOrigin(0.5, 0.5);
	Picture_ModPreview->setPosition("71%", "61%");
	Picture_ModPreview->setSize("49%", "53%");
	Panel_Main->add(Picture_ModPreview, "Picture_ModPreview");

	tgui::Button::Ptr Button_Close = tgui::Button::create();
	Button_Close->getRenderer()->setBorders(0);
	Button_Close->setPosition("90%", "6%");
	Button_Close->setSize(31, 32);
	Button_Close->onClick(&Class_Engine::Close, this);
	Panel_Main->add(Button_Close, "Button_Close");

	tgui::Button::Ptr Button_Minimize = tgui::Button::create();
	Button_Minimize->getRenderer()->setBorders(0);
	Button_Minimize->setPosition("85%", "6%");
	Button_Minimize->setSize(31, 32);
	Button_Minimize->onClick([&] { { ShowWindow(Window_Main->getSystemHandle(), SW_SHOWMINIMIZED); }});
	Panel_Main->add(Button_Minimize, "Button_Minimize");

	tgui::Button::Ptr Button_MoveBar = tgui::Button::create();
	Button_MoveBar->setOrigin(0.5, 0.5);
	Button_MoveBar->getRenderer()->setBorders(0);
	Button_MoveBar->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
	Button_MoveBar->getRenderer()->setBackgroundColorDown(tgui::Color::Transparent);
	Button_MoveBar->getRenderer()->setBackgroundColorHover(tgui::Color::Transparent);
	Button_MoveBar->setPosition("42%", "10%");
	Button_MoveBar->setSize("84%", "20%");
	Panel_Main->add(Button_MoveBar, "Button_MoveBar");
}

