//
// Created by ZHENGTAO JIANG on 6/2/24.
//

#ifndef SPA_PARSER_H
#define SPA_PARSER_H
#include "PKB.h"
#include "common/EntityType.h"
#include "qps/entity/query/Query.h"

class QueryParser {
public:
    QueryParser();
    ~QueryParser();

    EntityType convertStringToEntityType(std::string entity);
    std::shared_ptr<Query> parse(std::vector<std::vector<std::vector<std::string>>> tokens);
};


#endif //SPA_PARSER_H
