// Main file

#include "ftl.h"
#include "pack.h"
#include "settings.h"
#include "text.h"
#include "util.h"

int32_t main(int32_t argc, char *argv[])
{
	char *ftl_dir;
	settings_t *settings;
	pkg_file_t *ftl_dat;
	char *path;
	SDL_Window *wnd;
	char *wnd_title;
	int32_t wnd_width;
	int32_t wnd_height;

	if (argc < 2) {
		FTL_LOG("Not enough arguments, expected FTL directory as first argument\n");
		return 1;
	}

	ftl_dir = util_strfmt(NULL, "%s", argv[1]);

	FTL_LOG("Initializing SDL\n");
	FTL_ASSERT(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_VIDEO) == 0);

	path = util_strfmt(NULL, "%s/settings.ini", ftl_dir);
	settings = settings_init(path);
	stbds_arrfree(path);

	path = util_strfmt(NULL, "%s/ftl.dat", ftl_dir);
	ftl_dat = pkg_parse(path);
	stbds_arrfree(path);

	// Load texts
	text_load(ftl_dat, settings);

	wnd_title = text_get("window_title");
	FTL_LOG("Dat file %s claims to be \"%s\" version \"%s\"\n", ftl_dat->path, wnd_title, text_get("version"));

	// Default window size. FTL only seems to use the screen_x and screen_y after manual and only if manual is 1, and the
	// ones the ini parser can reach are 0.
	wnd_width = 1024;
	wnd_height = 576;
	FTL_LOG("Creating %dx%d window titled \"%s\"\n", wnd_width, wnd_height, wnd_title);
	//wnd = SDL_CreateWindow(wnd_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wnd_width,
	//		       wnd_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	//FTL_ASSERT(wnd);

	FTL_LOG("Cleaning up resources\n");
	text_cleanup();
	pkg_close(ftl_dat);
	free(settings);
	stbds_arrfree(ftl_dir);

	return 0;
}
