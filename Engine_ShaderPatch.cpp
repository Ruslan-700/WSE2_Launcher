#include "Engine.h"
#include "Http.h"
#include "Zip.h"
#include <filesystem>

// Downloads the shader patch release and lays it out over the game.
//
// The archive mirrors the destination: files at its root belong in the game folder,
// and a folder under Modules belongs in the module of that name. No module is named
// anywhere here - whatever a module's folder in the archive holds is what that module
// gets, be it one effect, a pair of them, or a pairing table alongside. A module the
// archive says nothing about takes the root build, unless it ships an effect of its
// own, which the root build would not replace.
//
// Installing is undoable. A file that was already there is moved aside once, and a
// manifest records everything written, so removing puts the moved files back and
// deletes the ones the patch itself introduced.

namespace
{
	std::wstring ToWide(const std::string& Text)
	{
		if (Text.empty()) return L"";
		int Length = MultiByteToWideChar(CP_UTF8, 0, Text.c_str(), (int)Text.length(), NULL, 0);
		if (Length <= 0) return L"";
		std::wstring Result((size_t)Length, L' ');
		MultiByteToWideChar(CP_UTF8, 0, Text.c_str(), (int)Text.length(), &Result[0], Length);
		return Result;
	}

	std::string ToNarrow(const std::wstring& Text)
	{
		if (Text.empty()) return "";
		int Length = WideCharToMultiByte(CP_UTF8, 0, Text.c_str(), (int)Text.length(), NULL, 0, NULL, NULL);
		if (Length <= 0) return "";
		std::string Result((size_t)Length, ' ');
		WideCharToMultiByte(CP_UTF8, 0, Text.c_str(), (int)Text.length(), &Result[0], Length, NULL, NULL);
		return Result;
	}

	bool WriteWholeFile(const std::wstring& Path, const std::vector<uint8_t>& Data)
	{
		std::ofstream File(Path, std::ios::binary | std::ios::trunc);
		if (!File.good()) return false;
		if (!Data.empty()) File.write((const char*)Data.data(), (std::streamsize)Data.size());
		bool Result = File.good();
		File.close();
		return Result;
	}

	// Everything this archive holds sits one level below its destination, so a name
	// carrying a separator, a drive or a climb out is not something to salvage.
	bool IsPlainFileName(const std::wstring& Name)
	{
		if (Name.empty() || Name == L"." || Name == L"..") return false;
		return Name.find_first_of(L"\\/:") == std::wstring::npos;
	}

	// The part of an archive path below Prefix, or empty when it is not below it or
	// lies deeper than one level.
	std::wstring NameBelow(const std::wstring& EntryPath, const std::wstring& Prefix)
	{
		if (EntryPath.length() <= Prefix.length()) return L"";
		if (_wcsnicmp(EntryPath.c_str(), Prefix.c_str(), Prefix.length()) != 0) return L"";

		std::wstring Name = EntryPath.substr(Prefix.length());
		return IsPlainFileName(Name) ? Name : L"";
	}

	bool PathsAreEqual(const std::wstring& Left, const std::wstring& Right)
	{
		return _wcsicmp(Left.c_str(), Right.c_str()) == 0;
	}

	std::string FormatSize(double Bytes)
	{
		char Buffer[32] = "";
		if (Bytes >= 1024.0 * 1024.0) sprintf_s(Buffer, "%.1f MB", Bytes / (1024.0 * 1024.0));
		else sprintf_s(Buffer, "%.0f KB", Bytes / 1024.0);
		return Buffer;
	}
}

// The folder the selected module lives in. Workshop modules are not under Modules,
// so they are resolved the same way the preview image is.
std::wstring Class_Engine::ShaderPatch_ModuleDirectory(const std::string& ModuleName)
{
	if (ModuleName.empty()) return L"";

#if !defined WFAS
	if (IsItemFromWorkshop(ModuleName)) return ToWide(getPathOfWorkshopItem(ModuleName));
#endif

	return GetLauncherDirectory() + L"\\Modules\\" + ToWide(ModuleName);
}

bool Class_Engine::ShaderPatch_IsInstalledIn(const std::wstring& Directory)
{
	if (Directory.empty()) return false;
	std::wstring Manifest = Directory + L"\\" + SHADER_PATCH_MANIFEST;
	return GetFileAttributesW(Manifest.c_str()) != INVALID_FILE_ATTRIBUTES;
}

// Whether the module carries an effect of its own. The engine prefers those to the
// copies in the game folder, so such a module is not served by the root build.
bool Class_Engine::ShaderPatch_ModuleHasOwnEffect(const std::wstring& Directory)
{
	if (Directory.empty()) return false;

	const wchar_t* Names[] = { L"mb.fx", L"mb_2a.fxo", L"mb_2b.fxo" };
	for (const wchar_t* Name : Names) {
		if (GetFileAttributesW((Directory + L"\\" + Name).c_str()) != INVALID_FILE_ATTRIBUTES) return true;
	}
	return false;
}

