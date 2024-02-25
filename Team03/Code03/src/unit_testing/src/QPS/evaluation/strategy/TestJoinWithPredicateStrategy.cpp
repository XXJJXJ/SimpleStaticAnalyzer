#include "catch.hpp"
#include "qps/entity/strategy/JoinWithPredicateStrategy.h"
#include "../../fakeEntities/FakeQueryManager.cpp"
#include "qps/entity/evaluation/QueryEvaluationContext.h"
#include "qps/entity/clause/FollowsPredicate.h"
#include "qps/entity/evaluation/EvaluationPlanner.h"
#include "qps/entity/evaluation/HeaderTable.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <random>
#include <algorithm>
#include <set>

// ai-gen-start(gpt, 1, e)
// prompt: https://chat.openai.com/share/c6f7b0af-7abf-4441-addf-aa9a0550dccc

TEST_CASE("No Table Initialized, No Predicate Table Available", "[JoinWithPredicateStrategy]") {
    auto fakeQueryManager = std::make_shared<FakeQueryManager>();
    QueryEvaluationContext context;
    context.setQueryManager(fakeQueryManager);

    auto predicate = std::make_shared<FollowsPredicate>(1, "_");
    JoinWithPredicateStrategy strategy(predicate);

    strategy.execute(context);

    REQUIRE(context.isCurrentResultEmpty());
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

    auto headers = std::vector<std::shared_ptr<Synonym>>{stmtSyn1Ptr, stmtSyn2Ptr};
    auto entities = std::vector<std::vector<std::shared_ptr<Entity>>>{{stmt1, stmt2}};
    auto expectedTableForSyn1 = std::make_shared<HeaderTable>(headers, entities);

    auto actualTableForSyn1 = context.getTableForSynonym(*stmtSyn1Ptr);
    auto actualTableForSyn2 = context.getTableForSynonym(*stmtSyn2Ptr);

    REQUIRE(actualTableForSyn1 != nullptr);
    REQUIRE(actualTableForSyn2 != nullptr);
    REQUIRE(*actualTableForSyn1 == *expectedTableForSyn1);
    REQUIRE(*actualTableForSyn2 == *expectedTableForSyn1);
}

TEST_CASE("Synonyms Grouped by Connected Predicates", "[JoinWithPredicateStrategy]") {
    auto fakeQueryManager = std::make_shared<FakeQueryManager>();
    QueryEvaluationContext context;
    context.setQueryManager(fakeQueryManager);

    // Create Statements to simulate Follows relationship
    auto stmt1 = std::make_shared<Statement>(1, EntityType::Stmt, "dummyProc1");
    auto stmt2 = std::make_shared<Statement>(2, EntityType::Stmt, "dummyProc2");
    // Simulate that stmt2 follows stmt1 in the program order
    fakeQueryManager->addFakeFollows(stmt1, stmt2);

    // Setup Synonyms
    auto stmtSyn1Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto stmtSyn2Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s2");
    auto stmtSyn3Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s3");
    auto stmtSyn4Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s4");

    // Define groups based on predicate connections
    std::vector<SynonymPtrSet> groups;
    SynonymPtrSet group1 {stmtSyn1Ptr}; // s1 alone
    SynonymPtrSet group2 {stmtSyn2Ptr, stmtSyn3Ptr}; // s2, s3 connected by FollowsPredicate
    SynonymPtrSet group3 {stmtSyn4Ptr}; // s4 alone
    groups.push_back(group1);
    groups.push_back(group2);
    groups.push_back(group3);
    context.setSynonymGroups(groups);

    auto predicate = std::make_shared<FollowsPredicate>(*stmtSyn2Ptr, *stmtSyn3Ptr);
    JoinWithPredicateStrategy strategy(predicate);

    strategy.execute(context);

    // Expectations: Since the predicate connects s2 and s3, we expect updates in their group's table
    std::vector<std::shared_ptr<Synonym>> headersGroup2 {stmtSyn2Ptr, stmtSyn3Ptr};
    // Assuming the FollowsPredicate leads to creating a table where s2 is followed by s3
    std::vector<std::vector<std::shared_ptr<Entity>>> entitiesGroup2 {{stmt1, stmt2}};

    auto expectedTableForGroup2 = std::make_shared<HeaderTable>(headersGroup2, entitiesGroup2);

    auto actualTableForGroup2 = context.getTableForSynonym(*stmtSyn2Ptr); // This fetches the table for the group containing s2 and s3

    REQUIRE(actualTableForGroup2 != nullptr);
    REQUIRE(*actualTableForGroup2 == *expectedTableForGroup2);
}




