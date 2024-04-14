#ifndef PROC_NAME_EXTRACTOR_H
#define PROC_NAME_EXTRACTOR_H

#include "AttributeExtractor.h"
#include "AttributeValue.h"
#include "common/Procedure.h" // Include the Procedure class definition
#include "common/statement/CallStatement.h"

class ProcNameExtractor : public AttributeExtractor {
public:
    AttributeValue extract(const Entity &entity) const override;
};

#endif // PROC_NAME_EXTRACTOR_H
