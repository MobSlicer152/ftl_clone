workspace "ftl"
	configurations { "Debug", "Release" }
	platforms { "x64", "ARM64" }

	location "proj"
	targetdir "bin"
	objdir "bin-int"

	cdialect "C11"
	warnings "Extra"

	files { "premake5.lua" }

	includedirs {
		"ftl"
	}

	filter "configurations:Debug"
		defines "FTL_DEBUG=1"
		symbols "On"
	filter "configurations:Release"
		defines "FTL_RELEASE=1"
		symbols "Off"
		optimize "On"
	filter "platforms:x64"
		architecture "x64"
		defines "FTL_X64=1"
	filter "platforms:ARM64"
		architecture "ARM64"
		defines "FTL_ARM64=1"
	filter ""

	filter "action:vs*"
		defines {
			"_CRT_SECURE_NO_DEPRACATE",
			"_CRT_SECURE_NO_WARNINGS",
			"_CRT_NONSTDC_NO_WARNINGS",
		}
	filter ""


include "ftl"
