#include "Global.h"
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#pragma warning( disable : 4996)

int main() {
	Class_Engine Engine;
	Engine.Start();
	return 0;
}