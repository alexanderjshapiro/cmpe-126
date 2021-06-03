set(HEADER_FILES
		inc/LinkedListNode.h
        inc/LinkedList.h
		inc/LinkedListStack.h
		inc/LinkedListQueue.h
		inc/LinkedListCalculator.h
        )

set(SOURCE_FILES
        src/LinkedList.cpp
		src/LinkedListStack.cpp
		src/LinkedListQueue.cpp
		src/LinkedListCalculator.cpp
		)
include_directories(inc)
add_library(lab5_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(lab5_lib lab1_lib)