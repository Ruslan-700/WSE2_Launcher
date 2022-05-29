#include "Global.h"
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main() {
	Class_Engine Engine;
	Engine.Start();
	return 0;
}