#include "Engine.h"

void Class_Engine::Initialize()
{
	ReadCurrentUserPath();
	ReadCurrentLanguage();
	ReadLocalizationFiles();
	RefreshModulesList();

	Initialize_UI_Main();
	Initialize_UI_Options();

	BuildLanguagesList();
	UpdateTextures();
	UpdateText();
	UpdateModPreviewImage();
}

void Class_Engine::Close() {
	Window_Main->close();
}

std::wstring Class_Engine::GetLastModule()
{
	std::wstring Result = L"Native";
	WCHAR Buffer[512];
	DWORD BufferSize = sizeof(Buffer);
	ULONG Error;
	HKEY Key;
	RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\MountAndBladeWarbandKeys", 0, KEY_READ, &Key);
	Error = RegQueryValueExW(Key, L"last_module_warband", 0, NULL, (LPBYTE)Buffer, &BufferSize);
	if (Error == ERROR_SUCCESS) Result = Buffer;
	return Result;
}

void Class_Engine::UpdateTextures()
{
	Texture_MainBackground.loadFromMemory(Image_MainBackground, Image_MainBackground_Length);
	Texture_OptionsBackground.loadFromMemory(Image_OptionsBackground, Image_OptionsBackground_Length);
	Texture_Close.loadFromMemory(Image_Close, Image_Close_Length);
	Texture_CloseDown.loadFromMemory(Image_CloseDown, Image_CloseDown_Length);
	Texture_Minimize.loadFromMemory(Image_Minimize, Image_Minimize_Length);
	Texture_MinimizeDown.loadFromMemory(Image_MinimizeDown, Image_MinimizeDown_Length);

	tgui::Button::Ptr Button_Close = GUI_Main.get<tgui::Button>("Button_Close");
	tgui::Button::Ptr Button_Minimize = GUI_Main.get<tgui::Button>("Button_Minimize");
	tgui::Button::Ptr Options_Button_Close = GUI_Options.get<tgui::Button>("Button_Close");
	tgui::Button::Ptr Options_Button_Minimize = GUI_Options.get<tgui::Button>("Button_Minimize");

	Button_Close->getRenderer()->setTexture(Texture_Close);
	Button_Close->getRenderer()->setTextureDown(Texture_CloseDown);
	Button_Minimize->getRenderer()->setTexture(Texture_Minimize);
	Button_Minimize->getRenderer()->setTextureDown(Texture_MinimizeDown);
	Options_Button_Close->getRenderer()->setTexture(Texture_Close);
	Options_Button_Close->getRenderer()->setTextureDown(Texture_CloseDown);
	Options_Button_Minimize->getRenderer()->setTexture(Texture_Minimize);
	Options_Button_Minimize->getRenderer()->setTextureDown(Texture_MinimizeDown);
	Panel_Main->getRenderer()->setTextureBackground(Texture_MainBackground);
	Panel_Options->getRenderer()->setTextureBackground(Texture_OptionsBackground);

	Font_Latin = tgui::Font(RawFont_Latin, RawFont_Latin_Length);
	Font_Universal = tgui::Font(RawFont_Universal, RawFont_Universal_Length);
}

