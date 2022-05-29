#include "Engine.h"

void Class_Engine::Initialize_UI_Options()
{
	Panel_Options = tgui::Panel::create();
	GUI_Options.add(Panel_Options, "Panel_Options");

	tgui::Label::Ptr Label_Options = tgui::Label::create(" ");
	Label_Options->setOrigin(0.5, 0.5);
	Label_Options->setPosition("50%", "8%");
	Panel_Options->add(Label_Options, "Label_Options");

	tgui::Label::Ptr Label_Language = tgui::Label::create(" ");
	Label_Language->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	Label_Language->setOrigin(0, 0.5);
	Label_Language->setPosition("8%", "25%");
	Panel_Options->add(Label_Language, "Label_Language");

	tgui::ComboBox::Ptr ComboBox_Languages = tgui::ComboBox::create();
	ComboBox_Languages->setOrigin(1, 0.5);
	ComboBox_Languages->setPosition("85%", "25%");
	ComboBox_Languages->setSize("34%", "4%");
	ComboBox_Languages->onItemSelect(&Class_Engine::ChangeLanguage, this);
	ComboBox_Languages->setChangeItemOnScroll(true);
	ComboBox_Languages->getRenderer()->setBorders(0);
	ComboBox_Languages->getRenderer()->setPadding({ 5, 0, 0, 0 });
	Panel_Options->add(ComboBox_Languages, "ComboBox_Languages");

	tgui::Label::Ptr Label_OnDemandTextures = tgui::Label::create(" ");
	Label_OnDemandTextures->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	Label_OnDemandTextures->setOrigin(0, 0.5);
	Label_OnDemandTextures->setPosition("8%", "35%");
	Panel_Options->add(Label_OnDemandTextures, "Label_OnDemandTextures");

	tgui::CheckBox::Ptr Checkbox_OnDemandTextures = tgui::CheckBox::create();
	Checkbox_OnDemandTextures->setOrigin(0.5, 0.5);
	Checkbox_OnDemandTextures->setPosition("85%", "35%");
	Checkbox_OnDemandTextures->setChecked(Options["bOnDemandTextures"] == "true");
	Checkbox_OnDemandTextures->onCheck([&] { Options.insert_or_assign("bOnDemandTextures", "true"); });
	Checkbox_OnDemandTextures->onUncheck([&] { Options.insert_or_assign("bOnDemandTextures", "false"); });
	Panel_Options->add(Checkbox_OnDemandTextures, "Checkbox_OnDemandTextures");

	tgui::Label::Ptr Label_OcclusionFilter = tgui::Label::create("Occlusion Low-Pass Filter");
	Label_OcclusionFilter->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	Label_OcclusionFilter->setOrigin(0, 0.5);
	Label_OcclusionFilter->setPosition("8%", "49%");
	Panel_Options->add(Label_OcclusionFilter, "Label_OcclusionFilter");

	tgui::CheckBox::Ptr Checkbox_OcclusionFilter = tgui::CheckBox::create();
	Checkbox_OcclusionFilter->setOrigin(0.5, 0.5);
	Checkbox_OcclusionFilter->setPosition("85%", "49%");
	Checkbox_OcclusionFilter->setChecked(Options["bOcclusionFilter"] == "true");
	Checkbox_OcclusionFilter->onCheck([&] { Options.insert_or_assign("bOcclusionFilter", "true"); });
	Checkbox_OcclusionFilter->onUncheck([&] { Options.insert_or_assign("bOcclusionFilter", "false"); });
	Panel_Options->add(Checkbox_OcclusionFilter, "Checkbox_OcclusionFilter");

	tgui::Label::Ptr Label_HrtfFilter = tgui::Label::create("HRTF Low-Pass Filter");
	Label_HrtfFilter->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	Label_HrtfFilter->setOrigin(0, 0.5);
	Label_HrtfFilter->setPosition("8%", "55%");
	Panel_Options->add(Label_HrtfFilter, "Label_HrtfFilter");

	tgui::CheckBox::Ptr Checkbox_HrtfFilter = tgui::CheckBox::create();
	Checkbox_HrtfFilter->setOrigin(0.5, 0.5);
	Checkbox_HrtfFilter->setPosition("85%", "55%");
	Checkbox_HrtfFilter->setChecked(Options["bHrtfFilter"] == "true");
	Checkbox_HrtfFilter->onCheck([&] { Options.insert_or_assign("bHrtfFilter", "true"); });
	Checkbox_HrtfFilter->onUncheck([&] { Options.insert_or_assign("bHrtfFilter", "false"); });
	Panel_Options->add(Checkbox_HrtfFilter, "Checkbox_HrtfFilter");

	tgui::Label::Ptr Label_DistanceFilter = tgui::Label::create("Distance Low/High-Pass Filter");
	Label_DistanceFilter->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	Label_DistanceFilter->setOrigin(0, 0.5);
	Label_DistanceFilter->setPosition("8%", "61%");
	Panel_Options->add(Label_DistanceFilter, "Label_DistanceFilter");

	tgui::CheckBox::Ptr Checkbox_DistanceFilter = tgui::CheckBox::create();
	Checkbox_DistanceFilter->setOrigin(0.5, 0.5);
	Checkbox_DistanceFilter->setPosition("85%", "61%");
	Checkbox_DistanceFilter->setChecked(Options["bDistanceFilter"] == "true");
	Checkbox_DistanceFilter->onCheck([&] { Options.insert_or_assign("bDistanceFilter", "true"); });
	Checkbox_DistanceFilter->onUncheck([&] { Options.insert_or_assign("bDistanceFilter", "false"); });
	Panel_Options->add(Checkbox_DistanceFilter, "Checkbox_DistanceFilter");

	tgui::Label::Ptr Label_Sound = tgui::Label::create(" ");
	Label_Sound->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	Label_Sound->setOrigin(0, 0.5);
	Label_Sound->setPosition("8%", "74%");

	tgui::CheckBox::Ptr Checkbox_Sound = tgui::CheckBox::create();
	Checkbox_Sound->setOrigin(0.5, 0.5);
	Checkbox_Sound->setPosition("85%", "74%");
	Checkbox_Sound->setChecked(Options["bSound"] == "true");
	Checkbox_Sound->onCheck([&] { Options.insert_or_assign("bSound", "false"); });
	Checkbox_Sound->onUncheck([&] { Options.insert_or_assign("bSound", "true"); });

	tgui::Label::Ptr Label_Music = tgui::Label::create(" ");
	Label_Music->setTextSize(15);
	Label_Music->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	Label_Music->setOrigin(0, 0.5);
	Label_Music->setPosition("8%", "80%");

	tgui::CheckBox::Ptr Checkbox_Music = tgui::CheckBox::create();
	Checkbox_Music->setOrigin(0.5, 0.5);
	Checkbox_Music->setPosition("85%", "80%");
	Checkbox_Music->setChecked(Options["bMusic"] == "true");
	Checkbox_Music->onCheck([&] { Options.insert_or_assign("bMusic", "false"); });
	Checkbox_Music->onUncheck([&] { Options.insert_or_assign("bMusic", "true"); });

	tgui::Label::Ptr Label_Message1 = tgui::Label::create(" ");
	Label_Message1->setTextSize(10);
	Label_Message1->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	Label_Message1->setOrigin(0.5, 0.5);
	Label_Message1->setPosition("50%", "85%");

	tgui::Button::Ptr Button_Save = tgui::Button::create(" ");
	Button_Save->getRenderer()->setBorders(0);
	Button_Save->setOrigin(0.5, 0.5);
	Button_Save->setPosition("30%", "91%");
	Button_Save->setSize(111, 34);
	Button_Save->onClick([&] { if (ApplyOptions()) { Window_Options->close(); }});

	tgui::Button::Ptr Button_Cancel = tgui::Button::create(" ");
	Button_Cancel->getRenderer()->setBorders(0);
	Button_Cancel->setOrigin(0.5, 0.5);
	Button_Cancel->setPosition("70%", "91%");
	Button_Cancel->setSize(111, 34);
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

	tgui::Button::Ptr Button_MoveBar = tgui::Button::create();
	Button_MoveBar->setOrigin(0.5, 0.5);
	Button_MoveBar->getRenderer()->setBorders(0);
	Button_MoveBar->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
	Button_MoveBar->getRenderer()->setBackgroundColorDown(tgui::Color::Transparent);
	Button_MoveBar->getRenderer()->setBackgroundColorHover(tgui::Color::Transparent);
	Button_MoveBar->setPosition("42%", "10%");
	Button_MoveBar->setSize("75%", "20%");
	Panel_Options->add(Button_MoveBar, "Button_MoveBar");

	Panel_Options->add(Button_Cancel, "Button_Cancel");
	Panel_Options->add(Button_Save, "Button_Save");
	Panel_Options->add(Label_Sound, "Label_Sound");
	Panel_Options->add(Checkbox_Sound, "Checkbox_Sound");
	Panel_Options->add(Label_Music, "Label_Music");
	Panel_Options->add(Checkbox_Music, "Checkbox_Music");
	Panel_Options->add(Label_Message1, "Label_Message1");
}

void Class_Engine::CancelChanges()
{
	CurrentLanguage = PreviousLanguage;

	tgui::ComboBox::Ptr ComboBox_Languages = GUI_Options.get<tgui::ComboBox>("ComboBox_Languages");
	ComboBox_Languages->setSelectedItemById(CurrentLanguage);

	std::ofstream File_language(std::string(CurentDocumentsPath) + std::string("\\AppData\\Roaming\\Mount&Blade Warband WSE2\\language.txt"));
	if (File_language.good())
	{
		File_language << CurrentLanguage;
		File_language.close();
	}
	ReadLocalizationFiles();
	UpdateText();
	Window_Options->close();
}