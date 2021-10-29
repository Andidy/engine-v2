newoption 
{
   trigger = "opengl43",
   description = "use OpenGL 4.3"
}

workspace "engine-v2"
	configurations { "Debug","Debug.DLL", "Release", "Release.DLL" }
	platforms { "x64" }

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		
	filter "configurations:Debug.DLL"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"	
		
	filter "configurations:Release.DLL"
		defines { "NDEBUG" }
		optimize "On"	
		
	filter { "platforms:x64" }
		architecture "x86_64"
	
	targetdir "build/%{cfg.buildcfg}/"
	
	defines{"PLATFORM_DESKTOP"}
	if (_OPTIONS["opengl43"]) then
		defines{"GRAPHICS_API_OPENGL_43"}
	else
		defines{"GRAPHICS_API_OPENGL_33"}
	end
	
project "raylib"
		filter "configurations:Debug.DLL OR Release.DLL"
			kind "SharedLib"
			defines {"BUILD_LIBTYPE_SHARED"}
			
		filter "configurations:Debug OR Release"
			kind "StaticLib"
			
		filter "action:vs*"
			defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_WIN32"}
			links {"winmm"}
			
		filter "action:gmake*"
			links {"pthread", "GL", "m", "dl", "rt", "X11"}
			
		filter{}
		
		location "vs"
		language "C++"
		targetdir "build/%{cfg.buildcfg}"
		cppdialect "C++17"
		
		includedirs { "raysan5/raylib/src", "raysan5/raylib/src/external/glfw/include"}
		vpaths 
		{
			["Header Files"] = { "raysan5/raylib/src/**.h"},
			["Source Files/*"] = {"raysan5/raylib/src/**.c"},
		}
		files {"raysan5/raylib/src/*.h", "raysan5/raylib/src/*.c"}
		
project "engine-v2"
	kind "ConsoleApp"
	location "vs"
	language "C++"
	targetdir "build/%{cfg.buildcfg}"
	cppdialect "C++17"
	
	includedirs {"src"}
	vpaths 
	{
		["Header Files"] = { "**.h"},
		["Source Files"] = {"**.c", "**.cpp"},
	}
	files {"%{wks.name}/**.c", "%{wks.name}/**.cpp", "%{wks.name}/**.h"}

	links {"raylib"}
	
	includedirs { "%{wks.name}", "raysan5/raylib/src", "raysan5/raygui/src" }
	defines{"PLATFORM_DESKTOP", "GRAPHICS_API_OPENGL_33"}
	
	filter "action:vs*"
		defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_WIN32"}
		dependson {"raylib"}
		links {"raylib.lib", "winmm", "kernel32"}
		libdirs {"build/%{cfg.buildcfg}"}
		
	filter "action:gmake*"
		links {"pthread", "GL", "m", "dl", "rt", "X11"}