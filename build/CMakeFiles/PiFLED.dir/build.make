# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/Documents/Programming/source/PiFLED/source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Documents/Programming/source/PiFLED/build

# Include any dependencies generated for this target.
include CMakeFiles/PiFLED.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PiFLED.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PiFLED.dir/flags.make

CMakeFiles/PiFLED.dir/main.cpp.o: CMakeFiles/PiFLED.dir/flags.make
CMakeFiles/PiFLED.dir/main.cpp.o: /home/pi/Documents/Programming/source/PiFLED/source/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Documents/Programming/source/PiFLED/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PiFLED.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PiFLED.dir/main.cpp.o -c /home/pi/Documents/Programming/source/PiFLED/source/main.cpp

CMakeFiles/PiFLED.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PiFLED.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Documents/Programming/source/PiFLED/source/main.cpp > CMakeFiles/PiFLED.dir/main.cpp.i

CMakeFiles/PiFLED.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PiFLED.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Documents/Programming/source/PiFLED/source/main.cpp -o CMakeFiles/PiFLED.dir/main.cpp.s

# Object files for target PiFLED
PiFLED_OBJECTS = \
"CMakeFiles/PiFLED.dir/main.cpp.o"

# External object files for target PiFLED
PiFLED_EXTERNAL_OBJECTS =

PiFLED: CMakeFiles/PiFLED.dir/main.cpp.o
PiFLED: CMakeFiles/PiFLED.dir/build.make
PiFLED: librpi_ws2811.a
PiFLED: CMakeFiles/PiFLED.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Documents/Programming/source/PiFLED/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable PiFLED"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PiFLED.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PiFLED.dir/build: PiFLED

.PHONY : CMakeFiles/PiFLED.dir/build

CMakeFiles/PiFLED.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PiFLED.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PiFLED.dir/clean

CMakeFiles/PiFLED.dir/depend:
	cd /home/pi/Documents/Programming/source/PiFLED/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Documents/Programming/source/PiFLED/source /home/pi/Documents/Programming/source/PiFLED/source /home/pi/Documents/Programming/source/PiFLED/build /home/pi/Documents/Programming/source/PiFLED/build /home/pi/Documents/Programming/source/PiFLED/build/CMakeFiles/PiFLED.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PiFLED.dir/depend

