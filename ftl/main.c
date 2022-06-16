// Main file

#include "ftl.h"
#include "pack.h"

int32_t main(int32_t argc, char* argv[])
{
	pkg_file_t *ftl_dat;
	pkg_entry_t *blueprints;
	uint8_t *blueprints_raw;

	if (argc < 2) {
		FTL_LOG("Not enough arguments\n");
		return 1;
	}

	ftl_dat = pkg_parse(argv[1]);
	
	blueprints = pkg_get(ftl_dat, "data/blueprints.xml");
	blueprints_raw = pkg_read(ftl_dat, blueprints);
	printf("data/blueprints.xml:\n%s\n", blueprints_raw);
	free(blueprints_raw);

	pkg_close(ftl_dat);
}
