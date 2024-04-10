#include "WithPredicate.h"
#include "qps/entity/clause/attribute/Ref.h"
#include "qps/entity/evaluation/BooleanTable.h"

WithPredicate::WithPredicate(Ref ref1, Ref ref2) : ref1(std::move(ref1)), ref2(std::move(ref2)) {
    if (ref1.getAttributeValueType() != ref2.getAttributeValueType()) {
        throw SemanticErrorException("Comparison between two invalid attribute types");
    }
    addRef(this->ref1);
    addRef(this->ref2);
    addRowFilter(*getRowFilter());
}

PredicateType WithPredicate::getType() const {
    return PredicateType::With;
}

std::shared_ptr<BaseTable> WithPredicate::getFullTable(QueryManager &qm) {
    if (synonyms.empty()) {
        return std::make_shared<BooleanTable>(ref1.getValue().equals(ref2.getValue()));
    }

    HeaderTable resultTable;
    bool isTableSet = false;
    for (const auto& synonym : synonyms) {
        auto allEntities = qm.getAllEntitiesByType(synonym->getType());
        HeaderTable result = HeaderTable(synonym, allEntities);
        if (!isTableSet) {
            resultTable = result;
            isTableSet = true;
        } else {
            resultTable = *resultTable.crossJoin(result);
        }
    }
    return std::make_shared<HeaderTable>(resultTable);
}


std::shared_ptr<RowFilter> WithPredicate::getRowFilter() {
    WithPredicate self = *this;
    return std::make_shared<RowFilter>([self](const TableRow& row) -> bool {
        shared_ptr<AttributeValue> expectedValue = nullptr;
        bool isValueSet = false;
        vector<Ref> attrRefs;
        if (!self.ref1.holdsSynonym()) {
            expectedValue = make_shared<AttributeValue>(self.ref1.getValue());
            isValueSet = true;
        } else {
            attrRefs.push_back(self.ref1);
        }
        if (!self.ref2.holdsSynonym()) {
            auto value = make_shared<AttributeValue>(self.ref2.getValue());
            if (isValueSet && !(*expectedValue).equals(*value)) {
                return false;
            } else {
                expectedValue = value;
                isValueSet = true;
            }
        } else {
            attrRefs.push_back(self.ref2);
        }

        // Ensures that attrRefs size == row size
        if (attrRefs.size() != row.size()) {
            throw QPSEvaluationException("WithPredicate::getRowFilter: extractor size != row size");
        }

        for (int i = 0; i < attrRefs.size(); ++i) {
            auto extractedValue = attrRefs[i].extractAttribute(*row.getByIndex(i));
            if (isValueSet && !extractedValue.equals(*expectedValue)) {
                return false;
            } else {
                expectedValue = make_shared<AttributeValue>(extractedValue);
                isValueSet = true;
            }
        }
        return true;
    });
}

bool WithPredicate::operator==(const WithPredicate &other) const {
    return this->ref1 == other.ref1 && this->ref2 == other.ref2;
}
size_t WithPredicate::hash() const {
    return std::hash<PredicateType>()(getType()) ^ (ref1.hash() << 1) 
            ^ (ref2.hash() >> 1);
}
bool WithPredicate::equals(const Predicate &other) const {
    if (getType() != other.getType()) {
        return false;
    }
    auto castedOther = static_cast<const WithPredicate&>(other);
    return *this == castedOther;
}