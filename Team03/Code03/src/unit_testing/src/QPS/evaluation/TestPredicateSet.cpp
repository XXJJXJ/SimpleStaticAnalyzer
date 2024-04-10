#include <catch.hpp>

#include "qps/entity/query/Synonym.h"
#include "qps/entity/evaluation/PredicateSet.h"

TEST_CASE("Predicates test individual duplicate removal in set", "[Predicates]") {
    Synonym stmtSyn(EntityType::Stmt, "s1");
    Synonym stmtSyn2(EntityType::Stmt, "s2");
    Synonym varSyn(EntityType::Variable, "v");
    Synonym varSyn2(EntityType::Variable, "v2");
    Synonym procSyn(EntityType::Procedure, "p");
    Synonym procSyn2(EntityType::Procedure, "p2");
    Synonym assignSyn(EntityType::Assign, "a");
    std::string validString = "procName"; // Example of a valid non-empty string for procedure names
    std::string wildcard = "_";
    std::string exactMatch = "x*y";
    std::string partialMatch = "_\"x*y\"_";

    SECTION("Affects Predicates Test") {
        std::unordered_set<std::shared_ptr<AffectsPredicate>> predicatesSet;
        auto a1 = make_shared<AffectsPredicate>(stmtSyn, stmtSyn2);
        auto a2 = make_shared<AffectsPredicate>(stmtSyn, stmtSyn2);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        auto a3 = make_shared<AffectsPredicate>(stmtSyn2, stmtSyn);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
    SECTION("AssignPattern Predicates Test") {
        std::unordered_set<std::shared_ptr<AssignPatternPredicate>> predicatesSet;
        auto a1 = make_shared<AssignPatternPredicate>(assignSyn, varSyn, wildcard);
        auto a2 = make_shared<AssignPatternPredicate>(assignSyn, varSyn, wildcard);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        auto a3 = make_shared<AssignPatternPredicate>(assignSyn, varSyn2, wildcard);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
    SECTION("Calls Predicates Test") {
        std::unordered_set<std::shared_ptr<CallsPredicate>> predicatesSet;
        auto a1 = make_shared<CallsPredicate>(procSyn, procSyn2);
        auto a2 = make_shared<CallsPredicate>(procSyn, procSyn2);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        auto a3 = make_shared<CallsPredicate>(procSyn2, procSyn);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
    SECTION("CallsT Predicates Test") {
        std::unordered_set<std::shared_ptr<CallsTPredicate>> predicatesSet;
        auto a1 = make_shared<CallsTPredicate>(procSyn, procSyn2);
        auto a2 = make_shared<CallsTPredicate>(procSyn, procSyn2);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        auto a3 = make_shared<CallsTPredicate>(procSyn2, procSyn);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
    SECTION("Follows Predicates Test") {
        std::unordered_set<std::shared_ptr<FollowsPredicate>> predicatesSet;
        auto a1 = make_shared<FollowsPredicate>(stmtSyn, stmtSyn2);
        auto a2 = make_shared<FollowsPredicate>(stmtSyn, stmtSyn2);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        auto a3 = make_shared<FollowsPredicate>(stmtSyn2, stmtSyn);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
    SECTION("FollowsT Predicates Test") {
        std::unordered_set<std::shared_ptr<FollowsTPredicate>> predicatesSet;
        auto a1 = make_shared<FollowsTPredicate>(stmtSyn, stmtSyn2);
        auto a2 = make_shared<FollowsTPredicate>(stmtSyn, stmtSyn2);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        auto a3 = make_shared<FollowsTPredicate>(stmtSyn2, stmtSyn);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
    SECTION("IfPattern Predicates Test") {
        Synonym ifSyn(EntityType::If, "s1");
        std::unordered_set<std::shared_ptr<IfPatternPredicate> >predicatesSet;
        auto a1 = make_shared<IfPatternPredicate>(ifSyn, varSyn);
        auto a2 = make_shared<IfPatternPredicate>(ifSyn, varSyn);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        auto a3 = make_shared<IfPatternPredicate>(ifSyn, varSyn2);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
    SECTION("Modifies Predicates Test") {
        std::unordered_set<std::shared_ptr<ModifiesPredicate> >predicatesSet;
        auto a1 = make_shared<ModifiesPredicate>(stmtSyn, varSyn);
        auto a2 = make_shared<ModifiesPredicate>(stmtSyn, varSyn);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        auto a3 = make_shared<ModifiesPredicate>(stmtSyn, varSyn2);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
    SECTION("Next Predicates Test") {
        std::unordered_set<std::shared_ptr<NextPredicate>> predicatesSet;
        auto a1 = make_shared<NextPredicate>(stmtSyn, stmtSyn2);
        auto a2 = make_shared<NextPredicate>(stmtSyn, stmtSyn2);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        auto a3 = make_shared<NextPredicate>(stmtSyn2, stmtSyn);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
    SECTION("NextT Predicates Test") {
        std::unordered_set<std::shared_ptr<NextTPredicate>> predicatesSet;
        auto a1 = make_shared<NextTPredicate>(stmtSyn, stmtSyn2);
        auto a2 = make_shared<NextTPredicate>(stmtSyn, stmtSyn2);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        auto a3 = make_shared<NextTPredicate>(stmtSyn2, stmtSyn);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
    SECTION("Not Predicates Test") {
        std::unordered_set<std::shared_ptr<NotPredicate>> predicatesSet;
        auto temp1 = make_shared<NextTPredicate>(stmtSyn, stmtSyn2);
        auto temp2 = make_shared<NextTPredicate>(stmtSyn, stmtSyn2);
        auto a1 = make_shared<NotPredicate>(temp1);
        auto a2 = make_shared<NotPredicate>(temp2);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        auto temp3 = make_shared<NextTPredicate>(stmtSyn2, stmtSyn);
        auto a3 = make_shared<NotPredicate>(temp3);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
    SECTION("Parent Predicates Test") {
        std::unordered_set<std::shared_ptr<ParentPredicate>> predicatesSet;
        auto a1 = make_shared<ParentPredicate>(stmtSyn, stmtSyn2);
        auto a2 = make_shared<ParentPredicate>(stmtSyn, stmtSyn2);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        auto a3 = make_shared<ParentPredicate>(stmtSyn2, stmtSyn);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
    SECTION("ParentT Predicates Test") {
        std::unordered_set<std::shared_ptr<ParentTPredicate>> predicatesSet;
        auto a1 = make_shared<ParentTPredicate>(stmtSyn, stmtSyn2);
        auto a2 = make_shared<ParentTPredicate>(stmtSyn, stmtSyn2);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        auto a3 = make_shared<ParentTPredicate>(stmtSyn2, stmtSyn);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
    SECTION("Uses Predicates Test") {
        std::unordered_set<std::shared_ptr<UsesPredicate> >predicatesSet;
        auto a1 = make_shared<UsesPredicate>(stmtSyn, varSyn);
        auto a2 = make_shared<UsesPredicate>(stmtSyn, varSyn);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        auto a3 = make_shared<UsesPredicate>(stmtSyn, varSyn2);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
    SECTION("WhilePattern Predicates Test") {
        Synonym whileSyn(EntityType::While, "s1");
        std::unordered_set<std::shared_ptr<WhilePatternPredicate> >predicatesSet;
        auto a1 = make_shared<WhilePatternPredicate>(whileSyn, varSyn);
        auto a2 = make_shared<WhilePatternPredicate>(whileSyn, varSyn);
        auto a3 = make_shared<WhilePatternPredicate>(whileSyn, varSyn2);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
    SECTION("With Predicates Test") {
        Ref r1(AttributeValue(1));
        Ref r2(AttributeValue(1));
        Ref r3(AttributeValue(3));
        std::unordered_set<std::shared_ptr<WithPredicate> >predicatesSet;
        auto a1 = make_shared<WithPredicate>(r1, r2);
        auto a2 = make_shared<WithPredicate>(r1, r2);
        auto a3 = make_shared<WithPredicate>(r1, r3);
        predicatesSet.insert(a1);
        predicatesSet.insert(a2);
        REQUIRE(predicatesSet.size() == 1);
        predicatesSet.insert(a3);
        REQUIRE(predicatesSet.size() == 2);
    }
}


TEST_CASE("PredicateSet functionality test") {
    Synonym stmtSyn(EntityType::Stmt, "s");
    Synonym stmtSyn2(EntityType::Stmt, "s2");
    Synonym varSyn(EntityType::Variable, "v");
    Synonym varSyn2(EntityType::Variable, "v2");
    Synonym procSyn(EntityType::Procedure, "p");
    Synonym procSyn2(EntityType::Procedure, "p2");
    Synonym assignSyn(EntityType::Assign, "a");
    Synonym ifSyn(EntityType::If, "ifs");
    Synonym whileSyn(EntityType::While, "whiles");
    std::string wildcard = "_";

    PredicateSet ps;
    ps.add(make_shared<AffectsPredicate>(stmtSyn, stmtSyn2));
    ps.add(make_shared<AffectsPredicate>(stmtSyn, stmtSyn2));
    ps.add(make_shared<AffectsPredicate>(stmtSyn2, stmtSyn));

    ps.add(make_shared<AssignPatternPredicate>(assignSyn, varSyn, wildcard));
    ps.add(make_shared<AssignPatternPredicate>(assignSyn, varSyn, wildcard));
    ps.add(make_shared<AssignPatternPredicate>(assignSyn, varSyn2, wildcard));

    ps.add(make_shared<CallsPredicate>(procSyn, procSyn2));
    ps.add(make_shared<CallsPredicate>(procSyn, procSyn2));
    ps.add(make_shared<CallsPredicate>(procSyn2, procSyn));

    ps.add(make_shared<CallsTPredicate>(procSyn, procSyn2));
    ps.add(make_shared<CallsTPredicate>(procSyn, procSyn2));
    ps.add(make_shared<CallsTPredicate>(procSyn2, procSyn));

    ps.add(make_shared<FollowsPredicate>(stmtSyn, stmtSyn2));
    ps.add(make_shared<FollowsPredicate>(stmtSyn, stmtSyn2));
    ps.add(make_shared<FollowsPredicate>(stmtSyn2, stmtSyn));
    
    ps.add(make_shared<FollowsTPredicate>(stmtSyn, stmtSyn2));
    ps.add(make_shared<FollowsTPredicate>(stmtSyn, stmtSyn2));
    ps.add(make_shared<FollowsTPredicate>(stmtSyn2, stmtSyn));

    ps.add(make_shared<IfPatternPredicate>(ifSyn, varSyn));
    ps.add(make_shared<IfPatternPredicate>(ifSyn, varSyn));
    ps.add(make_shared<IfPatternPredicate>(ifSyn, varSyn2));

    ps.add(make_shared<ModifiesPredicate>(stmtSyn, varSyn));
    ps.add(make_shared<ModifiesPredicate>(stmtSyn, varSyn));
    ps.add(make_shared<ModifiesPredicate>(stmtSyn, varSyn2));

    ps.add(make_shared<NextPredicate>(stmtSyn, stmtSyn2));
    ps.add(make_shared<NextPredicate>(stmtSyn, stmtSyn2));
    ps.add(make_shared<NextPredicate>(stmtSyn2, stmtSyn));

    ps.add(make_shared<NextTPredicate>(stmtSyn, stmtSyn2));
    ps.add(make_shared<NextTPredicate>(stmtSyn, stmtSyn2));
    ps.add(make_shared<NextTPredicate>(stmtSyn2, stmtSyn));

    auto temp1 = make_shared<NextTPredicate>(stmtSyn, stmtSyn2);
    auto temp2 = make_shared<NextTPredicate>(stmtSyn, stmtSyn2);
    auto temp3 = make_shared<NextTPredicate>(stmtSyn2, stmtSyn);
    ps.add(make_shared<NotPredicate>(temp1));
    ps.add(make_shared<NotPredicate>(temp2));
    ps.add(make_shared<NotPredicate>(temp3));

    ps.add(make_shared<ParentPredicate>(stmtSyn, stmtSyn2));
    ps.add(make_shared<ParentPredicate>(stmtSyn, stmtSyn2));
    ps.add(make_shared<ParentPredicate>(stmtSyn2, stmtSyn));

    ps.add(make_shared<ParentTPredicate>(stmtSyn, stmtSyn2));
    ps.add(make_shared<ParentTPredicate>(stmtSyn, stmtSyn2));
    ps.add(make_shared<ParentTPredicate>(stmtSyn2, stmtSyn));

    ps.add(make_shared<UsesPredicate>(stmtSyn, varSyn));
    ps.add(make_shared<UsesPredicate>(stmtSyn, varSyn));
    ps.add(make_shared<UsesPredicate>(stmtSyn, varSyn2));

    ps.add(make_shared<WhilePatternPredicate>(whileSyn, varSyn));
    ps.add(make_shared<WhilePatternPredicate>(whileSyn, varSyn));
    ps.add(make_shared<WhilePatternPredicate>(whileSyn, varSyn2));

    Ref r1(AttributeValue(1));
    Ref r2(AttributeValue(1));
    Ref r3(AttributeValue(3));
    ps.add(make_shared<WithPredicate>(r1, r2));
    ps.add(make_shared<WithPredicate>(r1, r2));
    ps.add(make_shared<WithPredicate>(r1, r3));

    REQUIRE(ps.getUniquePredicates().size() == 32);
}