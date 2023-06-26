#include "Global.h"

void Class_Engine::FillMissingLocalizationKeys()
{
	if (CurrentLanguage == "en" || CurrentLanguage == "cns" || CurrentLanguage == "cnt") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", "Play M&B WFaS WSE2"));
#else
		LocalizedText.insert(std::pair("ui_play", "Play M&B Warband WSE2"));
#endif
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
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"Играть в M&B WFaS WSE2"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"Играть в M&B Warband WSE2"));
#endif
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Запустить выделенный сервер"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Отключить звук"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Отключить музыку"));
		LocalizedText.insert(std::pair("ui_language", u8"Язык:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Текущий мод:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Загружать текстуры по требованию:"));
		LocalizedText.insert(std::pair("ui_update_wse2", u8"Обновить WSE2"));
		LocalizedText.insert(std::pair("ui_install_wse2", u8"Установить WSE2"));
		LocalizedText.insert(std::pair("ui_version_is_up_to_date", u8"У вас последняя версия WSE2."));
		LocalizedText.insert(std::pair("ui_newer_version_available", u8"Новая версия WSE2 доступна для скачивания."));
		LocalizedText.insert(std::pair("ui_wse2_not_installed", u8"WSE2 не установлен."));
		LocalizedText.insert(std::pair("ui_please_wait", u8"Пожалуйста, подождите..."));
		LocalizedText.insert(std::pair("ui_downloading_", u8"Скачивание "));
	}
	if (CurrentLanguage == "de") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"M&B WFaS WSE2 spielen"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"M&B Warband WSE2 spielen"));
#endif
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Starten dedizierten server"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Musik deaktivieren"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Sound deaktivieren"));
		LocalizedText.insert(std::pair("ui_language", u8"Sprache:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Aktuelles Mod:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Texturen nach Bedarf laden:"));
		LocalizedText.insert(std::pair("ui_update_wse2", u8"Aktualisieren WSE2"));
		LocalizedText.insert(std::pair("ui_install_wse2", u8"WSE2 installieren"));
		LocalizedText.insert(std::pair("ui_version_is_up_to_date", u8"Die WSE2-Version ist auf dem neuesten Stand."));
		LocalizedText.insert(std::pair("ui_newer_version_available", u8"Neuere WSE2-Version ist verfügbar."));
		LocalizedText.insert(std::pair("ui_wse2_not_installed", u8"Sie haben WSE2 nicht installiert."));
		LocalizedText.insert(std::pair("ui_please_wait", u8"Bitte warten..."));
		LocalizedText.insert(std::pair("ui_downloading_", u8"Heruntergeladen "));
	}
	if (CurrentLanguage == "fr") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"Jouer a M&B WFaS WSE2"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"Jouer a M&B Warband WSE2"));
#endif
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Démarrer le serveur dédié"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Désactiver les sons"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Désactiver la musique"));
		LocalizedText.insert(std::pair("ui_language", u8"Langue:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Mod actuel:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Charger les textures а la demande:"));
		LocalizedText.insert(std::pair("ui_update_wse2", u8"Mettre a jour WSE2"));
		LocalizedText.insert(std::pair("ui_install_wse2", u8"Installer WSE2"));
		LocalizedText.insert(std::pair("ui_version_is_up_to_date", u8"Votre version actuelle de WSE2 est a jour."));
		LocalizedText.insert(std::pair("ui_newer_version_available", u8"Une version plus récente de WSE2 est disponible."));
		LocalizedText.insert(std::pair("ui_wse2_not_installed", u8"WSE2 n'est pas installé."));
		LocalizedText.insert(std::pair("ui_please_wait", u8"Veuillez patienter..."));
		LocalizedText.insert(std::pair("ui_downloading_", u8"Téléchargement "));
	}
	if (CurrentLanguage == "cz") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"Hrát M&B WFaS WSE2"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"Hrát M&B Warband WSE2"));
#endif
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Spusťte dedikovaný server"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Vypnout zvuk"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Vypnout hudbu"));
		LocalizedText.insert(std::pair("ui_language", u8"Jazyk:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Aktuální mod:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Načíst textury na požádání:"));		
		LocalizedText.insert(std::pair("ui_update_wse2", u8"Aktualizace WSE2"));
		LocalizedText.insert(std::pair("ui_install_wse2", u8"Instalovat WSE2"));
		LocalizedText.insert(std::pair("ui_version_is_up_to_date", u8"Vaše aktuální verze WSE2 je aktuální."));
		LocalizedText.insert(std::pair("ui_newer_version_available", u8"K dispozici je novější verze WSE2."));
		LocalizedText.insert(std::pair("ui_wse2_not_installed", u8"Nemáte nainstalovaný WSE2."));
		LocalizedText.insert(std::pair("ui_please_wait", u8"Počkejte prosím..."));
		LocalizedText.insert(std::pair("ui_downloading_", u8"Stahování "));
	}
	if (CurrentLanguage == "hu") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"A M&B WFaS WSE2 indítása"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"A M&B Warband WSE2 indítása"));
