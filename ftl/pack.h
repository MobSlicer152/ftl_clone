// Asset pack formats. Currently only the ftl.dat format, but maybe zip files and folders and stuff later.

#include "ftl.h"

// ftl.dat index (table of offsets to the file entries)
typedef struct dat_index {
	uint32_t index_size; // Number of offsets
	uint32_t* index; // Offsets of entries
} dat_index_t;

// ftl.dat file entry
typedef struct dat_entry {
	uint32_t offset; // Offset. Part of the index, not the entry
	uint32_t data_size; // Size of data
	uint32_t path_len; // Length of path
	char* path; // Path within the file
	uint32_t data_offset; // Offset to the data
} dat_entry_t;
