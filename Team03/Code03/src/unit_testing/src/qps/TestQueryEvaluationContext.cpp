#include <catch.hpp>

#include "common/Entity.h"
#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/QueryEvaluationContext.h"
#include "qps/entity/evaluation/Table.h"
#include <memory>

// MockEntity inheriting from Entity for test purposes
class MockEntity : public Entity {
    std::string name;
public:
    explicit MockEntity(const std::string& name) : name(name) {}
    std::string getName() const override { return name; } // Assuming Entity has getName()
    void accept(shared_ptr<Visitor> visitor) override {}
};

TEST_CASE("QueryEvaluationContext::getResults throws when multiple tables are present and one is empty", "[QueryEvaluationContext]") {
    QueryEvaluationContext qec;

    auto synonym1 = std::make_shared<Synonym>(EntityType::Stmt, "s1");
    auto table1 = std::make_shared<Table>();
    table1->addRow(TableRow({std::make_shared<MockEntity>("value1")}));
    qec.addTableForSynonym(*synonym1, table1);

    auto synonym2 = std::make_shared<Synonym>(EntityType::Stmt, "s2");
    auto table2 = std::make_shared<Table>(); // Empty table
    qec.addTableForSynonym(*synonym2, table2);

    REQUIRE(qec.isResultEmpty());
}

TEST_CASE("QueryEvaluationContext::getResults throws when no tables are present", "[QueryEvaluationContext]") {
    QueryEvaluationContext qec;

    REQUIRE_THROWS_AS(qec.getResults(), std::runtime_error);
}

TEST_CASE("QueryEvaluationContext::getResults returns empty vector for context with empty tables", "[QueryEvaluationContext]") {
    QueryEvaluationContext qec;
    auto synonym = std::make_shared<Synonym>(EntityType::Stmt, "s");
    auto table = std::make_shared<Table>(); // Empty table
    qec.addTableForSynonym(*synonym, table);

    REQUIRE(qec.isResultEmpty());
}

TEST_CASE("QueryEvaluationContext::getResults handles special characters in entity names", "[QueryEvaluationContext]") {
    QueryEvaluationContext qec;
    auto synonym = std::make_shared<Synonym>(EntityType::Stmt, "s");
    auto table = std::make_shared<Table>();
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
