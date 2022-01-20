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
	std::string ExeName;
	if (L_ExeType == ExeType_DedicatedServer) ExeName = "mb_warband_wse2_dedicated.exe";
	else  ExeName = "mb_warband_wse2.exe";

	std::string Arguments = ExeName + " --module " + ComboBoxModule->getSelectedItemId().toStdString() + " --no-intro";
	std::cout << Arguments << std::endl;

	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;
	if (CreateProcess((LPCSTR)ExeName.c_str(), (LPSTR)Arguments.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
	{
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
		Window->close();
	}
}