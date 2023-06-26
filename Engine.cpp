#include "Engine.h"

void Class_Engine::Initialize()
{
	Initialize_UI_Main();
	Initialize_UI_Options();

	ReadCurrentUserPath();
	ReadCurrentLanguage();
	ReadLocalizationFiles();
	ReadWSE2Version();
	RefreshModulesList();
	CreateDefaultRglConfig();

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
	RegOpenKeyExW(HKEY_CURRENT_USER, REGISTRY_KEY, 0, KEY_READ, &Key);
	Error = RegQueryValueExW(Key, L"last_module_warband", 0, NULL, (LPBYTE)Buffer, &BufferSize);
	if (Error == ERROR_SUCCESS) Result = Buffer;
	return Result;
}

void Class_Engine::SetLastModule()
{
	HKEY Key;
	RegOpenKeyExW(HKEY_CURRENT_USER, REGISTRY_KEY, 0, KEY_WRITE, &Key);
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
	TguiButton->getRenderer()->setBorders(tgui::Borders::Outline(0));
	TguiButton->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
	TguiButton->getRenderer()->setBackgroundColorDown(tgui::Color::Transparent);
	TguiButton->getRenderer()->setBackgroundColorHover(tgui::Color::Transparent);
	TguiButton->getRenderer()->setBackgroundColorFocused(tgui::Color::Transparent);
	TguiButton->getRenderer()->setBackgroundColorDownFocused(tgui::Color::Transparent);
	TguiButton->setOrigin(0.5, 0.5);
	TguiButton->getRenderer()->setTextColor(tgui::Color(97, 70, 43));
	TguiButton->getRenderer()->setTextColorHover(tgui::Color(159, 52, 35));
	TguiButton->getRenderer()->setTextColorDown(tgui::Color(159, 52, 35));
	TguiButton->getRenderer()->setTextOutlineThickness(0.17);
}

void Class_Engine::ReadCurrentUserPath()
{
	HRESULT Result1 = SHGetFolderPath(0, CSIDL_MYDOCUMENTS, 0, 0, CurentDocumentsPath);
	if (Result1 != S_OK) DisplayErrorMessageMain("Error - could not open Documents folder. ");
	HRESULT Result2 = SHGetFolderPath(0, CSIDL_APPDATA, 0, 0, CurentAppdataPath);
	if (Result2 != S_OK) DisplayErrorMessageMain("Error - could not open Appdata folder. ");
	else try { if (!std::filesystem::is_directory(std::filesystem::path(CurentAppdataPath + std::string(MB_NAME_PATH)))) std::filesystem::create_directory(std::filesystem::path(CurentAppdataPath + std::string(MB_NAME_PATH))); }
	catch (const std::exception& Exception) { DisplayErrorMessageMain("Error (unhandled exception in ReadCurrentUserPath) - ''" + std::string(Exception.what()) + "''. ");  }
}

void Class_Engine::ReadCurrentLanguage()
{
	std::ifstream File_language(std::string(CurentAppdataPath) + MB_LANGUAGE);
	if (File_language.good())
	{
		try { std::getline(File_language, CurrentLanguage); }
		catch (const std::exception& Exception) { DisplayErrorMessageMain("Error (unhandled exception in ReadCurrentLanguage) - ''" + std::string(Exception.what()) + "''. "); }
		File_language.close();
	}
}

void Class_Engine::ReadLocalizationFiles()
{
		LocalizedText.clear();
		std::ifstream File_ui(std::string("languages\\" + CurrentLanguage + "\\ui.csv"));
		std::string Line;
		if (File_ui.good()) {
			try { while (std::getline(File_ui, Line)) {
					std::string::size_type Position = Line.find('|');
					if (Position != std::string::npos)
					{
						LocalizedText.insert(std::pair(Line.substr(0, Position), Line.substr(Position + 1)));
					}
				}
			} catch (const std::exception& Exception) { DisplayErrorMessageMain("Error (unhandled exception in ReadLocalizationFiles) - ''" + std::string(Exception.what()) + "''. "); }
			File_ui.close();
		}
		FillMissingLocalizationKeys();
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
	try {
		if (!std::filesystem::is_directory(std::filesystem::path(L"languages\\"))) {
			DisplayErrorMessageMain("Error - languages folder not found. ");
			return;
		}
		for (const auto& Entry : std::filesystem::directory_iterator(Path)) {
			std::size_t Pos = Entry.path().generic_string().find("\\");
			if (std::filesystem::exists(Entry.path().generic_string() + "\\uimain.csv")) {
				ComboBox_Languages->addItem(GetLanguageNameById(Entry.path().generic_string().substr(Pos + 11)), Entry.path().generic_string().substr(Pos + 11));
			}
		}
	} catch (const std::exception& Exception) { DisplayErrorMessageMain("Error (unhandled exception in BuildLanguagesList) - ''" + std::string(Exception.what()) + "''. "); }
	ComboBox_Languages->setSelectedItemById(CurrentLanguage);
}

