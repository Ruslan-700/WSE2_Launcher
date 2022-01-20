#include "Engine.h"

void Class_Engine::Start()
{
	Window = new sf::RenderWindow{ {800, 600}, "WSE2 Launcher" };
	GUI.setTarget(*Window);
	Initialize();
	Runtime();
}