TEST_CASE("Mix of Constant Predicates and Predicates with Synonyms", "[JoinWithPredicateStrategy]") {
    auto fakeQueryManager = std::make_shared<FakeQueryManager>();
    QueryEvaluationContext context;
    context.setQueryManager(fakeQueryManager);

    // Simulate Follows relationship for constant predicate
    auto stmt1 = std::make_shared<Statement>(1, EntityType::Stmt, "ProcA");
    auto stmt2 = std::make_shared<Statement>(2, EntityType::Stmt, "ProcB");
    fakeQueryManager->addFakeFollows(stmt1, stmt2); // Simulating Follows(1, 2)

    // Setup Synonyms and Groups
    auto stmtSynPtr = std::make_shared<Synonym>(EntityType::Stmt, "s");

    std::vector<SynonymPtrSet> groups;
    SynonymPtrSet group {stmtSynPtr}; // Only one group with a synonym for this test
    groups.push_back(group);
    context.setSynonymGroups(groups);

    // Predicate setup
    auto constantPredicate = std::make_shared<FollowsPredicate>(1, "_");
    auto synonymPredicate = std::make_shared<FollowsPredicate>(*stmtSynPtr, "_");

    // Execute strategies
    JoinWithPredicateStrategy constantStrategy(constantPredicate);
    constantStrategy.execute(context);

    JoinWithPredicateStrategy synonymStrategy(synonymPredicate);
    synonymStrategy.execute(context);

    // Verification
    // For constantPredicate, since it's not directly adding or modifying any synonym-based table, we focus on synonymPredicate
    auto actualTableForSynonym = context.getTableForSynonym(*stmtSynPtr);

    // Expected table setup
    // First stretegy does not affect the table for the synonym
    // Second strategy should leave stmt1 in the result table
    std::vector<std::shared_ptr<Synonym>> headers {stmtSynPtr};
    std::vector<std::vector<std::shared_ptr<Entity>>> entities {{stmt1}};

    auto expectedTable = std::make_shared<HeaderTable>(headers, entities);

    REQUIRE(actualTableForSynonym != nullptr);
    REQUIRE(*actualTableForSynonym == *expectedTable);
}


TEST_CASE("Predicates Affecting the Same Group Multiple Times", "[JoinWithPredicateStrategy]") {
    auto fakeQueryManager = std::make_shared<FakeQueryManager>();
    QueryEvaluationContext context;
    context.setQueryManager(fakeQueryManager);

    // Simulate Follows relationships
    auto stmt1 = std::make_shared<Statement>(1, EntityType::Stmt, "ProcA");
    auto stmt2 = std::make_shared<Statement>(2, EntityType::Stmt, "ProcB");
    fakeQueryManager->addFakeFollows(stmt1, stmt2); // Assuming this simulates Follows(1, 2) for testing

    // Setup Synonyms and Group
    auto stmtSyn1Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto stmtSyn2Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s2");
    std::vector<SynonymPtrSet> groups;
    SynonymPtrSet group {stmtSyn1Ptr, stmtSyn2Ptr};
    groups.push_back(group);
    context.setSynonymGroups(groups);

    // Predicates setup
    auto predicate1 = std::make_shared<FollowsPredicate>(*stmtSyn1Ptr, *stmtSyn2Ptr);
    auto predicate2 = std::make_shared<FollowsPredicate>(*stmtSyn2Ptr, *stmtSyn1Ptr); // For the sake of example, assume it's valid

    // Execute strategies
    JoinWithPredicateStrategy strategy1(predicate1);
    strategy1.execute(context);
    JoinWithPredicateStrategy strategy2(predicate2);
    strategy2.execute(context);

    // Verification
    auto actualTableForGroup = context.getTableForSynonym(*stmtSyn1Ptr); // Fetches the table for the group

    // Construct the expected table
    std::vector<std::shared_ptr<Synonym>> expectedHeaders {stmtSyn1Ptr, stmtSyn2Ptr};
    std::vector<std::vector<std::shared_ptr<Entity>>> expectedEntities {};    // expects empty result

    auto expectedTable = std::make_shared<HeaderTable>(expectedHeaders, expectedEntities);

    REQUIRE(actualTableForGroup != nullptr);
    REQUIRE(*actualTableForGroup == *expectedTable);
}

