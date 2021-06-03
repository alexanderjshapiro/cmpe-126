set(HEADER_FILES
        inc/HashTable.h)

set(SOURCE_FILES
        src/HashTable.cpp
        src/sorts.cpp)
include_directories(inc)
add_library(lab8_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(lab8_lib lab6_lib)