# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jt/projects/C/VSMP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jt/projects/C/VSMP/build

# Include any dependencies generated for this target.
include CMakeFiles/VSMP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/VSMP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/VSMP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VSMP.dir/flags.make

CMakeFiles/VSMP.dir/main.c.o: CMakeFiles/VSMP.dir/flags.make
CMakeFiles/VSMP.dir/main.c.o: /home/jt/projects/C/VSMP/main.c
CMakeFiles/VSMP.dir/main.c.o: CMakeFiles/VSMP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jt/projects/C/VSMP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/VSMP.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/VSMP.dir/main.c.o -MF CMakeFiles/VSMP.dir/main.c.o.d -o CMakeFiles/VSMP.dir/main.c.o -c /home/jt/projects/C/VSMP/main.c

CMakeFiles/VSMP.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/VSMP.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jt/projects/C/VSMP/main.c > CMakeFiles/VSMP.dir/main.c.i

CMakeFiles/VSMP.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/VSMP.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jt/projects/C/VSMP/main.c -o CMakeFiles/VSMP.dir/main.c.s

CMakeFiles/VSMP.dir/dither.c.o: CMakeFiles/VSMP.dir/flags.make
CMakeFiles/VSMP.dir/dither.c.o: /home/jt/projects/C/VSMP/dither.c
CMakeFiles/VSMP.dir/dither.c.o: CMakeFiles/VSMP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jt/projects/C/VSMP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/VSMP.dir/dither.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/VSMP.dir/dither.c.o -MF CMakeFiles/VSMP.dir/dither.c.o.d -o CMakeFiles/VSMP.dir/dither.c.o -c /home/jt/projects/C/VSMP/dither.c

CMakeFiles/VSMP.dir/dither.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/VSMP.dir/dither.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jt/projects/C/VSMP/dither.c > CMakeFiles/VSMP.dir/dither.c.i

CMakeFiles/VSMP.dir/dither.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/VSMP.dir/dither.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jt/projects/C/VSMP/dither.c -o CMakeFiles/VSMP.dir/dither.c.s

# Object files for target VSMP
VSMP_OBJECTS = \
"CMakeFiles/VSMP.dir/main.c.o" \
"CMakeFiles/VSMP.dir/dither.c.o"

# External object files for target VSMP
VSMP_EXTERNAL_OBJECTS =

VSMP: CMakeFiles/VSMP.dir/main.c.o
VSMP: CMakeFiles/VSMP.dir/dither.c.o
VSMP: CMakeFiles/VSMP.dir/build.make
VSMP: /usr/lib/x86_64-linux-gnu/libavdevice.so
VSMP: /usr/lib/x86_64-linux-gnu/libavfilter.so
VSMP: /usr/lib/x86_64-linux-gnu/libavformat.so
VSMP: /usr/lib/x86_64-linux-gnu/libavcodec.so
VSMP: /usr/lib/x86_64-linux-gnu/libswresample.so
VSMP: /usr/lib/x86_64-linux-gnu/libswscale.so
VSMP: /usr/lib/x86_64-linux-gnu/libavutil.so
VSMP: CMakeFiles/VSMP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jt/projects/C/VSMP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable VSMP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VSMP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VSMP.dir/build: VSMP
.PHONY : CMakeFiles/VSMP.dir/build

CMakeFiles/VSMP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VSMP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VSMP.dir/clean

CMakeFiles/VSMP.dir/depend:
	cd /home/jt/projects/C/VSMP/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jt/projects/C/VSMP /home/jt/projects/C/VSMP /home/jt/projects/C/VSMP/build /home/jt/projects/C/VSMP/build /home/jt/projects/C/VSMP/build/CMakeFiles/VSMP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VSMP.dir/depend

