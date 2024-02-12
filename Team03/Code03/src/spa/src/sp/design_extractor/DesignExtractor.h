#include <memory>

#include "common/Program.h"
#include "EntityExtractor.h"
#include "pkb/PopulatePKB.h"

class DesignExtractor {
public:
	void extractDesign(shared_ptr<Program> program);
};