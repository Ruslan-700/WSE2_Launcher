#include "Engine.h"

void Class_Engine::Button_Options_onClick()
{
	if (Window_Options == nullptr) {
		if (UpdateOptions()) {
		Window_Options = std::make_shared<sf::RenderWindow>();
		Window_Options->create({ 400, 400 }, "Options");
		GUI_Options.setTarget(*Window_Options);
		Panel_Options = tgui::Panel::create();
		GUI_Options.add(Panel_Options, "Panel_Options");

		tgui::Label::Ptr Label_Options = tgui::Label::create("Options");
		Label_Options->setTextSize(25);
		Label_Options->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
		Label_Options->setOrigin(0.5, 0.5);
		Label_Options->setPosition("50%", "6%");

		tgui::Label::Ptr Label_Sound = tgui::Label::create("Sound");
		Label_Sound->setTextSize(15);
		Label_Sound->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
		Label_Sound->setOrigin(0, 0.5);
		Label_Sound->setPosition("10%", "20%");

		tgui::CheckBox::Ptr Checkbox_Sound = tgui::CheckBox::create();
		Checkbox_Sound->setOrigin(0.5, 0.5);
		Checkbox_Sound->setPosition("50%", "20%");
		Checkbox_Sound->setChecked(Options["bSound"] == "true");
		Checkbox_Sound->onCheck([&] { Options.insert_or_assign("bSound", "true"); });
		Checkbox_Sound->onUncheck([&] { Options.insert_or_assign("bSound", "false"); });

		tgui::Label::Ptr Label_Music = tgui::Label::create("Music");
		Label_Music->setTextSize(15);
		Label_Music->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
		Label_Music->setOrigin(0, 0.5);
		Label_Music->setPosition("10%", "30%");

		tgui::CheckBox::Ptr Checkbox_Music = tgui::CheckBox::create();
		Checkbox_Music->setOrigin(0.5, 0.5);
		Checkbox_Music->setPosition("50%", "30%");
		Checkbox_Music->setChecked(Options["bMusic"] == "true");
		Checkbox_Music->onCheck([&] { Options.insert_or_assign("bMusic", "true"); });
		Checkbox_Music->onUncheck([&] { Options.insert_or_assign("bMusic", "false"); });

		tgui::Label::Ptr Label_Message1 = tgui::Label::create(" ");
		Label_Message1->setTextSize(10);
		Label_Message1->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
		Label_Message1->setOrigin(0.5, 0.5);
		Label_Message1->setPosition("50%", "78%");

		tgui::Button::Ptr Button_Save = tgui::Button::create("Save");
		Button_Save->getRenderer()->setBorders(tgui::Borders::Outline(2));
		Button_Save->getRenderer()->setBorderColor(tgui::Color::Black);
		Button_Save->setOrigin(0, 0.5);
		Button_Save->setPosition("10%", "85%");
		Button_Save->setSize("55%", "10%");
		Button_Save->onClick([&] { if (ApplyOptions()) { Window_Options->close(); }});

		tgui::Button::Ptr Button_Cancel = tgui::Button::create("Cancel");
		Button_Cancel->getRenderer()->setBorders(tgui::Borders::Outline(2));
		Button_Cancel->getRenderer()->setBorderColor(tgui::Color::Black);
		Button_Cancel->setOrigin(1, 0.5);
		Button_Cancel->setPosition("90%", "85%");
		Button_Cancel->setSize("20%", "10%");
		Button_Cancel->onClick([&] { Window_Options->close(); });

		Panel_Options->add(Button_Cancel, "Button_Cancel");
		Panel_Options->add(Button_Save, "Button_Save");
		Panel_Options->add(Label_Sound, "Label_Sound");
		Panel_Options->add(Checkbox_Sound, "Checkbox_Sound");
		Panel_Options->add(Label_Music, "Label_Music");
		Panel_Options->add(Checkbox_Music, "Checkbox_Music");
		Panel_Options->add(Label_Options, "Label_Options");
		Panel_Options->add(Label_Message1, "Label_Message1");
		}
	}
	else Window_Options->close();
}