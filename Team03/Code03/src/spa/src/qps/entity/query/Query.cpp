#include "Query.h"

#include <utility>
#include <algorithm>

vector<shared_ptr<Predicate>> Query::getPredicates() const {
    return predicates;
}

Query::Query(vector<shared_ptr<Synonym>> declarations, vector<shared_ptr<AttrRef>> selections,
             vector<shared_ptr<Predicate>> predicates) {
    this->declarations = std::move(declarations);
    this->selections = std::move(selections);
    this->predicates = std::move(predicates);
}

// TODO: uncomment when evaluation refactoring done
//vector<shared_ptr<AttrRef>> Query::getSelections() const {
//    return selections;
//}

// TEMP: to convert AttrRef back to Synonym for evaluator, until evaluator refactors to use AttrRef for selections instead
vector<shared_ptr<Synonym>> Query::getSelections() const {
    vector<shared_ptr<Synonym>> synonyms;

    std::transform(selections.begin(), selections.end(), std::back_inserter(synonyms), [](const std::shared_ptr<AttrRef>& attrRef) {
        return attrRef.get()->getSynonym();
        });

    return synonyms;
}

vector<shared_ptr<Synonym>> Query::getDeclarations() const {
    return declarations;
}

