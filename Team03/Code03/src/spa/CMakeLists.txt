file(GLOB srcs 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/common/spa_exception*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/sp/tokenizer*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/sp/parser/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/sp/design_extractor/*.cpp")

file(GLOB headers 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/common/spa_exception*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/sp/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/sp/tokenizer*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/sp/parser/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/sp/design_extractor/*.h")
add_library(spa ${srcs} ${headers})
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


