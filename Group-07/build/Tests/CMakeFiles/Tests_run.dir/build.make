# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = /home/ap/Downloads/CSE498-Spring2025/Group-07

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ap/Downloads/CSE498-Spring2025/Group-07/build

# Include any dependencies generated for this target.
include Tests/CMakeFiles/Tests_run.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Tests/CMakeFiles/Tests_run.dir/compiler_depend.make

# Include the progress variables for this target.
include Tests/CMakeFiles/Tests_run.dir/progress.make

# Include the compile flags for this target's objects.
include Tests/CMakeFiles/Tests_run.dir/flags.make

Tests/CMakeFiles/Tests_run.dir/AuditedArrayTest.cpp.o: Tests/CMakeFiles/Tests_run.dir/flags.make
Tests/CMakeFiles/Tests_run.dir/AuditedArrayTest.cpp.o: /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/AuditedArrayTest.cpp
Tests/CMakeFiles/Tests_run.dir/AuditedArrayTest.cpp.o: Tests/CMakeFiles/Tests_run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ap/Downloads/CSE498-Spring2025/Group-07/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Tests/CMakeFiles/Tests_run.dir/AuditedArrayTest.cpp.o"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Tests/CMakeFiles/Tests_run.dir/AuditedArrayTest.cpp.o -MF CMakeFiles/Tests_run.dir/AuditedArrayTest.cpp.o.d -o CMakeFiles/Tests_run.dir/AuditedArrayTest.cpp.o -c /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/AuditedArrayTest.cpp

Tests/CMakeFiles/Tests_run.dir/AuditedArrayTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Tests_run.dir/AuditedArrayTest.cpp.i"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/AuditedArrayTest.cpp > CMakeFiles/Tests_run.dir/AuditedArrayTest.cpp.i

Tests/CMakeFiles/Tests_run.dir/AuditedArrayTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Tests_run.dir/AuditedArrayTest.cpp.s"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/AuditedArrayTest.cpp -o CMakeFiles/Tests_run.dir/AuditedArrayTest.cpp.s

Tests/CMakeFiles/Tests_run.dir/DataFileManagerTest.cpp.o: Tests/CMakeFiles/Tests_run.dir/flags.make
Tests/CMakeFiles/Tests_run.dir/DataFileManagerTest.cpp.o: /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/DataFileManagerTest.cpp
Tests/CMakeFiles/Tests_run.dir/DataFileManagerTest.cpp.o: Tests/CMakeFiles/Tests_run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ap/Downloads/CSE498-Spring2025/Group-07/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Tests/CMakeFiles/Tests_run.dir/DataFileManagerTest.cpp.o"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Tests/CMakeFiles/Tests_run.dir/DataFileManagerTest.cpp.o -MF CMakeFiles/Tests_run.dir/DataFileManagerTest.cpp.o.d -o CMakeFiles/Tests_run.dir/DataFileManagerTest.cpp.o -c /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/DataFileManagerTest.cpp

Tests/CMakeFiles/Tests_run.dir/DataFileManagerTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Tests_run.dir/DataFileManagerTest.cpp.i"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/DataFileManagerTest.cpp > CMakeFiles/Tests_run.dir/DataFileManagerTest.cpp.i

Tests/CMakeFiles/Tests_run.dir/DataFileManagerTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Tests_run.dir/DataFileManagerTest.cpp.s"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/DataFileManagerTest.cpp -o CMakeFiles/Tests_run.dir/DataFileManagerTest.cpp.s

Tests/CMakeFiles/Tests_run.dir/OutputLogTest.cpp.o: Tests/CMakeFiles/Tests_run.dir/flags.make
Tests/CMakeFiles/Tests_run.dir/OutputLogTest.cpp.o: /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/OutputLogTest.cpp
Tests/CMakeFiles/Tests_run.dir/OutputLogTest.cpp.o: Tests/CMakeFiles/Tests_run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ap/Downloads/CSE498-Spring2025/Group-07/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Tests/CMakeFiles/Tests_run.dir/OutputLogTest.cpp.o"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Tests/CMakeFiles/Tests_run.dir/OutputLogTest.cpp.o -MF CMakeFiles/Tests_run.dir/OutputLogTest.cpp.o.d -o CMakeFiles/Tests_run.dir/OutputLogTest.cpp.o -c /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/OutputLogTest.cpp

Tests/CMakeFiles/Tests_run.dir/OutputLogTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Tests_run.dir/OutputLogTest.cpp.i"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/OutputLogTest.cpp > CMakeFiles/Tests_run.dir/OutputLogTest.cpp.i

Tests/CMakeFiles/Tests_run.dir/OutputLogTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Tests_run.dir/OutputLogTest.cpp.s"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/OutputLogTest.cpp -o CMakeFiles/Tests_run.dir/OutputLogTest.cpp.s

Tests/CMakeFiles/Tests_run.dir/SchedulerTest.cpp.o: Tests/CMakeFiles/Tests_run.dir/flags.make
Tests/CMakeFiles/Tests_run.dir/SchedulerTest.cpp.o: /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/SchedulerTest.cpp
Tests/CMakeFiles/Tests_run.dir/SchedulerTest.cpp.o: Tests/CMakeFiles/Tests_run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ap/Downloads/CSE498-Spring2025/Group-07/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object Tests/CMakeFiles/Tests_run.dir/SchedulerTest.cpp.o"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Tests/CMakeFiles/Tests_run.dir/SchedulerTest.cpp.o -MF CMakeFiles/Tests_run.dir/SchedulerTest.cpp.o.d -o CMakeFiles/Tests_run.dir/SchedulerTest.cpp.o -c /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/SchedulerTest.cpp

