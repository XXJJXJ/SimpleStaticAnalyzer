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
		src/qps/entity/clause/attribute/AttributeExtractor.h
		src/qps/entity/clause/attribute/AttrRef.cpp
		src/qps/entity/clause/attribute/AttrRef.h
		src/qps/entity/clause/attribute/AttributeValue.cpp
		src/qps/entity/clause/attribute/AttributeValue.h
		src/qps/entity/clause/attribute/StmtNumberExtractor.cpp
		src/qps/entity/clause/attribute/StmtNumberExtractor.h
		src/qps/entity/clause/attribute/ValueExtractor.cpp
		src/qps/entity/clause/attribute/ValueExtractor.h
		src/qps/entity/clause/attribute/ProcNameExtractor.cpp
		src/qps/entity/clause/attribute/ProcNameExtractor.h
		src/qps/entity/clause/attribute/VarNameExtractor.cpp
		src/qps/entity/clause/attribute/VarNameExtractor.h)
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


