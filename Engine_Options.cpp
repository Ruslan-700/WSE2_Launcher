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
		Checkbox_OnDemandTextures->setChecked(Options["bOnDemandTextures"] == "true");
		Checkbox_OcclusionFilter->setChecked(Options["bOcclusionFilter"] == "true");
		Checkbox_HrtfFilter->setChecked(Options["bHrtfFilter"] == "true");
		Checkbox_DistanceFilter->setChecked(Options["bDistanceFilter"] == "true");
		Checkbox_Sound->setChecked(Options["bSound"] == "false");
		Checkbox_Music->setChecked(Options["bMusic"] == "false");

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
		if (std::remove(std::string(std::string(CurentDocumentsPath) + RGL_CONFIG).c_str()) != 0) goto LABEL_ERROR;
		if (std::rename(std::string(std::string(CurentDocumentsPath) + RGL_CONFIG_TEMP).c_str(), std::string(std::string(CurentDocumentsPath) + RGL_CONFIG).c_str()) != 0) goto LABEL_ERROR;
		return true;
	}
	else {
	LABEL_ERROR:
		DisplayErrorMessageOptions("Error - could not write to rgl_config.ini. ");
		return false;
	}
	return false;
}
