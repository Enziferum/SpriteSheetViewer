# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.3.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SpriteSheetViewer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SpriteSheetViewer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SpriteSheetViewer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SpriteSheetViewer.dir/flags.make

CMakeFiles/SpriteSheetViewer.dir/src/PanelManager.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/flags.make
CMakeFiles/SpriteSheetViewer.dir/src/PanelManager.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/includes_CXX.rsp
CMakeFiles/SpriteSheetViewer.dir/src/PanelManager.cpp.obj: ../src/PanelManager.cpp
CMakeFiles/SpriteSheetViewer.dir/src/PanelManager.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SpriteSheetViewer.dir/src/PanelManager.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SpriteSheetViewer.dir/src/PanelManager.cpp.obj -MF CMakeFiles\SpriteSheetViewer.dir\src\PanelManager.cpp.obj.d -o CMakeFiles\SpriteSheetViewer.dir\src\PanelManager.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\PanelManager.cpp

CMakeFiles/SpriteSheetViewer.dir/src/PanelManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpriteSheetViewer.dir/src/PanelManager.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\PanelManager.cpp > CMakeFiles\SpriteSheetViewer.dir\src\PanelManager.cpp.i

CMakeFiles/SpriteSheetViewer.dir/src/PanelManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpriteSheetViewer.dir/src/PanelManager.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\PanelManager.cpp -o CMakeFiles\SpriteSheetViewer.dir\src\PanelManager.cpp.s

CMakeFiles/SpriteSheetViewer.dir/src/Panels.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/flags.make
CMakeFiles/SpriteSheetViewer.dir/src/Panels.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/includes_CXX.rsp
CMakeFiles/SpriteSheetViewer.dir/src/Panels.cpp.obj: ../src/Panels.cpp
CMakeFiles/SpriteSheetViewer.dir/src/Panels.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SpriteSheetViewer.dir/src/Panels.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SpriteSheetViewer.dir/src/Panels.cpp.obj -MF CMakeFiles\SpriteSheetViewer.dir\src\Panels.cpp.obj.d -o CMakeFiles\SpriteSheetViewer.dir\src\Panels.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\Panels.cpp

CMakeFiles/SpriteSheetViewer.dir/src/Panels.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpriteSheetViewer.dir/src/Panels.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\Panels.cpp > CMakeFiles\SpriteSheetViewer.dir\src\Panels.cpp.i

CMakeFiles/SpriteSheetViewer.dir/src/Panels.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpriteSheetViewer.dir/src/Panels.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\Panels.cpp -o CMakeFiles\SpriteSheetViewer.dir\src\Panels.cpp.s

CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheet.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/flags.make
CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheet.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/includes_CXX.rsp
CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheet.cpp.obj: ../src/SpriteSheet.cpp
CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheet.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheet.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheet.cpp.obj -MF CMakeFiles\SpriteSheetViewer.dir\src\SpriteSheet.cpp.obj.d -o CMakeFiles\SpriteSheetViewer.dir\src\SpriteSheet.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\SpriteSheet.cpp

CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheet.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\SpriteSheet.cpp > CMakeFiles\SpriteSheetViewer.dir\src\SpriteSheet.cpp.i

CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheet.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\SpriteSheet.cpp -o CMakeFiles\SpriteSheetViewer.dir\src\SpriteSheet.cpp.s

CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheetAnimation.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/flags.make
CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheetAnimation.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/includes_CXX.rsp
CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheetAnimation.cpp.obj: ../src/SpriteSheetAnimation.cpp
CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheetAnimation.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheetAnimation.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheetAnimation.cpp.obj -MF CMakeFiles\SpriteSheetViewer.dir\src\SpriteSheetAnimation.cpp.obj.d -o CMakeFiles\SpriteSheetViewer.dir\src\SpriteSheetAnimation.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\SpriteSheetAnimation.cpp

CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheetAnimation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheetAnimation.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\SpriteSheetAnimation.cpp > CMakeFiles\SpriteSheetViewer.dir\src\SpriteSheetAnimation.cpp.i

CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheetAnimation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheetAnimation.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\SpriteSheetAnimation.cpp -o CMakeFiles\SpriteSheetViewer.dir\src\SpriteSheetAnimation.cpp.s

CMakeFiles/SpriteSheetViewer.dir/src/Viewer.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/flags.make
CMakeFiles/SpriteSheetViewer.dir/src/Viewer.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/includes_CXX.rsp
CMakeFiles/SpriteSheetViewer.dir/src/Viewer.cpp.obj: ../src/Viewer.cpp
CMakeFiles/SpriteSheetViewer.dir/src/Viewer.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/SpriteSheetViewer.dir/src/Viewer.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SpriteSheetViewer.dir/src/Viewer.cpp.obj -MF CMakeFiles\SpriteSheetViewer.dir\src\Viewer.cpp.obj.d -o CMakeFiles\SpriteSheetViewer.dir\src\Viewer.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\Viewer.cpp

CMakeFiles/SpriteSheetViewer.dir/src/Viewer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpriteSheetViewer.dir/src/Viewer.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\Viewer.cpp > CMakeFiles\SpriteSheetViewer.dir\src\Viewer.cpp.i

CMakeFiles/SpriteSheetViewer.dir/src/Viewer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpriteSheetViewer.dir/src/Viewer.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\Viewer.cpp -o CMakeFiles\SpriteSheetViewer.dir\src\Viewer.cpp.s

