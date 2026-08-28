#pragma once
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <SFML/Graphics.hpp>
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
enum UpdateCommand { UpdateCommand_None, UpdateCommand_Install, UpdateCommand_Stop};
enum UpdateState { UpdateState_None, UpdateState_WaitingInstall, UpdateState_WaitingUpdate, UpdateState_Downloading, UpdateState_Extracting, UpdateState_Updated, UpdateState_RestartRequired, UpdateState_Failed };
// Kept apart from UpdateState: the shader patch and the WSE2 update share a worker
// thread but drive their own button, and one must not overwrite the other's text.
enum ShaderPatchCommand { ShaderPatchCommand_None, ShaderPatchCommand_Install, ShaderPatchCommand_Remove };
enum ShaderPatchState { ShaderPatchState_None, ShaderPatchState_NotInstalled, ShaderPatchState_Installed, ShaderPatchState_Working, ShaderPatchState_Unavailable, ShaderPatchState_Failed };

class Class_Engine;

#include "Engine.h"

#include "Images.h"
#include "Fonts.h"
