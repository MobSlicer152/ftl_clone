project "ftl"
	kind "ConsoleApp"
	language "C"

	files {
		"premake5.lua",

		"ftl.h",
		"pack.h",
		"util.h",

		"main.c",
		"pack.c",
		"util.c",
	}

	sharedlibs({
		"SDL2",
		"zlib-ng2",
	})
