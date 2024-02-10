//
// Created by ZHENGTAO JIANG on 8/2/24.
//

#ifndef SPA_QUERY_H
#define SPA_QUERY_H


#include "qps/entity/strategy/Strategy.h"
#include "Declaration.h"
#include "Synonym.h"
#include "qps/entity/clause/Clause.h"
#include <vector>
#include <memory>


class Query {
public:
    std::vector<Strategy> getStrategies();
private:
    std::vector<Declaration> declarations;
    std::vector<Synonym> synonyms;
    std::vector<Clause> clauses;

};


#endif //SPA_QUERY_H
