#pragma once

#include <string>
#include <memory>
#include <vector>
#include "ClauseObject.h"

class ClauseFactory {
public:
	virtual std::shared_ptr<ClauseObject> createClauseObject(const std::vector<std::string>& token) = 0;
};