#include "WithPredicate.h"
#include "qps/entity/clause/attribute/Ref.h"

WithPredicate::WithPredicate(Ref ref1, Ref ref2) : ref1(std::move(ref1)), ref2(std::move(ref2)) {
    if (ref1.getAttributeValueType() != ref2.getAttributeValueType()) {
        throw SemanticErrorException("Comparison between two invalid attribute types");
    }
}