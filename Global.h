#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <algorithm>
#include <memory>
#include <shlobj.h>
#include <fstream>
#include <cstdio>
#include <WinUser.h>
#include <future>

enum ExeType { ExeType_DedicatedServer, ExeType_NotDedicatedServer};
enum FTPCommand { FTPCommand_None, FTPCommand_DownloadAllFiles, FTPCommand_Stop};
enum FTPDownloadState { FTPDownloadState_None, FTPDownloadState_WaitingInstall, FTPDownloadState_WaitingUpdate, FTPDownloadState_Downloading, FTPDownloadState_Updated };
enum TGUIWidget { TGUIWidget_TGUIButton, TGUIWidget_TGUILabel};

class Class_Engine;
class Class_TGUIWidgetPropertyChangeRequest {
public:
	Class_TGUIWidgetPropertyChangeRequest(tgui::Gui* L_Panel, TGUIWidget L_WidgetType, std::string L_WidgetName, std::string L_Parameter1) {
		Panel = L_Panel;
		WidgetType = L_WidgetType;
		WidgetName = L_WidgetName;
		Parameter1 = L_Parameter1;
	}
	tgui::Gui* Panel;
	TGUIWidget WidgetType;
	std::string WidgetName, Parameter1;
};

#include "Engine.h"

#include "Images.h"
#include "Fonts.h"