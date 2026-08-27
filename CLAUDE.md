# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

WSE2 Launcher is a Windows GUI application for launching Mount & Blade Warband WSE2 (modding engine). Built with C++17, SFML, and TGUI. Windows-only (Win32 API, registry, CreateProcess).

## Build System

Visual Studio 2022 (MSVC v143, PlatformToolset v143). Solution file: `WSE2_Launcher.sln`.

**Build configurations:**
- `Release|x64` / `Release|Win32` — Standard Warband WSE2 launcher
- `WFaS|x64` / `WFaS|Win32` — Warband: Fire and Sword variant (defines `WFAS` preprocessor macro)
- `Debug|x64` / `Debug|Win32` — Debug builds

**Build from command line:**
```
msbuild WSE2_Launcher.sln /p:Configuration=Release /p:Platform=x64
```

**Output:** `wse2_launcher.exe`

All libraries are statically linked (`SFML_STATIC`, `TGUI_STATIC`). The Steam API DLL is delay-loaded and renamed to `steam_api_wse2.dll` to avoid conflicts with the vanilla game.

## Architecture

### Single class design

The entire application is the `Class_Engine` class, split across multiple `.cpp` files by responsibility:

- **Start.cpp** — `main()` entry point; delay-load hook redirecting `steam_api.dll` → `steam_api_wse2.dll`
- **Engine.cpp** — `Initialize()`: reads user paths, language, localization, then sets up UI
- **Engine_Start.cpp** — Window creation, transparency setup, main event loop
- **Engine_Initialize_Main.cpp** — Main window UI (module selector, buttons, labels)
- **Engine_Initialize_Options.cpp** — Options window UI
- **Engine_Interact.cpp** — Event handlers (mouse, keyboard, window events)
- **Engine_Buttons.cpp** — Button click handlers (Launch, Launch Dedicated, Options)
- **Engine_Options.cpp** — Reading/writing `rgl_config.ini` settings
- **Engine_RefreshModulesList.cpp** — Discovers game modules from filesystem
- **Engine_Update.cpp** — Background thread that checks GitHub Releases and installs WSE2 updates
- **Http.cpp** — Minimal HTTPS client on WinHTTP (SFML cannot do TLS)
- **Zip.cpp** — Zip reader with its own inflate, so no compression library has to be linked
- **Engine_UpdateText.cpp** — Applies localized text to UI elements
- **Engine_FillMissingLocalizationKeys.cpp** — Fallback to English for missing translations
- **steamWorkshopItem.cpp** — Steam Workshop integration (compiled out when `WFAS` is defined)

### WFaS conditional compilation

`#if !defined WFAS` / `#if defined WFAS` guards throughout the codebase switch between Warband and Fire & Sword variants. This controls: Steam Workshop support (Warband only), registry keys, executable names, and the release asset name. Key defines are in `Engine.h` (lines 97-118).

### Embedded resources

`Fonts.h` and `Images.h` contain raw binary data for fonts and UI images embedded directly in the executable — these files are very large (3MB+ and 5MB+). Do not modify these unless updating assets.

### Dependencies (in SDK/)

- **SFML 2.5.1** — Graphics and windowing
- **TGUI 0.9** — GUI widgets on top of SFML
- **Steamworks SDK 1.57** — Steam Workshop (delay-loaded)
- **FreeType, zlib, libpng, Brotli, bz2** — Font rendering and image handling

The `SDK/` directory is gitignored. Dependencies must be present locally to build.

### Threading

Update checking and installing run asynchronously via `std::future` + `std::mutex`. The worker thread owns `Current_UpdateState` and touches widgets only under `UpdateThread_Mutex`, which the main loop holds around event handling and drawing.

The launcher updates itself: files it holds open (its own exe, `steam_api_wse2.dll`) cannot be overwritten, so they are renamed to `*.wse2old` and removed on the next start.

### Data storage

- Windows Registry (`HKCU\SOFTWARE\MountAndBladeWarbandKeys`) — user preferences, last module
- `rgl_config.ini` — graphics/audio settings (in user's Documents path)
- `languages/[code]/*.csv` — localization strings (12 languages: en, ru, de, fr, es, pl, hu, cz, tr, cnt, cns)

## Code Conventions

- Class naming: `Class_Engine`
- UI initialization methods: `Initialize_UI_Main()`, `Initialize_UI_Options()`
- Interaction methods: `Interact_Main()`, `Interact_Options()`
- Button handlers: `Button_[Name]_onClick()`
- Member variables: no consistent prefix (some `m_`, some bare names)
- Charset: MultiByte (not Unicode)
