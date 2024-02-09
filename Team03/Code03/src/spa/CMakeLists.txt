file(GLOB srcs
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*.cpp")

file(GLOB headers 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" 
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/common/SpaException*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/SP/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Tokenizer*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/SP/Parser/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/SP/DesignExtractor/*.h")

add_library(spa ${srcs} ${headers} "src/SP/Parser/ProcedureParser.h" "src/SP/Parser/ProcedureParser.cpp" "src/SP/Parser/PrintStatementParser.cpp" "src/SP/Parser/PrintStatementParser.h" "src/SP/Parser/ReadStatementParser.cpp" "src/SP/Parser/ReadStatementParser.h" "src/SP/Parser/StatementParser.cpp" "src/SP/Parser/StatementParser.h" "src/SP/Parser/EntityParser.h" "src/SP/Parser/OperationParser.cpp" "src/SP/Parser/OperationParser.h" "src/SP/Parser/ExpressionParser.h" "src/SP/Parser/ExpressionParser.cpp" "src/SP/DesignExtractor/DesignExtractor.cpp" "src/SP/DesignExtractor/DesignExtractor.h" "src/SP/DesignExtractor/Visitor.h" "src/SP/DesignExtractor/EntityExtractor.cpp" "src/SP/DesignExtractor/EntityExtractor.h" "src/SP/Parser/VariableParser.cpp" "src/SP/Parser/VariableParser.h"   "src/SP/Sp.cpp" "src/SP/Sp.h" "src/common/Statement.h" "src/common/Statement.cpp" "src/common/Variable.cpp" "src/common/Variable.h" "src/common/ReadStatement.h" "src/common/ReadStatement.cpp" "src/common/PrintStatement.h" "src/common/PrintStatement.cpp" "src/common/Expression.cpp" "src/common/Expression.h" "src/common/Operation.cpp" "src/common/Operation.h" "src/qps/QueryParser.cpp" "src/qps/QueryFacade.cpp" "src/qps/QueryEvaluator.cpp" "src/qps/QueryValidator.cpp")

# this makes the headers accessible for other projects which uses spa lib
target_include_directories(spa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


