#pragma once

#include "SemanticErrorException.h"

SemanticErrorException::SemanticErrorException() : SpaException(
    make_shared<string>("Semantic Error")) {}

SemanticErrorException::SemanticErrorException(std::string_view message)
    : SpaException(make_shared<std::string_view>(message)) {}

shared_ptr<std::string_view> SemanticErrorException::error() {
    return message;
}