#include "Engine.h"

void Class_Engine::Initialize()
{
	ReadCurrentUserPath();
	ReadCurrentLanguage();
	ReadLocalizationFiles();
	ReadWSE2Version();
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
	WCHAR Buffer[128];
	DWORD BufferSize = sizeof(Buffer);
	ULONG Error;
	HKEY Key;
	RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\MountAndBladeWarbandKeys", 0, KEY_READ, &Key);
	Error = RegQueryValueExW(Key, L"last_module_warband", 0, NULL, (LPBYTE)Buffer, &BufferSize);
	if (Error == ERROR_SUCCESS) Result = Buffer;
	return Result;
}

void Class_Engine::SetLastModule()
{
	HKEY Key;
	RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\MountAndBladeWarbandKeys", 0, KEY_WRITE, &Key);
	LONG error = RegSetValueEx(Key, "last_module_warband", 0, REG_SZ, (LPBYTE)GetCurrentModule().c_str(), strlen(GetCurrentModule().c_str()) + 1);
}

void Class_Engine::UpdateTextures()
{
	Texture_MainBackground.loadFromMemory(Image_MainBackground, Image_MainBackground_Length);
	Texture_OptionsBackground.loadFromMemory(Image_OptionsBackground, Image_OptionsBackground_Length);
	Texture_Close.loadFromMemory(Image_Close, Image_Close_Length);
	Texture_CloseDown.loadFromMemory(Image_CloseDown, Image_CloseDown_Length);
	Texture_Minimize.loadFromMemory(Image_Minimize, Image_Minimize_Length);
	Texture_MinimizeDown.loadFromMemory(Image_MinimizeDown, Image_MinimizeDown_Length);
	Texture_Button.loadFromMemory(Image_Button, Image_Button_Length);
	Texture_Button_Hover.loadFromMemory(Image_Button_Hover, Image_Button_Hover_Length);
	Texture_Button_Down.loadFromMemory(Image_Button_Down, Image_Button_Down_Length);
	Texture_Combobox.loadFromMemory(Image_Combobox, Image_Combobox_Length);
	Texture_Combobox_Arrow.loadFromMemory(Image_Combobox_Arrow, Image_Combobox_Arrow_Length);

	tgui::Button::Ptr Button_Close = GUI_Main.get<tgui::Button>("Button_Close");
	tgui::Button::Ptr Button_Minimize = GUI_Main.get<tgui::Button>("Button_Minimize");
	tgui::ComboBox::Ptr ComboBoxModule = GUI_Main.get<tgui::ComboBox>("ComboBoxModule");
	tgui::Button::Ptr Options_Button_Close = GUI_Options.get<tgui::Button>("Button_Close");
	tgui::Button::Ptr Options_Button_Minimize = GUI_Options.get<tgui::Button>("Button_Minimize");
	tgui::Button::Ptr Button_Save = GUI_Options.get<tgui::Button>("Button_Save");
	tgui::Button::Ptr Button_Cancel = GUI_Options.get<tgui::Button>("Button_Cancel");
	tgui::ComboBox::Ptr ComboBox_Languages = GUI_Options.get<tgui::ComboBox>("ComboBox_Languages");

	Button_Save->getRenderer()->setTexture(Texture_Button);
	Button_Save->getRenderer()->setTextureHover(Texture_Button_Hover);
	Button_Save->getRenderer()->setTextureDown(Texture_Button_Down);
	Button_Cancel->getRenderer()->setTexture(Texture_Button);
	Button_Cancel->getRenderer()->setTextureHover(Texture_Button_Hover);
	Button_Cancel->getRenderer()->setTextureDown(Texture_Button_Down);
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
	ComboBoxModule->getRenderer()->setTextureBackground(Texture_Combobox);
	ComboBoxModule->getRenderer()->setTextureArrow(Texture_Combobox_Arrow);
	ComboBox_Languages->getRenderer()->setTextureBackground(Texture_Combobox);
	ComboBox_Languages->getRenderer()->setTextureArrow(Texture_Combobox_Arrow);


	Font_Latin = tgui::Font(RawFont_Latin, RawFont_Latin_Length);
	Font_Universal = tgui::Font(RawFont_Universal, RawFont_Universal_Length);
}

std::string Class_Engine::GetLocalizedTextEntry(std::string Key)
{
	if (LocalizedText.find(Key) != LocalizedText.end()) return LocalizedText.find(Key)->second;
	return Key;
}

