#pragma once

#include <iostream>

class SpaException : public std::exception {
public:
	SpaException() = default;
	SpaException(shared_ptr<std::string_view> message);
	virtual shared_ptr<std::string_view> error() = 0;

protected:
	shared_ptr<std::string> message;
};