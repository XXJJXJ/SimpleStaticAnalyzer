#ifndef SPA_EXTRACTORFACTORY_H
#define SPA_EXTRACTORFACTORY_H

#include "AttributeExtractor.h"
#include "ProcNameExtractor.h"
#include "StmtNumberExtractor.h"
#include "ValueExtractor.h"
#include "VarNameExtractor.h"
#include "NameExtractor.h"
#include "common/spa_exception/QPSEvaluationException.h"

class ExtractorFactory {
public:
    static shared_ptr<AttributeExtractor> createExtractor(AttributeType attributeType);
};

#endif //SPA_EXTRACTORFACTORY_H
