//
// Created by ZHENGTAO JIANG on 8/2/24.
//

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

#include "Synonym.h"
#include "qps/entity/clause/Predicate.h"
#include "qps/entity/clause/attribute/AttrRef.h"
#include <vector>
#include <memory>

class Query {
public:

    Query(
        vector<shared_ptr<Synonym>> declarations,
        vector<shared_ptr<AttrRef>> selections,
        vector<shared_ptr<Predicate>> predicates);

    vector<shared_ptr<Synonym>> declarations;  // declared synonyms
    vector<shared_ptr<AttrRef>> selections;  // selected synonym
    vector<shared_ptr<Predicate>> predicates;
    vector<shared_ptr<Predicate>> getPredicates() const;
    vector<shared_ptr<AttributeExtractor>> getSelectedAttributes() const;
    vector<shared_ptr<Synonym>> getSelectedSynonyms() const;
    vector<shared_ptr<Synonym>> getDeclarations() const;
};

#endif //SPA_QUERY_H
