set(HEADER_FILES
        inc/TreeNode.h
		inc/Tree.h
	)

set(SOURCE_FILES
		src/Tree.cpp
        )
include_directories(inc)
add_library(lab7_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
