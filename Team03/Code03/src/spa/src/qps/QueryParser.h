//
// Created by ZHENGTAO JIANG on 6/2/24.
//

#ifndef SPA_PARSER_H
#define SPA_PARSER_H
#include "PKB.h"


class QueryParser {
public:
    QueryParser();

    ~QueryParser();

    std::string parse(const std::string& query);
};


#endif //SPA_PARSER_H
