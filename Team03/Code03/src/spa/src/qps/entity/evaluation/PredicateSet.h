#pragma once
#include <unordered_set>
#include <memory>
#include "qps/entity/clause/AffectsPredicate.h"
#include "qps/entity/clause/AssignPatternPredicate.h"
#include "qps/entity/clause/CallsPredicate.h"
#include "qps/entity/clause/CallsTPredicate.h"
#include "qps/entity/clause/FollowsPredicate.h"
#include "qps/entity/clause/FollowsTPredicate.h"
#include "qps/entity/clause/IfPatternPredicate.h"
#include "qps/entity/clause/ModifiesPredicate.h"
#include "qps/entity/clause/NextPredicate.h"
#include "qps/entity/clause/NextTPredicate.h"
#include "qps/entity/clause/NotPredicate.h"
#include "qps/entity/clause/ParentPredicate.h"
#include "qps/entity/clause/ParentTPredicate.h"
#include "qps/entity/clause/UsesPredicate.h"
#include "qps/entity/clause/WhilePatternPredicate.h"
#include "qps/entity/clause/WithPredicate.h"
#ifndef SPA_PREDICATESET_H
#define SPA_PREDICATESET_H

using namespace std;

class PredicateSet {
private:
    unordered_set<shared_ptr<AffectsPredicate>> affects;
    unordered_set<shared_ptr<AssignPatternPredicate>> assignPat;
    unordered_set<shared_ptr<CallsPredicate>> calls;
    unordered_set<shared_ptr<CallsTPredicate>> callsT;
    unordered_set<shared_ptr<FollowsPredicate>> follows;
    unordered_set<shared_ptr<FollowsTPredicate>> followsT;
    unordered_set<shared_ptr<IfPatternPredicate>> ifPat;
    unordered_set<shared_ptr<ModifiesPredicate>> modifies;
    unordered_set<shared_ptr<NextPredicate>> next;
    unordered_set<shared_ptr<NextTPredicate>> nextT;
    unordered_set<shared_ptr<NotPredicate>> notPreds;
    unordered_set<shared_ptr<ParentPredicate>> parent;
    unordered_set<shared_ptr<ParentTPredicate>> parentT;
    unordered_set<shared_ptr<UsesPredicate>> uses;
    unordered_set<shared_ptr<WhilePatternPredicate>> whilePat;
    unordered_set<shared_ptr<WithPredicate>> with;
public:
    PredicateSet() = default;
    void add(shared_ptr<Predicate> pred);
    vector<shared_ptr<Predicate>> getUniquePredicates();
};

#endif //SPA_PREDICATESET_H
