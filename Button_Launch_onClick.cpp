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
		ExeName = "mb_warband_wse2_dedicated.exe";
		Arguments = ExeName + "--config-path server_config.ini -r " + CurrentModule() + ".txt --module" + CurrentModule();
	}
	else  {
		ExeName = "mb_warband_wse2.exe";
		Arguments = ExeName + " --module " + CurrentModule() + " --no-intro";
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