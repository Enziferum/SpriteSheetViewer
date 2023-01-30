cmake_minimum_required(VERSION 3.16)
project(SpriteSheetViewer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")

find_package(glfw3 3.3 REQUIRED)
find_package(robot2D REQUIRED)
find_package(robot2D_ext REQUIRED)
find_package(spdlog REQUIRED)

file(GLOB_RECURSE SRC src/*.cpp)

add_subdirectory(ext/TinyXML)
add_subdirectory(ext/robot2D-imgui)
add_subdirectory(ext/Profiler)

set(LIBS robot2D robot2D_imgui Profiler tinyxml )

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIBS})

target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>")

#add_custom_command(
#        TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_CURRENT_SOURCE_DIR}/res/
#        ${CMAKE_CURRENT_BINARY_DIR}/res/)