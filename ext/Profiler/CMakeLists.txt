cmake_minimum_required(VERSION 3.11)
project(Profiler)

#TODO install options for example

option(BUILD_EXAMPLE "Build example of Profiler?" ON)
option(BUILD_TESTS "Build tests of Profiler?" ON)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/incl)

set(SRC
        src/ProfilerManager.cpp
        src/Timer.cpp
        src/ThreadConverter.cpp)

add_library(${PROJECT_NAME} STATIC ${SRC})
target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_SOURCE_DIR}/incl)

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

if(BUILD_TESTS)
    include(cmake/External_GTest.cmake)
    enable_testing()

    set(TESTS_NAME run_all_tests)

    include_directories(.)
    include_directories(${GTEST_INCLUDE_DIRS})
    set(SRC
            tests/runner.cpp
            tests/test_sample.cpp
            )

    add_executable(${TESTS_NAME} ${SRC})
    target_link_libraries(${TESTS_NAME}  gtest Profiler)

    add_dependencies(${TESTS_NAME} gtest_ext)
    #Todo Compile Options & Gcov
    #target_compile_options( PRIVATE -fprofile-arcs -ftest-coverage -O0 -pg -g)
    #target_compile_options(${TESTS_NAME} PRIVATE -fprofile-arcs -ftest-coverage -O0 -g -pg)
    #target_compile_options(gtest PRIVATE -fprofile-arcs -ftest-coverage -O0 -pg -g)
    add_test(NAME unit_tests COMMAND ${TESTS_NAME})
endif()
