#include "Global.h"

void Class_Engine::FillMissingLocalizationKeys() // because uimain.csv files have stupid non-unicode encoding i dont know how to parse
{
	if (CurrentLanguage == "en" || CurrentLanguage == "cns" || CurrentLanguage == "cnt") {
		LocalizedText.insert(std::pair("ui_play", "Play M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_start_dedicated", "Start dedicated server"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Disable sound"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Disable music"));
		LocalizedText.insert(std::pair("ui_language", u8"Language:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Current mod:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Load textures on demand:"));
		LocalizedText.insert(std::pair("ui_update_wse2", u8"Update WSE2"));
		LocalizedText.insert(std::pair("ui_install_wse2", u8"Install WSE2"));
		LocalizedText.insert(std::pair("ui_version_is_up_to_date", u8"Your current WSE2 version is up-to-date."));
		LocalizedText.insert(std::pair("ui_newer_version_available", u8"Newer WSE2 version is available."));
		LocalizedText.insert(std::pair("ui_wse2_not_installed", u8"You don't have WSE2 installed."));
		LocalizedText.insert(std::pair("ui_please_wait", u8"Please wait..."));
		LocalizedText.insert(std::pair("ui_downloading_", u8"Downloading "));
	}
	if (CurrentLanguage == "ru") {
		LocalizedText.insert(std::pair("ui_play", u8"Играть в M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Запустить выделенный сервер"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Отключить звук"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Отключить музыку"));
		LocalizedText.insert(std::pair("ui_language", u8"Язык:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Текущий мод:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Загружать текстуры по необходимости:"));
		LocalizedText.insert(std::pair("ui_update_wse2", u8"Обновить WSE2"));
		LocalizedText.insert(std::pair("ui_install_wse2", u8"Установить WSE2"));
		LocalizedText.insert(std::pair("ui_version_is_up_to_date", u8"У вас последняя версия WSE2."));
		LocalizedText.insert(std::pair("ui_newer_version_available", u8"Новая версия WSE2 доступна для скачивания."));
		LocalizedText.insert(std::pair("ui_wse2_not_installed", u8"WSE2 не установлен."));
		LocalizedText.insert(std::pair("ui_please_wait", u8"Пожалуйста, подождите..."));
		LocalizedText.insert(std::pair("ui_downloading_", u8"Скачивание "));
	}
	if (CurrentLanguage == "de") {
		LocalizedText.insert(std::pair("ui_play", u8"M&B Warband WSE2 spielen"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Starten dedizierten server"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Musik deaktivieren"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Sound deaktivieren"));
		LocalizedText.insert(std::pair("ui_language", u8"Sprache:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Aktuelles Mod:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Texturen nach Bedarf laden:"));
	}
	if (CurrentLanguage == "fr") {
		LocalizedText.insert(std::pair("ui_play", u8"Jouer a M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Démarrer le serveur dédié"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Désactiver les sons"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Désactiver la musique"));
		LocalizedText.insert(std::pair("ui_language", u8"Langue:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Mod actuel:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Charger les textures а la demande:"));
	}
	if (CurrentLanguage == "cz") {
		LocalizedText.insert(std::pair("ui_play", u8"Hrát M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Spusťte dedikovaný server"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Vypnout zvuk"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Vypnout hudbu"));
		LocalizedText.insert(std::pair("ui_language", u8"Jazyk:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Aktuální mod:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Načíst textury na požádání:"));
	}
	if (CurrentLanguage == "hu") {
		LocalizedText.insert(std::pair("ui_play", u8"A M&B Warband WSE2 indítása"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Indítsa el a dedikált szervert"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Hangok kikapcsolása"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Zene kikapcsolása"));
		LocalizedText.insert(std::pair("ui_language", u8"Nyelv:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Jelenlegi mod:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Textúrák kívánság szerinti betöltése:"));
	}
	if (CurrentLanguage == "es") {
		LocalizedText.insert(std::pair("ui_play", u8"Jugar M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Iniciar servidor dedicado"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Desactivar sonido"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Desactivar música"));
		LocalizedText.insert(std::pair("ui_language", u8"El Idioma:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Mód actual:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Cargar texturas sobre demanda:"));
	}
	if (CurrentLanguage == "tr") {
		LocalizedText.insert(std::pair("ui_play", u8"M&B Warband WSE2'i Oyna"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Özel sunucuyu başlat"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Sesi Kapat"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Müziği Kapat"));
		LocalizedText.insert(std::pair("ui_language", u8"Dil:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Mevcut mod:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Dokuları ihtiyaç halinde yükle:"));
	}
	if (CurrentLanguage == "pl") {
		LocalizedText.insert(std::pair("ui_play", u8"Graj w M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Uruchom serwer dedykowany"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Wyłącz dźwięki"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Wyłącz muzykę"));
		LocalizedText.insert(std::pair("ui_language", u8"Język"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Aktualny moduł:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Wczytaj tekstury na żądanie:"));
	}
	if (CurrentLanguage == "cns" || CurrentLanguage == "cnt") {
		LocalizedText.insert_or_assign("ui_save", "Save");
		LocalizedText.insert_or_assign("ui_cancel", "Cancel");
		LocalizedText.insert_or_assign("ui_exit", "Exit");
		LocalizedText.insert_or_assign("ui_options", "Options");
	}
}