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
include ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/compiler_depend.make

# Include the progress variables for this target.
include ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/progress.make

# Include the compile flags for this target's objects.
include ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/flags.make

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/flags.make
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/includes_CXX.rsp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui.cpp.obj: ../ext/robot2D-imgui/src/imgui.cpp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui.cpp.obj"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui.cpp.obj -MF CMakeFiles\robot2D_imgui.dir\src\imgui.cpp.obj.d -o CMakeFiles\robot2D_imgui.dir\src\imgui.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\imgui.cpp

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robot2D_imgui.dir/src/imgui.cpp.i"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\imgui.cpp > CMakeFiles\robot2D_imgui.dir\src\imgui.cpp.i

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robot2D_imgui.dir/src/imgui.cpp.s"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\imgui.cpp -o CMakeFiles\robot2D_imgui.dir\src\imgui.cpp.s

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_widgets.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/flags.make
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_widgets.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/includes_CXX.rsp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_widgets.cpp.obj: ../ext/robot2D-imgui/src/imgui_widgets.cpp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_widgets.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_widgets.cpp.obj"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_widgets.cpp.obj -MF CMakeFiles\robot2D_imgui.dir\src\imgui_widgets.cpp.obj.d -o CMakeFiles\robot2D_imgui.dir\src\imgui_widgets.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\imgui_widgets.cpp

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robot2D_imgui.dir/src/imgui_widgets.cpp.i"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\imgui_widgets.cpp > CMakeFiles\robot2D_imgui.dir\src\imgui_widgets.cpp.i

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robot2D_imgui.dir/src/imgui_widgets.cpp.s"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\imgui_widgets.cpp -o CMakeFiles\robot2D_imgui.dir\src\imgui_widgets.cpp.s

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_tables.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/flags.make
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_tables.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/includes_CXX.rsp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_tables.cpp.obj: ../ext/robot2D-imgui/src/imgui_tables.cpp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_tables.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_tables.cpp.obj"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_tables.cpp.obj -MF CMakeFiles\robot2D_imgui.dir\src\imgui_tables.cpp.obj.d -o CMakeFiles\robot2D_imgui.dir\src\imgui_tables.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\imgui_tables.cpp

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robot2D_imgui.dir/src/imgui_tables.cpp.i"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\imgui_tables.cpp > CMakeFiles\robot2D_imgui.dir\src\imgui_tables.cpp.i

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robot2D_imgui.dir/src/imgui_tables.cpp.s"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\imgui_tables.cpp -o CMakeFiles\robot2D_imgui.dir\src\imgui_tables.cpp.s

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_draw.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/flags.make
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_draw.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/includes_CXX.rsp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_draw.cpp.obj: ../ext/robot2D-imgui/src/imgui_draw.cpp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_draw.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_draw.cpp.obj"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_draw.cpp.obj -MF CMakeFiles\robot2D_imgui.dir\src\imgui_draw.cpp.obj.d -o CMakeFiles\robot2D_imgui.dir\src\imgui_draw.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\imgui_draw.cpp

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robot2D_imgui.dir/src/imgui_draw.cpp.i"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\imgui_draw.cpp > CMakeFiles\robot2D_imgui.dir\src\imgui_draw.cpp.i

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robot2D_imgui.dir/src/imgui_draw.cpp.s"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\imgui_draw.cpp -o CMakeFiles\robot2D_imgui.dir\src\imgui_draw.cpp.s

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_demo.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/flags.make
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_demo.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/includes_CXX.rsp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_demo.cpp.obj: ../ext/robot2D-imgui/src/imgui_demo.cpp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_demo.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_demo.cpp.obj"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_demo.cpp.obj -MF CMakeFiles\robot2D_imgui.dir\src\imgui_demo.cpp.obj.d -o CMakeFiles\robot2D_imgui.dir\src\imgui_demo.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\imgui_demo.cpp

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robot2D_imgui.dir/src/imgui_demo.cpp.i"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\imgui_demo.cpp > CMakeFiles\robot2D_imgui.dir\src\imgui_demo.cpp.i

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robot2D_imgui.dir/src/imgui_demo.cpp.s"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\imgui_demo.cpp -o CMakeFiles\robot2D_imgui.dir\src\imgui_demo.cpp.s

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Api.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/flags.make
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Api.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/includes_CXX.rsp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Api.cpp.obj: ../ext/robot2D-imgui/src/robot2D/Api.cpp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Api.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Api.cpp.obj"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Api.cpp.obj -MF CMakeFiles\robot2D_imgui.dir\src\robot2D\Api.cpp.obj.d -o CMakeFiles\robot2D_imgui.dir\src\robot2D\Api.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\Api.cpp

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Api.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robot2D_imgui.dir/src/robot2D/Api.cpp.i"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\Api.cpp > CMakeFiles\robot2D_imgui.dir\src\robot2D\Api.cpp.i

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Api.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robot2D_imgui.dir/src/robot2D/Api.cpp.s"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\Api.cpp -o CMakeFiles\robot2D_imgui.dir\src\robot2D\Api.cpp.s

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Gui.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/flags.make
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Gui.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/includes_CXX.rsp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Gui.cpp.obj: ../ext/robot2D-imgui/src/robot2D/Gui.cpp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Gui.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Gui.cpp.obj"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Gui.cpp.obj -MF CMakeFiles\robot2D_imgui.dir\src\robot2D\Gui.cpp.obj.d -o CMakeFiles\robot2D_imgui.dir\src\robot2D\Gui.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\Gui.cpp

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Gui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robot2D_imgui.dir/src/robot2D/Gui.cpp.i"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\Gui.cpp > CMakeFiles\robot2D_imgui.dir\src\robot2D\Gui.cpp.i

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Gui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robot2D_imgui.dir/src/robot2D/Gui.cpp.s"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\Gui.cpp -o CMakeFiles\robot2D_imgui.dir\src\robot2D\Gui.cpp.s

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/OrthoView.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/flags.make
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/OrthoView.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/includes_CXX.rsp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/OrthoView.cpp.obj: ../ext/robot2D-imgui/src/robot2D/OrthoView.cpp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/OrthoView.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/OrthoView.cpp.obj"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/OrthoView.cpp.obj -MF CMakeFiles\robot2D_imgui.dir\src\robot2D\OrthoView.cpp.obj.d -o CMakeFiles\robot2D_imgui.dir\src\robot2D\OrthoView.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\OrthoView.cpp

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/OrthoView.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robot2D_imgui.dir/src/robot2D/OrthoView.cpp.i"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\OrthoView.cpp > CMakeFiles\robot2D_imgui.dir\src\robot2D\OrthoView.cpp.i

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/OrthoView.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robot2D_imgui.dir/src/robot2D/OrthoView.cpp.s"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\OrthoView.cpp -o CMakeFiles\robot2D_imgui.dir\src\robot2D\OrthoView.cpp.s

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Util.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/flags.make
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Util.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/includes_CXX.rsp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Util.cpp.obj: ../ext/robot2D-imgui/src/robot2D/Util.cpp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Util.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Util.cpp.obj"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Util.cpp.obj -MF CMakeFiles\robot2D_imgui.dir\src\robot2D\Util.cpp.obj.d -o CMakeFiles\robot2D_imgui.dir\src\robot2D\Util.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\Util.cpp

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robot2D_imgui.dir/src/robot2D/Util.cpp.i"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\Util.cpp > CMakeFiles\robot2D_imgui.dir\src\robot2D\Util.cpp.i

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robot2D_imgui.dir/src/robot2D/Util.cpp.s"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\Util.cpp -o CMakeFiles\robot2D_imgui.dir\src\robot2D\Util.cpp.s

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Render.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/flags.make
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Render.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/includes_CXX.rsp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Render.cpp.obj: ../ext/robot2D-imgui/src/robot2D/Render.cpp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Render.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Render.cpp.obj"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Render.cpp.obj -MF CMakeFiles\robot2D_imgui.dir\src\robot2D\Render.cpp.obj.d -o CMakeFiles\robot2D_imgui.dir\src\robot2D\Render.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\Render.cpp

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Render.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robot2D_imgui.dir/src/robot2D/Render.cpp.i"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\Render.cpp > CMakeFiles\robot2D_imgui.dir\src\robot2D\Render.cpp.i

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Render.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robot2D_imgui.dir/src/robot2D/Render.cpp.s"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\Render.cpp -o CMakeFiles\robot2D_imgui.dir\src\robot2D\Render.cpp.s

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/WindowOptions.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/flags.make
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/WindowOptions.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/includes_CXX.rsp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/WindowOptions.cpp.obj: ../ext/robot2D-imgui/src/robot2D/WindowOptions.cpp
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/WindowOptions.cpp.obj: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/WindowOptions.cpp.obj"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/WindowOptions.cpp.obj -MF CMakeFiles\robot2D_imgui.dir\src\robot2D\WindowOptions.cpp.obj.d -o CMakeFiles\robot2D_imgui.dir\src\robot2D\WindowOptions.cpp.obj -c C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\WindowOptions.cpp

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/WindowOptions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robot2D_imgui.dir/src/robot2D/WindowOptions.cpp.i"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\WindowOptions.cpp > CMakeFiles\robot2D_imgui.dir\src\robot2D\WindowOptions.cpp.i

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/WindowOptions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robot2D_imgui.dir/src/robot2D/WindowOptions.cpp.s"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui\src\robot2D\WindowOptions.cpp -o CMakeFiles\robot2D_imgui.dir\src\robot2D\WindowOptions.cpp.s

