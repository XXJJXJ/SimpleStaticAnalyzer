#include <catch.hpp>

#include "common/Entity.h"
#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/SynonymValues.h"
#include "qps/entity/evaluation/QueryEvaluationContext.h"
#include <memory>

// MockEntity inheriting from Entity for test purposes
class MockEntity : public Entity {
    std::string name;
public:
    explicit MockEntity(const std::string& name) : name(name) {}
    std::string getName() const override { return name; } // Assuming Entity has getName()
    void accept(shared_ptr<Visitor> visitor) override {}
};

TEST_CASE("QueryEvaluationContext::resultToString throws when multiple SynonymValues are present", "[QueryEvaluationContext]") {
    QueryEvaluationContext qec;

    auto synonym1 = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    SynonymValues sv1(synonym1);
    sv1.addValue(std::make_shared<MockEntity>("value1"));

    auto synonym2 = std::make_shared<Synonym>(EntityType::Stmt, "s2");
    SynonymValues sv2(synonym2);
    sv2.addValue(std::make_shared<MockEntity>("value2"));

    qec.addSynonymValues(sv1);
    qec.addSynonymValues(sv2);

    REQUIRE_THROWS_AS(qec.resultToString(), std::runtime_error);
}

TEST_CASE("QueryEvaluationContext::resultToString throws when no SynonymValues are present", "[QueryEvaluationContext]") {
    QueryEvaluationContext qec;

    REQUIRE_THROWS_AS(qec.resultToString(), std::runtime_error);
}

TEST_CASE("QueryEvaluationContext::resultToString returns empty string for empty SynonymValues", "[QueryEvaluationContext]") {
    auto synonym = std::make_shared<Synonym>(EntityType::Stmt, "s");
    SynonymValues sv(synonym);

    QueryEvaluationContext qec;
    qec.addSynonymValues(sv);

    std::string result = qec.resultToString();
    REQUIRE(result.empty());
}
TEST_CASE("QueryEvaluationContext::resultToString handles special characters in entity names", "[QueryEvaluationContext]") {
    auto synonym = std::make_shared<Synonym>(EntityType::Stmt, "s");
    SynonymValues sv(synonym);
    sv.addValue(std::make_shared<MockEntity>("$1"));
    sv.addValue(std::make_shared<MockEntity>("value#2"));
    sv.addValue(std::make_shared<MockEntity>("value, 3"));

    QueryEvaluationContext qec;
    qec.addSynonymValues(sv);

    std::string result = qec.resultToString();
    REQUIRE(result == "$1, value#2, value, 3");
}
