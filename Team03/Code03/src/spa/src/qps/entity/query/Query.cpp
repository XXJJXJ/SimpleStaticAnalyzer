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

vector<shared_ptr<Synonym>> Query::getSelectedSynonyms() const {
    vector<shared_ptr<Synonym>> synonyms;

    std::transform(selections.begin(), selections.end(), std::back_inserter(synonyms), [](const std::shared_ptr<AttrRef>& attrRef) {
        return attrRef->getSynonym();
        });

    return synonyms;
}

vector<shared_ptr<Synonym>> Query::getDeclarations() const {
    return declarations;
}

vector<shared_ptr<AttributeExtractor>> Query::getSelectedAttributes() const {
    vector<shared_ptr<AttributeExtractor>> selectedAttributes;
    selectedAttributes.reserve(selections.size());
    for (const auto& attrRef : selections) {
        selectedAttributes.push_back(attrRef->getExtractor());
    }
    return selectedAttributes;
}

