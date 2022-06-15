// Main file

#include "ftl.h"
#include "pack.h"

int32_t main(int32_t argc, char* argv[])
{
	dat_file_t *ftl_dat;

	FTL_ASSERT(argc >= 2);

	ftl_dat = dat_read_index(argv[1]);
}