# Object files for target robot2D_imgui
robot2D_imgui_OBJECTS = \
"CMakeFiles/robot2D_imgui.dir/src/imgui.cpp.obj" \
"CMakeFiles/robot2D_imgui.dir/src/imgui_widgets.cpp.obj" \
"CMakeFiles/robot2D_imgui.dir/src/imgui_tables.cpp.obj" \
"CMakeFiles/robot2D_imgui.dir/src/imgui_draw.cpp.obj" \
"CMakeFiles/robot2D_imgui.dir/src/imgui_demo.cpp.obj" \
"CMakeFiles/robot2D_imgui.dir/src/robot2D/Api.cpp.obj" \
"CMakeFiles/robot2D_imgui.dir/src/robot2D/Gui.cpp.obj" \
"CMakeFiles/robot2D_imgui.dir/src/robot2D/OrthoView.cpp.obj" \
"CMakeFiles/robot2D_imgui.dir/src/robot2D/Util.cpp.obj" \
"CMakeFiles/robot2D_imgui.dir/src/robot2D/Render.cpp.obj" \
"CMakeFiles/robot2D_imgui.dir/src/robot2D/WindowOptions.cpp.obj"

# External object files for target robot2D_imgui
robot2D_imgui_EXTERNAL_OBJECTS =

