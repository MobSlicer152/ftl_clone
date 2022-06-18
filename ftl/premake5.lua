project "ftl"
	kind "ConsoleApp"
	language "C"

	files {
		"premake5.lua",

		"ftl.h",
		"ini.h",
		"pack.h",
		"settings.h",
		"text.h",
		"util.h",

		"ini.c",
		"main.c",
		"pack.c",
		"settings.c",
		"text.c",
		"util.c",
	}

	sharedlibs({
		"libxml2",
		"SDL2",
		"zlib-ng2",
	})
