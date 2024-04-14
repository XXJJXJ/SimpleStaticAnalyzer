#include "ProcNameExtractor.h"

AttributeValue ProcNameExtractor::extract(const Entity &entity) const {
    if (const auto *procedure = dynamic_cast<const Procedure *>(&entity)) {
        return {procedure->getName()};
    } else if (const auto *call = dynamic_cast<const CallStatement *>(&entity)) {
        return {call->getTargetProcedureName()};
    } else {
        throw QPSEvaluationException(
            "ProcNameExtractor::extract called with an entity that is neither Procedure nor Call");
    }
}
