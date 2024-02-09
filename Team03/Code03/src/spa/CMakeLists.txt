file(GLOB srcs 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/common/SpaException*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Tokenizer*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/SP/DesignExtractor/*.cpp")

file(GLOB headers 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/common/SpaException*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Tokenizer*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/SP/DesignExtractor/*.h")
add_library(spa ${srcs} ${headers})
# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


