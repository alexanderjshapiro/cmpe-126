cmake_minimum_required(VERSION 3.1)

if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(googletest-distribution)
set(GOOGLETEST_VERSION 1.10.0)

enable_testing()

include(CMakeDependentOption)
include(GNUInstallDirs)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(
        runBasicTests
        lab01_tests.cpp
        lab02_tests.cpp
        lab03_tests.cpp
        lab04_tests.cpp
        lab05_tests.cpp
        lab06_tests.cpp
        lab07_tests.cpp
        lab08_tests.cpp
)

add_subdirectory(gtest)

target_link_libraries(runBasicTests gtest gtest_main)

target_link_libraries(
        runBasicTests
        lab1_lib
        lab2_lib
        lab3_lib
        lab4_lib
        lab5_lib
        lab6_lib
        lab7_lib
        lab8_lib
)