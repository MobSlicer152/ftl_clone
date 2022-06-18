// Functions for texts

#pragma once

#include "ftl.h"
#include "pack.h"
#include "settings.h"
#include "util.h"

// Parses the XML documents containing the game's texts
extern void text_load(pkg_file_t *ftl_dat, settings_t *settings);

// Gets the text associated with an ID
extern char *text_get(const char *id);

// Cleans up the data associated with the texts
extern void text_cleanup(void);
