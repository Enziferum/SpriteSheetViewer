cmake_minimum_required(VERSION 3.11)
project(SpriteSheetViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")

find_package(glfw3 3.3 REQUIRED)
find_package(robot2D REQUIRED)
find_package(robot2D_ext REQUIRED)
find_package(spdlog REQUIRED)


include_directories(${CMAKE_SOURCE_DIR}/incl)

file(GLOB_RECURSE SRC src/*.cpp)

add_subdirectory(ext/tinyfiledialog)
add_subdirectory(ext/TinyXML)
add_subdirectory(ext/robot2D-imgui)

set(LIBS robot2D robot2D_imgui tinyxml tinyfiledialogs)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIBS})
