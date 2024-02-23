#include "Query.h"

#include <utility>

vector<shared_ptr<Predicate>> Query::getPredicates() const {
    return predicates;
}

Query::Query(vector<shared_ptr<Synonym>> declarations, vector<shared_ptr<Synonym>> selections,
             vector<shared_ptr<Predicate>> predicates) {
    this->declarations = std::move(declarations);
    this->selections = std::move(selections);
    this->predicates = std::move(predicates);
}

