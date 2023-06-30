#include "Engine.h"

void Class_Engine::RefreshModulesList()
{
#if !defined WFAS
	m_numWorkshopItems = 0;

	if (SteamUGC())
	{
		PublishedFileId_t vecSubscribedItems[255];

		int numSubscribedItems = SteamUGC()->GetSubscribedItems(vecSubscribedItems, 255);

		if (numSubscribedItems > 255)
			numSubscribedItems = 255;

		for (int iSubscribedItem = 0; iSubscribedItem < numSubscribedItems; iSubscribedItem++)
		{
			PublishedFileId_t workshopItemID = vecSubscribedItems[iSubscribedItem];

			uint32 unItemState = SteamUGC()->GetItemState(workshopItemID);

			if (unItemState & k_EItemStateInstalled)
			{
				uint32 unTimeStamp = 0;
				uint64 unSizeOnDisk = 0;
				char szItemFolder[MAX_PATH] = { 0 };

				SteamUGC()->GetItemInstallInfo(workshopItemID, &unSizeOnDisk, szItemFolder, sizeof(szItemFolder), &unTimeStamp);

				if (std::filesystem::exists(std::string(szItemFolder) + "/module.ini"))
				{
					SteamAPICall_t hSteamAPICall = SteamUGC()->RequestUGCDetails(workshopItemID, 60);

					steamWorkshopItem* pItem = new steamWorkshopItem;
					pItem->m_modulePath = szItemFolder;
					m_workshopItems[m_numWorkshopItems++] = pItem;

					pItem->m_steamCallResultUGCDetails.Set(hSteamAPICall, pItem, &steamWorkshopItem::OnUGCDetailsResult);

					while (!pItem->m_detailsLoaded)
						SteamAPI_RunCallbacks();
				}
			}
		}
	}
#endif

	Modules.clear();
	std::string Path = "Modules/";
	try {
		if (!std::filesystem::is_directory(std::filesystem::path(L"Modules/"))) {
			return;
		}
		for (const auto& Entry : std::filesystem::directory_iterator(Path)) {
			std::size_t Pos = Entry.path().generic_string().find("/");
			if (std::filesystem::exists(Entry.path().generic_string() + "/module.ini")) {
				Modules.push_back(Entry.path().generic_string().substr(Pos + 1));
			}
		}
	}
	catch (const std::exception& Exception) { 
	//	DisplayErrorMessageMain("Error (unhandled exception in RefreshModulesList) - ''" + std::string(Exception.what()) + "''. "); 
	}

#if !defined WFAS
	for (int i = 0; i < m_numWorkshopItems; i++)
	{
		Modules.push_back(m_workshopItems[i]->m_moduleName + " (Steam Workshop)");
	}
#endif

	for (size_t i = 0; i < Modules.size(); i++)
	{
		ComboBoxModule->addItem(Modules[i], Modules[i]);
	}

	ComboBoxModule->setSelectedItem(GetLastModule());
}

std::string Class_Engine::GetCurrentModule()
{
	return ComboBoxModule->getSelectedItemId().toStdString();
}
