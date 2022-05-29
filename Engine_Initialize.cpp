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
	Panel_Main->getRenderer()->setTextureBackground(Texture_MainBackground);
	Panel_Options->getRenderer()->setTextureBackground(Texture_OptionsBackground);
	Font_Latin = tgui::Font(RawFont_Latin, RawFont_Latin_Length);
	Font_Cyrillic = tgui::Font(RawFont_Cyrillic, RawFont_Cyrillic_Length);
}

void Class_Engine::UpdateText()
{
	float DefaultTextSize = 18;
	if (CurrentLanguage == "ru") DefaultTextSize = 15;

	GUI_Main.setFont(Font_Latin);
	GUI_Options.setFont(Font_Latin);

	tgui::Button::Ptr Button_Launch = GUI_Main.get<tgui::Button>("Button_Launch");
	tgui::Button::Ptr Button_Launch_Dedicated = GUI_Main.get<tgui::Button>("Button_Launch_Dedicated");
	tgui::Button::Ptr Button_Options = GUI_Main.get<tgui::Button>("Button_Options");
	tgui::Button::Ptr Button_Exit = GUI_Main.get<tgui::Button>("Button_Exit");

	Button_Launch->setText(GetLocalizedTextEntry(L"ui_wse2_start_game"));
	Button_Launch_Dedicated->setText(GetLocalizedTextEntry(L"ui_wse2_start_dedicated"));
	Button_Options->setText(GetLocalizedTextEntry(L"ui_configure"));
	Button_Exit->setText(GetLocalizedTextEntry(L"ui_close"));

	Button_Launch->setTextSize(DefaultTextSize);
	Button_Launch_Dedicated->setTextSize(DefaultTextSize);
	Button_Options->setTextSize(DefaultTextSize);
	Button_Exit->setTextSize(DefaultTextSize);

	if (CurrentLanguage == "en") Button_Options->setText("Options");
	if (CurrentLanguage == "ru") {
		GUI_Main.setFont(Font_Cyrillic);
		GUI_Options.setFont(Font_Cyrillic);
	}
}

std::wstring Class_Engine::GetLocalizedTextEntry(std::wstring Key)
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
	HRESULT Result = SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, SHGFP_TYPE_CURRENT, CurentDocumentsPath);
	if (Result != S_OK) {
		Label_Message1->setText(Label_Message1->getText() + "Error - could not open current user folder. ");
	}
}

void Class_Engine::ReadCurrentLanguage()
{
	std::ifstream File_language(std::string(CurentDocumentsPath) + std::string("\\AppData\\Roaming\\Mount&Blade Warband WSE2\\language.txt"));
	if (File_language.good())
	{
		std::getline(File_language, CurrentLanguage);
	}
}

void Class_Engine::ReadLocalizationFiles()
{
	LocalizedText.clear();
	std::wifstream File_uimain(std::string("languages\\" + CurrentLanguage + "\\uimain.csv"));
	std::wifstream File_uiwse2(std::string("languages\\" + CurrentLanguage + "\\uiwse2.csv"));
	std::wstring Line;
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
	if (File_uiwse2.is_open()) {
		while (std::getline(File_uiwse2, Line))
		{
			std::string::size_type Position = Line.find('|');
			if (Position != std::string::npos)
			{
				LocalizedText.insert(std::pair(Line.substr(0, Position), Line.substr(Position + 1)));
			}
		}
		File_uiwse2.close();
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

}