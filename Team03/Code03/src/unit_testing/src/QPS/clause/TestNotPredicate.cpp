#include "catch.hpp"
#include "qps/entity/clause/NotPredicate.h"
#include "../fakeEntities/MockPredicates.cpp"
#include "../fakeEntities/MockEntity.cpp"
#include "../fakeEntities/FakeQueryManager.cpp"

TEST_CASE("NotPredicate with QueryManager Setup", "[NotPredicate]") {
    QueryEvaluationContext qec;
    shared_ptr<FakeQueryManager> qm = make_shared<FakeQueryManager>();
    qec.setQueryManager(qm);

    // Mock data setup for QueryManager
    shared_ptr<Synonym> synonymA = std::make_shared<Synonym>(EntityType::Stmt, "A");
    shared_ptr<Synonym> synonymB = std::make_shared<Synonym>(EntityType::Variable, "B");
    vector<shared_ptr<Entity>> allEntitiesA =
        {std::make_shared<MockEntity>("1", EntityType::Stmt), std::make_shared<MockEntity>("2", EntityType::Stmt),
         std::make_shared<MockEntity>("3", EntityType::Stmt)};
    vector<shared_ptr<Entity>> allEntitiesB = {std::make_shared<MockEntity>("x", EntityType::Variable),
                                               std::make_shared<MockEntity>("y", EntityType::Variable)};
    // Configure the QueryManager with mock responses for all entities by type
    qm->addFakeResponse(EntityType::Stmt, allEntitiesA);
    qm->addFakeResponse(EntityType::Variable, allEntitiesB);

    // Test negating a Boolean result
    SECTION("Negating a Boolean Result") {
        auto truePredicate = std::make_shared<MockBooleanPredicate>(true);
        NotPredicate notPredicate(truePredicate);

        auto resultTable = notPredicate.getResultTable(qec);
        REQUIRE(resultTable->isBoolean());
        auto boolTable = std::dynamic_pointer_cast<BooleanTable>(resultTable);
        REQUIRE(boolTable != nullptr);
        REQUIRE_FALSE(boolTable->isTrue()); // Expecting the negation of true -> false
    }

        // Test obtaining complement of a HeaderTable result
    SECTION("Obtaining Complement of a HeaderTable Result") {
        // Use MockTablePredicate to simulate an initial table result
        // This setup presumes the full table includes all combinations of A and B entities
        // and that MockTablePredicate simulates a scenario where some rows are already selected
        auto headerTable = std::make_shared<HeaderTable>(std::vector<shared_ptr<Synonym>>{synonymA, synonymB},
                                                         std::vector<std::vector<shared_ptr<Entity>>>{
                                                             {allEntitiesA[0], allEntitiesB[0]}});
        auto tablePredicate = std::make_shared<MockTablePredicate>(headerTable);
        NotPredicate notTablePredicate(tablePredicate);

        auto complementTable = notTablePredicate.getResultTable(qec);
        REQUIRE(complementTable != nullptr);
        REQUIRE(complementTable->getSize()
                    == 5); // Expecting complement size to be total possible combinations minus the existing row
    }
}

