#ifndef VAR_NAME_EXTRACTOR_H
#define VAR_NAME_EXTRACTOR_H

#include "AttributeExtractor.h"
#include "AttributeValue.h"
#include "common/expression/Variable.h" // Include the Variable class definition
#include "common/statement/ReadStatement.h"
#include "common/statement/PrintStatement.h"

class VarNameExtractor : public AttributeExtractor {
public:
    [[nodiscard]] AttributeValue extract(const Entity& entity) const override;
};

#endif // VAR_NAME_EXTRACTOR_H
