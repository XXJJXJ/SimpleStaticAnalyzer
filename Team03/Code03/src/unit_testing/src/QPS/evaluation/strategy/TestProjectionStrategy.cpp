#include "catch.hpp"
#include "qps/entity/evaluation/QueryEvaluationContext.h"
#include "qps/entity/strategy/ProjectionStrategy.h"
#include <memory>
#include "../../fakeEntities/FakeQueryManager.cpp"
#include "../../fakeEntities/MockEntity.cpp"
#include "qps/entity/evaluation/HeaderTable.h"

// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a

TEST_CASE("ProjectionStrategy sets empty table when context has an empty table", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto synonym = std::make_shared<Synonym>(EntityType::Stmt, "s");
    auto emptyTable = std::make_shared<HeaderTable>(); // Intentionally empty
    emptyTable->setHeaders({synonym}); // Adapting for vector<shared_ptr<Synonym>>
    qec.addTableForSynonym(*synonym, emptyTable);
    ProjectionStrategy strategy({synonym});

    strategy.execute(qec);

    auto resultBaseTable = qec.getResultTable();
    auto resultTable = std::dynamic_pointer_cast<HeaderTable>(resultBaseTable);

    REQUIRE(resultTable != nullptr);
    REQUIRE(resultTable->isEmpty());
    REQUIRE(resultTable->getHeaders().front() == synonym);
}

TEST_CASE("ProjectionStrategy queries and sets new table when synonym not in any table", "[ProjectionStrategy]") {
    auto fakeManager = std::make_shared<FakeQueryManager>();
    auto mockEntity = std::make_shared<MockEntity>("mockName");
    fakeManager->addFakeResponse<MockEntity>(EntityType::Stmt, {mockEntity});

    QueryEvaluationContext qec;
    qec.setQueryManager(fakeManager);

    auto synonym = std::make_shared<Synonym>(EntityType::Stmt, "s");
    qec.setSynonymGroups({{synonym}});
    ProjectionStrategy strategy({synonym});

    strategy.execute(qec);

    auto resultBaseTable = qec.getResultTable();
    auto resultTable = std::dynamic_pointer_cast<HeaderTable>(resultBaseTable);

    auto resultStrings = resultTable->toStrings();

    REQUIRE(resultTable != nullptr);
    REQUIRE_FALSE(resultTable->isEmpty());
    REQUIRE(resultTable->getSize() == 1);
    REQUIRE(resultStrings.count("mockName") == 1);
}

TEST_CASE("ProjectionStrategy projects column correctly when table with synonym exists", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto synonym = std::make_shared<Synonym>(EntityType::Stmt, "s");
    auto table = std::make_shared<HeaderTable>();
    table->setHeaders({synonym});
    table->addRow(TableRow({std::make_shared<MockEntity>("entityValue")}));
    qec.addTableForSynonym(*synonym, table);
    qec.setSynonymGroups({{synonym}});

    ProjectionStrategy strategy({synonym});

    strategy.execute(qec);

    auto resultBaseTable = qec.getResultTable();
    auto resultTable = std::dynamic_pointer_cast<HeaderTable>(resultBaseTable);
    auto resultStrings = resultTable->toStrings();

    REQUIRE(resultTable != nullptr);
    REQUIRE_FALSE(resultTable->isEmpty());
    REQUIRE(resultTable->getSize() == 1);
    REQUIRE(resultStrings.count("entityValue") == 1);
}

TEST_CASE("ProjectionStrategy with multiple tables, some empty", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto synonym1 = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto table1 = std::make_shared<HeaderTable>();
    table1->setHeaders({synonym1});
    table1->addRow(TableRow({std::make_shared<MockEntity>("entity1")}));

    auto synonym2 = std::make_shared<Synonym>(EntityType::Stmt, "s2");
    auto emptyTable = std::make_shared<HeaderTable>(); // Intentionally empty
    qec.addTableForSynonym(*synonym1, table1);
    qec.addTableForSynonym(*synonym2, emptyTable);

    ProjectionStrategy strategy({synonym1});
    strategy.execute(qec);

    auto resultBaseTable = qec.getResultTable();
    auto resultTable = std::dynamic_pointer_cast<HeaderTable>(resultBaseTable);
    REQUIRE(resultTable->isEmpty());
}

