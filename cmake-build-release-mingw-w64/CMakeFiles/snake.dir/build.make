# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\file\code\PROJECTS\snake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\file\code\PROJECTS\snake\cmake-build-release-mingw-w64

# Include any dependencies generated for this target.
include CMakeFiles/snake.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/snake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/snake.dir/flags.make

CMakeFiles/snake.dir/main.c.obj: CMakeFiles/snake.dir/flags.make
CMakeFiles/snake.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\file\code\PROJECTS\snake\cmake-build-release-mingw-w64\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/snake.dir/main.c.obj"
	D:\msys64\mingw64\bin\clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\snake.dir\main.c.obj -c D:\file\code\PROJECTS\snake\main.c

CMakeFiles/snake.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/snake.dir/main.c.i"
	D:\msys64\mingw64\bin\clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\file\code\PROJECTS\snake\main.c > CMakeFiles\snake.dir\main.c.i

CMakeFiles/snake.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/snake.dir/main.c.s"
	D:\msys64\mingw64\bin\clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\file\code\PROJECTS\snake\main.c -o CMakeFiles\snake.dir\main.c.s

# Object files for target snake
snake_OBJECTS = \
"CMakeFiles/snake.dir/main.c.obj"

# External object files for target snake
snake_EXTERNAL_OBJECTS =

snake.exe: CMakeFiles/snake.dir/main.c.obj
snake.exe: CMakeFiles/snake.dir/build.make
snake.exe: CMakeFiles/snake.dir/linklibs.rsp
snake.exe: CMakeFiles/snake.dir/objects1.rsp
snake.exe: CMakeFiles/snake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\file\code\PROJECTS\snake\cmake-build-release-mingw-w64\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable snake.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\snake.dir\link.txt --verbose=$(VERBOSE)
	C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -noprofile -executionpolicy Bypass -file D:/vcpkg/scripts/buildsystems/msbuild/applocal.ps1 -targetBinary D:/file/code/PROJECTS/snake/cmake-build-release-mingw-w64/snake.exe -installedDir D:/vcpkg/installed/x64-mingw-dynamic/bin -OutVariable out

# Rule to build all files generated by this target.
CMakeFiles/snake.dir/build: snake.exe

.PHONY : CMakeFiles/snake.dir/build

CMakeFiles/snake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\snake.dir\cmake_clean.cmake
.PHONY : CMakeFiles/snake.dir/clean

CMakeFiles/snake.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\file\code\PROJECTS\snake D:\file\code\PROJECTS\snake D:\file\code\PROJECTS\snake\cmake-build-release-mingw-w64 D:\file\code\PROJECTS\snake\cmake-build-release-mingw-w64 D:\file\code\PROJECTS\snake\cmake-build-release-mingw-w64\CMakeFiles\snake.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/snake.dir/depend
