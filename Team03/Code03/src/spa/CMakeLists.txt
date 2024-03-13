file(GLOB srcs
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*/*.cpp"
)


file(GLOB headers
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*/*.h"
)
add_library(spa ${srcs} ${headers}
		src/qps/entity/clause/IfPatternPredicate.cpp
		src/qps/entity/clause/IfPatternPredicate.h
		src/qps/entity/clause/WhilePatternPredicate.cpp
		src/qps/entity/clause/WhilePatternPredicate.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


