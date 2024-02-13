// ai-gen start(gpt, 0, e)
#include "catch.hpp"
#include "FakeQueryManager.cpp"
#include "qps/entity/evaluation/QueryEvaluationContext.h"
#include "qps/entity/strategy/ProjectionStrategy.h"
#include "qps/entity/query/Synonym.h"

TEST_CASE("ProjectionStrategy updates context with only targeted SynonymValues", "[ProjectionStrategy]") {
    auto queryManager = std::make_shared<FakeQueryManager>();
    QueryEvaluationContext context;
    context.setQueryManager(queryManager);

    // Setup fake entities for testing
    auto targetSynonym = std::make_shared<Synonym>(EntityType::Variable, "v");
    auto otherSynonym = std::make_shared<Synonym>(EntityType::Procedure, "p");
    auto targetEntity = std::make_shared<Variable>("x");
    auto otherEntity = std::make_shared<Procedure>("Main");

    // Setup initial SynonymValues in context
    SynonymValues targetSynonymValues(targetSynonym);
    targetSynonymValues.addValue(targetEntity);
    context.addSynonymValues(targetSynonymValues);

    SynonymValues otherSynonymValues(otherSynonym);
    otherSynonymValues.addValue(otherEntity);
    context.addSynonymValues(otherSynonymValues);

    // Execute ProjectionStrategy targeting "v"
    ProjectionStrategy strategy(targetSynonym);
    strategy.execute(context);

    SECTION("Context should only contain SynonymValues for targeted synonym 'v'") {
        REQUIRE(context.containsSynonym(*targetSynonym));
        REQUIRE_FALSE(context.containsSynonym(*otherSynonym));
    }

    SECTION("Targeted SynonymValues should remain intact") {
        auto resultingSynonymValues = context.getSynonymValues(*targetSynonym);
        REQUIRE(resultingSynonymValues.getValues().size() == 1);
        REQUIRE(*(resultingSynonymValues.getValues().front()) == *targetEntity);
    }
}

TEST_CASE("ProjectionStrategy with non-existing target synonym does not alter context", "[ProjectionStrategy]") {
    auto queryManager = std::make_shared<FakeQueryManager>();
    QueryEvaluationContext context;
    context.setQueryManager(queryManager);

    // Setup a Synonym and SynonymValues that are not targeted
    auto nonTargetSynonym = std::make_shared<Synonym>(EntityType::Procedure, "p");
    auto nonTargetEntity = std::make_shared<Procedure>("Main");
    SynonymValues nonTargetSynonymValues(nonTargetSynonym);
    nonTargetSynonymValues.addValue(nonTargetEntity);
    context.addSynonymValues(nonTargetSynonymValues);

    // Execute ProjectionStrategy with a synonym that does not exist in context
    auto nonexistentSynonym = std::make_shared<Synonym>(EntityType::Variable, "v");
    ProjectionStrategy strategy(nonexistentSynonym);
    strategy.execute(context);

    SECTION("Context should remain unchanged when targeted synonym does not exist") {
        REQUIRE(context.containsSynonym(*nonTargetSynonym));
        REQUIRE(context.getSynonymValues(*nonTargetSynonym).getValues().size() == 1);
        REQUIRE(*(context.getSynonymValues(*nonTargetSynonym).getValues().front()) == *nonTargetEntity);
    }
}

// ai-gen end