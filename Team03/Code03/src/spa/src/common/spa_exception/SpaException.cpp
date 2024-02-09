#include "SpaException.h"

SpaException::SpaException(shared_ptr<std::string_view> message) : message(message) {}