TEST_CASE("ProjectionStrategy with table having multiple columns", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto synonym1 = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto synonym2 = std::make_shared<Synonym>(EntityType::Variable, "v1");
    auto table = std::make_shared<HeaderTable>();
    table->setHeaders({synonym1, synonym2});
    table->addRow(TableRow({std::make_shared<MockEntity>("entity1"), std::make_shared<MockEntity>("var1")}));
    qec.addTableForSynonym(*synonym1, table);
    qec.setSynonymGroups({{synonym1, synonym2}});

    ProjectionStrategy strategy({synonym1});
    strategy.execute(qec);

    auto resultBaseTable = qec.getResultTable();
    auto resultTable = std::dynamic_pointer_cast<HeaderTable>(resultBaseTable);
    REQUIRE_FALSE(resultTable->isEmpty());
    auto resultStrings = resultTable->toStrings();

    REQUIRE(resultTable->getSize() == 1);
    REQUIRE(resultStrings.count("entity1") == 1);
}

TEST_CASE("ProjectionStrategy selects specific column when multiple synonyms exist", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto synonym1 = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto synonym2 = std::make_shared<Synonym>(EntityType::Variable, "v1");
    auto table = std::make_shared<HeaderTable>();
    table->setHeaders({synonym1, synonym2});
    table->addRow(TableRow({std::make_shared<MockEntity>("entity1"), std::make_shared<MockEntity>("var1")}));
    table->addRow(TableRow({std::make_shared<MockEntity>("entity2"), std::make_shared<MockEntity>("var2")}));
    qec.addTableForSynonym(*synonym1, table);
    qec.addTableForSynonym(*synonym2, table);
    qec.setSynonymGroups({{synonym1, synonym2}});

    ProjectionStrategy strategy({synonym2}); // Projecting only the second column
    strategy.execute(qec);

    auto resultBaseTable = qec.getResultTable();
    auto resultTable = std::dynamic_pointer_cast<HeaderTable>(resultBaseTable);
    auto resultStrings = resultTable->toStrings();
    REQUIRE(resultTable->getSize() == 2);
    REQUIRE(resultStrings.count("var1") == 1);
    REQUIRE(resultStrings.count("var2") == 1);
}

TEST_CASE("ProjectionStrategy with multiple non-empty tables", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto synonym1 = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto synonym2 = std::make_shared<Synonym>(EntityType::Variable, "v1");
    auto table1 = std::make_shared<HeaderTable>();
    table1->setHeaders({synonym1});
    table1->addRow(TableRow({std::make_shared<MockEntity>("entity1")}));
    auto table2 = std::make_shared<HeaderTable>();
    table2->setHeaders({synonym2});
    table2->addRow(TableRow({std::make_shared<MockEntity>("var1")}));
    qec.addTableForSynonym(*synonym1, table1);
    qec.addTableForSynonym(*synonym2, table2);
    qec.setSynonymGroups({{synonym1}, {synonym2}});

    ProjectionStrategy strategy({synonym1}); // Projecting only the first synonym
    strategy.execute(qec);

    auto resultBaseTable = qec.getResultTable();
    auto resultTable = std::dynamic_pointer_cast<HeaderTable>(resultBaseTable);
    auto resultStrings = resultTable->toStrings();

    REQUIRE(resultTable->getSize() == 1);
    REQUIRE(resultStrings.count("entity1") == 1);
}

// ai-gen end

TEST_CASE("ProjectionStrategy selects multiple synonyms from same group", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto synonym1 = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto synonym2 = std::make_shared<Synonym>(EntityType::Variable, "v1");
    auto table1 = std::make_shared<HeaderTable>();
    table1->setHeaders({synonym1, synonym2});
    table1->addRow(TableRow({std::make_shared<MockEntity>("entity1"), std::make_shared<MockEntity>("var1")}));
    qec.addTableForSynonym(*synonym1, table1);
    qec.addTableForSynonym(*synonym2, table1);
    qec.setSynonymGroups({{synonym1, synonym2}});

    ProjectionStrategy strategy({synonym1, synonym2}); // Projecting both synonyms
    strategy.execute(qec);

    auto resultBaseTable = qec.getResultTable();
    auto resultTable = std::dynamic_pointer_cast<HeaderTable>(resultBaseTable);

    REQUIRE_FALSE(resultTable->isEmpty());
    REQUIRE(resultTable->getSize() == 1);
    auto resultRows = resultTable->toStrings();
    REQUIRE(resultRows.find("entity1 var1") != resultRows.end());
}

