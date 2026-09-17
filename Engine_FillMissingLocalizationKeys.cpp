#include "Global.h"

void Class_Engine::FillMissingLocalizationKeys()
{
	if (CurrentLanguage == "ru") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"Играть в M&B WFaS WSE2"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"Играть в M&B WFaS WSE2 x64"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"Играть в M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"Играть в M&B Warband WSE2 x64"));
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
		LocalizedText.insert(std::pair("ui_extracting", u8"Распаковка"));
		LocalizedText.insert(std::pair("ui_update_installed", u8"Обновление установлено."));
		LocalizedText.insert(std::pair("ui_restart_launcher", u8"Перезапустить лаунчер"));
		LocalizedText.insert(std::pair("ui_update_failed", u8"Не удалось обновить:"));
		LocalizedText.insert(std::pair("ui_install_shader_patch", u8"Поставить шейдерный патч"));
		LocalizedText.insert(std::pair("ui_remove_shader_patch", u8"Убрать шейдерный патч"));
		LocalizedText.insert(std::pair("ui_shader_patch_not_for_module", u8"Для этого модуля патча нет"));
		LocalizedText.insert(std::pair("ui_options", u8"Настройки"));
		LocalizedText.insert(std::pair("ui_save", u8"Сохранить"));
		LocalizedText.insert(std::pair("ui_cancel", u8"Отмена"));
		LocalizedText.insert(std::pair("ui_exit", u8"Выйти"));
	}
	if (CurrentLanguage == "de") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"M&B WFaS WSE2 spielen"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"M&B WFaS WSE2 x64 spielen"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"M&B Warband WSE2 spielen"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"M&B Warband WSE2 x64 spielen"));
#endif
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Starten dedizierten server"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Sound deaktivieren"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Musik deaktivieren"));
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
		LocalizedText.insert(std::pair("ui_extracting", u8"Entpacken"));
		LocalizedText.insert(std::pair("ui_update_installed", u8"Das Update wurde installiert."));
		LocalizedText.insert(std::pair("ui_restart_launcher", u8"Launcher neu starten"));
		LocalizedText.insert(std::pair("ui_update_failed", u8"Update fehlgeschlagen:"));
		LocalizedText.insert(std::pair("ui_install_shader_patch", u8"Shader-Patch installieren"));
		LocalizedText.insert(std::pair("ui_remove_shader_patch", u8"Shader-Patch entfernen"));
		LocalizedText.insert(std::pair("ui_shader_patch_not_for_module", u8"Für dieses Modul gibt es noch keinen Patch"));
		LocalizedText.insert(std::pair("ui_options", u8"Optionen"));
		LocalizedText.insert(std::pair("ui_save", u8"Speichern"));
		LocalizedText.insert(std::pair("ui_cancel", u8"Abbrechen"));
		LocalizedText.insert(std::pair("ui_exit", u8"Verlassen"));
	}
	if (CurrentLanguage == "fr") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"Lancer M&B WFaS WSE2"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"Lancer M&B WFaS WSE2 x64"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"Lancer M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"Lancer M&B Warband WSE2 x64"));
