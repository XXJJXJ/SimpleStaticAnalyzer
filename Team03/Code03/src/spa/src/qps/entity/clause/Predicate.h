// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/649c7ba0-9712-44e7-aa24-ca6262c5a922
#ifndef RELATIONSHIPPREDICATE_H
#define RELATIONSHIPPREDICATE_H

#include <string>
#include <variant>
#include "qps/entity/strategy/Strategy.h"

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;


using StatementRef = std::variant<int, Synonym, std::string>; // stmtRef: synonym | '_' | INTEGER
using EntityRef = std::variant<Synonym, std::string>; // entRef : synonym | '_' | '"' IDENT '"'

/**
 * Base class for all filtering conditions in a query, including relationship, pattern and with
 * clauses. Each predicate has a corresponding strategy that is used to filter the results of the
 * query.
 */
class Predicate {
protected:
    vector<shared_ptr<Synonym>> synonyms; // Synonyms used in the predicate
public:
    virtual ~Predicate() = default; // Ensure proper polymorphic deletion
    virtual shared_ptr<Strategy> getStrategy() const = 0; // Pure virtual function
    [[nodiscard]] vector<shared_ptr<Synonym>> getSynonyms() const { return synonyms; }
    [[nodiscard]] virtual shared_ptr<Table> getTable(const QueryManager& qm) {
        // Temp implementation to get code compiling, TODO: remove and set pure virtual
        return make_shared<Table>();
    };
};

#endif // RELATIONSHIPPREDICATE_H
// ai-gen end