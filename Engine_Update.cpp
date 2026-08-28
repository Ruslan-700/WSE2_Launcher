#include "Engine.h"
#include "Http.h"
#include "Zip.h"
#include <filesystem>

namespace
{
	std::wstring Widen(const std::string& Text)
	{
		if (Text.empty()) return L"";
		int Length = MultiByteToWideChar(CP_UTF8, 0, Text.c_str(), (int)Text.length(), NULL, 0);
		if (Length <= 0) return L"";
		std::wstring Result((size_t)Length, L' ');
		MultiByteToWideChar(CP_UTF8, 0, Text.c_str(), (int)Text.length(), &Result[0], Length);
		return Result;
	}

	std::string Narrow(const std::wstring& Text)
	{
		if (Text.empty()) return "";
		int Length = WideCharToMultiByte(CP_UTF8, 0, Text.c_str(), (int)Text.length(), NULL, 0, NULL, NULL);
		if (Length <= 0) return "";
		std::string Result((size_t)Length, ' ');
		WideCharToMultiByte(CP_UTF8, 0, Text.c_str(), (int)Text.length(), &Result[0], Length, NULL, NULL);
		return Result;
	}

	// Pulls "Key":"Value" out of a JSON document without dragging in a JSON parser.
	std::string ReadJsonString(const std::string& Json, const std::string& Key)
	{
		size_t KeyPosition = Json.find("\"" + Key + "\"");
		if (KeyPosition == std::string::npos) return "";
		size_t Colon = Json.find(':', KeyPosition);
		if (Colon == std::string::npos) return "";
		size_t Start = Json.find('"', Colon);
		if (Start == std::string::npos) return "";
		size_t End = Json.find('"', Start + 1);
		if (End == std::string::npos) return "";
		return Json.substr(Start + 1, End - Start - 1);
	}

	// "v1.1.5.0" -> "1150", the four digit form the launcher stores and compares.
	std::wstring VersionFromTag(const std::string& Tag)
	{
		std::wstring Result;
		for (char Character : Tag) if (Character >= '0' && Character <= '9') Result += (wchar_t)Character;
		return Result;
	}

	std::string FormatSize(double Bytes)
	{
		char Buffer[32] = "";
		if (Bytes >= 1024.0 * 1024.0) sprintf_s(Buffer, "%.1f MB", Bytes / (1024.0 * 1024.0));
		else sprintf_s(Buffer, "%.0f KB", Bytes / 1024.0);
		return Buffer;
	}

	std::string FormatDuration(int Seconds)
	{
		char Buffer[32] = "";
		sprintf_s(Buffer, "%d:%02d", Seconds / 60, Seconds % 60);
		return Buffer;
	}

