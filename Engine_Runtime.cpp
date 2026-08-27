#include "Engine.h"

void Class_Engine::Runtime()
{
	while (Window_Main->isOpen()) {
		if (!UpdateThread_IsRunning.load() && !UpdateThread_future.valid()) {
			UpdateThread_future = std::async(std::launch::async, [this] {UpdateThread_IsRunning.store(true);  UpdateThread(); UpdateThread_IsRunning.store(false); });
		}
		UpdateThread_Mutex.lock();
		Interact_Main();
		Window_Main->clear(sf::Color::White);
		GUI_Main.draw();
		UpdateThread_Mutex.unlock();
		Window_Main->display();
		if (Window_Options != nullptr) {
			if (Window_Options->isOpen()) {
				Interact_Options();
				Window_Options->clear(sf::Color::White);
				GUI_Options.draw();
				Window_Options->display();
			}
			else Window_Options = nullptr;
		}
	}
}
