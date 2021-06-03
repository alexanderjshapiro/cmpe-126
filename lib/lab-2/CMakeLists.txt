set(HEADER_FILES
        inc/StringVector.h)

set(SOURCE_FILES
        src/StringVector.cpp)
include_directories(inc)
add_library(lab2_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})