cmake_minimum_required(VERSION 3.9)
project(cmpe-126-lab)

if (WIN32)
    if (CYGWIN)
        add_definitions(-std=gnu++0x)
    elseif (MINGW)
        add_definitions(-std=c++11)
    endif (CYGWIN)
endif (WIN32)
if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)
if (UNIX)
    add_definitions(-std=gnu++0x)
endif (UNIX)

set(SOURCE_FILES main.cpp)

add_executable(labs_main ${SOURCE_FILES})

include_directories(
        lib/lab01/inc
)

add_subdirectory(lib/lab01 lab1_lib)

add_subdirectory(test)

target_link_libraries(
        labs_main
        lab1_lib
)