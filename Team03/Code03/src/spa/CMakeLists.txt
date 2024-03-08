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
		src/qps/entity/clause/validator/ColumnValidator.cpp
		src/qps/entity/clause/validator/ColumnValidator.h
		src/qps/entity/clause/validator/StatementNumberValidator.cpp
		src/qps/entity/clause/validator/StatementNumberValidator.h
		src/qps/entity/clause/validator/SynonymValidator.cpp
		src/qps/entity/clause/validator/SynonymValidator.h
		src/qps/entity/clause/validator/WildcardValidator.cpp
		src/qps/entity/clause/validator/WildcardValidator.h
		src/qps/entity/clause/validator/IdentifierValidator.cpp
		src/qps/entity/clause/validator/IdentifierValidator.h
		src/qps/entity/clause/Predicate.cpp
		src/qps/entity/evaluation/TableFactory.cpp
		src/qps/entity/evaluation/TableFactory.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


