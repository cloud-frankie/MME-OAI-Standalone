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
include tests/CMakeFiles/testfifo.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/testfifo.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/testfifo.dir/flags.make

tests/CMakeFiles/testfifo.dir/testfifo.c.o: tests/CMakeFiles/testfifo.dir/flags.make
tests/CMakeFiles/testfifo.dir/testfifo.c.o: ../tests/testfifo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/testfifo.dir/testfifo.c.o"
	cd /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/testfifo.dir/testfifo.c.o   -c /home/gcuba/openair-cn/build/git_submodules/freeDiameter/tests/testfifo.c

tests/CMakeFiles/testfifo.dir/testfifo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/testfifo.dir/testfifo.c.i"
	cd /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gcuba/openair-cn/build/git_submodules/freeDiameter/tests/testfifo.c > CMakeFiles/testfifo.dir/testfifo.c.i

tests/CMakeFiles/testfifo.dir/testfifo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/testfifo.dir/testfifo.c.s"
	cd /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gcuba/openair-cn/build/git_submodules/freeDiameter/tests/testfifo.c -o CMakeFiles/testfifo.dir/testfifo.c.s

tests/CMakeFiles/testfifo.dir/testfifo.c.o.requires:

.PHONY : tests/CMakeFiles/testfifo.dir/testfifo.c.o.requires

tests/CMakeFiles/testfifo.dir/testfifo.c.o.provides: tests/CMakeFiles/testfifo.dir/testfifo.c.o.requires
	$(MAKE) -f tests/CMakeFiles/testfifo.dir/build.make tests/CMakeFiles/testfifo.dir/testfifo.c.o.provides.build
.PHONY : tests/CMakeFiles/testfifo.dir/testfifo.c.o.provides

tests/CMakeFiles/testfifo.dir/testfifo.c.o.provides.build: tests/CMakeFiles/testfifo.dir/testfifo.c.o


# Object files for target testfifo
testfifo_OBJECTS = \
"CMakeFiles/testfifo.dir/testfifo.c.o"

# External object files for target testfifo
testfifo_EXTERNAL_OBJECTS =

tests/testfifo: tests/CMakeFiles/testfifo.dir/testfifo.c.o
tests/testfifo: tests/CMakeFiles/testfifo.dir/build.make
tests/testfifo: libfdcore/libfdcore.so.1.2.1
tests/testfifo: /usr/lib/x86_64-linux-gnu/libgnutls.so
tests/testfifo: /usr/lib/x86_64-linux-gnu/libgcrypt.so
tests/testfifo: libfdproto/libfdproto.so.1.2.1
tests/testfifo: tests/CMakeFiles/testfifo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable testfifo"
	cd /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testfifo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/testfifo.dir/build: tests/testfifo

.PHONY : tests/CMakeFiles/testfifo.dir/build

tests/CMakeFiles/testfifo.dir/requires: tests/CMakeFiles/testfifo.dir/testfifo.c.o.requires

.PHONY : tests/CMakeFiles/testfifo.dir/requires

tests/CMakeFiles/testfifo.dir/clean:
	cd /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/testfifo.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/testfifo.dir/clean

tests/CMakeFiles/testfifo.dir/depend:
	cd /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gcuba/openair-cn/build/git_submodules/freeDiameter /home/gcuba/openair-cn/build/git_submodules/freeDiameter/tests /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/tests /home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/tests/CMakeFiles/testfifo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/testfifo.dir/depend

