// Settings

#include "settings.h"

settings_t *settings_init(const char *path)
{
	settings_t *settings;
	char *path2;

	settings = calloc(1, sizeof(settings_t));
	FTL_ASSERT(settings);

	path2 = util_normalize_path(path);
	FTL_LOG("Reading settings from %s\n", path2);

	settings->fullscreen = ini_geti(NULL, "fullscreen", FULLSCREEN_DISABLED, path2);
	settings->last_fullscreen = ini_geti(NULL, "last_fullscreen", FULLSCREEN_DISABLED, path2);
	settings->screen_x = ini_geti(NULL, "screen_x", 0, path2);
	settings->screen_y = ini_geti(NULL, "screen_y", 0, path2);
	settings->music = ini_geti(NULL, "music", 100, path2);
	settings->sound = ini_geti(NULL, "sound", 100, path2);
	settings->altpause = ini_getbool(NULL, "altpause", true, path2);
	settings->dialog_keys = ini_getbool(NULL, "dialog_keys", true, path2);
	settings->showpaths = ini_getbool(NULL, "showpaths", true, path2);
	settings->lowend = ini_getbool(NULL, "lowend", false, path2);
	settings->fbError = ini_geti(NULL, "fbError", 0, path2);
	settings->logging = ini_getbool(NULL, "logging", true, path2);
	settings->ach_pop = ini_getbool(NULL, "ach_pop", true, path2);
	settings->vsync = ini_getbool(NULL, "vsync", true, path2);
	settings->framelimit = ini_getbool(NULL, "framelimit", settings->vsync, path2);
	settings->swapTexture = ini_getbool(NULL, "swapTexture", false, path2);
	settings->colorblind = ini_getbool(NULL, "colorblind", false, path2);
	settings->dlcEnabled = ini_getbool(NULL, "dlcEnabled", true, path2);
	settings->difficulty = ini_geti(NULL, "difficulty", 1, path2);
	settings->language = ini_geti(NULL, "language", LANGUAGE_ENGLISH, path2);

#ifdef FTL_DEBUG
	settings->debug = ini_getbool(NULL, "debug", false, path2);
#endif

	FTL_LOG("Done reading settings from %s\n", path2);
	stbds_arrfree(path2);

	return settings;
}

void settings_save(const char *path, settings_t *settings) {}
