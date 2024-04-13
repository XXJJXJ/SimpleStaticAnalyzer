//
// Created by ZHENGTAO JIANG on 8/2/24.
//

#ifndef SPA_STRATEGY_H
#define SPA_STRATEGY_H


#include "qps/entity/evaluation/QueryEvaluationContext.h"

class Strategy {
public:
    virtual void execute(QueryEvaluationContext &context) = 0;
};



#endif //SPA_STRATEGY_H