Tests/CMakeFiles/Tests_run.dir/SchedulerTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Tests_run.dir/SchedulerTest.cpp.i"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/SchedulerTest.cpp > CMakeFiles/Tests_run.dir/SchedulerTest.cpp.i

Tests/CMakeFiles/Tests_run.dir/SchedulerTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Tests_run.dir/SchedulerTest.cpp.s"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/SchedulerTest.cpp -o CMakeFiles/Tests_run.dir/SchedulerTest.cpp.s

Tests/CMakeFiles/Tests_run.dir/SerializerTest.cpp.o: Tests/CMakeFiles/Tests_run.dir/flags.make
Tests/CMakeFiles/Tests_run.dir/SerializerTest.cpp.o: /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/SerializerTest.cpp
Tests/CMakeFiles/Tests_run.dir/SerializerTest.cpp.o: Tests/CMakeFiles/Tests_run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ap/Downloads/CSE498-Spring2025/Group-07/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object Tests/CMakeFiles/Tests_run.dir/SerializerTest.cpp.o"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Tests/CMakeFiles/Tests_run.dir/SerializerTest.cpp.o -MF CMakeFiles/Tests_run.dir/SerializerTest.cpp.o.d -o CMakeFiles/Tests_run.dir/SerializerTest.cpp.o -c /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/SerializerTest.cpp

Tests/CMakeFiles/Tests_run.dir/SerializerTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Tests_run.dir/SerializerTest.cpp.i"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/SerializerTest.cpp > CMakeFiles/Tests_run.dir/SerializerTest.cpp.i

Tests/CMakeFiles/Tests_run.dir/SerializerTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Tests_run.dir/SerializerTest.cpp.s"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/SerializerTest.cpp -o CMakeFiles/Tests_run.dir/SerializerTest.cpp.s

Tests/CMakeFiles/Tests_run.dir/gtest_main.cpp.o: Tests/CMakeFiles/Tests_run.dir/flags.make
Tests/CMakeFiles/Tests_run.dir/gtest_main.cpp.o: /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/gtest_main.cpp
Tests/CMakeFiles/Tests_run.dir/gtest_main.cpp.o: Tests/CMakeFiles/Tests_run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ap/Downloads/CSE498-Spring2025/Group-07/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object Tests/CMakeFiles/Tests_run.dir/gtest_main.cpp.o"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Tests/CMakeFiles/Tests_run.dir/gtest_main.cpp.o -MF CMakeFiles/Tests_run.dir/gtest_main.cpp.o.d -o CMakeFiles/Tests_run.dir/gtest_main.cpp.o -c /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/gtest_main.cpp

Tests/CMakeFiles/Tests_run.dir/gtest_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Tests_run.dir/gtest_main.cpp.i"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/gtest_main.cpp > CMakeFiles/Tests_run.dir/gtest_main.cpp.i

Tests/CMakeFiles/Tests_run.dir/gtest_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Tests_run.dir/gtest_main.cpp.s"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests/gtest_main.cpp -o CMakeFiles/Tests_run.dir/gtest_main.cpp.s

# Object files for target Tests_run
Tests_run_OBJECTS = \
"CMakeFiles/Tests_run.dir/AuditedArrayTest.cpp.o" \
"CMakeFiles/Tests_run.dir/DataFileManagerTest.cpp.o" \
"CMakeFiles/Tests_run.dir/OutputLogTest.cpp.o" \
"CMakeFiles/Tests_run.dir/SchedulerTest.cpp.o" \
"CMakeFiles/Tests_run.dir/SerializerTest.cpp.o" \
"CMakeFiles/Tests_run.dir/gtest_main.cpp.o"

# External object files for target Tests_run
Tests_run_EXTERNAL_OBJECTS =

Tests/Tests_run: Tests/CMakeFiles/Tests_run.dir/AuditedArrayTest.cpp.o
Tests/Tests_run: Tests/CMakeFiles/Tests_run.dir/DataFileManagerTest.cpp.o
Tests/Tests_run: Tests/CMakeFiles/Tests_run.dir/OutputLogTest.cpp.o
Tests/Tests_run: Tests/CMakeFiles/Tests_run.dir/SchedulerTest.cpp.o
Tests/Tests_run: Tests/CMakeFiles/Tests_run.dir/SerializerTest.cpp.o
Tests/Tests_run: Tests/CMakeFiles/Tests_run.dir/gtest_main.cpp.o
Tests/Tests_run: Tests/CMakeFiles/Tests_run.dir/build.make
Tests/Tests_run: Team07Library/libTeam07Library.a
Tests/Tests_run: lib/libgtest.a
Tests/Tests_run: Tests/CMakeFiles/Tests_run.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ap/Downloads/CSE498-Spring2025/Group-07/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable Tests_run"
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tests_run.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Tests/CMakeFiles/Tests_run.dir/build: Tests/Tests_run
.PHONY : Tests/CMakeFiles/Tests_run.dir/build

Tests/CMakeFiles/Tests_run.dir/clean:
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests && $(CMAKE_COMMAND) -P CMakeFiles/Tests_run.dir/cmake_clean.cmake
.PHONY : Tests/CMakeFiles/Tests_run.dir/clean

Tests/CMakeFiles/Tests_run.dir/depend:
	cd /home/ap/Downloads/CSE498-Spring2025/Group-07/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ap/Downloads/CSE498-Spring2025/Group-07 /home/ap/Downloads/CSE498-Spring2025/Group-07/Tests /home/ap/Downloads/CSE498-Spring2025/Group-07/build /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests /home/ap/Downloads/CSE498-Spring2025/Group-07/build/Tests/CMakeFiles/Tests_run.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : Tests/CMakeFiles/Tests_run.dir/depend

