#ifndef QPSMANAGER_H
#define QPSMANAGER_H

#include <string>
#include <vector>

#include "QueryEvaluator.h"
#include "QueryParser.h"
#include "QueryTokenizer.h"
#include "QueryValidator.h"
#include "qps/entity/query/Query.h"
#include "qps/entity/evaluation/EvaluationPlanner.h"
#include "common/spa_exception/SyntaxErrorException.h"
#include "common/spa_exception/SemanticErrorException.h"

class QpsManager {
public:
    QpsManager();
    ~QpsManager();
    std::vector<std::string> processQuery(const std::string &query);

private:
    std::vector<std::string> tokenizeQuery(const std::string &query);
    std::vector<std::vector<std::vector<std::string>>> validateQuery(std::vector<std::string> tokens);
    std::shared_ptr<Query> parseQuery(std::vector<std::vector<std::vector<std::string>>> tokens);
    vector<std::string> evaluateQuery(const std::shared_ptr<Query> validatedQuery);
    void writeResults(const std::vector<std::string> &results, const std::string &outputFile);
};
#endif // QPSMANAGER_H
