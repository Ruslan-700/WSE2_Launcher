#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
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

enum ExeType { ExeType_DedicatedServer, ExeType_NotDedicatedServer};

class Class_Engine;

#include "Engine.h"

#include "Images.h"
#include "Fonts.h"