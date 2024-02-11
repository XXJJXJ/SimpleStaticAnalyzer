//#include "catch.hpp"
//#include "FakeQueryManager.h" // Use the FakeQueryManager class
//#include "qps/entity/evaluation/QueryEvaluationContext.h"
//#include "qps/entity/strategy/DeclarationStrategy.h"
//#include "qps/entity/query/Synonym.h"
//
//TEST_CASE("DeclarationStrategy Execution Scenarios") {
//    // Create and setup FakeQueryManager
//    auto queryManager = std::make_shared<FakeQueryManager>();
//    QueryEvaluationContext context;
//    context.setQueryManager(queryManager);
//
//    SECTION("No synonyms") {
//        std::vector<std::shared_ptr<Synonym>> synonyms = {};
//        DeclarationStrategy strategy(synonyms);
//        strategy.execute(context);
//
//        // Assertions...
//    }
//
//    SECTION("One synonym, no entities") {
//        auto synonym = std::make_shared<Synonym>(EntityType::Type1, "S1");
//        std::vector<std::shared_ptr<Synonym>> synonyms = {synonym};
//        DeclarationStrategy strategy(synonyms);
//
//        // Setup FakeQueryManager with no entities for this synonym
//        queryManager->addFakeResponse(EntityType::Type1, {});
//
//        strategy.execute(context);
//
//        // Assertions...
//    }
//
//    SECTION("One synonym, multiple entities") {
//        auto synonym = std::make_shared<Synonym>(EntityType::Type2, "S2");
//        std::vector<std::shared_ptr<Synonym>> synonyms = {synonym};
//        DeclarationStrategy strategy(synonyms);
//
//        // Setup FakeQueryManager with multiple entities for this synonym
//        std::vector<std::shared_ptr<Entity>> entities = {/* Entities setup */};
//        queryManager->addFakeResponse(EntityType::Type2, entities);
//
//        strategy.execute(context);
//
//        // Assertions...
//    }
//
//    // More sections for other scenarios...
//}
