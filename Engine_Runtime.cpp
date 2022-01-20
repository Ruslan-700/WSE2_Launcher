#include "Engine.h"

void Class_Engine::Runtime()
{
	while (Window->isOpen()) {
		Interact();
		Window->clear(sf::Color::White);
		GUI.draw();
		Window->display();
	}
}
