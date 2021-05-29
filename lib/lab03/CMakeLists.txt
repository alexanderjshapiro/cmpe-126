set(HEADER_FILES
        inc/StringVectorStack.h
        inc/StringVectorQueue.h)

set(SOURCE_FILES
        src/StringVectorStack.cpp
        src/StringVectorQueue.cpp)

include_directories(inc)
add_library(lab3_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(lab3_lib lab2_lib)