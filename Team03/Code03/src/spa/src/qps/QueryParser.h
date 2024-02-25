//
// Created by ZHENGTAO JIANG on 6/2/24.
//

#ifndef QUERYPARSER_H
#define QUERYPARSER_H

#include "common/EntityType.h"
#include "qps/entity/query/Query.h"

class QueryParser {
  public:
    QueryParser();
    ~QueryParser();

    std::shared_ptr<Query> parse(std::vector<std::vector<std::vector<std::string>>> tokens);
};

#endif // QUERYPARSER_H
