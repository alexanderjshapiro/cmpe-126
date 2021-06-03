set(HEADER_FILES
        inc/ExpressionStream.h)

set(SOURCE_FILES
        src/ExpressionStream.cpp)
include_directories(inc)
add_library(lab1_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})