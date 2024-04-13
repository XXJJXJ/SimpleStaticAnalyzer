#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "BaseTable.h"
#include "qps/entity/clause/PredicateUtils.h"
#ifndef SPA_PREDICATERESULTCACHE_H
#define SPA_PREDICATERESULTCACHE_H

class PredicateResultCache {
private:
    std::unordered_map<PredicateType, std::shared_ptr<BaseTable>, PredicateTypeHash> cache;
    const std::unordered_set<PredicateType> unCacheableTypes =
        {PredicateType::Not, PredicateType::Invalid, PredicateType::Unknown, PredicateType::AssignPattern,
         PredicateType::Pattern, PredicateType::With};

public:
    void storeResult(PredicateType predicateType, std::shared_ptr<BaseTable> table);
    std::shared_ptr<BaseTable> getResult(PredicateType predicateType);
    [[nodiscard]] bool hasResult(PredicateType predicateType) const;
};

#endif //SPA_PREDICATERESULTCACHE_H
