#include "catch.hpp"
#include "qps/entity/strategy/JoinWithPredicateStrategy.h"
#include "../../fakeEntities/FakeQueryManager.cpp"
#include "qps/entity/evaluation/QueryEvaluationContext.h"
#include "qps/entity/clause/FollowsPredicate.h"
#include "qps/entity/evaluation/EvaluationPlanner.h"
#include "qps/entity/evaluation/HeaderTable.h"

TEST_CASE("No Table Initialized, No Predicate Table Available", "[JoinWithPredicateStrategy]") {
    // Setup
    auto fakeQueryManager = std::make_shared<FakeQueryManager>();
    QueryEvaluationContext context;
    context.setQueryManager(fakeQueryManager);

    auto predicate = std::make_shared<FollowsPredicate>(1, "_");
    JoinWithPredicateStrategy strategy(predicate);

    // No table setup for the predicate in FakeQueryManager
    // fakeQueryManager->addFakeResponse(...); // Normally you'd setup responses here

    // Execute
    strategy.execute(context);

    // Verify
    REQUIRE(context.isCurrentResultEmpty()); // Adjust based on how you verify the outcome
}

TEST_CASE("No Table Initialized, Predicate Table Available", "[JoinWithPredicateStrategy]") {
    auto fakeQueryManager = std::make_shared<FakeQueryManager>();
    QueryEvaluationContext context;
    context.setQueryManager(fakeQueryManager);

    auto stmt1 = std::make_shared<Statement>(1, EntityType::Stmt, "dummyProc");
    auto stmt2 = std::make_shared<Statement>(2, EntityType::Stmt, "dummyProc");
    fakeQueryManager->addFakeFollows(stmt1, stmt2);

    auto stmtSyn1Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto stmtSyn2Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s2");

    std::vector<SynonymPtrSet> groups;
    SynonymPtrSet group1;
    group1.insert(stmtSyn1Ptr);
    group1.insert(stmtSyn2Ptr);
    groups.push_back(group1);
    context.setSynonymGroups(groups);

    auto predicate = std::make_shared<FollowsPredicate>(*stmtSyn1Ptr, *stmtSyn2Ptr);
    JoinWithPredicateStrategy strategy(predicate);

    strategy.execute(context);

    auto actualTableForSyn1 = context.getTableForSynonym(*stmtSyn1Ptr);
    auto actualTableForSyn2 = context.getTableForSynonym(*stmtSyn2Ptr);

    auto headers = std::vector<std::shared_ptr<Synonym>>{stmtSyn1Ptr, stmtSyn2Ptr};
    auto entities = std::vector<std::vector<std::shared_ptr<Entity>>>{{stmt1, stmt2}};
    auto expectedTableForSyn1 = std::make_shared<HeaderTable>(headers, entities);

    REQUIRE(actualTableForSyn1 != nullptr);
    REQUIRE(actualTableForSyn2 != nullptr);
    REQUIRE(*actualTableForSyn1 == *expectedTableForSyn1);
    REQUIRE(*actualTableForSyn2 == *expectedTableForSyn1);
}


