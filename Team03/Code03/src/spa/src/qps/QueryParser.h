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

    static std::pair<std::vector<std::vector<std::string>>, std::vector<std::string>> tokenizeString(const std::string& query);
    std::string removeSemiColon(std::string token);
    EntityType convertStringToEntityType(std::string entity);
    std::shared_ptr<Query> parse(const std::string& query);

};


#endif //SPA_PARSER_H