#endif
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Indítsa el a dedikált szervert"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Hangok kikapcsolása"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Zene kikapcsolása"));
		LocalizedText.insert(std::pair("ui_language", u8"Nyelv:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Jelenlegi mod:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Textúrák kívánság szerinti betöltése:"));
		LocalizedText.insert(std::pair("ui_update_wse2", u8"WSE2 frissítése"));
		LocalizedText.insert(std::pair("ui_install_wse2", u8"WSE2 telepítése"));
		LocalizedText.insert(std::pair("ui_version_is_up_to_date", u8"Your current WSE2 version is up-to-date."));
		LocalizedText.insert(std::pair("ui_newer_version_available", u8"Newer WSE2 version is available."));
		LocalizedText.insert(std::pair("ui_wse2_not_installed", u8"You don't have WSE2 installed."));
		LocalizedText.insert(std::pair("ui_please_wait", u8"Please wait..."));
		LocalizedText.insert(std::pair("ui_downloading_", u8"Downloading "));
	}
	if (CurrentLanguage == "es") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"Jugar M&B WFaS WSE2"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"Jugar M&B Warband WSE2"));
#endif
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Iniciar servidor dedicado"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Desactivar sonido"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Desactivar música"));
		LocalizedText.insert(std::pair("ui_language", u8"El Idioma:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Mód actual:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Cargar texturas sobre demanda:"));
		LocalizedText.insert(std::pair("ui_update_wse2", u8"Actualizar WSE2"));
		LocalizedText.insert(std::pair("ui_install_wse2", u8"Instalar WSE2"));
		LocalizedText.insert(std::pair("ui_version_is_up_to_date", u8"Tu versión WSE2 está desactualizada."));
		LocalizedText.insert(std::pair("ui_newer_version_available", u8"Hay una nueva versión WSE2 disponible."));
		LocalizedText.insert(std::pair("ui_wse2_not_installed", u8"No tienes WSE2 instalado."));
		LocalizedText.insert(std::pair("ui_please_wait", u8"Por favor espera..."));
		LocalizedText.insert(std::pair("ui_downloading_", u8"Descargando "));
	}
	if (CurrentLanguage == "tr") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"M&B WFaS WSE2'i Oyna"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"M&B Warband WSE2'i Oyna"));
#endif
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Özel sunucuyu başlat"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Sesi Kapat"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Müziği Kapat"));
		LocalizedText.insert(std::pair("ui_language", u8"Dil:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Mevcut mod:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Dokuları ihtiyaç halinde yükle:"));
		LocalizedText.insert(std::pair("ui_update_wse2", u8"WSE2'yi güncelle"));
		LocalizedText.insert(std::pair("ui_install_wse2", u8"WSE2'yi kur"));
		LocalizedText.insert(std::pair("ui_version_is_up_to_date", u8"WSE2 sürümü güncel."));
		LocalizedText.insert(std::pair("ui_newer_version_available", u8"Daha yeni WSE2 sürümü mevcut."));
		LocalizedText.insert(std::pair("ui_wse2_not_installed", u8"WSE2 kurulu değil."));
		LocalizedText.insert(std::pair("ui_please_wait", u8"Lütfen bekleyin..."));
		LocalizedText.insert(std::pair("ui_downloading_", u8"İndiriliyor "));
	}
	if (CurrentLanguage == "pl") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"Graj w M&B WFaS WSE2"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"Graj w M&B Warband WSE2"));
#endif
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Uruchom serwer dedykowany"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Wyłącz dźwięki"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Wyłącz muzykę"));
		LocalizedText.insert(std::pair("ui_language", u8"Język"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Aktualny moduł:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Wczytaj tekstury na żądanie:"));
		LocalizedText.insert(std::pair("ui_update_wse2", u8"Aktualizuj WSE2"));
		LocalizedText.insert(std::pair("ui_install_wse2", u8"Zainstaluj WSE2"));
		LocalizedText.insert(std::pair("ui_version_is_up_to_date", u8"WSE2 jest aktualna."));
		LocalizedText.insert(std::pair("ui_newer_version_available", u8"Nowsza wersja WSE2 jest dostępna."));
		LocalizedText.insert(std::pair("ui_wse2_not_installed", u8"Nie masz zainstalowanego WSE2."));
		LocalizedText.insert(std::pair("ui_please_wait", u8"Proszę czekać..."));
		LocalizedText.insert(std::pair("ui_downloading_", u8"Pobieranie "));
	}
	if (CurrentLanguage == "cns" || CurrentLanguage == "cnt") {
		LocalizedText.insert_or_assign("ui_save", "Save");
		LocalizedText.insert_or_assign("ui_cancel", "Cancel");
		LocalizedText.insert_or_assign("ui_exit", "Exit");
		LocalizedText.insert_or_assign("ui_options", "Options");
	}
}