CMakeFiles/SpriteSheetViewer.dir/src/ViewerScene.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/flags.make
CMakeFiles/SpriteSheetViewer.dir/src/ViewerScene.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/includes_CXX.rsp
CMakeFiles/SpriteSheetViewer.dir/src/ViewerScene.cpp.obj: ../src/ViewerScene.cpp
CMakeFiles/SpriteSheetViewer.dir/src/ViewerScene.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/SpriteSheetViewer.dir/src/ViewerScene.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SpriteSheetViewer.dir/src/ViewerScene.cpp.obj -MF CMakeFiles\SpriteSheetViewer.dir\src\ViewerScene.cpp.obj.d -o CMakeFiles\SpriteSheetViewer.dir\src\ViewerScene.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\ViewerScene.cpp

CMakeFiles/SpriteSheetViewer.dir/src/ViewerScene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpriteSheetViewer.dir/src/ViewerScene.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\ViewerScene.cpp > CMakeFiles\SpriteSheetViewer.dir\src\ViewerScene.cpp.i

CMakeFiles/SpriteSheetViewer.dir/src/ViewerScene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpriteSheetViewer.dir/src/ViewerScene.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\ViewerScene.cpp -o CMakeFiles\SpriteSheetViewer.dir\src\ViewerScene.cpp.s

CMakeFiles/SpriteSheetViewer.dir/src/main.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/flags.make
CMakeFiles/SpriteSheetViewer.dir/src/main.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/includes_CXX.rsp
CMakeFiles/SpriteSheetViewer.dir/src/main.cpp.obj: ../src/main.cpp
CMakeFiles/SpriteSheetViewer.dir/src/main.cpp.obj: CMakeFiles/SpriteSheetViewer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/SpriteSheetViewer.dir/src/main.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SpriteSheetViewer.dir/src/main.cpp.obj -MF CMakeFiles\SpriteSheetViewer.dir\src\main.cpp.obj.d -o CMakeFiles\SpriteSheetViewer.dir\src\main.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\main.cpp

CMakeFiles/SpriteSheetViewer.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpriteSheetViewer.dir/src/main.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\main.cpp > CMakeFiles\SpriteSheetViewer.dir\src\main.cpp.i

CMakeFiles/SpriteSheetViewer.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpriteSheetViewer.dir/src/main.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\src\main.cpp -o CMakeFiles\SpriteSheetViewer.dir\src\main.cpp.s

# Object files for target SpriteSheetViewer
SpriteSheetViewer_OBJECTS = \
"CMakeFiles/SpriteSheetViewer.dir/src/PanelManager.cpp.obj" \
"CMakeFiles/SpriteSheetViewer.dir/src/Panels.cpp.obj" \
"CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheet.cpp.obj" \
"CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheetAnimation.cpp.obj" \
"CMakeFiles/SpriteSheetViewer.dir/src/Viewer.cpp.obj" \
"CMakeFiles/SpriteSheetViewer.dir/src/ViewerScene.cpp.obj" \
"CMakeFiles/SpriteSheetViewer.dir/src/main.cpp.obj"

# External object files for target SpriteSheetViewer
SpriteSheetViewer_EXTERNAL_OBJECTS =

SpriteSheetViewer.exe: CMakeFiles/SpriteSheetViewer.dir/src/PanelManager.cpp.obj
SpriteSheetViewer.exe: CMakeFiles/SpriteSheetViewer.dir/src/Panels.cpp.obj
SpriteSheetViewer.exe: CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheet.cpp.obj
SpriteSheetViewer.exe: CMakeFiles/SpriteSheetViewer.dir/src/SpriteSheetAnimation.cpp.obj
SpriteSheetViewer.exe: CMakeFiles/SpriteSheetViewer.dir/src/Viewer.cpp.obj
SpriteSheetViewer.exe: CMakeFiles/SpriteSheetViewer.dir/src/ViewerScene.cpp.obj
SpriteSheetViewer.exe: CMakeFiles/SpriteSheetViewer.dir/src/main.cpp.obj
SpriteSheetViewer.exe: CMakeFiles/SpriteSheetViewer.dir/build.make
SpriteSheetViewer.exe: C:/Program\ Files\ (x86)/robot2D/lib/librobot2D.a
SpriteSheetViewer.exe: ext/robot2D-imgui/librobot2D_imgui.a
SpriteSheetViewer.exe: ext/TinyXML/libtinyxml.a
SpriteSheetViewer.exe: ext/tinyfiledialog/libtinyfiledialogs.a
SpriteSheetViewer.exe: C:/Program\ Files\ (x86)/robot2D/lib/librobot2D.a
SpriteSheetViewer.exe: C:/msys64/mingw64/lib/libglfw3.dll.a
SpriteSheetViewer.exe: C:/Program\ Files\ (x86)/robot2D_ext/lib/librobot2D_ext.a
SpriteSheetViewer.exe: C:/Program\ Files\ (x86)/spdlog/lib/libspdlog.a
SpriteSheetViewer.exe: CMakeFiles/SpriteSheetViewer.dir/linklibs.rsp
SpriteSheetViewer.exe: CMakeFiles/SpriteSheetViewer.dir/objects1.rsp
SpriteSheetViewer.exe: CMakeFiles/SpriteSheetViewer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable SpriteSheetViewer.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\SpriteSheetViewer.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SpriteSheetViewer.dir/build: SpriteSheetViewer.exe
.PHONY : CMakeFiles/SpriteSheetViewer.dir/build

CMakeFiles/SpriteSheetViewer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\SpriteSheetViewer.dir\cmake_clean.cmake
.PHONY : CMakeFiles/SpriteSheetViewer.dir/clean

CMakeFiles/SpriteSheetViewer.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles\SpriteSheetViewer.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SpriteSheetViewer.dir/depend

