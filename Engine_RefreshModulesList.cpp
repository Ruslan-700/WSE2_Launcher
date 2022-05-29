#include "Engine.h"

void Class_Engine::RefreshModulesList()
{
	Modules.clear();
	std::string Path = "Modules/";
	try {
		if (!std::filesystem::is_directory(std::filesystem::path(L"Modules/"))) {
			return;
		}
		for (const auto& Entry : std::filesystem::directory_iterator(Path)) {
			std::size_t Pos = Entry.path().generic_string().find("/");
			if (std::filesystem::exists(Entry.path().generic_string() + "/module.ini")) {
				Modules.push_back(Entry.path().generic_string().substr(Pos + 1));
			}
		}
	}
	catch (const std::exception& Exception) { DisplayErrorMessageMain("Error (unhandled exception in RefreshModulesList) - ''" + std::string(Exception.what()) + "''. "); }

	for (size_t i = 0; i < Modules.size(); i++)
	{
		ComboBoxModule->addItem(Modules[i], Modules[i]);
	}

	ComboBoxModule->setSelectedItem(GetLastModule());
}

std::string Class_Engine::GetCurrentModule()
{
	return ComboBoxModule->getSelectedItemId().toStdString();
}
