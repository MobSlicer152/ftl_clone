project "ftl"
	kind "ConsoleApp"
	language "C"

	files {
		"premake5.lua",

		"ftl.h",
		"pack.h",

		"main.c",
		"pack.c",
	}

	sharedlibs({
		"SDL2"
	})
