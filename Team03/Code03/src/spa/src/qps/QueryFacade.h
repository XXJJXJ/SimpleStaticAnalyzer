/*
* Created by ZHENGTAO JIANG on 8/2/24.
* 
* Users submit queries to the QPS using the evaluateQuery() method,
* Returns a string response with requested data:
* Statement Numbers e.g 1,3,5,6
* Variables e.g a,b,c,v
* 
*/

#ifndef SPA_QUERYFACADE_H
#define SPA_QUERYFACADE_H

#include <string>
#include <vector>
#include "qps/entity/query/Query.h"


class QueryFacade {
public:
    QueryFacade();
    ~QueryFacade();
    std::vector<std::string> processQuery(std::string query);

    std::vector<std::vector<std::vector<std::string>>> tokenizeQuery(const std::string& query);
    std::shared_ptr<Query> parseQuery(std::vector<std::vector<std::vector<std::string>>> tokens);
    vector<std::string> evaluateQuery(const std::shared_ptr<Query> validatedQuery);
    void writeResults(const std::vector<std::string>& results, const std::string& outputFile);
};
#endif //SPA_QUERYFACADE_H
