#include "Engine.h"

void Class_Engine::RefreshModulesList()
{
	Modules.clear();
	std::string Path = "Modules/";
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

std::string Class_Engine::CurrentModule()
{
	return ComboBoxModule->getSelectedItemId().toStdString();
}
