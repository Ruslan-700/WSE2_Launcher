#include "Engine.h"

void Class_Engine::Runtime()
{
	while (Window_Main->isOpen()) {
		if (!FTPThread_IsRunning) FTPThread_future = std::async(std::launch::async, [&] {FTPThread_IsRunning = true;  Class_Engine::FTPThread(); FTPThread_IsRunning = false; });
		FTPThread_Mutex.lock();
		Interact_Main();
		FTPThread_Mutex.unlock();
		Window_Main->clear(sf::Color::White);
		GUI_Main.draw();
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