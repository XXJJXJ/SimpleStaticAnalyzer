#include "catch.hpp"
#include "FakeQueryManager.cpp" // Use the FakeQueryManager class
#include "qps/entity/evaluation/QueryEvaluationContext.h"
#include "qps/entity/strategy/DeclarationStrategy.h"
#include "qps/entity/query/Synonym.h"

// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/5a9de667-07bb-4d68-86ec-9b4e16053517

TEST_CASE("DeclarationStrategy processes synonyms and updates context with SynonymValues", "[DeclarationStrategy]") {
    auto queryManager = std::make_shared<FakeQueryManager>();
    QueryEvaluationContext context = QueryEvaluationContext();
    context.setQueryManager(queryManager);

    // Setup fake responses in FakeQueryManager
    std::vector<std::shared_ptr<Procedure>> fakeProcedures = {std::make_shared<Procedure>("Main"), std::make_shared<Procedure>("Helper")};
    std::vector<std::shared_ptr<Variable>> fakeVariables = {std::make_shared<Variable>("x"), std::make_shared<Variable>("y")};
    queryManager->addFakeResponse("Procedure", fakeProcedures);
    queryManager->addFakeResponse("Variable", fakeVariables);

    // Synonyms setup
    auto procSynonym = std::make_shared<Synonym>(EntityType::Procedure, "p");
    auto varSynonym = std::make_shared<Synonym>(EntityType::Variable, "v");
    std::vector<std::shared_ptr<Synonym>> synonyms = {procSynonym, varSynonym};

    // DeclarationStrategy execution
    DeclarationStrategy strategy(synonyms);
    strategy.execute(context);

    // Assertions
    SECTION("Context should contain SynonymValues for each synonym") {
        REQUIRE(context.containsSynonym(*procSynonym));
        REQUIRE(context.containsSynonym(*varSynonym));
    }

    SECTION("SynonymValues should contain correct entities") {
        auto procSynonymValues = context.getSynonymValues(*procSynonym);
        auto expectedSynonymValues = SynonymValues(procSynonym);
        expectedSynonymValues.addValue(fakeProcedures[0]);
        expectedSynonymValues.addValue(fakeProcedures[1]);


        auto varSynonymValues = context.getSynonymValues(*varSynonym);
        auto expectedVarSynonymValues = SynonymValues(varSynonym);
        expectedVarSynonymValues.addValue(fakeVariables[0]);
        expectedVarSynonymValues.addValue(fakeVariables[1]);

        REQUIRE(procSynonymValues == expectedSynonymValues);
        REQUIRE(varSynonymValues == expectedVarSynonymValues);
    }
}


TEST_CASE("DeclarationStrategy Comprehensive Tests", "[DeclarationStrategy]") {
    auto queryManager = std::make_shared<FakeQueryManager>();
    QueryEvaluationContext context;
    context.setQueryManager(queryManager);

    SECTION("No declared synonyms") {
        std::vector<std::shared_ptr<Synonym>> synonyms = {}; // Explicitly declared empty vector

        DeclarationStrategy strategy(synonyms);
        strategy.execute(context);

        REQUIRE(context.getSynonyms().empty());
    }

    SECTION("Declared synonyms but no entities returned") {
        std::vector<std::shared_ptr<Procedure>> emptyProcedures; // Explicitly declare empty vector
        std::vector<std::shared_ptr<Variable>> emptyVariables; // Explicitly declare empty vector
        queryManager->addFakeResponse("Procedure", emptyProcedures);
        queryManager->addFakeResponse("Variable", emptyVariables);

        auto procSynonym = std::make_shared<Synonym>(EntityType::Procedure, "p");
        auto varSynonym = std::make_shared<Synonym>(EntityType::Variable, "v");
        std::vector<std::shared_ptr<Synonym>> synonyms = {procSynonym, varSynonym};

        DeclarationStrategy strategy(synonyms);
        strategy.execute(context);

        REQUIRE(context.getSynonymValues(*procSynonym).getValues().empty());
        REQUIRE(context.getSynonymValues(*varSynonym).getValues().empty());
    }

    SECTION("Mixed entity availability for declared synonyms") {
        std::vector<std::shared_ptr<Procedure>> proceduresWithEntities = {std::make_shared<Procedure>("Main")}; // Procedures with entities
        std::vector<std::shared_ptr<Variable>> emptyVariables; // Explicitly declare empty vector for Variables
        queryManager->addFakeResponse("Procedure", proceduresWithEntities);
        queryManager->addFakeResponse("Variable", emptyVariables);

        auto procSynonym = std::make_shared<Synonym>(EntityType::Procedure, "p");
        auto varSynonym = std::make_shared<Synonym>(EntityType::Variable, "v");
        std::vector<std::shared_ptr<Synonym>> synonyms = {procSynonym, varSynonym};

        DeclarationStrategy strategy(synonyms);
        strategy.execute(context);

        REQUIRE(context.getSynonymValues(*procSynonym).getValues().size() == 1);
        REQUIRE(context.getSynonymValues(*varSynonym).getValues().empty());
    }

    SECTION("All declared synonyms with entities returned") {
        std::vector<std::shared_ptr<Procedure>> proceduresWithEntities = {std::make_shared<Procedure>("Main"), std::make_shared<Procedure>("Helper")};
        std::vector<std::shared_ptr<Variable>> variablesWithEntities = {std::make_shared<Variable>("x"), std::make_shared<Variable>("y")};
        queryManager->addFakeResponse("Procedure", proceduresWithEntities);
        queryManager->addFakeResponse("Variable", variablesWithEntities);

        auto procSynonym = std::make_shared<Synonym>(EntityType::Procedure, "p");
        auto varSynonym = std::make_shared<Synonym>(EntityType::Variable, "v");
        std::vector<std::shared_ptr<Synonym>> synonyms = {procSynonym, varSynonym};

        DeclarationStrategy strategy(synonyms);
        strategy.execute(context);

        REQUIRE(context.containsSynonym(*procSynonym));
        REQUIRE(context.containsSynonym(*varSynonym));
        REQUIRE(context.getSynonymValues(*procSynonym).getValues().size() == 2);
        REQUIRE(context.getSynonymValues(*varSynonym).getValues().size() == 2);
    }
}

// ai-gen end