// The one place an install for this module can live, and the only place the button
// ever speaks about.
//
// A module carrying an effect of its own is not served by the copies in the game
// folder - the engine prefers its own - so its patch has to sit in its folder. Every
// other module reads the game folder, so that is where its patch is. Keeping install,
// remove and the button text on this single answer is what stops a game folder
// install from claiming to have patched a module it cannot reach.
std::wstring Class_Engine::ShaderPatch_TargetDirectory(const std::string& ModuleName)
{
	std::wstring ModuleDirectory = ShaderPatch_ModuleDirectory(ModuleName);

	if (!ModuleDirectory.empty()
		&& (ShaderPatch_IsInstalledIn(ModuleDirectory) || ShaderPatch_ModuleHasOwnEffect(ModuleDirectory)))
		return ModuleDirectory;

	return GetLauncherDirectory();
}

// Works out what a click would do now, for the module the combo box is showing.
//
// Takes no lock, and must not: the main loop holds UpdateThread_Mutex around event
// handling, so the combo box calls this with the mutex already held, and it is not a
// recursive one. Initialize() calls this before the worker thread exists.
void Class_Engine::ShaderPatch_Refresh()
{
	ShaderPatchModule = GetCurrentModule();

	bool Installed = ShaderPatch_IsInstalledIn(ShaderPatch_TargetDirectory(ShaderPatchModule));

	Current_ShaderPatchState.store(Installed ? ShaderPatchState_Installed : ShaderPatchState_NotInstalled);
	RefreshShaderPatchWidgets();
}

// Applies the current state to the button. The caller must hold UpdateThread_Mutex.
void Class_Engine::RefreshShaderPatchWidgets()
{
	tgui::Button::Ptr Button_ShaderPatch = GUI_Main.get<tgui::Button>("Button_ShaderPatch");
	if (Button_ShaderPatch == nullptr) return;

	switch (Current_ShaderPatchState.load())
	{
	case ShaderPatchState_Installed:
		Button_ShaderPatch->setText(GetLocalizedTextEntry("ui_remove_shader_patch"));
		break;
	case ShaderPatchState_Working:
	case ShaderPatchState_Unavailable:
	case ShaderPatchState_Failed:
		Button_ShaderPatch->setText(ShaderPatchText);
		break;
	default:
		Button_ShaderPatch->setText(GetLocalizedTextEntry("ui_install_shader_patch"));
		break;
	}
}

void Class_Engine::SetShaderPatchText(std::string Text)
{
	std::lock_guard<std::mutex> Lock(UpdateThread_Mutex);
	ShaderPatchText = Text;
	RefreshShaderPatchWidgets();
}

void Class_Engine::ShaderPatch_Fail(std::string Error)
{
	Current_ShaderPatchState.store(ShaderPatchState_Failed);
	SetShaderPatchText(GetLocalizedTextEntry("ui_update_failed") + " " + Error);
}

bool Class_Engine::ShaderPatch_Download(const std::wstring& ArchivePath)
{
	SetShaderPatchText(GetLocalizedTextEntry("ui_downloading_") + "0%");

	auto StartTime = std::chrono::steady_clock::now();
	auto LastRefresh = StartTime;
	std::string Error;

	bool Result = Http::DownloadToFile(SHADER_PATCH_DOWNLOAD_URL, ArchivePath, [&](uint64_t Downloaded, uint64_t Total) {
		if (Current_UpdateCommand.load() == UpdateCommand_Stop) return false;

		auto Now = std::chrono::steady_clock::now();
		if (Now - LastRefresh < std::chrono::milliseconds(250)) return true;
		LastRefresh = Now;

		std::string Text = GetLocalizedTextEntry("ui_downloading_");
		if (Total > 0) {
			char Percent[16] = "";
			sprintf_s(Percent, "%d%%", (int)(Downloaded * 100 / Total));
			Text += Percent;
		}
		else Text += FormatSize((double)Downloaded);

		SetShaderPatchText(Text);
		return true;
	}, Error);

	if (!Result && !Http::WasAborted(Error)) ShaderPatch_Fail(Error);
	return Result;
}