void Class_Engine::InitializeTextButton(tgui::Button::Ptr TguiButton) {
	//TguiButton->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
	TguiButton->getRenderer()->setBorders(tgui::Borders::Outline(0));
	TguiButton->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
	TguiButton->getRenderer()->setBackgroundColorDown(tgui::Color::Transparent);
	TguiButton->getRenderer()->setBackgroundColorHover(tgui::Color::Transparent);
	TguiButton->getRenderer()->setBackgroundColorFocused(tgui::Color::Transparent);
	TguiButton->getRenderer()->setBackgroundColorDownFocused(tgui::Color::Transparent);
	TguiButton->setOrigin(0.5, 0.5);
	TguiButton->getRenderer()->setTextColor(tgui::Color(97, 70, 43));
	TguiButton->getRenderer()->setTextColorHover(tgui::Color(182, 60, 41));
	TguiButton->getRenderer()->setTextColorDown(tgui::Color(182, 60, 41));
	TguiButton->getRenderer()->setTextOutlineThickness(0.17);
}

void Class_Engine::ReadCurrentUserPath()
{
	tgui::Label::Ptr Label_Message1 = GUI_Main.get<tgui::Label>("Label_Message1");
	HRESULT Result = SHGetFolderPath(0, CSIDL_MYDOCUMENTS, 0, 0, CurentDocumentsPath);
	if (Result != S_OK) {
		Label_Message1->setText(Label_Message1->getText() + "Error - could not open Documents folder. ");
	}
}

void Class_Engine::ReadCurrentLanguage()
{
	tgui::Label::Ptr Label_Message1 = GUI_Main.get<tgui::Label>("Label_Message1");
	HRESULT Result = SHGetFolderPath(0, CSIDL_APPDATA, 0, 0, CurentAppdataPath);
	if (Result != S_OK) {
		Label_Message1->setText(Label_Message1->getText() + "Error - could not open Appdata folder. ");
		return;
	}
	std::ifstream File_language(std::string(CurentAppdataPath) + std::string("\\Mount&Blade Warband WSE2\\language.txt"));
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
	FillMissingLocalizationKeys();
}

