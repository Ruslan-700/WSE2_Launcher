#include "Engine.h"

bool Class_Engine::UpdateOptions()
{
	Options.clear();
	std::ifstream File_rgl_config(std::string(CurentDocumentsPath) + std::string("/Mount&Blade Warband WSE2/rgl_config.ini"));
	std::string Line;
	if (File_rgl_config.is_open()) {
		while (std::getline(File_rgl_config, Line))
		{
			std::string::size_type Position = Line.find('=');
			if (Position != std::string::npos)
			{
				Options.insert(std::pair(Line.substr(0, Position), Line.substr(Position + 1)));
			}
		}
		File_rgl_config.close();
		return true;
	}
	else {
		DisplayErrorMessageMain("Error - could not open rgl_config.ini. ");
		return false;
	}
}

bool Class_Engine::ApplyOptions()
{
	std::string Line;
	std::ifstream File_rgl_config(std::string(CurentDocumentsPath) + std::string("/Mount&Blade Warband WSE2/rgl_config.ini"));
	std::remove(std::string(std::string(CurentDocumentsPath) + std::string("/Mount&Blade Warband WSE2/rgl_config_temp.ini")).c_str());
	std::ofstream OutputFile_rgl_config(std::string(CurentDocumentsPath) + std::string("/Mount&Blade Warband WSE2/rgl_config_temp.ini"));
	if (File_rgl_config.is_open() && OutputFile_rgl_config) {
		while (std::getline(File_rgl_config, Line))
		{
			std::string::size_type Position = Line.find('=');
			if (Position != std::string::npos)
			{
				auto Pair = Options.find(Line.substr(0, Position));
				if (Pair != Options.end()) {
					OutputFile_rgl_config << Pair->first << '=' << Pair->second << std::endl;
				}
				else OutputFile_rgl_config << Line << std::endl;
			}
			else OutputFile_rgl_config << Line << std::endl;
		}
		File_rgl_config.close();
		OutputFile_rgl_config.close();
		if (std::remove(std::string(std::string(CurentDocumentsPath) + std::string("/Mount&Blade Warband WSE2/rgl_config.ini")).c_str()) != 0) goto LABEL_ERROR;
		if (std::rename(std::string(std::string(CurentDocumentsPath) + std::string("/Mount&Blade Warband WSE2/rgl_config_temp.ini")).c_str(), std::string(std::string(CurentDocumentsPath) + "/Mount&Blade Warband WSE2/rgl_config.ini").c_str()) != 0) goto LABEL_ERROR;
		return true;
	}
	else {
	LABEL_ERROR:
		DisplayErrorMessageOptions("Error - could not write to rgl_config.ini. ");
		return false;
	}
	return false;
}
