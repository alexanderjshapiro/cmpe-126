set(HEADER_FILES
        inc/DoublyLinkedListNode.h
        inc/DoublyLinkedList.h)

set(SOURCE_FILES
        src/DoublyLinkedList.cpp)
include_directories(inc)
add_library(lab6_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
#target_link_libraries(lab6_lib labXX_lib)