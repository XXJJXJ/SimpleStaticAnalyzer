//
// Created by ZHENGTAO JIANG on 8/2/24.
//

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

#include "qps/entity/strategy/Strategy.h"
#include "qps/entity/strategy/DeclarationStrategy.h"
#include "qps/entity/strategy/ProjectionStrategy.h"
#include "Synonym.h"
#include "qps/entity/clause/Clause.h"
#include <vector>
#include <memory>


class Query {
public:
    [[nodiscard]] vector<shared_ptr<Strategy>> getStrategies() const;

    //constructor for a Query Object
    Query (vector<shared_ptr<Synonym>> declarations, vector<shared_ptr<Synonym>>
        selections, vector<shared_ptr<ClauseObject>> clauses) {
        this->declarations = declarations;
        this->selections = selections;
        this->clauses = clauses;
    }
    vector<shared_ptr<Synonym>> declarations;  // declared synonyms
    vector<shared_ptr<Synonym>> selections;  // selected synonym
    vector<shared_ptr<ClauseObject>> clauses;

};


#endif //SPA_QUERY_H