void Class_Engine::UpdateText()
{
	float DefaultTextSize = 18;
	if (CurrentLanguage == "ru") DefaultTextSize = 17;

	GUI_Main.setFont(Font_Latin);
	GUI_Options.setFont(Font_Latin);

	tgui::Button::Ptr Button_Launch = GUI_Main.get<tgui::Button>("Button_Launch");
	tgui::Button::Ptr Button_Launch_Dedicated = GUI_Main.get<tgui::Button>("Button_Launch_Dedicated");
	tgui::Button::Ptr Button_Options = GUI_Main.get<tgui::Button>("Button_Options");
	tgui::Button::Ptr Button_Exit = GUI_Main.get<tgui::Button>("Button_Exit");
	tgui::Label::Ptr Label_Options = GUI_Options.get<tgui::Label>("Label_Options");
	tgui::Label::Ptr Label_Sound = GUI_Options.get<tgui::Label>("Label_Sound");
	tgui::Label::Ptr Label_Music = GUI_Options.get<tgui::Label>("Label_Music");
	tgui::Label::Ptr Label_Language = GUI_Options.get<tgui::Label>("Label_Language");
	tgui::Button::Ptr Button_Save = GUI_Options.get<tgui::Button>("Button_Save");
	tgui::Button::Ptr Button_Cancel = GUI_Options.get<tgui::Button>("Button_Cancel");

	Button_Launch->setText(GetLocalizedTextEntry("ui_play"));
	Button_Launch_Dedicated->setText(GetLocalizedTextEntry("ui_wse2_start_dedicated"));
	Button_Options->setText(GetLocalizedTextEntry("ui_options"));
	Button_Exit->setText(GetLocalizedTextEntry("ui_exit"));
	Label_Options->setText(GetLocalizedTextEntry("ui_options"));
	Label_Sound->setText(GetLocalizedTextEntry("ui_disable_sound"));
	Label_Music->setText(GetLocalizedTextEntry("ui_disable_music"));
	Label_Language->setText(GetLocalizedTextEntry("ui_language"));
	Button_Save->setText(GetLocalizedTextEntry("ui_save"));
	Button_Cancel->setText(GetLocalizedTextEntry("ui_cancel"));


	Button_Launch->setTextSize(DefaultTextSize);
	Button_Launch_Dedicated->setTextSize(DefaultTextSize);
	Button_Options->setTextSize(DefaultTextSize);
	Button_Exit->setTextSize(DefaultTextSize);
	Label_Sound->setTextSize(DefaultTextSize*0.9);
	Label_Music->setTextSize(DefaultTextSize * 0.9);
	Label_Language->setTextSize(DefaultTextSize * 0.9);
	Button_Save->setTextSize(DefaultTextSize);
	Button_Cancel->setTextSize(DefaultTextSize);

	if (CurrentLanguage == "ru") {
		GUI_Main.setFont(Font_Universal);
		GUI_Options.setFont(Font_Universal);
	}
}

std::string Class_Engine::GetLocalizedTextEntry(std::string Key)
{
	if (LocalizedText.find(Key) != LocalizedText.end()) return LocalizedText.find(Key)->second;
	return Key;
}

void Class_Engine::InitializeTextButton(tgui::Button::Ptr TguiButton) {
	TguiButton->getRenderer()->setBorders(tgui::Borders::Outline(0));
	TguiButton->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
	TguiButton->getRenderer()->setBackgroundColorDown(tgui::Color::Transparent);
	TguiButton->getRenderer()->setBackgroundColorHover(tgui::Color::Transparent);
	TguiButton->getRenderer()->setBackgroundColorFocused(tgui::Color::Transparent);
	TguiButton->getRenderer()->setBackgroundColorDownFocused(tgui::Color::Transparent);
	TguiButton->setOrigin(0.5, 0.5);
}

void Class_Engine::ReadCurrentUserPath()
{
	tgui::Label::Ptr Label_Message1 = GUI_Main.get<tgui::Label>("Label_Message1");
	HRESULT Result = SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, SHGFP_TYPE_CURRENT, CurentUserPath);
	if (Result != S_OK) {
		Label_Message1->setText(Label_Message1->getText() + "Error - could not open current user folder. ");
	}
}

void Class_Engine::ReadCurrentLanguage()
{
	std::ifstream File_language(std::string(CurentUserPath) + std::string("\\AppData\\Roaming\\Mount&Blade Warband WSE2\\language.txt"));
	if (File_language.good())
	{
		std::getline(File_language, CurrentLanguage);
		File_language.close();
	}
}

void Class_Engine::ReadLocalizationFiles()
{
	LocalizedText.clear();
	std::ifstream File_ui(std::string("languages\\" + CurrentLanguage + "\\ui.csv"));
	std::ifstream File_uimain(std::string("languages\\" + CurrentLanguage + "\\uimain.csv"));
	//std::wifstream File_uiwse2(std::string("languages\\" + CurrentLanguage + "\\uiwse2.csv"));
	std::string Line;
	if (File_ui.is_open()) {
		while (std::getline(File_ui, Line))
		{
			std::string::size_type Position = Line.find('|');
			if (Position != std::string::npos)
			{
				LocalizedText.insert(std::pair(Line.substr(0, Position), Line.substr(Position + 1)));
			}
		}
		File_ui.close();
	}
	if (File_uimain.is_open()) {
		while (std::getline(File_uimain, Line))
		{
			std::string::size_type Position = Line.find('|');
			if (Position != std::string::npos)
			{
				LocalizedText.insert(std::pair(Line.substr(0, Position), Line.substr(Position + 1)));
			}
		}
		File_uimain.close();
	}
	FillMissingLocalizationKeys();
}

