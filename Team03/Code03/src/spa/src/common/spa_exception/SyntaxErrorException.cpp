#pragma once

#include "SyntaxErrorException.h"

SyntaxErrorException::SyntaxErrorException() : SpaException(
    make_shared<string>("Syntax Error")) {}

SyntaxErrorException::SyntaxErrorException(shared_ptr<std::string_view> message)
    : SpaException(message) {}

shared_ptr<std::string_view> SyntaxErrorException::error() {
    return message;
}