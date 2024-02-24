
#include "QPSEvaluationException.h"

QPSEvaluationException::QPSEvaluationException() : SpaException("QPS runtime exception") {}


std::string_view QPSEvaluationException::what() {
    return message;
}

QPSEvaluationException::QPSEvaluationException(std::string_view message)
        : SpaException(message) {}
