# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gcuba/openair-cn/build/git_submodules/freeDiameter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build

# Include any dependencies generated for this target.
include extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/depend.make

# Include the progress variables for this target.
include extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/progress.make

# Include the compile flags for this target's objects.
include extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/flags.make

extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/dict_Tsp.c.o: extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/flags.make
extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/dict_Tsp.c.o: ../extensions/dict_Tsp/dict_Tsp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/dict_Tsp.c.o"
	cd /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/extensions/dict_Tsp && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dict_Tsp.dir/dict_Tsp.c.o   -c /home/gcuba/openair-cn/build/git_submodules/freeDiameter/extensions/dict_Tsp/dict_Tsp.c

extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/dict_Tsp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dict_Tsp.dir/dict_Tsp.c.i"
	cd /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/extensions/dict_Tsp && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gcuba/openair-cn/build/git_submodules/freeDiameter/extensions/dict_Tsp/dict_Tsp.c > CMakeFiles/dict_Tsp.dir/dict_Tsp.c.i

extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/dict_Tsp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dict_Tsp.dir/dict_Tsp.c.s"
	cd /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/extensions/dict_Tsp && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gcuba/openair-cn/build/git_submodules/freeDiameter/extensions/dict_Tsp/dict_Tsp.c -o CMakeFiles/dict_Tsp.dir/dict_Tsp.c.s

extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/dict_Tsp.c.o.requires:

.PHONY : extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/dict_Tsp.c.o.requires

extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/dict_Tsp.c.o.provides: extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/dict_Tsp.c.o.requires
	$(MAKE) -f extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/build.make extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/dict_Tsp.c.o.provides.build
.PHONY : extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/dict_Tsp.c.o.provides

extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/dict_Tsp.c.o.provides.build: extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/dict_Tsp.c.o


# Object files for target dict_Tsp
dict_Tsp_OBJECTS = \
"CMakeFiles/dict_Tsp.dir/dict_Tsp.c.o"

# External object files for target dict_Tsp
dict_Tsp_EXTERNAL_OBJECTS =

extensions/dict_Tsp.fdx: extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/dict_Tsp.c.o
extensions/dict_Tsp.fdx: extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/build.make
extensions/dict_Tsp.fdx: extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared module ../dict_Tsp.fdx"
	cd /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/extensions/dict_Tsp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dict_Tsp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/build: extensions/dict_Tsp.fdx

.PHONY : extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/build

extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/requires: extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/dict_Tsp.c.o.requires

.PHONY : extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/requires

extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/clean:
	cd /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/extensions/dict_Tsp && $(CMAKE_COMMAND) -P CMakeFiles/dict_Tsp.dir/cmake_clean.cmake
.PHONY : extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/clean

extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/depend:
	cd /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gcuba/openair-cn/build/git_submodules/freeDiameter /home/gcuba/openair-cn/build/git_submodules/freeDiameter/extensions/dict_Tsp /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/extensions/dict_Tsp /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extensions/dict_Tsp/CMakeFiles/dict_Tsp.dir/depend

