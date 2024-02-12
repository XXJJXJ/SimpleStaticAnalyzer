//
// Created by ZHENGTAO JIANG on 8/2/24.
//

#ifndef SPA_QUERY_H
#define SPA_QUERY_H

#include "Declaration.h"
#include "Synonym.h"
//#include "Clauses.h"


#include "qps/entity/strategy/Strategy.h"
#include "qps/entity/strategy/DeclarationStrategy.h"
#include "Synonym.h"
#include "qps/entity/clause/Clause.h"
#include <vector>
#include <memory>


class Query {

public:
    [[nodiscard]] vector<shared_ptr<Strategy>> getStrategies() const;
private:
    vector<shared_ptr<Synonym>> synonyms;  // declared synonyms
    vector<shared_ptr<Clause>> clauses;

};


#endif //SPA_QUERY_H
