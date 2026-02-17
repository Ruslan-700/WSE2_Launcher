#include "Global.h"
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#pragma warning( disable : 4996)

#if !defined WFAS
FARPROC WINAPI delayHook(unsigned dliNotify, PDelayLoadInfo pdli)
{
	switch (dliNotify)
	{
		case dliNotePreLoadLibrary:
		{
			if (!strcmp(pdli->szDll, "steam_api.dll")) {
				HMODULE hModule = LoadLibrary("steam_api_wse2.dll");
				if (hModule) return (FARPROC)hModule;
			}
			break;
		}
	}

	return NULL;
}

PfnDliHook __pfnDliNotifyHook2 = delayHook;
#endif

int main() {
	Class_Engine Engine;
	Engine.Start();
	return 0;
}