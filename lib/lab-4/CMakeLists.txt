set(HEADER_FILES
        inc/StringVectorCalculator.h)

set(SOURCE_FILES
        src/StringVectorCalculator.cpp)
include_directories(inc)
add_library(lab4_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(lab4_lib lab1_lib)
target_link_libraries(lab4_lib lab3_lib)
