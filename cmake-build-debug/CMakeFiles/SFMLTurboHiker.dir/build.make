# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /var/lib/snapd/snap/clion/126/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /var/lib/snapd/snap/clion/126/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mohammed/CLionProjects/SFMLTurboHiker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mohammed/CLionProjects/SFMLTurboHiker/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SFMLTurboHiker.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SFMLTurboHiker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SFMLTurboHiker.dir/flags.make

CMakeFiles/SFMLTurboHiker.dir/main.cpp.o: CMakeFiles/SFMLTurboHiker.dir/flags.make
CMakeFiles/SFMLTurboHiker.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mohammed/CLionProjects/SFMLTurboHiker/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SFMLTurboHiker.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SFMLTurboHiker.dir/main.cpp.o -c /home/mohammed/CLionProjects/SFMLTurboHiker/main.cpp

CMakeFiles/SFMLTurboHiker.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SFMLTurboHiker.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mohammed/CLionProjects/SFMLTurboHiker/main.cpp > CMakeFiles/SFMLTurboHiker.dir/main.cpp.i

CMakeFiles/SFMLTurboHiker.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SFMLTurboHiker.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mohammed/CLionProjects/SFMLTurboHiker/main.cpp -o CMakeFiles/SFMLTurboHiker.dir/main.cpp.s

CMakeFiles/SFMLTurboHiker.dir/src/Animation.cpp.o: CMakeFiles/SFMLTurboHiker.dir/flags.make
CMakeFiles/SFMLTurboHiker.dir/src/Animation.cpp.o: ../src/Animation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mohammed/CLionProjects/SFMLTurboHiker/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SFMLTurboHiker.dir/src/Animation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SFMLTurboHiker.dir/src/Animation.cpp.o -c /home/mohammed/CLionProjects/SFMLTurboHiker/src/Animation.cpp

CMakeFiles/SFMLTurboHiker.dir/src/Animation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SFMLTurboHiker.dir/src/Animation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mohammed/CLionProjects/SFMLTurboHiker/src/Animation.cpp > CMakeFiles/SFMLTurboHiker.dir/src/Animation.cpp.i

CMakeFiles/SFMLTurboHiker.dir/src/Animation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SFMLTurboHiker.dir/src/Animation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mohammed/CLionProjects/SFMLTurboHiker/src/Animation.cpp -o CMakeFiles/SFMLTurboHiker.dir/src/Animation.cpp.s

# Object files for target SFMLTurboHiker
SFMLTurboHiker_OBJECTS = \
"CMakeFiles/SFMLTurboHiker.dir/main.cpp.o" \
"CMakeFiles/SFMLTurboHiker.dir/src/Animation.cpp.o"

# External object files for target SFMLTurboHiker
SFMLTurboHiker_EXTERNAL_OBJECTS =

SFMLTurboHiker: CMakeFiles/SFMLTurboHiker.dir/main.cpp.o
SFMLTurboHiker: CMakeFiles/SFMLTurboHiker.dir/src/Animation.cpp.o
SFMLTurboHiker: CMakeFiles/SFMLTurboHiker.dir/build.make
SFMLTurboHiker: /usr/lib/libsfml-audio.so
SFMLTurboHiker: /usr/lib/libsfml-graphics.so
SFMLTurboHiker: /usr/lib/libsfml-window.so
SFMLTurboHiker: /usr/lib/libsfml-system.so
SFMLTurboHiker: CMakeFiles/SFMLTurboHiker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mohammed/CLionProjects/SFMLTurboHiker/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable SFMLTurboHiker"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SFMLTurboHiker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SFMLTurboHiker.dir/build: SFMLTurboHiker

.PHONY : CMakeFiles/SFMLTurboHiker.dir/build

CMakeFiles/SFMLTurboHiker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SFMLTurboHiker.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SFMLTurboHiker.dir/clean

CMakeFiles/SFMLTurboHiker.dir/depend:
	cd /home/mohammed/CLionProjects/SFMLTurboHiker/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mohammed/CLionProjects/SFMLTurboHiker /home/mohammed/CLionProjects/SFMLTurboHiker /home/mohammed/CLionProjects/SFMLTurboHiker/cmake-build-debug /home/mohammed/CLionProjects/SFMLTurboHiker/cmake-build-debug /home/mohammed/CLionProjects/SFMLTurboHiker/cmake-build-debug/CMakeFiles/SFMLTurboHiker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SFMLTurboHiker.dir/depend

