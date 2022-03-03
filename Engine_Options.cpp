#include "Engine.h"

bool Class_Engine::UpdateOptions()
{
	Options.clear();
	tgui::Label::Ptr Label_Message1 = GUI_Main.get<tgui::Label>("Label_Message1");
	HRESULT Result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, CurentUserDocuments);
	if (Result != S_OK) {
		Label_Message1->setText("Error - could not open Documents folder.");
		return false;
	}
	else {
		std::ifstream File_rgl_config(std::string(CurentUserDocuments) + std::string("/Mount&Blade Warband WSE2/rgl_config.ini"));
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
			Label_Message1->setText("Error - could not open rgl_config.ini.");
			return false;
		}
	}
}

bool Class_Engine::ApplyOptions()
{
	std::string Line;
	tgui::Label::Ptr Label_Message1 = GUI_Options.get<tgui::Label>("Label_Message1");
	std::ifstream File_rgl_config(std::string(CurentUserDocuments) + std::string("/Mount&Blade Warband WSE2/rgl_config.ini"));
	std::ofstream OutputFile_rgl_config(std::string(CurentUserDocuments) + std::string("/Mount&Blade Warband WSE2/rgl_config2.ini"));
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
		if (std::remove(std::string(std::string(CurentUserDocuments) + std::string("/Mount&Blade Warband WSE2/rgl_config.ini")).c_str()) != 0) goto label_error;
		if (std::rename(std::string(std::string(CurentUserDocuments) + std::string("/Mount&Blade Warband WSE2/rgl_config2.ini")).c_str(), std::string(std::string(CurentUserDocuments) + "/Mount&Blade Warband WSE2/rgl_config.ini").c_str()) != 0) goto label_error;
		return true;
	}
	else {
	label_error:
		Label_Message1->setText("Error - could not write to rgl_config.ini.");
		return false;
	}
	return false;
}
