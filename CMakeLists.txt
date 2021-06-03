cmake_minimum_required(VERSION 3.1)
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
        lib/lab-1/inc
        lib/lab-2/inc
        lib/lab-3/inc
        lib/lab-4/inc
        lib/lab-5/inc
        lib/lab-6/inc
        lib/lab-7/inc
        lib/lab-8/inc
)

add_subdirectory(lib/lab-1 lab1_lib)
add_subdirectory(lib/lab-2 lab2_lib)
add_subdirectory(lib/lab-3 lab3_lib)
add_subdirectory(lib/lab-4 lab4_lib)
add_subdirectory(lib/lab-5 lab5_lib)
add_subdirectory(lib/lab-6 lab6_lib)
add_subdirectory(lib/lab-7 lab7_lib)
add_subdirectory(lib/lab-8 lab8_lib)

add_subdirectory(test)

target_link_libraries(
        labs_main
        lab1_lib
        lab2_lib
        lab3_lib
        lab4_lib
        lab5_lib
        lab6_lib
        lab7_lib
        lab8_lib
)