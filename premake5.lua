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
		"deps/include",
		"deps/stb",
		"ftl"
	}

	libdirs {
		"deps/lib/%{cfg.platform}"
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

function sharedlibs(_libs)
	links(_libs)
	if _TARGET_OS == "windows" then
		_libpat = "<LIBNAME>.dll"
		_postbuildcmds = {}
		i = 0
		table.foreachi(_libs, function(_lib)
			_libname = string.gsub(_libpat, "<LIBNAME>", _lib)
			_cmd = "{COPYFILE} " .. _MAIN_SCRIPT_DIR .. "/deps/lib/%{cfg.platform}/" .. _libname .. " %{cfg.linktarget.directory}/" .. _libname
			_postbuildcmds = table.flatten({ _postbuildcmds, { _cmd } })
			i = i + 1
		end)
		postbuildmessage("Copying " .. i .. " libraries for target %{cfg.linktarget.name}")
		postbuildcommands(_postbuildcmds)
	end
end

include "ftl"
