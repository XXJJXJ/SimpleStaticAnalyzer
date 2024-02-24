/*
 * Created by ZHENGTAO JIANG on 8/2/24.
 *
 * Users submit queries to the qps using the processQuery() method,
 * Returns a string response with requested data, depending on synonyms and clauses in the query.
 *
 */

#ifndef QPSMANAGER_H
#define QPSMANAGER_H

#include "qps/entity/query/Query.h"
#include <string>
#include <vector>

class QpsManager {
  public:
    QpsManager();
    ~QpsManager();
    std::vector<std::string> processQuery(std::string query);

  private:
    std::vector<std::vector<std::vector<std::string>>> tokenizeQuery(const std::string& query);
    std::shared_ptr<Query> parseQuery(std::vector<std::vector<std::vector<std::string>>> tokens);
    vector<std::string> evaluateQuery(const std::shared_ptr<Query> validatedQuery);
    void writeResults(const std::vector<std::string>& results, const std::string& outputFile);
};
#endif // QPSMANAGER_H
