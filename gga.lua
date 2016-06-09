solution "gga"
configurations {
   "Release",
   "Debug"
}
location (_OPTIONS["to"])

project "gga"
targetname "gga"
language "C++"
kind "ConsoleApp"
flags {
   "No64BitChecks",
   "StaticRuntime"
}

files {
   "./src/**.h",
   "./src/**.cpp"
}

configuration "Debug"
   defines     { "_DEBUG" }
   flags       { "Symbols" }

configuration "Release"
   defines     { "NDEBUG" }
   flags       { "OptimizeSize" }

configuration "windows"
   targetdir   "../bin/windows"

if _ACTION == "clean" then
   os.rmdir("bin")
   os.rmdir("build")
end
