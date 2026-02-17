#include "Engine.h"

bool Class_Engine::UpdateOptions()
{
	Options.clear();
	std::ifstream File_rgl_config(std::string(CurentDocumentsPath) + RGL_CONFIG);
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

		tgui::CheckBox::Ptr Checkbox_OnDemandTextures = GUI_Options.get<tgui::CheckBox>("Checkbox_OnDemandTextures");
		tgui::CheckBox::Ptr Checkbox_OcclusionFilter = GUI_Options.get<tgui::CheckBox>("Checkbox_OcclusionFilter");
		tgui::CheckBox::Ptr Checkbox_HrtfFilter = GUI_Options.get<tgui::CheckBox>("Checkbox_HrtfFilter");
		tgui::CheckBox::Ptr Checkbox_DistanceFilter = GUI_Options.get<tgui::CheckBox>("Checkbox_DistanceFilter");
		tgui::CheckBox::Ptr Checkbox_Sound = GUI_Options.get<tgui::CheckBox>("Checkbox_Sound");
		tgui::CheckBox::Ptr Checkbox_Music = GUI_Options.get<tgui::CheckBox>("Checkbox_Music");
		auto getOpt = [&](const std::string& key) -> std::string {
			auto it = Options.find(key);
			return it != Options.end() ? it->second : "";
		};
		Checkbox_OnDemandTextures->setChecked(getOpt("bOnDemandTextures") == "true");
		Checkbox_OcclusionFilter->setChecked(getOpt("bOcclusionFilter") == "true");
		Checkbox_HrtfFilter->setChecked(getOpt("bHrtfFilter") == "true");
		Checkbox_DistanceFilter->setChecked(getOpt("bDistanceFilter") == "true");
		Checkbox_Sound->setChecked(getOpt("bSound") == "false");
		Checkbox_Music->setChecked(getOpt("bMusic") == "false");

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
	std::ifstream File_rgl_config(std::string(CurentDocumentsPath) + RGL_CONFIG);
	std::remove(std::string(std::string(CurentDocumentsPath) + RGL_CONFIG_TEMP).c_str());
	std::ofstream OutputFile_rgl_config(std::string(CurentDocumentsPath) + RGL_CONFIG_TEMP);
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
		std::string configPath = std::string(CurentDocumentsPath) + RGL_CONFIG;
		std::string tempPath = std::string(CurentDocumentsPath) + RGL_CONFIG_TEMP;
		if (std::remove(configPath.c_str()) != 0 || std::rename(tempPath.c_str(), configPath.c_str()) != 0) {
			DisplayErrorMessageOptions("Error - could not write to rgl_config.ini. ");
			return false;
		}
		return true;
	}
	else {
		DisplayErrorMessageOptions("Error - could not write to rgl_config.ini. ");
		return false;
	}
}
