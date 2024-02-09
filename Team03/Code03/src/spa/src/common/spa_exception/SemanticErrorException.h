#pragma once

#include <iostream>
#include "SpaException.h"

class SemanticErrorException : public SpaException {
public:
	SemanticErrorException();
	SemanticErrorException(shared_ptr<std::string_view> message);
	shared_ptr<std::string_view> error();
};