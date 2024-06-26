#pragma once

#include <memory>
#include "qps/entity/clause/Predicate.h"
#include "qps/entity/clause/attribute/Ref.h"

class PredicateFactory {
public:
    static std::shared_ptr<Predicate> createPredicate(
        const std::vector<std::string> &tokens,
        const std::unordered_map<std::string, EntityType> &synonymMap);
    static std::shared_ptr<AttrRef> createAttrRef(
        const std::string &token,
        const std::unordered_map<std::string, EntityType> &synonymMap);
private:
    static std::variant<int, Synonym, std::string> stringToStatementRef(
        const std::string &token,
        const std::unordered_map<std::string,
                                 EntityType> &synonymMap);
    static std::variant<Synonym, std::string> stringToEntityRef(
        const std::string &token,
        const std::unordered_map<std::string,
                                 EntityType> &synonymMap);
    static Ref stringToRef(const std::string &token, const std::unordered_map<std::string, EntityType> &synonymMap);
    static std::shared_ptr<Predicate> parsePatternPredicate(
        const std::vector<std::string> &tokens,
        const std::unordered_map<std::string,
                                 EntityType> &synonymMap);
    static std::shared_ptr<Predicate> parseWithPredicate(
        const std::vector<std::string> &tokens,
        const std::unordered_map<std::string, EntityType> &synonymMap);
    static std::shared_ptr<Predicate> parseNotPredicate(
        const std::vector<std::string> &tokens,
        const std::unordered_map<std::string, EntityType> &synonymMap);
};