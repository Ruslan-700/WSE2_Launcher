#include "Engine.h"

void Class_Engine::Interact_Main()
{
	sf::Event event;
	while (Window_Main->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) Window_Main->close();
		bool InteractionResult = GUI_Main.handleEvent(event);
	}
}
void Class_Engine::Interact_Options()
{
	sf::Event event;
	while (Window_Options->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) Window_Options->close();
		bool InteractionResult = GUI_Options.handleEvent(event);
	}
}
