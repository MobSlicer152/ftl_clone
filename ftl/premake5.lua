project "ftl"
	kind "ConsoleApp"
	language "C"

	files {
		"premake5.lua",

		"ftl.h",
		"ini.h",
		"pack.h",
		"settings.h",
		"util.h",

		"ini.c",
		"main.c",
		"pack.c",
		"settings.c",
		"util.c",
	}

	sharedlibs({
		"expat",
		"SDL2",
		"zlib-ng2",
	})
