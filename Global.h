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
#include <cwctype>
#include <clocale>

enum ExeType { ExeType_DedicatedServer, ExeType_NotDedicatedServer};
enum FTPCommand { FTPCommand_None, FTPCommand_DownloadAllFiles, FTPCommand_Stop};
enum FTPDownloadState { FTPDownloadState_None, FTPDownloadState_WaitingInstall, FTPDownloadState_WaitingUpdate, FTPDownloadState_Downloading, FTPDownloadState_Updated };

class Class_Engine;

#include "Engine.h"

#include "Images.h"
#include "Fonts.h"