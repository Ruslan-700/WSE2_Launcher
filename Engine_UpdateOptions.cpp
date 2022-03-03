#include "Engine.h"

bool Class_Engine::UpdateOptions()
{
	tgui::Label::Ptr Label_Message1 = GUI_Main.get<tgui::Label>("Label_Message1");
	CHAR CurentUserDocuments[MAX_PATH];
	HRESULT Result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, CurentUserDocuments);

	if (Result != S_OK) {
		Label_Message1->setText("Error - could not open Documents folder.");
		return false;
	}
	else {
		std::ifstream File(std::string(CurentUserDocuments) + "/Mount&Blade Warband WSE2/rgl_config.ini");
		std::string Line;
		if (File.is_open()) {
			while (std::getline(File, Line))
			{
				std::string::size_type Position = Line.find('=');
				if (Position != std::string::npos)
				{
					Options.insert(std::pair(Line.substr(0, Position), Line.substr(Position + 1)));
				}
			}
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
	return true;
}

void Class_Engine::ChangeOption(std::string, std::string)
{
}