#endif
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Démarrer le serveur dédié"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Désactiver les sons"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Désactiver la musique"));
		LocalizedText.insert(std::pair("ui_language", u8"Langue :"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Mod actuel :"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Charger les textures а la demande :"));
		LocalizedText.insert(std::pair("ui_update_wse2", u8"Mettre a jour WSE2"));
		LocalizedText.insert(std::pair("ui_install_wse2", u8"Installer WSE2"));
		LocalizedText.insert(std::pair("ui_version_is_up_to_date", u8"Vous avez la dernière version de WSE2."));
		LocalizedText.insert(std::pair("ui_newer_version_available", u8"Une version plus récente de WSE2 est disponible."));
		LocalizedText.insert(std::pair("ui_wse2_not_installed", u8"WSE2 n'est pas installé."));
		LocalizedText.insert(std::pair("ui_please_wait", u8"Veuillez patienter..."));
		LocalizedText.insert(std::pair("ui_downloading_", u8"Téléchargement "));
		LocalizedText.insert(std::pair("ui_extracting", u8"Décompression"));
		LocalizedText.insert(std::pair("ui_update_installed", u8"La mise à jour a été installée."));
		LocalizedText.insert(std::pair("ui_restart_launcher", u8"Redémarrer le lanceur"));
		LocalizedText.insert(std::pair("ui_update_failed", u8"Échec de la mise à jour:"));
		LocalizedText.insert(std::pair("ui_install_shader_patch", u8"Installer le patch de shaders"));
		LocalizedText.insert(std::pair("ui_remove_shader_patch", u8"Supprimer le patch de shaders"));
		LocalizedText.insert(std::pair("ui_shader_patch_not_for_module", u8"Pas encore de patch pour ce module"));
		LocalizedText.insert(std::pair("ui_options", u8"Options"));
		LocalizedText.insert(std::pair("ui_save", u8"Sauvegarder"));
		LocalizedText.insert(std::pair("ui_cancel", u8"Annuler"));
		LocalizedText.insert(std::pair("ui_exit", u8"Quitter"));
	}
	if (CurrentLanguage == "cz") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"Hrát M&B WFaS WSE2"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"Hrát M&B WFaS WSE2 x64"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"Hrát M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"Hrát M&B Warband WSE2 x64"));
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
		LocalizedText.insert(std::pair("ui_extracting", u8"Rozbalování"));
		LocalizedText.insert(std::pair("ui_update_installed", u8"Aktualizace byla nainstalována."));
		LocalizedText.insert(std::pair("ui_restart_launcher", u8"Restartovat launcher"));
		LocalizedText.insert(std::pair("ui_update_failed", u8"Aktualizace se nezdařila:"));
		LocalizedText.insert(std::pair("ui_install_shader_patch", u8"Nainstalovat shader patch"));
		LocalizedText.insert(std::pair("ui_remove_shader_patch", u8"Odebrat shader patch"));
		LocalizedText.insert(std::pair("ui_shader_patch_not_for_module", u8"Pro tento mod zatím není patch"));
		LocalizedText.insert(std::pair("ui_options", u8"Nastavení"));
		LocalizedText.insert(std::pair("ui_save", u8"Uložit"));
		LocalizedText.insert(std::pair("ui_cancel", u8"Zrušit"));
		LocalizedText.insert(std::pair("ui_exit", u8"Východ"));
	}
	if (CurrentLanguage == "hu") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"A M&B WFaS WSE2 indítása"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"A M&B WFaS WSE2 x64 indítása"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"A M&B Warband WSE2 indítása"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"A M&B Warband WSE2 x64 indítása"));
#endif
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Indítsa el a dedikált szervert"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Hangok kikapcsolása"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Zene kikapcsolása"));
		LocalizedText.insert(std::pair("ui_language", u8"Nyelv:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Jelenlegi mod:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Textúrák kívánság szerinti betöltése:"));
		LocalizedText.insert(std::pair("ui_update_wse2", u8"WSE2 frissítése"));
		LocalizedText.insert(std::pair("ui_install_wse2", u8"WSE2 telepítése"));
		LocalizedText.insert(std::pair("ui_version_is_up_to_date", u8"A jelenlegi WSE2 verziód naprakész."));
		LocalizedText.insert(std::pair("ui_newer_version_available", u8"Újabb WSE2 verzió érhető el."));
		LocalizedText.insert(std::pair("ui_wse2_not_installed", u8"Nincs telepítve a WSE2."));
		LocalizedText.insert(std::pair("ui_please_wait", u8"Kérjük, várjon..."));
		LocalizedText.insert(std::pair("ui_downloading_", u8"Letöltés "));
		LocalizedText.insert(std::pair("ui_extracting", u8"Kicsomagolás"));
		LocalizedText.insert(std::pair("ui_update_installed", u8"A frissítés telepítve lett."));
		LocalizedText.insert(std::pair("ui_restart_launcher", u8"Indítóprogram újraindítása"));
		LocalizedText.insert(std::pair("ui_update_failed", u8"A frissítés sikertelen:"));
		LocalizedText.insert(std::pair("ui_install_shader_patch", u8"Shader patch telepítése"));
		LocalizedText.insert(std::pair("ui_remove_shader_patch", u8"Shader patch eltávolítása"));
		LocalizedText.insert(std::pair("ui_shader_patch_not_for_module", u8"Ehhez a modhoz még nincs patch"));
		LocalizedText.insert(std::pair("ui_options", u8"Beállítások"));
		LocalizedText.insert(std::pair("ui_save", u8"Mentés"));
		LocalizedText.insert(std::pair("ui_cancel", u8"Mégsem"));
		LocalizedText.insert(std::pair("ui_exit", u8"Kilépés"));
	}
	if (CurrentLanguage == "es") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"Jugar M&B WFaS WSE2"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"Jugar M&B WFaS WSE2 x64"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"Jugar M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"Jugar M&B Warband WSE2 x64"));
