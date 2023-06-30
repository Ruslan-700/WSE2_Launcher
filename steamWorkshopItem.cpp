#include "Engine.h"

#if !defined WFAS
steamWorkshopItem::steamWorkshopItem()
{
	m_detailsLoaded = false;
}

void steamWorkshopItem::OnUGCDetailsResult(SteamUGCRequestUGCDetailsResult_t* pCallback, bool bIOFailure)
{
	m_moduleName = pCallback->m_details.m_rgchTitle;
	m_detailsLoaded = true;
}

bool Class_Engine::IsItemFromWorkshop(const std::string &name)
{
	return name.find("(Steam Workshop)") != std::string::npos;
}

std::string Class_Engine::getPathOfWorkshopItem(const std::string &name)
{
	std::string moduleName = name.substr(0, name.rfind(" (Steam Workshop)"));

	for (int i = 0; i < m_numWorkshopItems; i++)
	{
		if (m_workshopItems[i]->m_moduleName == moduleName)
			return m_workshopItems[i]->m_modulePath;
	}

	return "";
}
#endif