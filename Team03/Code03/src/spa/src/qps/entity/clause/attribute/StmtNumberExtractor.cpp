#include "StmtNumberExtractor.h"

AttributeValue StmtNumberExtractor::extract(const Entity &entity) const {
    const auto *statement = dynamic_cast<const Statement *>(&entity);
    if (statement) {
        return {statement->getStatementNumber()};
    } else {
        throw QPSEvaluationException("StmtNumberExtractor::extract called with non-Statement entity");
    }
}
