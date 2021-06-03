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
        lab-1-tests.cpp
        lab-2-tests.cpp
        lab-3-tests.cpp
        lab-4-tests.cpp
        lab-5-tests.cpp
        lab-6-tests.cpp
        lab-7-tests.cpp
        lab-8-tests.cpp
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