TEST_CASE("ProjectionStrategy gives TRUE for queries with 0 predicates", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto fakeManager = std::make_shared<FakeQueryManager>();
    qec.setQueryManager(fakeManager);

    // Assuming you have a way to signify no predicates, possibly by not adding any synonyms or specific setup
    ProjectionStrategy strategy({}); // Empty synonym list represents 0 predicates in this context

    strategy.execute(qec);

    // Assuming `getQueryResultBool` retrieves the boolean result of the query
    auto queryResult = qec.getResultTable();
    auto result = queryResult->toStrings();

    REQUIRE(result.size() == 1);
    REQUIRE(result.find("TRUE") != result.end());  // No constraints in query

}

TEST_CASE("ProjectionStrategy gives FALSE for queries with empty result", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto fakeManager = std::make_shared<FakeQueryManager>();
    qec.setQueryManager(fakeManager);
    qec.setResultToFalse();     // The API called when the result is empty

    // Assuming you have a way to signify no predicates, possibly by not adding any synonyms or specific setup
    ProjectionStrategy strategy({}); // Empty synonym list represents 0 predicates in this context

    strategy.execute(qec);

    // Assuming `getQueryResultBool` retrieves the boolean result of the query
    auto queryResult = qec.getResultTable();
    auto result = queryResult->toStrings();

    REQUIRE(result.size() == 1);
    REQUIRE(result.find("FALSE") != result.end());  // No constraints in query

}

TEST_CASE("ProjectionStrategy selects synonyms from different groups", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto synonym1 = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto synonym2 = std::make_shared<Synonym>(EntityType::Variable, "v1");
    auto synonym3 = std::make_shared<Synonym>(EntityType::Stmt, "s2");
    auto table1 = std::make_shared<HeaderTable>();
    table1->setHeaders({synonym1, synonym2});
    table1->addRow(TableRow({std::make_shared<MockEntity>("entity1"), std::make_shared<MockEntity>("var1")}));
    table1->addRow(TableRow({std::make_shared<MockEntity>("entity2"), std::make_shared<MockEntity>("var2")}));
//    table1->addRow(TableRow({std::make_shared<MockEntity>("entity2"), std::make_shared<MockEntity>("var3")}));
    table1->addRow(TableRow({std::make_shared<MockEntity>("entity3"), std::make_shared<MockEntity>("var1")}));
    auto table2 = std::make_shared<HeaderTable>();
    table2->setHeaders({synonym3});
    table2->addRow(TableRow({std::make_shared<MockEntity>("entity999")}));
    table2->addRow(TableRow({std::make_shared<MockEntity>("entity998")}));

    qec.addTableForSynonym(*synonym1, table1);
    qec.addTableForSynonym(*synonym2, table1);
    qec.addTableForSynonym(*synonym3, table2);
    qec.setSynonymGroups({{synonym1, synonym2}, {synonym3}});

    ProjectionStrategy strategy({synonym1, synonym3}); // Selecting synonyms from different groups
    strategy.execute(qec);

    auto resultBaseTable = qec.getResultTable();
    auto resultTable = std::dynamic_pointer_cast<HeaderTable>(resultBaseTable);

    REQUIRE_FALSE(resultTable->isEmpty());
    REQUIRE(resultTable->getSize() == 6);
    auto resultRows = resultTable->toStrings();
    REQUIRE(resultRows.find("entity1 entity999") != resultRows.end());
    REQUIRE(resultRows.find("entity2 entity999") != resultRows.end());
    REQUIRE(resultRows.find("entity2 entity998") != resultRows.end());
    REQUIRE(resultRows.find("entity3 entity999") != resultRows.end());
    REQUIRE(resultRows.find("entity1 entity998") != resultRows.end());
    REQUIRE(resultRows.find("entity2 entity998") != resultRows.end());

}



