// Implementations of pack.h

#include "pack.h"

// Offset of the nth offset within the ftl.dat index
#define FTL_DAT_HEADER_INDEX_POS(n) (4 + (n)*4)

dat_file_t *dat_create_index(const char *path, uint32_t size)
{
	dat_file_t *file;
	uint32_t zero = 0;
	uint32_t i;

	file = calloc(1, sizeof(dat_file_t));
	FTL_ASSERT(file);

	file->fp = fopen(path, "wb+");
	FTL_ASSERT(file->fp);

	stbds_arrsetlen(file->entries, size);

	// Write the index size and fill it with empty offsets
	fwrite(&size, 4, 1, file->fp);
	for (i = 0; i < size; i++)
		fwrite(&zero, 4, 1, file->fp);
}

dat_file_t *dat_read_index(const char *path)
{
	dat_file_t *file;
	size_t len;
	uint32_t size;
	long entry_offset;
	uint32_t i;

	FTL_LOG("Reading dat file %s\n", path);

	file = calloc(1, sizeof(dat_file_t));
	FTL_ASSERT(file);

	file->fp = fopen(path, "rb+");
	FTL_ASSERT(file->fp);

	len = flen(file->fp);

	fread(&size, 4, 1, file->fp);
	FTL_ASSERT(size * 4 > len);

	FTL_LOG("Reading %d entries from %s\n", size, path);

	stbds_arrsetlen(file->entries, size);
	memset(file->entries, 0, sizeof(uint32_t) * size);


	for (i = 0; i < size; i++) {
		fread(&entry_offset, 4, 1, file->fp);
		if (entry_offset != 0)
			file->entries[i].offset = entry_offset;
	}
}
