# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Diassis 2022\Documents\PycharmProjects\computacao-grafica-1-freecam"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Diassis 2022\Documents\PycharmProjects\computacao-grafica-1-freecam\cmake-build-debug"

# Utility rule file for uninstall.

# Include any custom commands dependencies for this target.
include glfw/CMakeFiles/uninstall.dir/compiler_depend.make

# Include the progress variables for this target.
include glfw/CMakeFiles/uninstall.dir/progress.make

glfw/CMakeFiles/uninstall:
	cd /d C:\Users\DIASSI~1\DOCUME~1\PYCHAR~1\COMPUT~3\CMAKE-~1\glfw && "C:\Program Files\JetBrains\CLion 2022.2.4\bin\cmake\win\bin\cmake.exe" -P "C:/Users/Diassis 2022/Documents/PycharmProjects/computacao-grafica-1-freecam/cmake-build-debug/glfw/cmake_uninstall.cmake"

uninstall: glfw/CMakeFiles/uninstall
uninstall: glfw/CMakeFiles/uninstall.dir/build.make
.PHONY : uninstall

# Rule to build all files generated by this target.
glfw/CMakeFiles/uninstall.dir/build: uninstall
.PHONY : glfw/CMakeFiles/uninstall.dir/build

glfw/CMakeFiles/uninstall.dir/clean:
	cd /d C:\Users\DIASSI~1\DOCUME~1\PYCHAR~1\COMPUT~3\CMAKE-~1\glfw && $(CMAKE_COMMAND) -P CMakeFiles\uninstall.dir\cmake_clean.cmake
.PHONY : glfw/CMakeFiles/uninstall.dir/clean

glfw/CMakeFiles/uninstall.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Diassis 2022\Documents\PycharmProjects\computacao-grafica-1-freecam" "C:\Users\Diassis 2022\Documents\PycharmProjects\computacao-grafica-1-freecam\glfw" "C:\Users\Diassis 2022\Documents\PycharmProjects\computacao-grafica-1-freecam\cmake-build-debug" "C:\Users\Diassis 2022\Documents\PycharmProjects\computacao-grafica-1-freecam\cmake-build-debug\glfw" "C:\Users\Diassis 2022\Documents\PycharmProjects\computacao-grafica-1-freecam\cmake-build-debug\glfw\CMakeFiles\uninstall.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : glfw/CMakeFiles/uninstall.dir/depend

