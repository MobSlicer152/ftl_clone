// Implementations of pack.h

#include "pack.h"

#define PKG_TO_NATIVE16(x) x = SDL_SwapBE16(x)
#define PKG_TO_NATIVE32(x) x = SDL_SwapBE32(x)
#define PKG_HEADER_TO_NATIVE(header)                 \
	{                                            \
		PKG_TO_NATIVE16(header.header_size); \
		PKG_TO_NATIVE16(header.entry_size);  \
		PKG_TO_NATIVE32(header.entry_count); \
		PKG_TO_NATIVE32(header.path_size);   \
	}
#define PKG_ENTRY_TO_NATIVE(entry)                    \
	{                                             \
		PKG_TO_NATIVE32(entry.hash);          \
		PKG_TO_NATIVE32(entry.nameofs_flags); \
		PKG_TO_NATIVE32(entry.offset);        \
		PKG_TO_NATIVE32(entry.size);          \
		PKG_TO_NATIVE32(entry.data_size);     \
	}

pkg_file_t *pkg_parse(const char *path)
{
	pkg_file_t *file;
	uint32_t i;

	file = calloc(1, sizeof(pkg_file_t));
	FTL_ASSERT(file);
	file->path = util_normalize_path(path);

	FTL_LOG("Reading package file %s\n", file->path);

	file->fp = fopen(file->path, "rb+");
	FTL_ASSERT(file->fp);

	FTL_LOG("\tReading header\n");
	fread(&file->header, sizeof(pkg_header_t), 1, file->fp);
	PKG_HEADER_TO_NATIVE(file->header);
	FTL_LOG("\tHeader size %u, entry size %u, %u entries\n", file->header.header_size, file->header.entry_size,
		file->header.entry_count);
	FTL_ASSERT(memcmp(file->header.magic, PKG_MAGIC, 4) == 0);
	FTL_ASSERT(file->header.header_size == sizeof(pkg_header_t));
	FTL_ASSERT(file->header.entry_size == sizeof(pkg_entry_t));

	FTL_LOG("\tReading index (%u entries)\n", file->header.entry_count);
	file->entries = calloc(file->header.entry_count, sizeof(pkg_entry_t));
	FTL_ASSERT(file->entries);
	fread(file->entries, sizeof(pkg_entry_t), file->header.entry_count, file->fp);
	for (i = 0; i < file->header.entry_count; i++)
		PKG_ENTRY_TO_NATIVE(file->entries[i]);

	FTL_LOG("\tReading path buffer (%u bytes)\n", file->header.path_size);
	file->path_buf = calloc(file->header.path_size, 1);
	FTL_ASSERT(file->path_buf);
	fread(file->path_buf, 1, file->header.path_size, file->fp);

	FTL_LOG("Done reading package %s\n", file->path);

	return file;
}

void pkg_close(pkg_file_t *file)
{
	if (!file)
		return;

	FTL_LOG("Closing package file %s\n", file->path);

	free(file->entries);
	free(file->path_buf);
	fclose(file->fp);
	stbds_arrfree(file->path);
}

uint8_t *pkg_read(pkg_file_t *file, pkg_entry_t *entry)
{
	uint8_t *buf;

	if (!file || !entry)
		return NULL;

	FTL_LOG("Reading file %s (%u bytes%s at offset %u) from package %s\n", pkg_get_entry_name(file, entry), entry->size,
		entry->flags & 1 ? " compressed" : "", entry->offset, file->path);

	fseek(file->fp, entry->offset, SEEK_SET);
	buf = calloc(entry->size + 1, 1);
	FTL_ASSERT(buf);
	fread(buf, 1, entry->size, file->fp);

	return buf;
}

pkg_entry_t *pkg_get(pkg_file_t *file, const char *path)
{
	uint32_t hash;
	uint32_t i;

	if (!file || !path)
		return NULL;

	hash = pkg_hash(path);
	FTL_LOG("Getting file %s (hash %u) from package %s\n", path, hash, file->path);

	for (i = 0; i < file->header.entry_count; i++) {
		if (file->entries[i].hash == hash)
			break;
	}

	FTL_LOG("Found %s at index %u\n", path, i);

	return file->entries + i;
}
