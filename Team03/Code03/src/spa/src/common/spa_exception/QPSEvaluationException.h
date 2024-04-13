#ifndef SPA_QPSEVALUATIONEXCEPTION_H
#define SPA_QPSEVALUATIONEXCEPTION_H

#include <istream>
#include "SpaException.h"

class QPSEvaluationException : public SpaException {
public:
    QPSEvaluationException();
    explicit QPSEvaluationException(std::string_view message);
    std::string_view what();
};

#endif //SPA_QPSEVALUATIONEXCEPTION_H
