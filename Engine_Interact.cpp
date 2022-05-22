#include "Engine.h"

void Class_Engine::Interact_Main()
{
	MoveWindow_Main();
	sf::Event event;
	while (Window_Main->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) Window_Main->close();
		bool InteractionResult = GUI_Main.handleEvent(event);
	}
}
void Class_Engine::Interact_Options()
{
	MoveWindow_Options();
	sf::Event event;
	while (Window_Options->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) Window_Options->close();
		bool InteractionResult = GUI_Options.handleEvent(event);
	}
}

void Class_Engine::MoveWindow_Main()
{
	tgui::Button::Ptr Button_MoveBar = GUI_Main.get<tgui::Button>("Button_MoveBar");
	if (Window_Main->hasFocus() && MoveBar_X == -1 && Button_MoveBar->isMouseDown()) {
		MoveBar_X = sf::Mouse::getPosition().x - Window_Main->getPosition().x;
		MoveBar_Y = sf::Mouse::getPosition().y - Window_Main->getPosition().y;
	}
	if (MoveBar_X == -1 || !Button_MoveBar->isMouseDown()) {
		MoveBar_X = -1;
		return;
	}
		Window_Main->setPosition(sf::Vector2i(sf::Mouse::getPosition().x - MoveBar_X, sf::Mouse::getPosition().y - MoveBar_Y));
}

void Class_Engine::MoveWindow_Options()
{
	tgui::Button::Ptr Button_MoveBar = GUI_Options.get<tgui::Button>("Button_MoveBar");
	if (Window_Options->hasFocus() && Options_MoveBar_X == -1 && Button_MoveBar->isMouseDown()) {
		Options_MoveBar_X = sf::Mouse::getPosition().x - Window_Options->getPosition().x;
		Options_MoveBar_Y = sf::Mouse::getPosition().y - Window_Options->getPosition().y;
	}
	if (Options_MoveBar_X == -1 || !Button_MoveBar->isMouseDown()) {
		Options_MoveBar_X = -1;
		return;
	}
	Window_Options->setPosition(sf::Vector2i(sf::Mouse::getPosition().x - Options_MoveBar_X, sf::Mouse::getPosition().y - Options_MoveBar_Y));
}