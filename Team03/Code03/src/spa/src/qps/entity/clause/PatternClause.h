//
// Created by ZHENGTAO JIANG on 8/2/24.
//

#include "Clause.h"

#ifndef SPA_PATTERNCLAUSE_H
#define SPA_PATTERNCLAUSE_H


class PatternClause : public Clause {
public:
    PatternClause() = default;
    std::vector<std::shared_ptr<Strategy>> getStrategies() const override;
};

#endif //SPA_PATTERNCLAUSE_H
