file(GLOB srcs
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*.cpp"
)


file(GLOB headers
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*.h"
)
add_library(spa ${srcs} ${headers}
		src/qps/entity/clause/Predicate.h
        src/qps/entity/clause/FollowsPredicate.cpp
        src/qps/entity/clause/FollowsPredicate.h
		src/qps/entity/clause/ModifiesPredicate.cpp
		src/qps/entity/clause/ModifiesPredicate.h
		src/qps/entity/clause/UsesPredicate.cpp
		src/qps/entity/clause/UsesPredicate.h
		src/qps/entity/clause/FollowsTPredicate.cpp
		src/qps/entity/clause/FollowsTPredicate.h
		src/qps/entity/clause/ParentPredicate.cpp
		src/qps/entity/clause/ParentPredicate.h
		src/qps/entity/clause/ParentTPredicate.cpp
		src/qps/entity/clause/ParentTPredicate.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


