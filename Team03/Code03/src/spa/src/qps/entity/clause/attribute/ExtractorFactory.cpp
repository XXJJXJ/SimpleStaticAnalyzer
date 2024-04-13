
#include "ExtractorFactory.h"

shared_ptr<AttributeExtractor> ExtractorFactory::createExtractor(AttributeType attributeType) {
    shared_ptr<AttributeExtractor> extractor;
    switch (attributeType) {
        case AttributeType::ProcName:extractor = std::make_shared<ProcNameExtractor>();
            break;
        case AttributeType::VarName:extractor = std::make_shared<VarNameExtractor>();
            break;
        case AttributeType::Value:extractor = std::make_shared<ValueExtractor>();
            break;
        case AttributeType::StmtNumber:extractor = std::make_shared<StmtNumberExtractor>();
            break;
        case AttributeType::Name:extractor = std::make_shared<NameExtractor>();
            break;
        default:throw QPSEvaluationException("ExtractorFactory::createExtractor: Invalid attribute type.");
    }
    return extractor;
}
