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
CMAKE_BINARY_DIR = /home/kevin/Desktop/Project/MCPT/release

# Include any dependencies generated for this target.
include Scene/CMakeFiles/sceneLib.dir/depend.make

# Include the progress variables for this target.
include Scene/CMakeFiles/sceneLib.dir/progress.make

# Include the compile flags for this target's objects.
include Scene/CMakeFiles/sceneLib.dir/flags.make

Scene/CMakeFiles/sceneLib.dir/Mesh.cpp.o: Scene/CMakeFiles/sceneLib.dir/flags.make
Scene/CMakeFiles/sceneLib.dir/Mesh.cpp.o: ../Scene/Mesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/Desktop/Project/MCPT/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Scene/CMakeFiles/sceneLib.dir/Mesh.cpp.o"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sceneLib.dir/Mesh.cpp.o -c /home/kevin/Desktop/Project/MCPT/Scene/Mesh.cpp

Scene/CMakeFiles/sceneLib.dir/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sceneLib.dir/Mesh.cpp.i"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/Desktop/Project/MCPT/Scene/Mesh.cpp > CMakeFiles/sceneLib.dir/Mesh.cpp.i

Scene/CMakeFiles/sceneLib.dir/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sceneLib.dir/Mesh.cpp.s"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/Desktop/Project/MCPT/Scene/Mesh.cpp -o CMakeFiles/sceneLib.dir/Mesh.cpp.s

Scene/CMakeFiles/sceneLib.dir/Mesh.cpp.o.requires:

.PHONY : Scene/CMakeFiles/sceneLib.dir/Mesh.cpp.o.requires

Scene/CMakeFiles/sceneLib.dir/Mesh.cpp.o.provides: Scene/CMakeFiles/sceneLib.dir/Mesh.cpp.o.requires
	$(MAKE) -f Scene/CMakeFiles/sceneLib.dir/build.make Scene/CMakeFiles/sceneLib.dir/Mesh.cpp.o.provides.build
.PHONY : Scene/CMakeFiles/sceneLib.dir/Mesh.cpp.o.provides

Scene/CMakeFiles/sceneLib.dir/Mesh.cpp.o.provides.build: Scene/CMakeFiles/sceneLib.dir/Mesh.cpp.o


Scene/CMakeFiles/sceneLib.dir/Vertex.cpp.o: Scene/CMakeFiles/sceneLib.dir/flags.make
Scene/CMakeFiles/sceneLib.dir/Vertex.cpp.o: ../Scene/Vertex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/Desktop/Project/MCPT/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Scene/CMakeFiles/sceneLib.dir/Vertex.cpp.o"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sceneLib.dir/Vertex.cpp.o -c /home/kevin/Desktop/Project/MCPT/Scene/Vertex.cpp

Scene/CMakeFiles/sceneLib.dir/Vertex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sceneLib.dir/Vertex.cpp.i"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/Desktop/Project/MCPT/Scene/Vertex.cpp > CMakeFiles/sceneLib.dir/Vertex.cpp.i

Scene/CMakeFiles/sceneLib.dir/Vertex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sceneLib.dir/Vertex.cpp.s"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/Desktop/Project/MCPT/Scene/Vertex.cpp -o CMakeFiles/sceneLib.dir/Vertex.cpp.s

Scene/CMakeFiles/sceneLib.dir/Vertex.cpp.o.requires:

.PHONY : Scene/CMakeFiles/sceneLib.dir/Vertex.cpp.o.requires

Scene/CMakeFiles/sceneLib.dir/Vertex.cpp.o.provides: Scene/CMakeFiles/sceneLib.dir/Vertex.cpp.o.requires
	$(MAKE) -f Scene/CMakeFiles/sceneLib.dir/build.make Scene/CMakeFiles/sceneLib.dir/Vertex.cpp.o.provides.build
.PHONY : Scene/CMakeFiles/sceneLib.dir/Vertex.cpp.o.provides

Scene/CMakeFiles/sceneLib.dir/Vertex.cpp.o.provides.build: Scene/CMakeFiles/sceneLib.dir/Vertex.cpp.o


