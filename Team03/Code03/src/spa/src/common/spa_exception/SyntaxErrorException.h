#pragma once

#include <iostream>
#include "SpaException.h"

class SyntaxErrorException : public SpaException {
public:
	SyntaxErrorException();
	explicit SyntaxErrorException(shared_ptr<std::string_view> message);
	shared_ptr<std::string_view> error();
};