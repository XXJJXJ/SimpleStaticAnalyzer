#include "SemanticErrorException.h"

SemanticErrorException::SemanticErrorException() : SpaException("Semantic Error") {}

SemanticErrorException::SemanticErrorException(std::string_view message) : SpaException(message) {}

std::string_view SemanticErrorException::what() {
    return message;
}