TEST_CASE("Comprehensive Test: Single Group, Multiple Predicates", "[JoinWithPredicateStrategy]") {
    auto fakeQueryManager = std::make_shared<FakeQueryManager>();
    QueryEvaluationContext context;
    context.setQueryManager(fakeQueryManager);

    // Simulate a sequence of Follows relationships
    auto stmt1 = std::make_shared<Statement>(1, EntityType::Stmt, "ProcA");
    auto stmt2 = std::make_shared<Statement>(2, EntityType::Stmt, "ProcA");
    auto stmt3 = std::make_shared<Statement>(3, EntityType::Stmt, "ProcB");
    auto stmt4 = std::make_shared<Statement>(4, EntityType::Stmt, "ProcB");
    fakeQueryManager->addFakeFollows(stmt1, stmt2); // Follows(1, 2)
    fakeQueryManager->addFakeFollows(stmt2, stmt3); // Follows(2, 3)
    fakeQueryManager->addFakeFollows(stmt3, stmt4); // Follows(3, 4)

    // Setup Synonyms and a single Group since all are interconnected
    auto stmtSyn1Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto stmtSyn2Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s2");
    auto stmtSyn3Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s3");
    auto stmtSyn4Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s4");

    SynonymPtrSet group {stmtSyn1Ptr, stmtSyn2Ptr, stmtSyn3Ptr, stmtSyn4Ptr};
    context.setSynonymGroups({group}); // All synonyms in one group due to their connections

    // Predicates setup, demonstrating different types of relationships
    auto predicate1 = std::make_shared<FollowsPredicate>(*stmtSyn1Ptr, *stmtSyn2Ptr);
    auto predicate2 = std::make_shared<FollowsPredicate>(*stmtSyn3Ptr, *stmtSyn4Ptr);
    auto predicate3 = std::make_shared<FollowsPredicate>(*stmtSyn3Ptr, *stmtSyn2Ptr);

    // Execute strategies for both predicates
    JoinWithPredicateStrategy strategy1(predicate1);
    strategy1.execute(context);
    JoinWithPredicateStrategy strategy2(predicate2);
    strategy2.execute(context);
    JoinWithPredicateStrategy strategy3(predicate3);
    strategy3.execute(context);

    // Verification for the single group, expecting tables reflecting the Follows relationships
    auto actualTable = context.getTableForSynonym(*stmtSyn1Ptr); // Fetches the table for the group
    auto resultRows = actualTable->toStrings();

    // Expects "1 2 1 2", "2 3 2 3" "3 4 3 4" as the result, order doesn't matter
    REQUIRE(resultRows.size() == 3);
    REQUIRE(std::find(resultRows.begin(), resultRows.end(), "1 2 1 2") != resultRows.end());
    REQUIRE(std::find(resultRows.begin(), resultRows.end(), "2 3 2 3") != resultRows.end());
    REQUIRE(std::find(resultRows.begin(), resultRows.end(), "3 4 3 4") != resultRows.end());
}



void populateRandomFollowsData(std::shared_ptr<FakeQueryManager> fakeQueryManager, int numberOfStatements, int maxFollows, unsigned int seed) {
    std::vector<std::shared_ptr<Statement>> statements;
    statements.reserve(numberOfStatements);

    // Create statements with unique numbers
    for (int i = 1; i <= numberOfStatements; ++i) {
        std::string procedure = "Proc" + std::to_string((i - 1) % 20 + 1); // Cycle through Proc1 to Proc20
        statements.push_back(std::make_shared<Statement>(i, EntityType::Stmt, procedure));
    }

    std::mt19937 rng(seed); // Use seed for reproducibility
    std::uniform_int_distribution<int> dist(0, numberOfStatements - 1);
    std::set<std::pair<int, int>> generatedPairs; // To avoid duplicates

    // Generate random Follows relationships
    int followsCount = 0;
    while (followsCount < maxFollows) {
        int fromIndex = dist(rng);
        int toIndex = dist(rng);

        // Ensure no self-following and check for duplicates
        if (fromIndex != toIndex && generatedPairs.find({fromIndex, toIndex}) == generatedPairs.end()) {
            generatedPairs.insert({fromIndex, toIndex});
            fakeQueryManager->addFakeFollows(statements[fromIndex], statements[toIndex]);
            followsCount++;
        }
    }
}



