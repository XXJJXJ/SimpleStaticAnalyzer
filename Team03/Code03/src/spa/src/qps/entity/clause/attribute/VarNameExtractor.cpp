#include "VarNameExtractor.h"

AttributeValue VarNameExtractor::extract(const Entity &entity) const {
    if (const auto *variable = dynamic_cast<const Variable *>(&entity)) {
        return {variable->getName()};
    } else if (const auto *read = dynamic_cast<const ReadStatement *>(&entity)) {
        return {read->getVariable()->getName()};
    } else if (const auto *print = dynamic_cast<const PrintStatement *>(&entity)) {
        return {print->getVariable()->getName()};
    }

    throw QPSEvaluationException("VarNameExtractor::extract called with an entity that does not have a varName");

}
