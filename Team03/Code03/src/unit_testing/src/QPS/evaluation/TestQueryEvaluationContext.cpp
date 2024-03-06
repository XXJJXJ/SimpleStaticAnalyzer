#include "catch.hpp"

#include "common/Entity.h"
#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/QueryEvaluationContext.h"
#include "qps/entity/evaluation/HeaderTable.h"
#include <memory>
#include "../fakeEntities/MockEntity.cpp"

// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
// prompt: https://chat.openai.com/share/7c590366-8e0e-40e2-863f-2862fa1ae192
TEST_CASE("QueryEvaluationContext::getResults throws when multiple tables are present and one is empty", "[QueryEvaluationContext]") {
    QueryEvaluationContext qec;

    auto synonym1 = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto table1 = std::make_shared<HeaderTable>();
    table1->setHeaders({synonym1});
    table1->addRow(TableRow({std::make_shared<MockEntity>("value1")}));
    qec.addTableForSynonym(*synonym1, table1);

    auto synonym2 = std::make_shared<Synonym>(EntityType::Stmt, "s2");
    auto table2 = std::make_shared<HeaderTable>(); // Empty table
    qec.addTableForSynonym(*synonym2, table2);

    REQUIRE(qec.isCurrentResultEmpty());
}

TEST_CASE("QueryEvaluationContext::getResults throws when no tables are present", "[QueryEvaluationContext]") {
    QueryEvaluationContext qec;

    REQUIRE_THROWS_AS(qec.getResults(), std::runtime_error);
}

TEST_CASE("QueryEvaluationContext::getResults returns empty vector for context with empty tables", "[QueryEvaluationContext]") {
    QueryEvaluationContext qec;
    auto synonym = std::make_shared<Synonym>(EntityType::Stmt, "s");
    auto table = std::make_shared<HeaderTable>(); // Empty table
    qec.addTableForSynonym(*synonym, table);

    REQUIRE(qec.isCurrentResultEmpty());
}

TEST_CASE("QueryEvaluationContext::getResults handles special characters in entity names", "[QueryEvaluationContext]") {
    QueryEvaluationContext qec;
    auto synonym = std::make_shared<Synonym>(EntityType::Stmt, "s");
    auto table = std::make_shared<HeaderTable>();
    table->setHeaders({synonym});
    table->addRow(TableRow({std::make_shared<MockEntity>("$1")}));
    table->addRow(TableRow({std::make_shared<MockEntity>("value#2")}));
    table->addRow(TableRow({std::make_shared<MockEntity>("value, 3")}));
    qec.setResultTable(table);

    auto result = qec.getResults();
    REQUIRE(result.size() == 3);
    REQUIRE(result[0] == "$1");
    REQUIRE(result[1] == "value#2");
    REQUIRE(result[2] == "value, 3");
}
// ai-gen end
