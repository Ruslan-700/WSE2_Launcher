#include "Engine.h"

void Class_Engine::Interact()
{
	sf::Event event;
	while (Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) Window->close();
		bool L_InteractionResult = GUI.handleEvent(event);
	}
}
