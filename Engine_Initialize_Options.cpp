#include "Engine.h"

void Class_Engine::Initialize_UI_Options()
{
	Panel_Options = tgui::Panel::create();
	GUI_Options.add(Panel_Options, "Panel_Options");

	tgui::Label::Ptr Label_Options = tgui::Label::create(" ");
	Label_Options->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	Label_Options->setOrigin(0.5, 0.5);
	Label_Options->setPosition("50%", "6%");

	tgui::Label::Ptr Label_Language = tgui::Label::create(" ");
	Label_Language->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	Label_Language->setOrigin(0, 0.5);
	Label_Language->setPosition("10%", "25%");

	tgui::ComboBox::Ptr ComboBox_Languages = tgui::ComboBox::create();
	ComboBox_Languages->setOrigin(0.5, 0.5);
	ComboBox_Languages->setPosition("60%", "25%");
	ComboBox_Languages->setSize("30%", "4%");
	ComboBox_Languages->onItemSelect(&Class_Engine::ChangeLanguage, this);

	tgui::Label::Ptr Label_Sound = tgui::Label::create(" ");
	Label_Sound->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	Label_Sound->setOrigin(0, 0.5);
	Label_Sound->setPosition("10%", "62%");

	tgui::CheckBox::Ptr Checkbox_Sound = tgui::CheckBox::create();
	Checkbox_Sound->setOrigin(0.5, 0.5);
	Checkbox_Sound->setPosition("50%", "62%");
	Checkbox_Sound->setChecked(Options["bSound"] == "true");
	Checkbox_Sound->onCheck([&] { Options.insert_or_assign("bSound", "false"); });
	Checkbox_Sound->onUncheck([&] { Options.insert_or_assign("bSound", "true"); });

	tgui::Label::Ptr Label_Music = tgui::Label::create(" ");
	Label_Music->setTextSize(15);
	Label_Music->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	Label_Music->setOrigin(0, 0.5);
	Label_Music->setPosition("10%", "70%");

	tgui::CheckBox::Ptr Checkbox_Music = tgui::CheckBox::create();
	Checkbox_Music->setOrigin(0.5, 0.5);
	Checkbox_Music->setPosition("50%", "70%");
	Checkbox_Music->setChecked(Options["bMusic"] == "true");
	Checkbox_Music->onCheck([&] { Options.insert_or_assign("bMusic", "false"); });
	Checkbox_Music->onUncheck([&] { Options.insert_or_assign("bMusic", "true"); });

	tgui::Label::Ptr Label_Message1 = tgui::Label::create(" ");
	Label_Message1->setTextSize(10);
	Label_Message1->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	Label_Message1->setOrigin(0.5, 0.5);
	Label_Message1->setPosition("50%", "78%");

	tgui::Button::Ptr Button_Save = tgui::Button::create(" ");
	Button_Save->getRenderer()->setBorders(tgui::Borders::Outline(2));
	Button_Save->getRenderer()->setBorderColor(tgui::Color::Black);
	Button_Save->setOrigin(0, 0.5);
	Button_Save->setPosition("10%", "85%");
	Button_Save->setSize("55%", "10%");
	Button_Save->onClick([&] { if (ApplyOptions()) { Window_Options->close(); }});

	tgui::Button::Ptr Button_Cancel = tgui::Button::create(" ");
	Button_Cancel->getRenderer()->setBorders(tgui::Borders::Outline(2));
	Button_Cancel->getRenderer()->setBorderColor(tgui::Color::Black);
	Button_Cancel->setOrigin(1, 0.5);
	Button_Cancel->setPosition("90%", "85%");
	Button_Cancel->setSize("20%", "10%");
	Button_Cancel->onClick(&Class_Engine::CancelChanges, this);

	tgui::Button::Ptr Button_Close = tgui::Button::create();
	Button_Close->getRenderer()->setBorders(0);
	Button_Close->setPosition("86%", "6%");
	Button_Close->setSize(31, 32);
	Button_Close->onClick(&Class_Engine::CancelChanges, this);
	Panel_Options->add(Button_Close, "Button_Close");

	tgui::Button::Ptr Button_Minimize = tgui::Button::create();
	Button_Minimize->getRenderer()->setBorders(0);
	Button_Minimize->setPosition("78%", "6%");
	Button_Minimize->setSize(31, 32);
	Button_Minimize->onClick([&] { ShowWindow(Window_Options->getSystemHandle(), SW_SHOWMINIMIZED); });
	Panel_Options->add(Button_Minimize, "Button_Minimize");

	Panel_Options->add(Button_Cancel, "Button_Cancel");
	Panel_Options->add(Button_Save, "Button_Save");
	Panel_Options->add(Label_Sound, "Label_Sound");
	Panel_Options->add(Checkbox_Sound, "Checkbox_Sound");
	Panel_Options->add(Label_Music, "Label_Music");
	Panel_Options->add(Checkbox_Music, "Checkbox_Music");
	Panel_Options->add(Label_Options, "Label_Options");
	Panel_Options->add(Label_Message1, "Label_Message1");
	Panel_Options->add(ComboBox_Languages, "ComboBox_Languages");
	Panel_Options->add(Label_Language, "Label_Language");
}

void Class_Engine::CancelChanges()
{
	CurrentLanguage = PreviousLanguage;

	tgui::ComboBox::Ptr ComboBox_Languages = GUI_Options.get<tgui::ComboBox>("ComboBox_Languages");
	ComboBox_Languages->setSelectedItemById(CurrentLanguage);

	std::ofstream File_language(std::string(CurentUserPath) + std::string("\\AppData\\Roaming\\Mount&Blade Warband WSE2\\language.txt"));
	if (File_language.good())
	{
		File_language << CurrentLanguage;
		File_language.close();
	}
	ReadLocalizationFiles();
	UpdateText();
	Window_Options->close();
}