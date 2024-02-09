#pragma once

#include "../sp/design_extractor/Visitor.h"

class Entity {
public:
	virtual void accept(shared_ptr<Visitor> visitor) = 0;
};