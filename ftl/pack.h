// Asset pack formats. Currently only the ftl.dat format introduced in 1.6.1.

#pragma once

#include "ftl.h"

// FTL currently uses the System Interface Library PKG format for ftl.dat, and I'm too lazy to get that working with my
// build system, so I'm just going to reimplement specifically the stuff I need. It also seems that the format uses big
// endian, just to make my life harder.

// The magic bytes for the format. The last byte seems to be a version number, because it's 10 in ftl.dat, but 12 in
// current versions of the library.
#define PKG_MAGIC 'PKG\10'

typedef struct pkg_header {
	char magic[4]; // Must be PKG_MAGIC
	uint16_t header_size; // Size of the header

} pkg_header_t;
