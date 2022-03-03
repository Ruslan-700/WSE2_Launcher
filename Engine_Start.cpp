#include "Engine.h"

void Class_Engine::Start()
{
	Window_Main = std::make_shared<sf::RenderWindow>();
	Window_Main->create({ 800, 600 }, "WSE2 Launcher");
	GUI_Main.setTarget(*Window_Main);
	Initialize();
	Runtime();
}
