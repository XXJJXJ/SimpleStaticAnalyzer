#include "catch.hpp"
#include "sp/sp.h"
#include "qps/QueryParser.h"
#include "qps/QueryEvaluator.h"
#include "pkb/EntityManager.h"
#include "qps/QueryFacade.h"

TEST_CASE("queryTokenizer should return valid tokens") {
	QueryParser qp;
	std::string testString = "variable k; variable h; Select k";
	std::pair<std::vector<std::vector<std::string>>, std::vector<std::string>> expectedVector = { {{"variable", "k"}, {"variable", "h"}}, {"k"} };
	std::pair<std::vector<std::vector<std::string>>, std::vector<std::string>> tokenizedVector = qp.tokenizeString(testString);
	
	REQUIRE(tokenizedVector == expectedVector);
};

TEST_CASE("removeSemiColon should remove all instances of ; in string") {
	QueryParser qp;
	std::string testString1 = ";;hE;;L;o";
	std::string testString2 = "v;";
	std::string testString3 = "v";
	std::string expectedString = "hELo";
	std::string expectedString2 = "v";

	std::string output1 = qp.removeSemiColon(testString1);
	std::string output2 = qp.removeSemiColon(testString2);
	std::string output3 = qp.removeSemiColon(testString3);

	REQUIRE(output1 == expectedString);
	REQUIRE(output2 == expectedString2);
	REQUIRE(output3 == expectedString2);
}
//
// ai-gen start(gpt, 0, e)
//https://chat.openai.com/share/72133ed9-d959-44ae-9c81-143998296122

TEST_CASE("convertStringToEntityType should produce accurate entity type") {
	QueryParser queryParser;

	SECTION("Test valid entity types") {
		REQUIRE(queryParser.convertStringToEntityType("stmt") == EntityType::Stmt);
		REQUIRE(queryParser.convertStringToEntityType("read") == EntityType::Read);
		REQUIRE(queryParser.convertStringToEntityType("print") == EntityType::Print);
		REQUIRE(queryParser.convertStringToEntityType("call") == EntityType::Call);
		REQUIRE(queryParser.convertStringToEntityType("while") == EntityType::While);
		REQUIRE(queryParser.convertStringToEntityType("if") == EntityType::If);
		REQUIRE(queryParser.convertStringToEntityType("assign") == EntityType::Assign);
		REQUIRE(queryParser.convertStringToEntityType("variable") == EntityType::Variable);
		REQUIRE(queryParser.convertStringToEntityType("constant") == EntityType::Constant);
		REQUIRE(queryParser.convertStringToEntityType("procedure") == EntityType::Procedure);
	}

	SECTION("Test unknown entity type") {
		REQUIRE(queryParser.convertStringToEntityType("unknown") == EntityType::Unknown);
	}
}
// ai-gen end

TEST_CASE("parse should produce valid results") {
	Sp sp = Sp();
    sp.ProcessSIMPLE("sprint1_source.txt");
    QueryFacade qf = QueryFacade();
	std::string query = "stmt s; Select s";
	std::shared_ptr<Query> parsedQuery = qf.parseQuery(query);
    vector<std::string> result = qf.evaluateQuery(parsedQuery);
    // print result
    for (const auto& res : result) {
        std::cout << res << std::endl;
    }
//    printf("%s\n", result.c_str());
//    REQUIRE(result == "xy, y, x, yx");

//	std::string expectedResult = "synonyms variable x selected variable x";
//
//	std::string queryResult = "synonyms ";
//
//	vector<shared_ptr<Synonym>> synonyms = result->synonyms;
//	shared_ptr<Synonym> selectedSynonym = result->selectedSynonym;
//
//	for (const auto& synonym : synonyms) {
//		if (synonym->getType() == EntityType::Variable) {
//			queryResult += "variable " + synonym->getName() + " ";
//		}
//	}
//
//	queryResult += "selected ";
//
//	if (selectedSynonym->getType() == EntityType::Variable) {
//		queryResult += "variable " + selectedSynonym->getName();
//	}
//
//	REQUIRE(queryResult == expectedResult);
//	QueryEvaluator qe;
//	std::cout << qe.evaluate(result) << std::endl;
//	EntityManager::clear();
}