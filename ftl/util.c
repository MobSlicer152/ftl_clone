// Implementations of util.h

// All the stb headers are included in ftl.h, which util.h includes
#define STB_DS_IMPLEMENTATION

#include "util.h"

size_t flen(FILE *stream)
{
	long offs;
	size_t len = 0;

	if (!stream)
		return 0;

	offs = ftell(stream);
	fseek(stream, 0, SEEK_END);
	len = ftell(stream);
	fseek(stream, offs, SEEK_SET);

	return len;
}