#endif
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"Iniciar servidor dedicado"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"Desactivar sonido"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"Desactivar música"));
		LocalizedText.insert(std::pair("ui_language", u8"El Idioma:"));
		LocalizedText.insert(std::pair("ui_current_module", u8"Mód actual:"));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"Cargar texturas sobre demanda:"));
		LocalizedText.insert(std::pair("ui_update_wse2", u8"Actualizar WSE2"));
		LocalizedText.insert(std::pair("ui_install_wse2", u8"Instalar WSE2"));
		LocalizedText.insert(std::pair("ui_version_is_up_to_date", u8"Tu versión WSE2 está actualizada."));
		LocalizedText.insert(std::pair("ui_newer_version_available", u8"Hay una nueva versión WSE2 disponible."));
		LocalizedText.insert(std::pair("ui_wse2_not_installed", u8"No tienes WSE2 instalado."));
		LocalizedText.insert(std::pair("ui_please_wait", u8"Por favor espera..."));
		LocalizedText.insert(std::pair("ui_downloading_", u8"Descargando "));
		LocalizedText.insert(std::pair("ui_extracting", u8"Descomprimiendo"));
		LocalizedText.insert(std::pair("ui_update_installed", u8"La actualización se ha instalado."));
		LocalizedText.insert(std::pair("ui_restart_launcher", u8"Reiniciar el lanzador"));
		LocalizedText.insert(std::pair("ui_update_failed", u8"Error al actualizar:"));
		LocalizedText.insert(std::pair("ui_install_shader_patch", u8"Instalar el parche de shaders"));
		LocalizedText.insert(std::pair("ui_remove_shader_patch", u8"Quitar el parche de shaders"));
		LocalizedText.insert(std::pair("ui_shader_patch_not_for_module", u8"Todavía no hay parche para este mod"));
		LocalizedText.insert(std::pair("ui_options", u8"Opciones"));
		LocalizedText.insert(std::pair("ui_save", u8"Guardar"));
		LocalizedText.insert(std::pair("ui_cancel", u8"Cancelar"));
		LocalizedText.insert(std::pair("ui_exit", u8"Salir"));
	}
	if (CurrentLanguage == "tr") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"M&B WFaS WSE2'i Oyna"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"M&B WFaS WSE2 x64'i Oyna"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"M&B Warband WSE2'i Oyna"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"M&B Warband WSE2 x64'i Oyna"));
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
		LocalizedText.insert(std::pair("ui_extracting", u8"Ayıklanıyor"));
		LocalizedText.insert(std::pair("ui_update_installed", u8"Güncelleme kuruldu."));
		LocalizedText.insert(std::pair("ui_restart_launcher", u8"Başlatıcıyı yeniden başlat"));
		LocalizedText.insert(std::pair("ui_update_failed", u8"Güncelleme başarısız:"));
		LocalizedText.insert(std::pair("ui_install_shader_patch", u8"Gölgelendirici yamasını kur"));
		LocalizedText.insert(std::pair("ui_remove_shader_patch", u8"Gölgelendirici yamasını kaldır"));
		LocalizedText.insert(std::pair("ui_shader_patch_not_for_module", u8"Bu mod için henüz yama yok"));
		LocalizedText.insert(std::pair("ui_options", u8"Seçenekler"));
		LocalizedText.insert(std::pair("ui_save", u8"Kaydet"));
		LocalizedText.insert(std::pair("ui_cancel", u8"İptal"));
		LocalizedText.insert(std::pair("ui_exit", u8"Çık"));
	}
	if (CurrentLanguage == "pl") {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"Graj w M&B WFaS WSE2"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"Graj w M&B WFaS WSE2 x64"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"Graj w M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"Graj w M&B Warband WSE2 x64"));
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
		LocalizedText.insert(std::pair("ui_extracting", u8"Rozpakowywanie"));
		LocalizedText.insert(std::pair("ui_update_installed", u8"Aktualizacja została zainstalowana."));
		LocalizedText.insert(std::pair("ui_restart_launcher", u8"Uruchom ponownie launcher"));
		LocalizedText.insert(std::pair("ui_update_failed", u8"Aktualizacja nie powiodła się:"));
		LocalizedText.insert(std::pair("ui_install_shader_patch", u8"Zainstaluj łatkę shaderów"));
		LocalizedText.insert(std::pair("ui_remove_shader_patch", u8"Usuń łatkę shaderów"));
		LocalizedText.insert(std::pair("ui_shader_patch_not_for_module", u8"Brak jeszcze łatki dla tego modułu"));
		LocalizedText.insert(std::pair("ui_options", u8"Opcje"));
		LocalizedText.insert(std::pair("ui_save", u8"Zapisz"));
		LocalizedText.insert(std::pair("ui_cancel", u8"Anuluj"));
		LocalizedText.insert(std::pair("ui_exit", u8"Wyjdź"));
	}
	if (CurrentLanguage == "cns" && LoadCJKFont()) {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"启动 M&B WFaS WSE2"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"启动 M&B WFaS WSE2 x64"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"启动 M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"启动 M&B Warband WSE2 x64"));
#endif
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"启动专用服务器"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"关闭声效"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"关闭音乐"));
		LocalizedText.insert(std::pair("ui_language", u8"语言："));
		LocalizedText.insert(std::pair("ui_current_module", u8"当前模组："));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"在需要时再载入纹理："));
		LocalizedText.insert(std::pair("ui_update_wse2", u8"更新 WSE2"));
		LocalizedText.insert(std::pair("ui_install_wse2", u8"安装 WSE2"));
		LocalizedText.insert(std::pair("ui_version_is_up_to_date", u8"您的 WSE2 已是最新版本。"));
		LocalizedText.insert(std::pair("ui_newer_version_available", u8"有新版本的 WSE2 可用。"));
		LocalizedText.insert(std::pair("ui_wse2_not_installed", u8"您尚未安装 WSE2。"));
		LocalizedText.insert(std::pair("ui_please_wait", u8"请稍候..."));
		LocalizedText.insert(std::pair("ui_downloading_", u8"正在下载 "));
		LocalizedText.insert(std::pair("ui_extracting", u8"正在解压"));
		LocalizedText.insert(std::pair("ui_update_installed", u8"更新已安装。"));
		LocalizedText.insert(std::pair("ui_restart_launcher", u8"重启启动器"));
		LocalizedText.insert(std::pair("ui_update_failed", u8"更新失败："));
		LocalizedText.insert(std::pair("ui_install_shader_patch", u8"安装着色器补丁"));
		LocalizedText.insert(std::pair("ui_remove_shader_patch", u8"移除着色器补丁"));
		LocalizedText.insert(std::pair("ui_shader_patch_not_for_module", u8"暂无适用于此模组的补丁"));
		LocalizedText.insert(std::pair("ui_options", u8"选项"));
		LocalizedText.insert(std::pair("ui_save", u8"保存"));
		LocalizedText.insert(std::pair("ui_cancel", u8"取消"));
		LocalizedText.insert(std::pair("ui_exit", u8"离开"));
	}
	if (CurrentLanguage == "cnt" && LoadCJKFont()) {
#if defined WFAS
		LocalizedText.insert(std::pair("ui_play", u8"啟動 M&B WFaS WSE2"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"啟動 M&B WFaS WSE2 x64"));
#else
		LocalizedText.insert(std::pair("ui_play", u8"啟動 M&B Warband WSE2"));
		LocalizedText.insert(std::pair("ui_play_x64", u8"啟動 M&B Warband WSE2 x64"));
#endif
		LocalizedText.insert(std::pair("ui_start_dedicated", u8"啟動專用伺服器"));
		LocalizedText.insert(std::pair("ui_disable_sound", u8"關閉聲效"));
		LocalizedText.insert(std::pair("ui_disable_music", u8"關閉音樂"));
		LocalizedText.insert(std::pair("ui_language", u8"語言："));
		LocalizedText.insert(std::pair("ui_current_module", u8"目前模組："));
		LocalizedText.insert(std::pair("ui_ondemand_textures", u8"在需要時再載入紋理："));
		LocalizedText.insert(std::pair("ui_update_wse2", u8"更新 WSE2"));
		LocalizedText.insert(std::pair("ui_install_wse2", u8"安裝 WSE2"));
		LocalizedText.insert(std::pair("ui_version_is_up_to_date", u8"您的 WSE2 已是最新版本。"));
		LocalizedText.insert(std::pair("ui_newer_version_available", u8"有新版本的 WSE2 可用。"));
		LocalizedText.insert(std::pair("ui_wse2_not_installed", u8"您尚未安裝 WSE2。"));
		LocalizedText.insert(std::pair("ui_please_wait", u8"請稍候..."));
		LocalizedText.insert(std::pair("ui_downloading_", u8"正在下載 "));
		LocalizedText.insert(std::pair("ui_extracting", u8"正在解壓"));
		LocalizedText.insert(std::pair("ui_update_installed", u8"更新已安裝。"));
		LocalizedText.insert(std::pair("ui_restart_launcher", u8"重新啟動啟動器"));
		LocalizedText.insert(std::pair("ui_update_failed", u8"更新失敗："));
		LocalizedText.insert(std::pair("ui_install_shader_patch", u8"安裝著色器修補檔"));
		LocalizedText.insert(std::pair("ui_remove_shader_patch", u8"移除著色器修補檔"));
		LocalizedText.insert(std::pair("ui_shader_patch_not_for_module", u8"暫無適用於此模組的修補檔"));
		LocalizedText.insert(std::pair("ui_options", u8"選項"));
		LocalizedText.insert(std::pair("ui_save", u8"保存"));
		LocalizedText.insert(std::pair("ui_cancel", u8"取消"));
		LocalizedText.insert(std::pair("ui_exit", u8"離開"));
	}
	if ((CurrentLanguage == "cns" || CurrentLanguage == "cnt") && !LoadCJKFont()) {
		// No font to draw Chinese with, so keep the game's own translations out of the window too.
		LocalizedText.insert_or_assign("ui_save", "Save");
		LocalizedText.insert_or_assign("ui_cancel", "Cancel");
		LocalizedText.insert_or_assign("ui_exit", "Exit");
		LocalizedText.insert_or_assign("ui_options", "Options");
	}

	// English is the fallback: for languages without a block above, and for keys a translation
	// does not carry yet. insert() keeps whatever a block already set.
