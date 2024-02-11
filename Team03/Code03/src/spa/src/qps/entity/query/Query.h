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
public:
    std::vector<shared_ptr<Strategy>> getStrategies() const;
    vector<shared_ptr<DeclarationStrategy>> getDeclarationStrategies() const;
private:
    std::vector<shared_ptr<Synonym>> synonyms;  // declared synonyms
    std::vector<shared_ptr<Clause>> clauses;

};


#endif //SPA_QUERY_H