ext/robot2D-imgui/librobot2D_imgui.a: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui.cpp.obj
ext/robot2D-imgui/librobot2D_imgui.a: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_widgets.cpp.obj
ext/robot2D-imgui/librobot2D_imgui.a: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_tables.cpp.obj
ext/robot2D-imgui/librobot2D_imgui.a: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_draw.cpp.obj
ext/robot2D-imgui/librobot2D_imgui.a: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/imgui_demo.cpp.obj
ext/robot2D-imgui/librobot2D_imgui.a: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Api.cpp.obj
ext/robot2D-imgui/librobot2D_imgui.a: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Gui.cpp.obj
ext/robot2D-imgui/librobot2D_imgui.a: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/OrthoView.cpp.obj
ext/robot2D-imgui/librobot2D_imgui.a: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Util.cpp.obj
ext/robot2D-imgui/librobot2D_imgui.a: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/Render.cpp.obj
ext/robot2D-imgui/librobot2D_imgui.a: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/src/robot2D/WindowOptions.cpp.obj
ext/robot2D-imgui/librobot2D_imgui.a: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/build.make
ext/robot2D-imgui/librobot2D_imgui.a: ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX static library librobot2D_imgui.a"
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && $(CMAKE_COMMAND) -P CMakeFiles\robot2D_imgui.dir\cmake_clean_target.cmake
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\robot2D_imgui.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/build: ext/robot2D-imgui/librobot2D_imgui.a
.PHONY : ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/build

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/clean:
	cd /d C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui && $(CMAKE_COMMAND) -P CMakeFiles\robot2D_imgui.dir\cmake_clean.cmake
.PHONY : ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/clean

ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\ext\robot2D-imgui C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui C:\Users\ElNecromant\Documents\dev\cpp\SpriteSheetViewer\cmake-build-debug\ext\robot2D-imgui\CMakeFiles\robot2D_imgui.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : ext/robot2D-imgui/CMakeFiles/robot2D_imgui.dir/depend