Scene/CMakeFiles/sceneLib.dir/Material.cpp.o: Scene/CMakeFiles/sceneLib.dir/flags.make
Scene/CMakeFiles/sceneLib.dir/Material.cpp.o: ../Scene/Material.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/Desktop/Project/MCPT/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Scene/CMakeFiles/sceneLib.dir/Material.cpp.o"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sceneLib.dir/Material.cpp.o -c /home/kevin/Desktop/Project/MCPT/Scene/Material.cpp

Scene/CMakeFiles/sceneLib.dir/Material.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sceneLib.dir/Material.cpp.i"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/Desktop/Project/MCPT/Scene/Material.cpp > CMakeFiles/sceneLib.dir/Material.cpp.i

Scene/CMakeFiles/sceneLib.dir/Material.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sceneLib.dir/Material.cpp.s"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/Desktop/Project/MCPT/Scene/Material.cpp -o CMakeFiles/sceneLib.dir/Material.cpp.s

Scene/CMakeFiles/sceneLib.dir/Material.cpp.o.requires:

.PHONY : Scene/CMakeFiles/sceneLib.dir/Material.cpp.o.requires

Scene/CMakeFiles/sceneLib.dir/Material.cpp.o.provides: Scene/CMakeFiles/sceneLib.dir/Material.cpp.o.requires
	$(MAKE) -f Scene/CMakeFiles/sceneLib.dir/build.make Scene/CMakeFiles/sceneLib.dir/Material.cpp.o.provides.build
.PHONY : Scene/CMakeFiles/sceneLib.dir/Material.cpp.o.provides

Scene/CMakeFiles/sceneLib.dir/Material.cpp.o.provides.build: Scene/CMakeFiles/sceneLib.dir/Material.cpp.o


Scene/CMakeFiles/sceneLib.dir/Loader.cpp.o: Scene/CMakeFiles/sceneLib.dir/flags.make
Scene/CMakeFiles/sceneLib.dir/Loader.cpp.o: ../Scene/Loader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/Desktop/Project/MCPT/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object Scene/CMakeFiles/sceneLib.dir/Loader.cpp.o"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sceneLib.dir/Loader.cpp.o -c /home/kevin/Desktop/Project/MCPT/Scene/Loader.cpp

Scene/CMakeFiles/sceneLib.dir/Loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sceneLib.dir/Loader.cpp.i"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/Desktop/Project/MCPT/Scene/Loader.cpp > CMakeFiles/sceneLib.dir/Loader.cpp.i

Scene/CMakeFiles/sceneLib.dir/Loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sceneLib.dir/Loader.cpp.s"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/Desktop/Project/MCPT/Scene/Loader.cpp -o CMakeFiles/sceneLib.dir/Loader.cpp.s

Scene/CMakeFiles/sceneLib.dir/Loader.cpp.o.requires:

.PHONY : Scene/CMakeFiles/sceneLib.dir/Loader.cpp.o.requires

Scene/CMakeFiles/sceneLib.dir/Loader.cpp.o.provides: Scene/CMakeFiles/sceneLib.dir/Loader.cpp.o.requires
	$(MAKE) -f Scene/CMakeFiles/sceneLib.dir/build.make Scene/CMakeFiles/sceneLib.dir/Loader.cpp.o.provides.build
.PHONY : Scene/CMakeFiles/sceneLib.dir/Loader.cpp.o.provides

Scene/CMakeFiles/sceneLib.dir/Loader.cpp.o.provides.build: Scene/CMakeFiles/sceneLib.dir/Loader.cpp.o


Scene/CMakeFiles/sceneLib.dir/Scene.cpp.o: Scene/CMakeFiles/sceneLib.dir/flags.make
Scene/CMakeFiles/sceneLib.dir/Scene.cpp.o: ../Scene/Scene.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/Desktop/Project/MCPT/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object Scene/CMakeFiles/sceneLib.dir/Scene.cpp.o"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sceneLib.dir/Scene.cpp.o -c /home/kevin/Desktop/Project/MCPT/Scene/Scene.cpp

Scene/CMakeFiles/sceneLib.dir/Scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sceneLib.dir/Scene.cpp.i"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/Desktop/Project/MCPT/Scene/Scene.cpp > CMakeFiles/sceneLib.dir/Scene.cpp.i

