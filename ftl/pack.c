#include "pack.h"

// Offset of the nth offset within the ftl.dat index
#define FTL_DAT_HEADER_INDEX_POS(n) (4 + (n)*4)

dat_file_t *dat_create_index(const char *path, uint32_t size) {
	dat_file_t *file;

	file = calloc(1, sizeof(dat_file_t));
	FTL_ASSERT(file);

	file->fp = fopen(path, "wb+");
	FTL_ASSERT(file->fp);


}