	// Rejects absolute paths and anything trying to climb out of the game folder.
	bool MakeSafeRelativePath(const std::wstring& EntryPath, std::wstring& OutPath)
	{
		OutPath.clear();
		if (EntryPath.find(L':') != std::wstring::npos) return false;

		std::wstring Segment;
		std::vector<std::wstring> Segments;
		for (wchar_t Character : EntryPath + L"/") {
			if (Character == L'/' || Character == L'\\') {
				if (Segment == L"." || Segment == L"..") return false;
				if (!Segment.empty()) Segments.push_back(Segment);
				Segment.clear();
			}
			else Segment += Character;
		}
		if (Segments.empty()) return false;

		for (size_t i = 0; i < Segments.size(); i++) {
			if (i != 0) OutPath += L"\\";
			OutPath += Segments[i];
		}
		return true;
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

	bool PathsAreEqual(const std::wstring& Left, const std::wstring& Right)
	{
		return _wcsicmp(Left.c_str(), Right.c_str()) == 0;
	}
}

std::wstring Class_Engine::GetLauncherPath()
{
	WCHAR Buffer[MAX_PATH] = L"";
	if (GetModuleFileNameW(NULL, Buffer, MAX_PATH) == 0) return L"";
	return Buffer;
}

std::wstring Class_Engine::GetLauncherDirectory()
{
	std::wstring Path = GetLauncherPath();
	size_t Separator = Path.find_last_of(L"\\/");
	if (Separator == std::wstring::npos) return L".";
	return Path.substr(0, Separator);
}

// Files that were in use during an update were renamed instead of overwritten; by the
// next start nothing holds them any more, so they can go.
void Class_Engine::RemoveReplacedFiles()
{
	try {
		for (const std::filesystem::directory_entry& Entry : std::filesystem::directory_iterator(GetLauncherDirectory())) {
			if (Entry.is_regular_file() && Entry.path().extension() == REPLACED_FILE_SUFFIX) DeleteFileW(Entry.path().c_str());
		}
	}
	catch (const std::exception&) {}
}

void Class_Engine::RestartLauncher()
{
	std::wstring Path = GetLauncherPath();
	std::wstring Directory = GetLauncherDirectory();
	if (Path.empty()) return;

	STARTUPINFOW StartupInfo = { sizeof(StartupInfo) };
	PROCESS_INFORMATION ProcessInformation;
	if (CreateProcessW(Path.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, Directory.c_str(), &StartupInfo, &ProcessInformation)) {
		CloseHandle(ProcessInformation.hProcess);
		CloseHandle(ProcessInformation.hThread);
		Close();
	}
}

void Class_Engine::SetUpdateProgressText(std::string Text)
{
	std::lock_guard<std::mutex> Lock(UpdateThread_Mutex);
	UpdateProgressText = Text;
	RefreshUpdateWidgets();
}

// Applies the current update state to the button and the label above the Play button.
// The caller must hold UpdateThread_Mutex.
void Class_Engine::RefreshUpdateWidgets()
{
	tgui::Button::Ptr Button_Update = GUI_Main.get<tgui::Button>("Button_Update");
	tgui::Label::Ptr Label_Update = GUI_Main.get<tgui::Label>("Label_Update");
	if (Button_Update == nullptr || Label_Update == nullptr) return;

	bool ButtonIsVisible = true;
	std::string ButtonText, LabelText;

	switch (Current_UpdateState.load())
	{
	case UpdateState_WaitingInstall:
		ButtonText = GetLocalizedTextEntry("ui_install_wse2");
		LabelText = GetLocalizedTextEntry("ui_wse2_not_installed");
		break;
	case UpdateState_WaitingUpdate:
		ButtonText = GetLocalizedTextEntry("ui_update_wse2");
		LabelText = GetLocalizedTextEntry("ui_newer_version_available");
		break;
	case UpdateState_Downloading:
	case UpdateState_Extracting:
		ButtonText = GetLocalizedTextEntry("ui_please_wait");
		LabelText = UpdateProgressText;
		break;
	case UpdateState_Updated:
		ButtonIsVisible = false;
		LabelText = GetLocalizedTextEntry("ui_version_is_up_to_date");
		break;
	case UpdateState_RestartRequired:
		ButtonText = GetLocalizedTextEntry("ui_restart_launcher");
		LabelText = GetLocalizedTextEntry("ui_update_installed");
		break;
	case UpdateState_Failed:
		ButtonText = GetLocalizedTextEntry(WSE2IsInstalled ? "ui_update_wse2" : "ui_install_wse2");
		LabelText = UpdateProgressText;
		break;
	default:
		Button_Update->setVisible(false);
		Label_Update->setVisible(false);
		return;
	}

	Button_Update->setVisible(ButtonIsVisible);
	Button_Update->setText(ButtonText);
	Label_Update->setVisible(true);
	Label_Update->setText(LabelText);
	Label_Update->setPosition("23%", ButtonIsVisible ? "35%" : "43%");
}

void Class_Engine::CheckForUpdates()
{
	std::string Body, Error;
	if (!Http::Get(UPDATE_API_URL, Body, Error)) return;

	std::string Tag = ReadJsonString(Body, "tag_name");
	std::wstring Version = VersionFromTag(Tag);
	if (Version.length() != 4 || Body.find("\"" UPDATE_ASSET "\"") == std::string::npos) return;

	LatestVersion = Version;
	LatestDownloadUrl = std::wstring(UPDATE_DOWNLOAD_URL) + Widen(Tag) + L"/" + Widen(UPDATE_ASSET);

	std::wstring ExecutablePath = GetLauncherDirectory() + L"\\" + Widen(EXECUTABLE);
	WSE2IsInstalled = GetFileAttributesW(ExecutablePath.c_str()) != INVALID_FILE_ATTRIBUTES;

	// An unknown local version (no rgl_log.txt and nothing in the registry yet) is
	// treated as outdated, so the update stays offered instead of silently hidden.
	if (!WSE2IsInstalled) Current_UpdateState.store(UpdateState_WaitingInstall);
	else if (WSE2Version.length() != 4 || IsCurrentVersionOlderThan(LatestVersion)) Current_UpdateState.store(UpdateState_WaitingUpdate);
	else Current_UpdateState.store(UpdateState_Updated);

	std::lock_guard<std::mutex> Lock(UpdateThread_Mutex);
	RefreshUpdateWidgets();
}

bool Class_Engine::DownloadUpdate(const std::wstring& ArchivePath)
{
	Current_UpdateState.store(UpdateState_Downloading);
	SetUpdateProgressText(GetLocalizedTextEntry("ui_downloading_") + "0%");

	auto StartTime = std::chrono::steady_clock::now();
	auto LastRefresh = StartTime;
	std::string Error;

	bool Result = Http::DownloadToFile(LatestDownloadUrl, ArchivePath, [&](uint64_t Downloaded, uint64_t Total) {
		if (Current_UpdateCommand.load() == UpdateCommand_Stop) return false;

		auto Now = std::chrono::steady_clock::now();
		if (Now - LastRefresh < std::chrono::milliseconds(250)) return true;
		LastRefresh = Now;

		double Seconds = std::chrono::duration<double>(Now - StartTime).count();
		std::string Text = GetLocalizedTextEntry("ui_downloading_");
		if (Total > 0) {
			char Percent[16] = "";
			sprintf_s(Percent, "%d%%  ", (int)(Downloaded * 100 / Total));
			Text += Percent;
		}
		if (Seconds > 1.0) {
			double Speed = Downloaded / Seconds;
			Text += FormatSize(Speed) + "/s";
			if (Total > Downloaded && Speed > 0.0) Text += "  ~" + FormatDuration((int)((Total - Downloaded) / Speed));
		}
		SetUpdateProgressText(Text);
		return true;
	}, Error);

	if (!Result && !Http::WasAborted(Error)) FailUpdate(Error);
	return Result;
}

bool Class_Engine::ExtractUpdate(const std::wstring& ArchivePath)
{
	Current_UpdateState.store(UpdateState_Extracting);
	SetUpdateProgressText(GetLocalizedTextEntry("ui_extracting"));

	std::string Error;
	Zip::Archive Archive;
	if (!Archive.Open(ArchivePath, Error)) { FailUpdate(Error); return false; }

	std::wstring TargetDirectory = GetLauncherDirectory();
	std::wstring LauncherPath = GetLauncherPath();
	const std::vector<Zip::Entry>& Entries = Archive.GetEntries();
	size_t Extracted = 0;

	for (size_t i = 0; i < Entries.size(); i++) {
		if (Current_UpdateCommand.load() == UpdateCommand_Stop) return false;
		if (Entries[i].IsDirectory) continue;

		std::wstring RelativePath;
		if (!MakeSafeRelativePath(Entries[i].Path, RelativePath)) continue;
		std::wstring Destination = TargetDirectory + L"\\" + RelativePath;

		std::vector<uint8_t> Data;
		if (!Archive.Extract(Entries[i], Data, Error)) { FailUpdate(Error); return false; }

		try {
			size_t Separator = Destination.find_last_of(L'\\');
			if (Separator != std::wstring::npos) std::filesystem::create_directories(Destination.substr(0, Separator));
		}
		catch (const std::exception&) { FailUpdate("could not create " + Narrow(RelativePath)); return false; }

		// Files the running launcher holds open (its own image, the Steam API dll)
		// cannot be overwritten, but Windows still allows renaming them out of the way.
		bool IsLauncher = PathsAreEqual(Destination, LauncherPath);
		if (IsLauncher || !WriteWholeFile(Destination, Data)) {
			std::wstring ReplacedFile = Destination + REPLACED_FILE_SUFFIX;
			DeleteFileW(ReplacedFile.c_str());
			if (!MoveFileExW(Destination.c_str(), ReplacedFile.c_str(), MOVEFILE_REPLACE_EXISTING) || !WriteWholeFile(Destination, Data)) { FailUpdate("could not write " + Narrow(RelativePath) + ", try running the launcher as administrator"); return false; }
			if (IsLauncher) LauncherWasReplaced = true;
		}

		Extracted++;
		char Progress[32] = "";
		sprintf_s(Progress, "  %d%%", (int)(Extracted * 100 / (Entries.size() > 0 ? Entries.size() : 1)));
		SetUpdateProgressText(GetLocalizedTextEntry("ui_extracting") + Progress);
	}

	return true;
}

void Class_Engine::FailUpdate(std::string Error)
{
	Current_UpdateState.store(UpdateState_Failed);
	SetUpdateProgressText(GetLocalizedTextEntry("ui_update_failed") + " " + Error);
}

void Class_Engine::InstallUpdate()
{
	WCHAR TempDirectory[MAX_PATH] = L"";
	if (GetTempPathW(MAX_PATH, TempDirectory) == 0) { FailUpdate("no temporary folder available"); return; }
	std::wstring ArchivePath = std::wstring(TempDirectory) + Widen(UPDATE_ASSET);

	LauncherWasReplaced = false;
	bool Result = DownloadUpdate(ArchivePath) && ExtractUpdate(ArchivePath);
	DeleteFileW(ArchivePath.c_str());
	if (!Result) return;

	WSE2Version = LatestVersion;
	WSE2VersionWithDots = WSE2Version;
	for (size_t i = 1; i < 4; i++) WSE2VersionWithDots.insert(i * 2 - 1, L".");
	WSE2IsInstalled = true;

	HKEY Key;
	if (RegOpenKeyExW(HKEY_CURRENT_USER, REGISTRY_KEY, 0, KEY_WRITE, &Key) == ERROR_SUCCESS) {
		RegSetValueExW(Key, L"wse2_version", 0, REG_SZ, (LPBYTE)WSE2Version.c_str(), (DWORD)((WSE2Version.length() + 1) * sizeof(wchar_t)));
		RegCloseKey(Key);
	}

	Current_UpdateState.store(LauncherWasReplaced ? UpdateState_RestartRequired : UpdateState_Updated);

	std::lock_guard<std::mutex> Lock(UpdateThread_Mutex);
	tgui::Label::Ptr Label_WSE2Version = GUI_Main.get<tgui::Label>("Label_WSE2Version");
	if (Label_WSE2Version != nullptr) Label_WSE2Version->setText(wstring_Converter.to_bytes(L"WSE2 ver. " + WSE2VersionWithDots));
	RefreshUpdateWidgets();
}

void Class_Engine::UpdateThread()
{
	auto LastCheck = std::chrono::steady_clock::now() - std::chrono::hours(1);

	while (Current_UpdateCommand.load() != UpdateCommand_Stop) {
		UpdateState State = Current_UpdateState.load();
		auto Now = std::chrono::steady_clock::now();

		// A successful check leaves a state of its own, so GitHub is only asked again
		// when the previous attempt did not get through.
		if ((State == UpdateState_None || State == UpdateState_Failed) && Now - LastCheck >= std::chrono::minutes(15)) {
			LastCheck = Now;
			CheckForUpdates();
		}

		UpdateCommand ExpectedCommand = UpdateCommand_Install;
		if (Current_UpdateCommand.compare_exchange_strong(ExpectedCommand, UpdateCommand_None)) InstallUpdate();

		ShaderPatchCommand PatchCommand = Current_ShaderPatchCommand.exchange(ShaderPatchCommand_None);
		if (PatchCommand == ShaderPatchCommand_Install) ShaderPatch_Install();
		else if (PatchCommand == ShaderPatchCommand_Remove) ShaderPatch_Remove();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

bool Class_Engine::IsCurrentVersionOlderThan(std::wstring NewVersion)
{
	if (WSE2Version.length() < 4 || NewVersion.length() < 4) return false;
	if (WSE2Version[0] < NewVersion[0] || (WSE2Version[0] <= NewVersion[0] && WSE2Version[1] < NewVersion[1]) || (WSE2Version[0] <= NewVersion[0] && WSE2Version[1] <= NewVersion[1] && WSE2Version[2] < NewVersion[2]) || (WSE2Version[0] <= NewVersion[0] && WSE2Version[1] <= NewVersion[1] && WSE2Version[2] <= NewVersion[2] && WSE2Version[3] < NewVersion[3])) return true;
	return false;
}