Scene/CMakeFiles/sceneLib.dir/Scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sceneLib.dir/Scene.cpp.s"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/Desktop/Project/MCPT/Scene/Scene.cpp -o CMakeFiles/sceneLib.dir/Scene.cpp.s

Scene/CMakeFiles/sceneLib.dir/Scene.cpp.o.requires:

.PHONY : Scene/CMakeFiles/sceneLib.dir/Scene.cpp.o.requires

Scene/CMakeFiles/sceneLib.dir/Scene.cpp.o.provides: Scene/CMakeFiles/sceneLib.dir/Scene.cpp.o.requires
	$(MAKE) -f Scene/CMakeFiles/sceneLib.dir/build.make Scene/CMakeFiles/sceneLib.dir/Scene.cpp.o.provides.build
.PHONY : Scene/CMakeFiles/sceneLib.dir/Scene.cpp.o.provides

Scene/CMakeFiles/sceneLib.dir/Scene.cpp.o.provides.build: Scene/CMakeFiles/sceneLib.dir/Scene.cpp.o


# Object files for target sceneLib
sceneLib_OBJECTS = \
"CMakeFiles/sceneLib.dir/Mesh.cpp.o" \
"CMakeFiles/sceneLib.dir/Vertex.cpp.o" \
"CMakeFiles/sceneLib.dir/Material.cpp.o" \
"CMakeFiles/sceneLib.dir/Loader.cpp.o" \
"CMakeFiles/sceneLib.dir/Scene.cpp.o"

# External object files for target sceneLib
sceneLib_EXTERNAL_OBJECTS =

Scene/libsceneLib.a: Scene/CMakeFiles/sceneLib.dir/Mesh.cpp.o
Scene/libsceneLib.a: Scene/CMakeFiles/sceneLib.dir/Vertex.cpp.o
Scene/libsceneLib.a: Scene/CMakeFiles/sceneLib.dir/Material.cpp.o
Scene/libsceneLib.a: Scene/CMakeFiles/sceneLib.dir/Loader.cpp.o
Scene/libsceneLib.a: Scene/CMakeFiles/sceneLib.dir/Scene.cpp.o
Scene/libsceneLib.a: Scene/CMakeFiles/sceneLib.dir/build.make
Scene/libsceneLib.a: Scene/CMakeFiles/sceneLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kevin/Desktop/Project/MCPT/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libsceneLib.a"
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && $(CMAKE_COMMAND) -P CMakeFiles/sceneLib.dir/cmake_clean_target.cmake
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sceneLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Scene/CMakeFiles/sceneLib.dir/build: Scene/libsceneLib.a

.PHONY : Scene/CMakeFiles/sceneLib.dir/build

Scene/CMakeFiles/sceneLib.dir/requires: Scene/CMakeFiles/sceneLib.dir/Mesh.cpp.o.requires
Scene/CMakeFiles/sceneLib.dir/requires: Scene/CMakeFiles/sceneLib.dir/Vertex.cpp.o.requires
Scene/CMakeFiles/sceneLib.dir/requires: Scene/CMakeFiles/sceneLib.dir/Material.cpp.o.requires
Scene/CMakeFiles/sceneLib.dir/requires: Scene/CMakeFiles/sceneLib.dir/Loader.cpp.o.requires
Scene/CMakeFiles/sceneLib.dir/requires: Scene/CMakeFiles/sceneLib.dir/Scene.cpp.o.requires

.PHONY : Scene/CMakeFiles/sceneLib.dir/requires

Scene/CMakeFiles/sceneLib.dir/clean:
	cd /home/kevin/Desktop/Project/MCPT/release/Scene && $(CMAKE_COMMAND) -P CMakeFiles/sceneLib.dir/cmake_clean.cmake
.PHONY : Scene/CMakeFiles/sceneLib.dir/clean

Scene/CMakeFiles/sceneLib.dir/depend:
	cd /home/kevin/Desktop/Project/MCPT/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kevin/Desktop/Project/MCPT /home/kevin/Desktop/Project/MCPT/Scene /home/kevin/Desktop/Project/MCPT/release /home/kevin/Desktop/Project/MCPT/release/Scene /home/kevin/Desktop/Project/MCPT/release/Scene/CMakeFiles/sceneLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Scene/CMakeFiles/sceneLib.dir/depend

