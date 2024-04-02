#ifndef STMT_NUMBER_EXTRACTOR_H
#define STMT_NUMBER_EXTRACTOR_H

#include "AttributeExtractor.h"
#include "AttributeValue.h"
#include "common/statement/Statement.h"

class StmtNumberExtractor : public AttributeExtractor {
public:
    [[nodiscard]] AttributeValue extract(const Entity& entity) const override;
};

#endif // STMT_NUMBER_EXTRACTOR_H
