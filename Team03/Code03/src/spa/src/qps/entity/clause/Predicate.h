// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/649c7ba0-9712-44e7-aa24-ca6262c5a922
#ifndef RELATIONSHIPPREDICATE_H
#define RELATIONSHIPPREDICATE_H

#include <string>
#include <variant>
#include "qps/entity/strategy/Strategy.h"
#include "common/spa_exception/SemanticErrorException.h"
#include "common/spa_exception/QPSEvaluationException.h"
#include "qps/entity/clause/validator/ColumnValidator.h"



/**
 * Base class for all filtering conditions in a query, including relationship, pattern and with
 * clauses. Each predicate has a corresponding strategy that is used to filter the results of the
 * query.
 */
class Predicate {
protected:
    vector<shared_ptr<Synonym>> synonyms; // Synonyms used in the predicate
    vector<shared_ptr<ColumnValidator>> validators; // Validators for columns obtained by predicate
public:
    virtual ~Predicate() = default; // Ensure proper polymorphic deletion
    [[nodiscard]] vector<shared_ptr<Synonym>> getSynonyms() const { return synonyms; }
    [[nodiscard]] virtual shared_ptr<BaseTable> getTable(QueryManager& qm) = 0;
    virtual std::string toString() const;
    virtual bool isValidRow(const vector<shared_ptr<Entity>>& row) const;
};

#endif // RELATIONSHIPPREDICATE_H
// ai-gen end