solution "gga"
   configurations {"Release", "Debug" }
   location (_OPTIONS["to"])
      
-------------------------------------
-- glfw static lib
-------------------------------------
   project "glfw_proj"
   targetname "glfw"
   language "C"
   kind "StaticLib"
   defines {
      "_CRT_SECURE_NO_WARNINGS"
   }

   includedirs {
      "./3rdParty/glfw/include"
   }

   files {
      "./3rdParty/glfw/src/internal.h",
      "./3rdParty/glfw/src/glfw_config.h",
      "./3rdParty/glfw/include/GLFW/glfw3.h",
      "./3rdParty/glfw/include/GLFW/glfw3native.h",
      "./3rdParty/glfw/src/context.c",
      "./3rdParty/glfw/src/init.c",
      "./3rdParty/glfw/src/input.c",
      "./3rdParty/glfw/src/monitor.c",
      "./3rdParty/glfw/src/window.c"
   }

   configuration "windows"
   defines {
      "_GLFW_WIN32"
   }
   files {
      "./3rdParty/glfw/src/vulkan.c",
      "./3rdParty/glfw/src/win32_platform.h",
      "./3rdParty/glfw/src/win32_joystick.h",
      "./3rdParty/glfw/src/wgl_context.h",
      "./3rdParty/glfw/src/egl_context.c",
      "./3rdParty/glfw/src/win32_init.c",
      "./3rdParty/glfw/src/win32_joystick.c",
      "./3rdParty/glfw/src/win32_monitor.c",
      "./3rdParty/glfw/src/win32_time.c",
      "./3rdParty/glfw/src/win32_tls.c",
      "./3rdParty/glfw/src/win32_window.c",
      "./3rdParty/glfw/src/wgl_context.c",
      "./3rdParty/glfw/src/egl_context.c"
   }
   targetdir "./lib"
   links       { "gdi32" }
   
   configuration "Debug"
      defines     { "_DEBUG" }
      flags       { "Symbols" }
      links       { "msvcrtd" }
      targetdir   "./lib/debug"

   configuration "Release"
      defines     { "NDEBUG" }
      flags       { "OptimizeSize" }
      links       { "msvcrt" }
      targetdir   "./lib/release"
      
-------------------------------------
-- glew static lib
-------------------------------------
   project "glew_proj"
   targetname "glew"
   language "C"
   kind "StaticLib"

   includedirs {
      "./3rdParty/glew/include"
   }

   files {
      "./3rdParty/glew/src/**.h",
      "./3rdParty/glew/src/**.c",
      "./3rdParty/glew/include/GL/**.h"
   }
   
   configuration "windows"
      targetdir "./lib"

   configuration "Debug"
      defines     { "_DEBUG" }
      flags       { "Symbols" }
      targetdir   "./lib/debug"

   configuration "Release"
      defines     { "NDEBUG" }
      flags       { "OptimizeSize" }
      targetdir   "./lib/release"

-------------------------------------   
-- top level gga project
-------------------------------------
   project "gga"
   targetname "gga"
   language "C++"
   kind "ConsoleApp"
   
   flags {
      "No64BitChecks",
      "StaticRuntime"
   }
   
   includedirs {
      "./lib",
      "./3rdParty/glew/include",
      "./3rdParty/glfw/include/"
   }

   libdirs {
      "./lib"
   }

   links {
      "glfw_proj",
      "glew_proj"
   }
   
   files {
      "./src/**.h",
      "./src/**.cpp"
   }

   configuration "Debug"
      defines     { "_DEBUG" }
      flags       { "Symbols" }
      libdirs     { "./lib/debug" }
      links       { "glew", "glfw" }

   configuration "Release"
      defines     { "NDEBUG" }
      flags       { "OptimizeSize" }
      libdirs     { "./lib/release" }
      links       { "glew", "glfw" }

   configuration "windows"
      defines     { "_WIN32" }
      targetdir   "./bin/windows"

if _ACTION == "clean" then
   os.rmdir("bin")
   os.rmdir("build")
end

newoption {
   trigger = "to",
   value   = "path",
   description = "Set the output location for the generated files"
}
