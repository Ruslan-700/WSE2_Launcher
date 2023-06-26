#include "Engine.h"

void Class_Engine::Button_Launch_onClick()
{
	LaunchGame(ExeType_NotDedicatedServer);
}

void Class_Engine::Button_Launch_Dedicated_onClick()
{
	LaunchGame(ExeType_DedicatedServer);
}

void Class_Engine::LaunchGame(ExeType L_ExeType)
{
	std::string ExeName, Arguments;
	if (L_ExeType == ExeType_DedicatedServer) {
		ExeName = EXECUTABLE_DEDICATED;
		Arguments = ExeName + "--config-path server_config.ini -r " + GetCurrentModule() + ".txt --module" + GetCurrentModule();
	}
	else  {
		ExeName = EXECUTABLE;
		Arguments = ExeName + " --module " + GetCurrentModule() + " --no-intro";
		}

	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;
	if (CreateProcess((LPCSTR)ExeName.c_str(), (LPSTR)Arguments.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
	{
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
		Window_Main->close();
	}
}

void Class_Engine::Button_Options_onClick()
{
	if (Window_Options == nullptr) {
		if (UpdateOptions()) {
			Window_Options = std::make_shared<sf::RenderWindow>();
			Window_Options->create({ 421, 489 }, "Options", sf::Style::None);
			GUI_Options.setTarget(*Window_Options);
			PreviousLanguage = CurrentLanguage;
		}
	}
	else Window_Options->close();
}