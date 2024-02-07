#pragma once

#include "../SP/DesignExtractor/Visitor.h"

class Entity {
public:
	virtual void accept(shared_ptr<Visitor> visitor) = 0;
};