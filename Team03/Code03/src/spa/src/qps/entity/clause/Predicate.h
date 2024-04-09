// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/649c7ba0-9712-44e7-aa24-ca6262c5a922
#ifndef RELATIONSHIPPREDICATE_H
#define RELATIONSHIPPREDICATE_H

#include <string>
#include <variant>
#include "qps/entity/strategy/Strategy.h"
#include "common/spa_exception/SemanticErrorException.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "qps/entity/clause/cellFilter/CellFilter.h"
#include "qps/entity/clause/cellFilter/RowFilter.h"
#include "qps/entity/clause/cellFilter/filterUtils.h"
#include "qps/entity/evaluation/TableFactory.h"
#include "qps/entity/clause/PredicateUtils.h"
#include "attribute/Ref.h"



/**
 * Base class for all filtering conditions in a query, including relationship, pattern and with
 * clauses. Each predicate has a corresponding strategy that is used to filter the results of the
 * query.
 */
class Predicate {
protected:
    vector<shared_ptr<Synonym>> synonyms; // Synonyms used in the predicate
    // TODO: it's possible to keep rowFilters only, but idc already
    vector<shared_ptr<CellFilter>> cellFilters; // Cell filters that are used to filter the rows in result table
    vector<shared_ptr<RowFilter>> rowFilters; // Row filters that are used to filter the rows in result table
    vector<bool> projectionFilter; // Filter to determine which columns to keep in the result table
    virtual std::shared_ptr<BaseTable> getFullTable(QueryManager& qm); // Gets the full table for the predicate
    void addRowFilter(RowFilter &rowFilter);
    void addStmtRef(StatementRef &stmtRef);
    void addEntityRef(EntityRef& entityRef);
    void addProcAndStmtRef(ProcAndStmtRef &procAndStmtRef);
    void addRef(Ref &ref);
    bool isValidRow(const vector<shared_ptr<Entity>>& row) const;
public:
    virtual ~Predicate() = default; // Ensure proper polymorphic deletion
    [[nodiscard]] vector<shared_ptr<Synonym>> getSynonyms() const { return synonyms; }
    [[nodiscard]] virtual shared_ptr<BaseTable> getResultTable(QueryEvaluationContext &qec);
    [[nodiscard]] virtual PredicateType getType() const;
};

#endif // RELATIONSHIPPREDICATE_H
// ai-gen end