#include <memory>
#include <vector>
#include "qps/entity/clause//Predicate.h"
#include "qps/entity/evaluation/BooleanTable.h"
#include "qps/entity/evaluation/HeaderTable.h"
#include "pkb/QueryPKB.h"

class MockBooleanPredicate : public Predicate {
private:
    bool returnValue;
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override {
        return std::make_shared<HeaderTable>(); // unused
    }

public:
    explicit MockBooleanPredicate(bool returnValue) : returnValue(returnValue) {}


    [[nodiscard]] shared_ptr<BaseTable> getResultTable(QueryEvaluationContext &qec) override {
        // Here we simulate returning a BooleanTable based on the specified return value
        return std::make_shared<BooleanTable>(returnValue);
    }

};

class MockTablePredicate : public Predicate {
private:
    std::shared_ptr<HeaderTable> tableToReturn;
protected:
    std::shared_ptr<BaseTable> getFullTable(QueryManager& qm) override {
        // unused
        return std::make_shared<HeaderTable>();
    }

public:
    explicit MockTablePredicate(std::shared_ptr<HeaderTable> tableToReturn) : tableToReturn(std::move(tableToReturn)) {}


    [[nodiscard]] shared_ptr<BaseTable> getResultTable(QueryEvaluationContext &qec) override {
        // Directly return the predefined HeaderTable
        return tableToReturn;
    }
};
