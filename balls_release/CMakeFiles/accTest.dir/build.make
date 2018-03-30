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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kevin/Desktop/Project/MCPT

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kevin/Desktop/Project/MCPT/balls_release

# Include any dependencies generated for this target.
include CMakeFiles/accTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/accTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/accTest.dir/flags.make

CMakeFiles/accTest.dir/AccTest.cpp.o: CMakeFiles/accTest.dir/flags.make
CMakeFiles/accTest.dir/AccTest.cpp.o: ../AccTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/Desktop/Project/MCPT/balls_release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/accTest.dir/AccTest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/accTest.dir/AccTest.cpp.o -c /home/kevin/Desktop/Project/MCPT/AccTest.cpp

CMakeFiles/accTest.dir/AccTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/accTest.dir/AccTest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/Desktop/Project/MCPT/AccTest.cpp > CMakeFiles/accTest.dir/AccTest.cpp.i

CMakeFiles/accTest.dir/AccTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/accTest.dir/AccTest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/Desktop/Project/MCPT/AccTest.cpp -o CMakeFiles/accTest.dir/AccTest.cpp.s

CMakeFiles/accTest.dir/AccTest.cpp.o.requires:

.PHONY : CMakeFiles/accTest.dir/AccTest.cpp.o.requires

CMakeFiles/accTest.dir/AccTest.cpp.o.provides: CMakeFiles/accTest.dir/AccTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/accTest.dir/build.make CMakeFiles/accTest.dir/AccTest.cpp.o.provides.build
.PHONY : CMakeFiles/accTest.dir/AccTest.cpp.o.provides

CMakeFiles/accTest.dir/AccTest.cpp.o.provides.build: CMakeFiles/accTest.dir/AccTest.cpp.o


# Object files for target accTest
accTest_OBJECTS = \
"CMakeFiles/accTest.dir/AccTest.cpp.o"

# External object files for target accTest
accTest_EXTERNAL_OBJECTS =

accTest: CMakeFiles/accTest.dir/AccTest.cpp.o
accTest: CMakeFiles/accTest.dir/build.make
accTest: Scene/libsceneLib.a
accTest: Accelerate/libaccelerateLib.a
accTest: Ray/librayLib.a
accTest: Camera/libcameraLib.a
accTest: PathTracing/libtracingLib.a
accTest: /usr/local/lib/libopencv_dnn.so.3.4.1
accTest: /usr/local/lib/libopencv_shape.so.3.4.1
accTest: /usr/local/lib/libopencv_videostab.so.3.4.1
accTest: /usr/local/lib/libopencv_ml.so.3.4.1
accTest: /usr/local/lib/libopencv_stitching.so.3.4.1
accTest: /usr/local/lib/libopencv_objdetect.so.3.4.1
accTest: /usr/local/lib/libopencv_superres.so.3.4.1
accTest: /usr/local/lib/libopencv_photo.so.3.4.1
accTest: /usr/local/lib/libopencv_calib3d.so.3.4.1
accTest: /usr/local/lib/libopencv_features2d.so.3.4.1
accTest: /usr/local/lib/libopencv_highgui.so.3.4.1
accTest: /usr/local/lib/libopencv_flann.so.3.4.1
accTest: /usr/local/lib/libopencv_video.so.3.4.1
accTest: /usr/local/lib/libopencv_videoio.so.3.4.1
accTest: /usr/local/lib/libopencv_imgcodecs.so.3.4.1
accTest: /usr/local/lib/libopencv_imgproc.so.3.4.1
accTest: /usr/local/lib/libopencv_core.so.3.4.1
accTest: CMakeFiles/accTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kevin/Desktop/Project/MCPT/balls_release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable accTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/accTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/accTest.dir/build: accTest

.PHONY : CMakeFiles/accTest.dir/build

CMakeFiles/accTest.dir/requires: CMakeFiles/accTest.dir/AccTest.cpp.o.requires

.PHONY : CMakeFiles/accTest.dir/requires

CMakeFiles/accTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/accTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/accTest.dir/clean

CMakeFiles/accTest.dir/depend:
	cd /home/kevin/Desktop/Project/MCPT/balls_release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kevin/Desktop/Project/MCPT /home/kevin/Desktop/Project/MCPT /home/kevin/Desktop/Project/MCPT/balls_release /home/kevin/Desktop/Project/MCPT/balls_release /home/kevin/Desktop/Project/MCPT/balls_release/CMakeFiles/accTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/accTest.dir/depend