// Writes the entries the filter accepts into Destination and records what was written,
// so that removing later knows which files to put back and which to delete.
bool Class_Engine::ShaderPatch_ExtractInto(Zip::Archive& Archive, const std::wstring& Prefix,
                                           const std::wstring& Destination, int& OutCount)
{
	std::string Error;
	std::vector<std::wstring> Written;

	try { std::filesystem::create_directories(Destination); }
	catch (const std::exception&) { ShaderPatch_Fail("could not open " + ToNarrow(Destination)); return false; }

	for (const Zip::Entry& Entry : Archive.GetEntries()) {
		if (Current_UpdateCommand.load() == UpdateCommand_Stop) return false;
		if (Entry.IsDirectory) continue;

		std::wstring Name = NameBelow(Entry.Path, Prefix);
		if (Name.empty()) continue;

		std::vector<uint8_t> Data;
		if (!Archive.Extract(Entry, Data, Error)) { ShaderPatch_Fail(Error); return false; }

		std::wstring Target = Destination + L"\\" + Name;
		std::wstring Backup = Target + SHADER_PATCH_BACKUP_SUFFIX;

		// Moved aside once and only once: a second install must not overwrite the
		// backup with a file the first install already put there.
		if (GetFileAttributesW(Target.c_str()) != INVALID_FILE_ATTRIBUTES
			&& GetFileAttributesW(Backup.c_str()) == INVALID_FILE_ATTRIBUTES) {
			CopyFileW(Target.c_str(), Backup.c_str(), TRUE);
		}

		if (!WriteWholeFile(Target, Data)) {
			ShaderPatch_Fail("could not write " + ToNarrow(Name) + ", try running the launcher as administrator");
			return false;
		}

		Written.push_back(Name);
		SetShaderPatchText(GetLocalizedTextEntry("ui_extracting"));
	}

	if (Written.empty()) return true;

	std::ofstream Manifest(Destination + L"\\" + SHADER_PATCH_MANIFEST, std::ios::trunc);
	if (Manifest.good()) {
		for (const std::wstring& Name : Written) Manifest << ToNarrow(Name) << "\n";
		Manifest.close();
	}

	OutCount += (int)Written.size();
	return true;
}

void Class_Engine::ShaderPatch_Install()
{
	Current_ShaderPatchState.store(ShaderPatchState_Working);

	WCHAR TempDirectory[MAX_PATH] = L"";
	if (GetTempPathW(MAX_PATH, TempDirectory) == 0) { ShaderPatch_Fail("no temporary folder available"); return; }
	std::wstring ArchivePath = std::wstring(TempDirectory) + SHADER_PATCH_ASSET;

	if (!ShaderPatch_Download(ArchivePath)) { DeleteFileW(ArchivePath.c_str()); return; }

	SetShaderPatchText(GetLocalizedTextEntry("ui_extracting"));

	std::string Error;
	Zip::Archive Archive;
	if (!Archive.Open(ArchivePath, Error)) { DeleteFileW(ArchivePath.c_str()); ShaderPatch_Fail(Error); return; }

	std::string ModuleName = ShaderPatchModule;
	std::wstring Destination = ShaderPatch_TargetDirectory(ModuleName);
	bool IntoModule = !PathsAreEqual(Destination, GetLauncherDirectory());
	std::wstring Prefix = IntoModule ? L"Modules/" + ToWide(ModuleName) + L"/" : L"";

	int Count = 0;
	bool Result = ShaderPatch_ExtractInto(Archive, Prefix, Destination, Count);

	DeleteFileW(ArchivePath.c_str());
	if (!Result) return;

	if (Count == 0) {
		// The module keeps an effect of its own and the release carries no build made
		// against it. The stock build is no answer: it knows nothing of what this
		// module added, and putting it in the module folder would take those shaders
		// away. A state of its own, because NotInstalled would put the invitation to
		// install back on the button and wipe the explanation with it.
		if (IntoModule) {
			Current_ShaderPatchState.store(ShaderPatchState_Unavailable);
			SetShaderPatchText(GetLocalizedTextEntry("ui_shader_patch_not_for_module"));
		}
		else ShaderPatch_Fail("the release archive held nothing to install");

		return;
	}

	Current_ShaderPatchState.store(ShaderPatchState_Installed);
	SetShaderPatchText("");
}

// Undoes an install: files it replaced go back, files it introduced go away.
void Class_Engine::ShaderPatch_Remove()
{
	Current_ShaderPatchState.store(ShaderPatchState_Working);

	// Only the install this module actually reads, so removing while looking at one
	// module cannot undo another one's.
	std::wstring Directory = ShaderPatch_TargetDirectory(ShaderPatchModule);
	std::wstring ManifestPath = Directory + L"\\" + SHADER_PATCH_MANIFEST;
	std::ifstream Manifest(ManifestPath);

	if (Manifest.good()) {
		std::string Line;
		while (std::getline(Manifest, Line)) {
			if (Line.empty()) continue;

			std::wstring Name = ToWide(Line);
			if (!IsPlainFileName(Name)) continue;

			std::wstring Target = Directory + L"\\" + Name;
			std::wstring Backup = Target + SHADER_PATCH_BACKUP_SUFFIX;

			if (GetFileAttributesW(Backup.c_str()) != INVALID_FILE_ATTRIBUTES) {
				CopyFileW(Backup.c_str(), Target.c_str(), FALSE);
				DeleteFileW(Backup.c_str());
			}
			else DeleteFileW(Target.c_str());
		}

		Manifest.close();
		DeleteFileW(ManifestPath.c_str());
	}

	Current_ShaderPatchState.store(ShaderPatchState_NotInstalled);
	SetShaderPatchText("");
}