void Class_Engine::FillMissingLocalizationKeys() // because uimain.csv files have stupid non-unicode encoding i dont know how to parse
{
	if (CurrentLanguage == "en") {
		LocalizedText.insert(std::pair("ui_play", "Play M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_start_dedicated","Start dedicated server"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Disable sound"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Disable music"));
		LocalizedText.insert(std::pair("ui_language", u8"Language:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Current mod:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Load textures on demand:"));
	}
	if (CurrentLanguage == "ru") {
		LocalizedText.insert(std::pair("ui_play", u8"Играть в M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Запустить выделенный сервер"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Отключить звук"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Отключить музыку"));
		LocalizedText.insert(std::pair("ui_language", u8"Язык:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Текущий мод:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Загружать текстуры по необходимости:"));
	}
	if (CurrentLanguage == "de") {
		LocalizedText.insert(std::pair("ui_play", u8"M&B Warband WSE2 spielen"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Starten dedizierten server"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Musik deaktivieren"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Sound deaktivieren"));
		LocalizedText.insert(std::pair("ui_language", u8"Sprache:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Aktuelles Mod:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Texturen nach Bedarf laden:"));
	}
	if (CurrentLanguage == "fr") {
		LocalizedText.insert(std::pair("ui_play", u8"Jouer а M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Démarrer le serveur dédié"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Désactiver les sons"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Désactiver la musique"));
		LocalizedText.insert(std::pair("ui_language", u8"Langue:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Mod actuel:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Charger les textures а la demande:"));
	}
	if (CurrentLanguage == "cz") {
		LocalizedText.insert(std::pair("ui_play", u8"Hrát M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Spusťte dedikovaný server"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Vypnout zvuk"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Vypnout hudbu"));
		LocalizedText.insert(std::pair("ui_language", u8"Jazyk:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Aktuální mod:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Načíst textury na požádání:"));
	}
	if (CurrentLanguage == "hu") {
		LocalizedText.insert(std::pair("ui_play", u8"A M&B Warband WSE2 indítása"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Indítsa el a dedikált szervert"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Hangok kikapcsolása"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Zene kikapcsolása"));
		LocalizedText.insert(std::pair("ui_language", u8"Nyelv:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Jelenlegi mod:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Textúrák kívánság szerinti betöltése:"));
	}
	if (CurrentLanguage == "es") {
		LocalizedText.insert(std::pair("ui_play", u8"Jugar M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Iniciar servidor dedicado"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Desactivar sonido"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Desactivar música"));
		LocalizedText.insert(std::pair("ui_language", u8"El Idioma:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Mód actual:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Cargar texturas sobre demanda:"));
	}
	if (CurrentLanguage == "tr") {
		LocalizedText.insert(std::pair("ui_play", u8"M&B Warband WSE2'i Oyna"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Özel sunucuyu başlat"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Sesi Kapat"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Müziği Kapat"));
		LocalizedText.insert(std::pair("ui_language", u8"Dil:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Mevcut mod:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Dokuları ihtiyaç halinde yükle:"));
	}
	if (CurrentLanguage == "pl") {
		LocalizedText.insert(std::pair("ui_play", u8"Graj w M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Uruchom serwer dedykowany"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Wyłącz dźwięki"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Wyłącz muzykę"));
		LocalizedText.insert(std::pair("ui_language", u8"Język"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Aktualny moduł:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Wczytaj tekstury na żądanie:"));
	}
	if (CurrentLanguage == "cns") {
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"启动专用服务器"));
	}
	if (CurrentLanguage == "cnt") {
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"啟動專用服務器"));
	}
}

void Class_Engine::UpdateModPreviewImage()
{
	tgui::Picture::Ptr Picture_ModPreview = GUI_Main.get<tgui::Picture>("Picture_ModPreview");
	Texture_ModPreview.loadFromFile("Modules\\" + GetCurrentModule() + "\\main.bmp");
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
			ComboBox_Languages->addItem(GetLanguageNameById(Entry.path().generic_string().substr(Pos + 11)), Entry.path().generic_string().substr(Pos + 11));
		}
	}
	ComboBox_Languages->setSelectedItemById(CurrentLanguage);
}

void Class_Engine::ChangeLanguage()
{
	tgui::ComboBox::Ptr ComboBox_Languages = GUI_Options.get<tgui::ComboBox>("ComboBox_Languages");
	CurrentLanguage = ComboBox_Languages->getSelectedItemId().toStdString();
	std::ofstream File_language(std::string(CurentAppdataPath) + std::string("\\Mount&Blade Warband WSE2\\language.txt"));
	if (File_language.good())
	{
		File_language << CurrentLanguage;
		File_language.close();
	}
	ReadLocalizationFiles();
	UpdateText();
}

std::string Class_Engine::GetLanguageNameById(std::string LanguageId)
{

	if (LanguageId == "en") {
		return u8"English";
	}
	if (LanguageId == "ru") {
		return u8"Русский";
	}
	if (LanguageId == "de") {
		return u8"Deutsch";
	}
	if (LanguageId == "fr") {
		return u8"Français";
	}
	if (LanguageId == "cz") {
		return u8"Čeština";
	}
	if (LanguageId == "hu") {
		return u8"Magyar";
	}
	if (LanguageId == "es") {
		return u8"Español";
	}
	if (LanguageId == "tr") {
		return u8"Türkçe";
	}
	if (LanguageId == "pl") {
		return u8"Polski";
	}
	if (LanguageId == "cns") {
		return u8"Chinese (simplified)";
	}
	if (LanguageId == "cnt") {
		return u8"Chinese (traditional)";
	}
	return LanguageId;
}

void Class_Engine::ReadWSE2Version() // try to get wse2 version from rgl_log.txt, if failed then get it from registry
{
	std::ifstream File_rgl_log("rgl_log.txt");
	std::string Line;
	if (File_rgl_log.good())
	{
		for (size_t i = 0; i < 5; i++)
		{
			std::getline(File_rgl_log, Line);
			auto Pos = Line.find(u8"WSE2");
			if (Pos != std::string::npos) {
				for (size_t i = 0; i < 3; i++) Pos = Line.find_first_of(u8" ", Pos + 1);
				std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> Converter;
				WSE2Version = Converter.from_bytes(Line.substr(Pos+1, 4));
				HKEY Key;
				RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\MountAndBladeWarbandKeys", 0, KEY_WRITE, &Key);
				RegSetValueExW(Key, L"wse2_version", 0, REG_SZ, (LPBYTE)WSE2Version.c_str(), wcslen(WSE2Version.c_str()) * sizeof(wchar_t));
				for (size_t i = 1; i < 4; i++) WSE2Version.insert(i * 2 - 1, L".");
				break;
			}
		}
		File_rgl_log.close();
	}
	if (WSE2Version == L"") {
		WCHAR Buffer[32];
		DWORD BufferSize = sizeof(Buffer);
		ULONG Error;
		HKEY Key;
		RegOpenKeyExW(HKEY_CURRENT_USER, L"SOFTWARE\\MountAndBladeWarbandKeys", 0, KEY_READ, &Key);
		Error = RegQueryValueExW(Key, L"wse2_version", 0, NULL, (LPBYTE)Buffer, &BufferSize);
		if (Error == ERROR_SUCCESS) {
			WSE2Version = Buffer;
			for (size_t i = 1; i < 4; i++) WSE2Version.insert(i * 2 - 1, L".");
		}
	}
}