TEST_CASE("NotPredicate with QueryManager Setup Extended", "[NotPredicate]") {
    QueryEvaluationContext qec;
    shared_ptr<FakeQueryManager> qm = make_shared<FakeQueryManager>();
    qec.setQueryManager(qm);

    // Mock data setup for QueryManager
    shared_ptr<Synonym> synonymA = std::make_shared<Synonym>(EntityType::Stmt, "A");
    shared_ptr<Synonym> synonymB = std::make_shared<Synonym>(EntityType::Variable, "B");
    vector<shared_ptr<Entity>> allEntitiesA =
        {std::make_shared<MockEntity>("1", EntityType::Stmt), std::make_shared<MockEntity>("2", EntityType::Stmt),
         std::make_shared<MockEntity>("3", EntityType::Stmt)};
    vector<shared_ptr<Entity>> allEntitiesB = {std::make_shared<MockEntity>("x", EntityType::Variable),
                                               std::make_shared<MockEntity>("y", EntityType::Variable)};
    // Configure the QueryManager with mock responses for all entities by type
    qm->addFakeResponse(EntityType::Stmt, allEntitiesA);
    qm->addFakeResponse(EntityType::Variable, allEntitiesB);

    // Negating a Boolean result (True to False tested before)
    SECTION("Negating a False Boolean Result") {
        auto falsePredicate = std::make_shared<MockBooleanPredicate>(false);
        NotPredicate notPredicate(falsePredicate);

        auto resultTable = notPredicate.getResultTable(qec);
        REQUIRE(resultTable->isBoolean());
        auto boolTable = std::dynamic_pointer_cast<BooleanTable>(resultTable);
        REQUIRE(boolTable != nullptr);
        REQUIRE(boolTable->isTrue()); // Expecting the negation of false -> true
    }

        // Working with an Empty HeaderTable Result
    SECTION("Complement of an Empty HeaderTable") {
        // Simulate an empty initial table result
        auto emptyTable = std::make_shared<HeaderTable>();
        emptyTable->setHeaders(std::vector<shared_ptr<Synonym>>{synonymA, synonymB});
        auto tablePredicate = std::make_shared<MockTablePredicate>(emptyTable);
        NotPredicate notTablePredicate(tablePredicate);

        auto complementTable = notTablePredicate.getResultTable(qec);
        REQUIRE(complementTable != nullptr);
        // Assuming the full universe for A and B entities would give us 6 total combinations
        REQUIRE(complementTable->getSize()
                    == 6); // All combinations are part of the complement since the original table was empty
    }

        // Double Negation should return the original result
    SECTION("Double Negation Returns Original Result") {
        // This will test with a non-empty HeaderTable for a more complex scenario
        auto headerTable = std::make_shared<HeaderTable>(std::vector<shared_ptr<Synonym>>{synonymA, synonymB},
                                                         std::vector<std::vector<shared_ptr<Entity>>>{
                                                             {allEntitiesA[0], allEntitiesB[0]}});
        auto tablePredicate = std::make_shared<MockTablePredicate>(headerTable);
        NotPredicate notOncePredicate(tablePredicate);
        NotPredicate notTwicePredicate(std::make_shared<NotPredicate>(tablePredicate));
        NotPredicate notThricePredicate(std::make_shared<NotPredicate>(std::make_shared<NotPredicate>(tablePredicate)));

        auto originalResulTable = tablePredicate->getResultTable(qec);
        auto onceComplementTable = notOncePredicate.getResultTable(qec);
        auto twiceComplementTable = notTwicePredicate.getResultTable(qec);
        auto thriceComplementTable = notThricePredicate.getResultTable(qec);

        // For the double negation, the resulting table should match the original table's rows
        REQUIRE(twiceComplementTable != nullptr);
        REQUIRE(originalResulTable->getSize() == twiceComplementTable->getSize());
        // More detailed comparison can be done based on the contents of the tables if needed
        auto originalRowSet = dynamic_cast<HeaderTable *>(originalResulTable.get())->getRowSet();
        auto twiceRowSet = dynamic_cast<HeaderTable *>(twiceComplementTable.get())->getRowSet();
        REQUIRE(originalRowSet
                    == twiceRowSet); // This checks that the row sets are equivalent, thus confirming double negation logic

        // For the triple negation, the resulting table should match the negated table's rows
        REQUIRE(thriceComplementTable != nullptr);
        REQUIRE(onceComplementTable->getSize() == thriceComplementTable->getSize());
        auto onceRowSet = dynamic_cast<HeaderTable *>(onceComplementTable.get())->getRowSet();
        auto thriceRowSet = dynamic_cast<HeaderTable *>(thriceComplementTable.get())->getRowSet();
        REQUIRE(onceRowSet
                    == thriceRowSet); // This checks that the row sets are equivalent, thus confirming triple negation logic
    }
}
