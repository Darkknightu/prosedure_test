# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\cpp\CLion\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\cpp\CLion\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Science\avro_c++\Procedure\prosedure_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Science\avro_c++\Procedure\prosedure_test\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Procedure_testleet.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Procedure_testleet.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Procedure_testleet.dir/flags.make

CMakeFiles/Procedure_testleet.dir/testleet.cpp.obj: CMakeFiles/Procedure_testleet.dir/flags.make
CMakeFiles/Procedure_testleet.dir/testleet.cpp.obj: ../testleet.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Science\avro_c++\Procedure\prosedure_test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Procedure_testleet.dir/testleet.cpp.obj"
	D:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Procedure_testleet.dir\testleet.cpp.obj -c D:\Science\avro_c++\Procedure\prosedure_test\testleet.cpp

CMakeFiles/Procedure_testleet.dir/testleet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Procedure_testleet.dir/testleet.cpp.i"
	D:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Science\avro_c++\Procedure\prosedure_test\testleet.cpp > CMakeFiles\Procedure_testleet.dir\testleet.cpp.i

CMakeFiles/Procedure_testleet.dir/testleet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Procedure_testleet.dir/testleet.cpp.s"
	D:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Science\avro_c++\Procedure\prosedure_test\testleet.cpp -o CMakeFiles\Procedure_testleet.dir\testleet.cpp.s

# Object files for target Procedure_testleet
Procedure_testleet_OBJECTS = \
"CMakeFiles/Procedure_testleet.dir/testleet.cpp.obj"

# External object files for target Procedure_testleet
Procedure_testleet_EXTERNAL_OBJECTS =

testleet.exe: CMakeFiles/Procedure_testleet.dir/testleet.cpp.obj
testleet.exe: CMakeFiles/Procedure_testleet.dir/build.make
testleet.exe: CMakeFiles/Procedure_testleet.dir/linklibs.rsp
testleet.exe: CMakeFiles/Procedure_testleet.dir/objects1.rsp
testleet.exe: CMakeFiles/Procedure_testleet.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Science\avro_c++\Procedure\prosedure_test\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testleet.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Procedure_testleet.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Procedure_testleet.dir/build: testleet.exe

.PHONY : CMakeFiles/Procedure_testleet.dir/build

CMakeFiles/Procedure_testleet.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Procedure_testleet.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Procedure_testleet.dir/clean

CMakeFiles/Procedure_testleet.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Science\avro_c++\Procedure\prosedure_test D:\Science\avro_c++\Procedure\prosedure_test D:\Science\avro_c++\Procedure\prosedure_test\cmake-build-debug D:\Science\avro_c++\Procedure\prosedure_test\cmake-build-debug D:\Science\avro_c++\Procedure\prosedure_test\cmake-build-debug\CMakeFiles\Procedure_testleet.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Procedure_testleet.dir/depend