TEST_CASE("Comprehensive Test: Multiple Group, Multiple Predicates, Changing Evaluation Order", "[JoinWithPredicateStrategy]") {
    auto fakeQueryManager = std::make_shared<FakeQueryManager>();
    QueryEvaluationContext context;
    context.setQueryManager(fakeQueryManager);

    int numberOfStatements = 20;
    populateRandomFollowsData(fakeQueryManager, numberOfStatements, 100, 42);


    // Setup Synonyms and a single Group since all are interconnected
    auto stmtSyn1Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto stmtSyn2Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s2");
    auto stmtSyn3Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s3");
    auto stmtSyn4Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s4");
    auto stmtSyn5Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s5");
    auto stmtSyn6Ptr = std::make_shared<Synonym>(EntityType::Stmt, "s6");

    vector<SynonymPtrSet> groups {{stmtSyn1Ptr, stmtSyn2Ptr, stmtSyn5Ptr}, {stmtSyn3Ptr, stmtSyn6Ptr}, {stmtSyn4Ptr}};
    context.setSynonymGroups(groups); // All synonyms in one group due to their connections

    // Predicates setup, demonstrating different types of relationships
    // Group 1: s1, s2, s5
    auto predicate1 = std::make_shared<FollowsPredicate>(*stmtSyn1Ptr, *stmtSyn2Ptr);
    auto predicate2 = std::make_shared<FollowsPredicate>(*stmtSyn1Ptr, *stmtSyn5Ptr);
    auto predicate3 = std::make_shared<FollowsPredicate>(*stmtSyn5Ptr, *stmtSyn2Ptr);
    auto predicate4 = std::make_shared<FollowsPredicate>(*stmtSyn5Ptr, "_");
    auto predicate5 = std::make_shared<FollowsPredicate>("_", *stmtSyn2Ptr);

    // Group 2: s3, s6
    auto predicate6 = std::make_shared<FollowsPredicate>(*stmtSyn3Ptr, *stmtSyn6Ptr);
    auto predicate7 = std::make_shared<FollowsPredicate>(*stmtSyn3Ptr, 4);

    // Group 3: s4
    auto predicate8 = std::make_shared<FollowsPredicate>(*stmtSyn4Ptr, "_");

    auto strategies = std::vector<JoinWithPredicateStrategy>{
        JoinWithPredicateStrategy(predicate1),
        JoinWithPredicateStrategy(predicate2),
        JoinWithPredicateStrategy(predicate3),
        JoinWithPredicateStrategy(predicate4),
        JoinWithPredicateStrategy(predicate5),
        JoinWithPredicateStrategy(predicate6),
        JoinWithPredicateStrategy(predicate7),
        JoinWithPredicateStrategy(predicate8)
    };

    for (int i = 0; i < 10; i++) {
        // Randomize the order of strategies
        std::shuffle(strategies.begin(), strategies.end(), std::mt19937(std::random_device()()));
        for (auto& strategy : strategies) {
            strategy.execute(context);
        }


        auto resultTable1 = context.getTableForSynonym(*stmtSyn1Ptr);
        auto resultTable2 = context.getTableForSynonym(*stmtSyn3Ptr);
        auto resultTable3 = context.getTableForSynonym(*stmtSyn4Ptr);
        REQUIRE(resultTable1 != nullptr);
        REQUIRE(resultTable2 != nullptr);
        REQUIRE(resultTable3 != nullptr);

        auto table1Rows = resultTable1->toStrings();
        auto table2Rows = resultTable2->toStrings();
        auto table3Rows = resultTable3->toStrings();
        REQUIRE(table1Rows.size() == 108);
        REQUIRE(table2Rows.size() == 32);
        REQUIRE(table3Rows.size() == 20);
        // print current order of strategies
//        for (auto& strategy : strategies) {
//            std::cout << strategy.toString() << std::endl;
//        }
    }


}

// ai-gen-end