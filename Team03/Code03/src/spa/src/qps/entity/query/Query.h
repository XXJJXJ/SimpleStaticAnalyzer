//
// Created by ZHENGTAO JIANG on 8/2/24.
//

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

#include "qps/entity/strategy/Strategy.h"
#include "qps/entity/strategy/DeclarationStrategy.h"
#include "Synonym.h"
#include "qps/entity/clause/Clause.h"
#include <vector>
#include <memory>


class Query {
private:
    vector<shared_ptr<Synonym>> synonyms;  // declared synonyms
    vector<shared_ptr<Clause>> clauses;
public:
    [[nodiscard]] vector<shared_ptr<Strategy>> getStrategies() const;

    //constructor for a Query Object
    Query (vector<shared_ptr<Synonym>> s, vector<shared_ptr<Clause>> c) {
        this->synonyms = s;
        this->clauses = c;
    }
};


#endif //SPA_QUERY_H
