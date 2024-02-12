//
// Created by ZHENGTAO JIANG on 8/2/24.
//

#ifndef SPA_PROJECTIONSTRATEGY_H
#define SPA_PROJECTIONSTRATEGY_H


#include "Strategy.h"

class ProjectionStrategy : public Strategy {
public:
    void execute(QueryEvaluationContext &context) override;
};



#endif //SPA_PROJECTIONSTRATEGY_H
