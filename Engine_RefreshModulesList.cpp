#include "Engine.h"

void Class_Engine::RefreshModulesList()
{
	Modules.clear();
	std::string Path = "Modules/";
	for (const auto& Entry : std::filesystem::directory_iterator(Path)) {
		std::size_t Pos = Entry.path().generic_string().find("/");
		Modules.push_back(Entry.path().generic_string().substr(Pos+1));
		std::cout << Modules.back() << std::endl;
	}
}
