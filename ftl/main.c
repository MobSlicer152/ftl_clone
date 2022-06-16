// Main file

#include "ftl.h"
#include "pack.h"
#include "util.h"

int32_t main(int32_t argc, char *argv[])
{
	char *ftl_dir;
	SDL_Window *wnd;
	char *ftl_dat_path;
	pkg_file_t *ftl_dat;

	if (argc < 2) {
		FTL_LOG("Not enough arguments, expected FTL directory as first argument\n");
		return 1;
	}

	ftl_dir = ftl_strfmt(NULL, "%s", argv[1]);

	FTL_LOG("Initializing SDL\n");
	FTL_ASSERT(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_VIDEO) == 0);



	ftl_dat_path = ftl_strfmt(NULL, "%s/ftl.dat", ftl_dir);
	ftl_dat = pkg_parse(ftl_dat_path);
	stbds_arrfree(ftl_dat_path);

	pkg_close(ftl_dat);
	stbds_arrfree(ftl_dir);

	return 0;
}
