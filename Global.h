#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
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
#include <atomic>
#include <chrono>
#include <thread>
#include <cwctype>
#include <clocale>
#include <codecvt>

#if !defined WFAS
#ifndef DELAYIMP_INSECURE_WRITABLE_HOOKS
#define DELAYIMP_INSECURE_WRITABLE_HOOKS
#endif
#include <delayimp.h>
#pragma warning(push)
#pragma warning(disable: 4996)
#include "steam_api.h"
#pragma warning(pop)
#endif

enum ExeType { ExeType_DedicatedServer, ExeType_NotDedicatedServer, ExeType_x64};
enum FTPCommand { FTPCommand_None, FTPCommand_DownloadAllFiles, FTPCommand_Stop};
enum FTPDownloadState { FTPDownloadState_None, FTPDownloadState_WaitingInstall, FTPDownloadState_WaitingUpdate, FTPDownloadState_Downloading, FTPDownloadState_Updated };

class Class_Engine;

#include "Engine.h"

#include "Images.h"
#include "Fonts.h"