#if defined WFAS
	LocalizedText.insert(std::pair("ui_play", u8"Play M&B WFaS WSE2"));
	LocalizedText.insert(std::pair("ui_play_x64", u8"Play M&B WFaS WSE2 x64"));
#else
	LocalizedText.insert(std::pair("ui_play", u8"Play M&B Warband WSE2"));
	LocalizedText.insert(std::pair("ui_play_x64", u8"Play M&B Warband WSE2 x64"));
#endif
	LocalizedText.insert(std::pair("ui_start_dedicated", u8"Start dedicated server"));
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
	LocalizedText.insert(std::pair("ui_extracting", u8"Unpacking"));
	LocalizedText.insert(std::pair("ui_update_installed", u8"The update has been installed."));
	LocalizedText.insert(std::pair("ui_restart_launcher", u8"Restart launcher"));
	LocalizedText.insert(std::pair("ui_update_failed", u8"Update failed:"));
	LocalizedText.insert(std::pair("ui_install_shader_patch", u8"Install shader patch"));
	LocalizedText.insert(std::pair("ui_remove_shader_patch", u8"Remove shader patch"));
	LocalizedText.insert(std::pair("ui_shader_patch_not_for_module", u8"No patch for this module yet"));
	LocalizedText.insert(std::pair("ui_options", u8"Options"));
	LocalizedText.insert(std::pair("ui_save", u8"Save"));
	LocalizedText.insert(std::pair("ui_cancel", u8"Cancel"));
	LocalizedText.insert(std::pair("ui_exit", u8"Exit"));
	LocalizedText.insert(std::pair("ui_sound_occlusion_filter", u8"Occlusion Low-Pass Filter"));
	LocalizedText.insert(std::pair("ui_sound_hrtf_filter", u8"HRTF Low-Pass Filter"));
	LocalizedText.insert(std::pair("ui_sound_distance_filter", u8"Distance Low/High-Pass Filter"));
}