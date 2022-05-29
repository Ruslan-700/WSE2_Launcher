#include "Global.h"

void Class_Engine::UpdateText()
{

	tgui::Button::Ptr Button_FTP = GUI_Main.get<tgui::Button>("Button_FTP");
	tgui::Button::Ptr Button_Launch = GUI_Main.get<tgui::Button>("Button_Launch");
	tgui::Button::Ptr Button_Launch_Dedicated = GUI_Main.get<tgui::Button>("Button_Launch_Dedicated");
	tgui::Button::Ptr Button_Options = GUI_Main.get<tgui::Button>("Button_Options");
	tgui::Button::Ptr Button_Exit = GUI_Main.get<tgui::Button>("Button_Exit");
	tgui::Label::Ptr Label_CurrentModule = GUI_Main.get<tgui::Label>("Label_CurrentModule");
	tgui::Label::Ptr Label_FTP = GUI_Main.get<tgui::Label>("Label_FTP");
	tgui::ComboBox::Ptr ComboBoxModule = GUI_Main.get<tgui::ComboBox>("ComboBoxModule");
	tgui::Label::Ptr Label_WSE2Version = GUI_Main.get<tgui::Label>("Label_WSE2Version");
	tgui::Label::Ptr Label_OcclusionFilter = GUI_Options.get<tgui::Label>("Label_OcclusionFilter");
	tgui::Label::Ptr Label_DistanceFilter = GUI_Options.get<tgui::Label>("Label_DistanceFilter");
	tgui::Label::Ptr Label_HrtfFilter = GUI_Options.get<tgui::Label>("Label_HrtfFilter");
	tgui::Label::Ptr Label_Options = GUI_Options.get<tgui::Label>("Label_Options");
	tgui::Label::Ptr Label_Sound = GUI_Options.get<tgui::Label>("Label_Sound");
	tgui::Label::Ptr Label_Music = GUI_Options.get<tgui::Label>("Label_Music");
	tgui::Label::Ptr Label_Language = GUI_Options.get<tgui::Label>("Label_Language");
	tgui::Label::Ptr Label_OnDemandTextures = GUI_Options.get<tgui::Label>("Label_OnDemandTextures");
	tgui::Button::Ptr Button_Save = GUI_Options.get<tgui::Button>("Button_Save");
	tgui::Button::Ptr Button_Cancel = GUI_Options.get<tgui::Button>("Button_Cancel");
	tgui::ComboBox::Ptr ComboBox_Languages = GUI_Options.get<tgui::ComboBox>("ComboBox_Languages");

	GUI_Main.setFont(Font_Latin);
	GUI_Options.setFont(Font_Latin);

	float DefaultTextSize = 18;

	if (CurrentLanguage == "ru" || CurrentLanguage == "tr") { // mordred doesnt support these languages so use pt serif instead
		GUI_Main.setFont(Font_Universal);
		GUI_Options.setFont(Font_Universal);
		DefaultTextSize = 15;
	}

	Button_Launch->setText(GetLocalizedTextEntry("ui_play"));
	Button_Launch_Dedicated->setText(GetLocalizedTextEntry("ui_start_dedicated"));
	Button_Options->setText(GetLocalizedTextEntry("ui_options"));
	Button_Exit->setText(GetLocalizedTextEntry("ui_exit"));
	Label_Options->setText(GetLocalizedTextEntry("ui_options"));
	Label_Sound->setText(GetLocalizedTextEntry("ui_disable_sound"));
	Label_Music->setText(GetLocalizedTextEntry("ui_disable_music"));
	Label_Language->setText(GetLocalizedTextEntry("ui_language"));
	Button_Save->setText(GetLocalizedTextEntry("ui_save"));
	Button_Cancel->setText(GetLocalizedTextEntry("ui_cancel"));
	Label_CurrentModule->setText(GetLocalizedTextEntry("ui_current_module"));
	Label_OnDemandTextures->setText(GetLocalizedTextEntry("ui_ondemand_textures"));

	switch (Current_FTPDownloadState)
	{
	case FTPDownloadState_WaitingInstall:
		Button_FTP->setText(GetLocalizedTextEntry("ui_install_wse2"));
		Label_FTP->setText(GetLocalizedTextEntry("ui_wse2_not_installed"));
		break;
	case FTPDownloadState_WaitingUpdate:
		Button_FTP->setText(GetLocalizedTextEntry("ui_update_wse2"));
		Label_FTP->setText(GetLocalizedTextEntry("ui_newer_version_available"));
		break;
	case FTPDownloadState_Downloading:
		Button_FTP->setText(GetLocalizedTextEntry("ui_please_wait"));
		Label_FTP->setText(GetLocalizedTextEntry("ui_downloading_"));
		break;
	case FTPDownloadState_Updated:
		Label_FTP->setText(GetLocalizedTextEntry("ui_version_is_up_to_date"));
		break;
	}

	Button_FTP->setTextSize(DefaultTextSize * 1.13);
	Button_Launch->setTextSize(DefaultTextSize * 1.13);
	Button_Launch_Dedicated->setTextSize(DefaultTextSize * 1.13);
	Button_Options->setTextSize(DefaultTextSize * 1.13);
	Button_Exit->setTextSize(DefaultTextSize * 1.13);
	Label_CurrentModule->setTextSize(DefaultTextSize);
	Label_Sound->setTextSize(DefaultTextSize * 0.9);
	Label_Music->setTextSize(DefaultTextSize * 0.9);
	Label_HrtfFilter->setTextSize(DefaultTextSize * 0.9);
	Label_DistanceFilter->setTextSize(DefaultTextSize * 0.9);
	Label_OcclusionFilter->setTextSize(DefaultTextSize * 0.9);
	Label_Language->setTextSize(DefaultTextSize * 0.9);
	Button_Save->setTextSize(DefaultTextSize * 0.92);
	Button_Cancel->setTextSize(DefaultTextSize * 0.92);
	ComboBoxModule->setTextSize(DefaultTextSize);
	ComboBox_Languages->setTextSize(DefaultTextSize * 0.8);
	Label_Options->setTextSize(DefaultTextSize * 1.1);
	Label_OnDemandTextures->setTextSize(DefaultTextSize * 0.9);
	Label_FTP->setTextSize(12);

	ComboBox_Languages->getRenderer()->setFont(Font_Universal);
	ComboBox_Languages->getRenderer()->setListBox(tgui::ListBoxRenderer(ComboBox_Languages->getRenderer()->getListBox()).clone());
	tgui::ListBoxRenderer(ComboBox_Languages->getRenderer()->getListBox()).setFont(Font_Universal);
	Label_WSE2Version->getRenderer()->setFont(Font_Universal);
	Label_FTP->getRenderer()->setFont(Font_Universal);
}