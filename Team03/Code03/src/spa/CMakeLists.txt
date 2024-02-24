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
		src/qps/entity/evaluation/SynonymGraph.cpp
		src/qps/entity/evaluation/SynonymGraph.h
		src/qps/entity/evaluation/EvaluationPlanner.cpp
		src/qps/entity/evaluation/EvaluationPlanner.h
		src/qps/entity/strategy/JoinWithPredicateStrategy.cpp
		src/qps/entity/strategy/JoinWithPredicateStrategy.h
		src/common/spa_exception/QPSEvaluationException.cpp
		src/common/spa_exception/QPSEvaluationException.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


