#include "PredicateSet.h"

void PredicateSet::add(shared_ptr<Predicate> pred) {
    switch (pred->getType()) {
    case PredicateType::Affects: {
        affects.insert(dynamic_pointer_cast<AffectsPredicate>(pred));
        break;
    }
    case PredicateType::AssignPattern: {
        assignPat.insert(dynamic_pointer_cast<AssignPatternPredicate>(pred));
        break;
    }
    case PredicateType::Calls: {
        calls.insert(dynamic_pointer_cast<CallsPredicate>(pred));
        break;
    }
    case PredicateType::CallsT: {
        callsT.insert(dynamic_pointer_cast<CallsTPredicate>(pred));
        break;
    }
    case PredicateType::Follows: {
        follows.insert(dynamic_pointer_cast<FollowsPredicate>(pred));
        break;
    }
    case PredicateType::FollowsT: {
        followsT.insert(dynamic_pointer_cast<FollowsTPredicate>(pred));
        break;
    }
    case PredicateType::IfPattern: {
        ifPat.insert(dynamic_pointer_cast<IfPatternPredicate>(pred));
        break;
    }
    case PredicateType::Modifies: {
        modifies.insert(dynamic_pointer_cast<ModifiesPredicate>(pred));
        break;
    }
    case PredicateType::Next: {
        next.insert(dynamic_pointer_cast<NextPredicate>(pred));
        break;
    }
    case PredicateType::NextT: {
        nextT.insert(dynamic_pointer_cast<NextTPredicate>(pred));
        break;
    }
    case PredicateType::Not: {
        notPreds.insert(dynamic_pointer_cast<NotPredicate>(pred));
        break;
    }
    case PredicateType::Parent: {
        parent.insert(dynamic_pointer_cast<ParentPredicate>(pred));
        break;
    }
    case PredicateType::ParentT: {
        parentT.insert(dynamic_pointer_cast<ParentTPredicate>(pred));
        break;
    }
    case PredicateType::Uses: {
        uses.insert(dynamic_pointer_cast<UsesPredicate>(pred));
        break;
    }
    case PredicateType::WhilePattern: {
        whilePat.insert(dynamic_pointer_cast<WhilePatternPredicate>(pred));
        break;
    }
    case PredicateType::With: {
        with.insert(dynamic_pointer_cast<WithPredicate>(pred));
        break;
    }
    }
}


#include <algorithm>

vector<shared_ptr<Predicate>> PredicateSet::getUniquePredicates() {
    vector<shared_ptr<Predicate>> uniquePredicates;
    uniquePredicates.insert(uniquePredicates.end(), affects.begin(), affects.end());
    uniquePredicates.insert(uniquePredicates.end(), assignPat.begin(), assignPat.end());
    uniquePredicates.insert(uniquePredicates.end(), calls.begin(), calls.end());
    uniquePredicates.insert(uniquePredicates.end(), callsT.begin(), callsT.end());
    uniquePredicates.insert(uniquePredicates.end(), follows.begin(), follows.end());
    uniquePredicates.insert(uniquePredicates.end(), followsT.begin(), followsT.end());
    uniquePredicates.insert(uniquePredicates.end(), ifPat.begin(), ifPat.end());
    uniquePredicates.insert(uniquePredicates.end(), modifies.begin(), modifies.end());
    uniquePredicates.insert(uniquePredicates.end(), next.begin(), next.end());
    uniquePredicates.insert(uniquePredicates.end(), nextT.begin(), nextT.end());
    uniquePredicates.insert(uniquePredicates.end(), notPreds.begin(), notPreds.end());
    uniquePredicates.insert(uniquePredicates.end(), parent.begin(), parent.end());
    uniquePredicates.insert(uniquePredicates.end(), parentT.begin(), parentT.end());
    uniquePredicates.insert(uniquePredicates.end(), uses.begin(), uses.end());
    uniquePredicates.insert(uniquePredicates.end(), whilePat.begin(), whilePat.end());
    uniquePredicates.insert(uniquePredicates.end(), with.begin(), with.end());
    return uniquePredicates;
}


