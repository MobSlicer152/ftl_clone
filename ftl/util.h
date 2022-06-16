// Utility functions

#pragma once

#include "ftl.h"

// Get the length of a file
extern size_t ftl_fsize(FILE *stream);

// Normalize a path
extern char *ftl_normalize_path(const char *path);

// Duplicate a string
extern char *ftl_strdup(const char *str);

// Duplicate part of a string
extern char *ftl_strndup(const char *str, size_t n);

// Format a string
extern char *ftl_strfmt(size_t *size, const char *fmt, ...);

// Format a string
extern char *ftl_vstrfmt(size_t *size, const char *fmt, va_list args);
