#include "PredicateResultCache.h"

#include <utility>

void PredicateResultCache::storeResult(PredicateType predicateType, std::shared_ptr<BaseTable> table) {
    if (unCacheableTypes.find(predicateType) == unCacheableTypes.end()) {
        cache[predicateType] = std::move(table);
    }
}

std::shared_ptr<BaseTable> PredicateResultCache::getResult(PredicateType predicateType) {
    if (hasResult(predicateType)) {
        return cache[predicateType];
    } else {
        throw QPSEvaluationException("PredicateResultCache does not have result for predicate type");
    }
}

bool PredicateResultCache::hasResult(PredicateType predicateType) const {
    return cache.find(predicateType) != cache.end();
}
