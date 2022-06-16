// Asset pack formats. Currently only the ftl.dat format introduced in 1.6.1.

#pragma once

#include "ftl.h"
#include "util.h"

// FTL currently uses the System Interface Library PKG format for ftl.dat, and I'm too lazy to get that working with my
// build system, so I'm just going to reimplement specifically the stuff I need. It also seems that the format uses big
// endian, just to make my life harder (SDL has functions for this though).

// The magic bytes for the format.
#define PKG_MAGIC "PKG\12"

// Package header
typedef struct pkg_header {
	char magic[4]; // Must be PKG_MAGIC
	uint16_t header_size; // Size of the header (sizeof pkg_header_t)
	uint16_t entry_size; // Size of an entry (sizeof pkg_entry_t)
	uint32_t entry_count; // Number of entries
	uint32_t path_size; // Size of the path buffer
} pkg_header_t;

// Package entry
typedef struct pkg_entry {
	uint32_t hash; // Hash of the path
	union {
		uint32_t nameofs_flags;
		struct {
			uint32_t nameofs : 24; // Offset into the path buffer
			uint32_t flags : 8; // Flags
		};
	};
	uint32_t offset; // Offset within the package to the data for this entry
	uint32_t size; // Size of the data stored in the package
	uint32_t data_size; // Size of the data after decompression
} pkg_entry_t;

// Package file
typedef struct pkg_file {
	char *path; // Path to the file
	FILE *fp; // File stream
	pkg_header_t header; // File header
	pkg_entry_t *entries; // Entries in the file
	char *path_buf; // Path buffer
} pkg_file_t;

// Read a package file
extern pkg_file_t *pkg_parse(const char *path);

// Close a package
extern void pkg_close(pkg_file_t *file);

// Read a file from a package
extern uint8_t *pkg_read(pkg_file_t *file, pkg_entry_t *entry);

// Get a file entry within a package by its path
extern pkg_entry_t *pkg_get(pkg_file_t *file, const char *path);

// Hash function for package file entries
inline uint32_t pkg_hash(const char *path)
{
	uint32_t hash;
	uint32_t c;

	if (!path)
		return 0;

	hash = 0;
	while (*path) {
		c = *path++;
		if (c >= 'A' && c <= 'Z')
			c |= 0x20; // make letters lowercase
		hash = hash << 27 | hash >> 5;
		hash ^= c;
	}
	return hash;
}

// Get a file's name by index
inline const char *pkg_get_entry_name(pkg_file_t *file, pkg_entry_t *entry)
{
	if (!file || entry->nameofs > file->header.path_size)
		return "";

	return file->path_buf + entry->nameofs;
}
