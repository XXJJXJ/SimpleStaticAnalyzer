#include "catch.hpp"
#include "qps/entity/evaluation/QueryEvaluationContext.h"
#include "qps/entity/strategy/ProjectionStrategy.h"
#include <memory>
#include "../../fakeEntities/FakeQueryManager.cpp"
#include "../../fakeEntities/MockEntity.cpp"

// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a

TEST_CASE("ProjectionStrategy sets empty table when context has an empty table", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto synonym = std::make_shared<Synonym>(EntityType::Stmt, "s");
    auto emptyTable = std::make_shared<HeaderTable>(); // Intentionally empty
    qec.addTableForSynonym(*synonym, emptyTable);
    ProjectionStrategy strategy(synonym);

    strategy.execute(qec);

    auto resultTable = qec.getResultTable();
    REQUIRE(resultTable != nullptr);
    REQUIRE(resultTable->isEmpty());
    REQUIRE(resultTable->getHeaders().front() == *synonym);
}

TEST_CASE("ProjectionStrategy queries and sets new table when synonym not in any table", "[ProjectionStrategy]") {
    auto fakeManager = std::make_shared<FakeQueryManager>();
    auto mockEntity = std::make_shared<MockEntity>("mockName");
    fakeManager->addFakeResponse<MockEntity>(EntityType::Stmt, {mockEntity});

    QueryEvaluationContext qec;
    qec.setQueryManager(fakeManager);

    auto synonym = std::make_shared<Synonym>(EntityType::Stmt, "s");
    ProjectionStrategy strategy(synonym);

    strategy.execute(qec);

    auto resultTable = qec.getResultTable();
    REQUIRE(resultTable != nullptr);
    REQUIRE_FALSE(resultTable->isEmpty());
    REQUIRE(resultTable->getSize() == 1);
    REQUIRE(resultTable->toStrings().front() == "mockName");
}

TEST_CASE("ProjectionStrategy projects column correctly when table with synonym exists", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto synonym = std::make_shared<Synonym>(EntityType::Stmt, "s");
    auto table = std::make_shared<HeaderTable>();
    table->setHeaders({*synonym}); // Assume setHeaders exists
    // Assume MockEntity definition and it has a conversion method to TableRow
    table->addRow(TableRow({std::make_shared<MockEntity>("entityValue")}));
    qec.addTableForSynonym(*synonym, table);

    ProjectionStrategy strategy(synonym);

    strategy.execute(qec);

    auto resultTable = qec.getResultTable();
    REQUIRE(resultTable != nullptr);
    REQUIRE_FALSE(resultTable->isEmpty());
    // Verify that the resultTable contains only the column for the target synonym
    REQUIRE(resultTable->toStrings().front() == "entityValue");
}

TEST_CASE("ProjectionStrategy with multiple tables, some empty", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto synonym1 = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto table1 = std::make_shared<HeaderTable>();
    table1->setHeaders({*synonym1});
    table1->addRow(TableRow({std::make_shared<MockEntity>("entity1")}));

    auto synonym2 = std::make_shared<Synonym>(EntityType::Stmt, "s2");
    auto emptyTable = std::make_shared<HeaderTable>(); // Intentionally empty
    qec.addTableForSynonym(*synonym1, table1);
    qec.addTableForSynonym(*synonym2, emptyTable);

    ProjectionStrategy strategy(synonym1);
    strategy.execute(qec);

    auto resultTable = qec.getResultTable();
    auto results = resultTable->toStrings();
    REQUIRE(results.empty());
}

TEST_CASE("ProjectionStrategy with table having multiple columns", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto synonym1 = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto synonym2 = std::make_shared<Synonym>(EntityType::Variable, "v1");
    auto table = std::make_shared<HeaderTable>();
    table->setHeaders({*synonym1, *synonym2});
    table->addRow(TableRow({std::make_shared<MockEntity>("entity1"), std::make_shared<MockEntity>("var1")}));
    qec.addTableForSynonym(*synonym1, table);

    ProjectionStrategy strategy(synonym1);
    strategy.execute(qec);

    auto resultTable = qec.getResultTable();
    auto results = resultTable->toStrings();
    REQUIRE(results.size() == 1);
    REQUIRE(results.front() == "entity1");
}

TEST_CASE("ProjectionStrategy selects specific column when multiple synonyms exist", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto synonym1 = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto synonym2 = std::make_shared<Synonym>(EntityType::Variable, "v1");
    auto table = std::make_shared<HeaderTable>();
    table->setHeaders({*synonym1, *synonym2});
    table->addRow(TableRow({std::make_shared<MockEntity>("entity1"), std::make_shared<MockEntity>("var1")}));
    table->addRow(TableRow({std::make_shared<MockEntity>("entity2"), std::make_shared<MockEntity>("var2")}));
    qec.addTableForSynonym(*synonym1, table);
    qec.addTableForSynonym(*synonym2, table);


    ProjectionStrategy strategy(synonym2); // Projecting only the second column
    strategy.execute(qec);

    auto resultTable = qec.getResultTable();
    auto results = resultTable->toStrings();
    REQUIRE(results.size() == 2);
    REQUIRE(results[0] == "var1");
    REQUIRE(results[1] == "var2");
}

TEST_CASE("ProjectionStrategy with multiple non-empty tables", "[ProjectionStrategy]") {
    QueryEvaluationContext qec;
    auto synonym1 = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto synonym2 = std::make_shared<Synonym>(EntityType::Variable, "v1");
    auto table1 = std::make_shared<HeaderTable>();
    table1->setHeaders({*synonym1});
    table1->addRow(TableRow({std::make_shared<MockEntity>("entity1")}));
    auto table2 = std::make_shared<HeaderTable>();
    table2->setHeaders({*synonym2});
    table2->addRow(TableRow({std::make_shared<MockEntity>("var1")}));
    qec.addTableForSynonym(*synonym1, table1);
    qec.addTableForSynonym(*synonym2, table2);

    ProjectionStrategy strategy(synonym1); // Projecting only the first synonym
    strategy.execute(qec);

    auto resultTable = qec.getResultTable();
    auto results = resultTable->toStrings();
    REQUIRE(results.size() == 1);
    REQUIRE(results[0] == "entity1");
}
// ai-gen end


