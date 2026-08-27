#include "Engine.h"

void Class_Engine::Initialize_UI_Main()
{
	GUI_Main.setTarget(*Window_Main);

	Panel_Main = tgui::Panel::create();
	Panel_Main->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
	GUI_Main.add(Panel_Main, "Panel_Main");

	tgui::Label::Ptr Label_Message1 = tgui::Label::create(" ");
	Label_Message1->setTextSize(Scaled(11));
	Label_Message1->setOrigin(0, 0);
	Label_Message1->setPosition("2%", "74%");
	Label_Message1->setSize("20%", "15%");
	Label_Message1->setAutoSize(1);
	Label_Message1->setMaximumTextWidth(Scaled(270));
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
	ComboBoxModule->getRenderer()->setPadding({ Scaled(5), 0, 0, 0 });
	ComboBoxModule->setItemsToDisplay(10);
	ComboBoxModule->onItemSelect([this] {UpdateModPreviewImage(); SetLastModule(); });
	Panel_Main->add(ComboBoxModule, "ComboBoxModule");

	tgui::Label::Ptr Label_Update = tgui::Label::create(u8" ");
	Label_Update->setOrigin(0.5, 0.5);
	Label_Update->getRenderer()->setTextColor(tgui::Color(105, 80, 54));
	Panel_Main->add(Label_Update, "Label_Update");
	Label_Update->setVisible(false);

	tgui::Button::Ptr Button_Update = tgui::Button::create(" ");
	InitializeTextButton(Button_Update);
	Button_Update->setPosition("23%", "39%");
	Button_Update->setSize("30%", "12%");
	Panel_Main->add(Button_Update, "Button_Update");
	Button_Update->setVisible(false);
	Button_Update->onClick([this] {
		if (Current_UpdateState.load() == UpdateState_RestartRequired) RestartLauncher();
		else Current_UpdateCommand.store(UpdateCommand_Install);
	});

	tgui::Button::Ptr Button_Launch = tgui::Button::create(" ");
	InitializeTextButton(Button_Launch);
	Button_Launch->setPosition("23%", "47%");
	Button_Launch->setSize("30%", "8%");
	Button_Launch->onClick(&Class_Engine::Button_Launch_onClick, this);
	Panel_Main->add(Button_Launch, "Button_Launch");

	tgui::Button::Ptr Button_Launch_x64 = tgui::Button::create(" ");
	InitializeTextButton(Button_Launch_x64);
	Button_Launch_x64->setPosition("23%", "54%");
	Button_Launch_x64->setSize("30%", "8%");
	Button_Launch_x64->onClick(&Class_Engine::Button_Launch_x64_onClick, this);
	Panel_Main->add(Button_Launch_x64, "Button_Launch_x64");

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
	Button_Options->setPosition("23%", "61%");
	Button_Options->setSize("25%", "8%");
	Button_Options->onClick(&Class_Engine::Button_Options_onClick, this);
	Panel_Main->add(Button_Options, "Button_Options");

	tgui::Button::Ptr Button_Exit = tgui::Button::create(" ");
	InitializeTextButton(Button_Exit);
	Button_Exit->setPosition("23%", "68%");
	Button_Exit->setSize("25%", "7%");
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
	Button_Close->setSize(Scaled(31), Scaled(32));
	Button_Close->onClick(&Class_Engine::Close, this);
	Panel_Main->add(Button_Close, "Button_Close");

	tgui::Button::Ptr Button_Minimize = tgui::Button::create();
	Button_Minimize->getRenderer()->setBorders(0);
	Button_Minimize->setPosition("85%", "6%");
	Button_Minimize->setSize(Scaled(31), Scaled(32));
	Button_Minimize->onClick([this] { ShowWindow(Window_Main->getSystemHandle(), SW_SHOWMINIMIZED); });
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