void Class_Engine::ChangeLanguage()
{
	tgui::ComboBox::Ptr ComboBox_Languages = GUI_Options.get<tgui::ComboBox>("ComboBox_Languages");
	CurrentLanguage = ComboBox_Languages->getSelectedItemId().toStdString();
	std::ofstream File_language(std::string(CurentAppdataPath) + MB_LANGUAGE);
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

void Class_Engine::ReadWSE2Version()
{
	std::ifstream File_rgl_log("rgl_log.txt");
	std::string Line;
	if (File_rgl_log.good())
	{
		for (size_t i = 0; i < 5; i++)
		{
			try { std::getline(File_rgl_log, Line); }
			catch (const std::exception& Exception) { DisplayErrorMessageMain("Error (unhandled exception in ReadWSE2Version) - ''" + std::string(Exception.what()) + "''. "); continue; }
			auto Pos = Line.find(u8"WSE2 version:");
			if (Pos != std::string::npos) {
				for (size_t i = 0; i < 3; i++) Pos = Line.find_first_of(u8" ", Pos + 1);
				WSE2Version = wstring_Converter.from_bytes(Line.substr(Pos + 1, 4));
				break;
			}
		}
		File_rgl_log.close();
	}

	WCHAR Buffer[32];
	DWORD BufferSize = sizeof(Buffer);
	ULONG Error;
	HKEY Key1;
	RegOpenKeyExW(HKEY_CURRENT_USER, REGISTRY_KEY, 0, KEY_READ, &Key1);
	Error = RegQueryValueExW(Key1, L"wse2_version", 0, NULL, (LPBYTE)Buffer, &BufferSize);
	if (Error == ERROR_SUCCESS && (bool)std::iswdigit(Buffer[0]) && (WSE2Version == L"" || IsCurrentVersionOlderThan(Buffer))) WSE2Version = Buffer;
	else if (WSE2Version != L"") {
		HKEY Key2;
		RegOpenKeyExW(HKEY_CURRENT_USER, REGISTRY_KEY, 0, KEY_WRITE, &Key2);
		RegSetValueExW(Key2, L"wse2_version", 0, REG_SZ, (LPBYTE)WSE2Version.c_str(), wcslen(WSE2Version.c_str()) * sizeof(wchar_t));
	}

	if (WSE2Version != L"") {
		WSE2VersionWithDots = WSE2Version;
		for (size_t i = 1; i < 4; i++)  WSE2VersionWithDots.insert(i * 2 - 1, L".");
	}
	tgui::Label::Ptr Label_WSE2Version = GUI_Main.get<tgui::Label>("Label_WSE2Version");
	if (WSE2VersionWithDots != L"") Label_WSE2Version->setText(wstring_Converter.to_bytes(L"WSE2 ver. " + WSE2VersionWithDots));
}

Class_Engine::~Class_Engine()
{
	Current_FTPCommand = FTPCommand_Stop;
}

void Class_Engine::DisplayErrorMessageMain(std::string ErrorMessage)
{
	tgui::Label::Ptr Label_Message1 = GUI_Main.get<tgui::Label>("Label_Message1");
	Label_Message1->setText(Label_Message1->getText() + ErrorMessage);
}

void Class_Engine::DisplayErrorMessageOptions(std::string ErrorMessage)
{
	tgui::Label::Ptr Label_Message1 = GUI_Options.get<tgui::Label>("Label_Message1");
	Label_Message1->setText(Label_Message1->getText() + ErrorMessage);
}

void Class_Engine::CreateDefaultRglConfig()
{
	struct stat StatBuffer;
	if (stat(std::string((CurentDocumentsPath) + std::string(RGL_CONFIG)).c_str(), &StatBuffer) != 0) {
		std::ofstream File_RglConfig(std::string((CurentDocumentsPath) + std::string(RGL_CONFIG)).c_str(), std::ios::binary);
		if (File_RglConfig.good())
		{
		File_RglConfig.write(RawText_DefaultRglConfig, RawText_DefaultRglConfig_Length);
			File_RglConfig.close();
		}
	}
}