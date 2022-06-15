// Asset pack formats. Currently only the ftl.dat format, but maybe zip files and folders and stuff later.

#pragma once

#include "ftl.h"

// Key-value pair for stb_ds
typedef struct dat_path {
	char *key; // Path
	uint32_t value; // Location in the index
} dat_path_t;

// ftl.dat index (table of offsets to the file entries)
typedef struct dat_index {
	uint32_t index_size; // Number of offsets
	uint32_t *index; // Offsets of file entries
} dat_index_t;

// ftl.dat file entry
typedef struct dat_entry {
	uint32_t offset; // Offset. Part of the index, not the entry
	uint32_t data_size; // Size of data
	uint32_t path_len; // Length of path
	char *path; // Path within the file
	uint32_t data_offset; // Offset to the data
} dat_entry_t;

// A struct to hold ftl.dat file information
typedef struct dat_file {
	char *name; // Name of the file
	FILE *fp; // File pointer
	dat_index_t index; // Index of the file
	dat_entry_t *entries; // Pointers to entries
	dat_path_t *path_indices; // Indices of paths in the index
} dat_file_t;

// Create a new ftl.dat index with size entries. Truncates the file at path if it exists.
extern dat_file_t *dat_create_index(const char *path, uint32_t size);

// Read an ftl.dat index
extern dat_file_t *dat_read_index(const char *path);
