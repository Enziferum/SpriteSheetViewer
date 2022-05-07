cmake_minimum_required(VERSION 3.11)
project(robot2D_imgui)

option(BUILD_EXAMPLE "Build example application ?" ON)

if(MSVC)
    add_definitions(/MP)
endif()

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed.
    Please make a new directory (called a build directory)
	and run CMake from there. You may need to remove CMakeCache.txt.")
endif()

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 3.3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(robot2D REQUIRED)
find_package(robot2D_ext REQUIRED)

set (SRC
        include/imgui/imconfig.h
        include/imgui/imgui.h
        include/imgui/imgui_internal.h
        include/imgui/imstb_rectpack.h
        include/imgui/imstb_textedit.h
        include/imgui/imstb_truetype.h
        include/imgui/ImGui.hpp
        include/robot2D/Extra/Api.hpp
        include/robot2D/Extra/Gui.hpp
        include/robot2D/Extra/OrthoView.hpp
        include/robot2D/Extra/Util.hpp
        include/robot2D/Extra/Render.hpp
        include/robot2D/Extra/WindowOptions.hpp
        )

set(SRC ${SRC}
        src/imgui.cpp
        src/imgui_widgets.cpp
        src/imgui_tables.cpp
        src/imgui_draw.cpp
        src/imgui_demo.cpp
        src/robot2D/Api.cpp
        src/robot2D/Gui.cpp
        src/robot2D/OrthoView.cpp
        src/robot2D/Util.cpp
        src/robot2D/Render.cpp
        src/robot2D/WindowOptions.cpp
        )

add_library(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} robot2D spdlog::spdlog)
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()