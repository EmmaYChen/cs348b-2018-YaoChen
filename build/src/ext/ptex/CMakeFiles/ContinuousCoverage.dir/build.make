# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /Library/Python/2.7/site-packages/cmake/data/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Library/Python/2.7/site-packages/cmake/data/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/chenyao/Documents/GitHub/cs348b-2018-YaoChen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/chenyao/Documents/GitHub/cs348b-2018-YaoChen/build

# Utility rule file for ContinuousCoverage.

# Include the progress variables for this target.
include src/ext/ptex/CMakeFiles/ContinuousCoverage.dir/progress.make

src/ext/ptex/CMakeFiles/ContinuousCoverage:
	cd /Users/chenyao/Documents/GitHub/cs348b-2018-YaoChen/build/src/ext/ptex && /Library/Python/2.7/site-packages/cmake/data/CMake.app/Contents/bin/ctest -D ContinuousCoverage

ContinuousCoverage: src/ext/ptex/CMakeFiles/ContinuousCoverage
ContinuousCoverage: src/ext/ptex/CMakeFiles/ContinuousCoverage.dir/build.make

.PHONY : ContinuousCoverage

# Rule to build all files generated by this target.
src/ext/ptex/CMakeFiles/ContinuousCoverage.dir/build: ContinuousCoverage

.PHONY : src/ext/ptex/CMakeFiles/ContinuousCoverage.dir/build

src/ext/ptex/CMakeFiles/ContinuousCoverage.dir/clean:
	cd /Users/chenyao/Documents/GitHub/cs348b-2018-YaoChen/build/src/ext/ptex && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousCoverage.dir/cmake_clean.cmake
.PHONY : src/ext/ptex/CMakeFiles/ContinuousCoverage.dir/clean

src/ext/ptex/CMakeFiles/ContinuousCoverage.dir/depend:
	cd /Users/chenyao/Documents/GitHub/cs348b-2018-YaoChen/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/chenyao/Documents/GitHub/cs348b-2018-YaoChen /Users/chenyao/Documents/GitHub/cs348b-2018-YaoChen/src/ext/ptex /Users/chenyao/Documents/GitHub/cs348b-2018-YaoChen/build /Users/chenyao/Documents/GitHub/cs348b-2018-YaoChen/build/src/ext/ptex /Users/chenyao/Documents/GitHub/cs348b-2018-YaoChen/build/src/ext/ptex/CMakeFiles/ContinuousCoverage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/ext/ptex/CMakeFiles/ContinuousCoverage.dir/depend

