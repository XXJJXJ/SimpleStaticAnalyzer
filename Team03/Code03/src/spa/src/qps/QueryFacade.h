/*
* Created by ZHENGTAO JIANG on 8/2/24.
* 
* Users submit queries to the QPS using the evaluateQuery() method,
* Returns a string response with requested data:
* Statement Numbers e.g 1,3,5,6
* Variables e.g a,b,c,v
*/

#ifndef SPA_QUERYFACADE_H
#define SPA_QUERYFACADE_H

#include <string>
#include <vector>

class QueryFacade {
public:
    QueryFacade();
    ~QueryFacade();
    void processQueries(const std::string& inputFile, const std::string& outputFile);

private:
    std::string parseQuery(const std::string& query);
    bool validateQuery(const std::string& parsedQuery);
    std::string evaluateQuery(const std::string& validatedQuery);
    void writeResults(const std::vector<std::string>& results, const std::string& outputFile);
};
#endif //SPA_QUERYFACADE_H