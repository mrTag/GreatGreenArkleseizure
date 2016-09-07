solution "gga"
   configurations {"Release", "Debug" }
   location (_OPTIONS["to"])

-------------------------------------
-- freeglut static lib
-------------------------------------
   project "freeglut_proj"
   targetname "freeglut_static"
   language "C"
   kind "StaticLib"
   defines {
      "FREEGLUT_STATIC"
   }
   
   includedirs {
      "./3rdParty/freeglut/include"
   }

   files {
      "./3rdParty/freeglut/src/**.h",
      "./3rdParty/freeglut/src/**.c"
   }

   configuration "windows"
   defines {
      "_WIN32",
      "TARGET_HOST_MS_WINDOWS"
   }
   
   configuration "Debug"
      defines     { "_DEBUG" }
      flags       { "Symbols" }
      targetdir   "./lib/debug"

   configuration "Release"
      defines     { "NDEBUG" }
      flags       { "OptimizeSize" }
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
   defines { "FREEGLUT_STATIC" }
   
   flags {
      "No64BitChecks",
      "StaticRuntime"
   }
   
   includedirs {
      "./lib",
      "./3rdParty/freeglut/include",
      "./3rdParty/glew/include"
   }

   libdirs {
      "./lib"
   }

   links {
      "freeglut_proj",
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
      links       { "glew", "freeglut_static" }

   configuration "Release"
      defines     { "NDEBUG" }
      flags       { "OptimizeSize" }
      libdirs     { "./lib/release" }
      links       { "glew", "freeglut_static" }

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
