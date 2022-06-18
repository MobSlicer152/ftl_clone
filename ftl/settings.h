// Settings stuff

#pragma once

#include "ftl.h"
#include "ini.h"
#include "util.h"

// Fullscreen type
typedef enum fullscreen {
	FULLSCREEN_DISABLED = 0, // Windowed
} fullscreen_t;

// Language
typedef enum language {
	LANGUAGE_ENGLISH = 0
} language_t;

// Settings
typedef struct settings { // Main settings
	fullscreen_t fullscreen; // Fullscreen type
	fullscreen_t last_fullscreen; // Last fullscreen type
	int32_t screen_x; // Something
	int32_t screen_y; // Something
	int32_t music; // Music volume
	int32_t sound; // Sound volume
	bool altpause; // Probably pausing with the scroll wheel
	bool dialog_keys; // Probably using the keyboard to navigate dialogs
	bool showpaths; // Probably showing paths between beacons
	bool lowend; // Probably whether to use worse graphics
	int32_t fbError; // Probably some kind of graphics error reporting thing
	bool logging; // Whether to enable logging
	bool ach_pop; // Something
	bool vsync; // VSync
	bool framelimit; // Frame limit
	bool swapTexture; // Something
	bool colorblind; // Colourblind mode
	bool dlcEnabled; // AE enabled
	int32_t difficulty; // Difficulty
	language_t language; // Language

	// Manual resolution
	bool manual; // Whether to use these settings
	int32_t manual_screen_x; // Width
	int32_t manual_screen_y; // Height
	bool windowed; // Windowed or not
	bool stretched; // Stretch to specified resolution

	// Keybinds

	// Debug
	bool debug;
} settings_t;

// Load or initialize the settings
extern settings_t *settings_init(const char *path);

// Save settings to a file
extern void settings_save(const char *path, settings_t *settings);