void Class_Engine::FillMissingLocalizationKeys() // temp?
{
	if (CurrentLanguage == "en") {
		LocalizedText.insert(std::pair("ui_wse2_start_dedicated","Start dedicated server"));
	}
	if (CurrentLanguage == "ru") {
		LocalizedText.insert(std::pair("ui_wse2_start_dedicated", "Запустить выделенный сервер"));
	}
	if (CurrentLanguage == "de") {
		LocalizedText.insert(std::pair("ui_wse2_start_dedicated", "Starten dedizierten server"));
	}
	if (CurrentLanguage == "fr") {
		LocalizedText.insert(std::pair("ui_wse2_start_dedicated", "Démarrer le serveur dédié"));
	}
	if (CurrentLanguage == "cz") {
		LocalizedText.insert(std::pair("ui_wse2_start_dedicated", "Spusťte dedikovaný server"));
	}
	if (CurrentLanguage == "hu") {
		LocalizedText.insert(std::pair("ui_wse2_start_dedicated", "Indítsa el a dedikált szervert"));
	}
	if (CurrentLanguage == "es") {
		LocalizedText.insert(std::pair("ui_wse2_start_dedicated", "Iniciar servidor dedicado"));
	}
	if (CurrentLanguage == "tr") {
		LocalizedText.insert(std::pair("ui_wse2_start_dedicated", "Özel sunucuyu başlat"));
	}
	if (CurrentLanguage == "pl") {
		LocalizedText.insert(std::pair("ui_wse2_start_dedicated", "Uruchom serwer dedykowany"));
	}
	if (CurrentLanguage == "cns") {
		LocalizedText.insert(std::pair("ui_wse2_start_dedicated", "启动专用服务器"));
	}
	if (CurrentLanguage == "cnt") {
		LocalizedText.insert(std::pair("ui_wse2_start_dedicated", "啟動專用服務器"));
	}
}

void Class_Engine::UpdateModPreviewImage()
{
	tgui::Picture::Ptr Picture_ModPreview = GUI_Main.get<tgui::Picture>("Picture_ModPreview");
	Texture_ModPreview.loadFromFile("Modules\\" + CurrentModule() + "\\main.bmp");
	Picture_ModPreview->getRenderer()->setTexture(Texture_ModPreview);
}

void Class_Engine::BuildLanguagesList()
{
	tgui::ComboBox::Ptr ComboBox_Languages = GUI_Options.get<tgui::ComboBox>("ComboBox_Languages");
	std::string Path = "languages\\";
	if (!std::filesystem::is_directory(std::filesystem::path(L"languages\\"))) {
		tgui::Label::Ptr Label_Message1 = GUI_Main.get<tgui::Label>("Label_Message1");
		Label_Message1->setText(Label_Message1->getText() + "Error - languages folder not found. ");
		return;
	}
	for (const auto& Entry : std::filesystem::directory_iterator(Path)) {
		std::size_t Pos = Entry.path().generic_string().find("\\");
		if (std::filesystem::exists(Entry.path().generic_string() + "\\uimain.csv")) {
			ComboBox_Languages->addItem(Entry.path().generic_string().substr(Pos + 11), Entry.path().generic_string().substr(Pos + 11));
		}
	}
	ComboBox_Languages->setSelectedItemById(CurrentLanguage);
}

void Class_Engine::ChangeLanguage()
{
	tgui::ComboBox::Ptr ComboBox_Languages = GUI_Options.get<tgui::ComboBox>("ComboBox_Languages");
	CurrentLanguage = ComboBox_Languages->getSelectedItem().toStdString();
	std::ofstream File_language(std::string(CurentUserPath) + std::string("\\AppData\\Roaming\\Mount&Blade Warband WSE2\\language.txt"));
	if (File_language.good())
	{
		File_language << CurrentLanguage;
		File_language.close();
	}
	ReadLocalizationFiles();
	UpdateText();
}