#include <memory>

#include "common/Program.h"
#include "EntityExtractor.h"
#include "AbstractionExtractor.h"
#include "CfgExtractor.h"
#include "pkb/PopulatePKB.h"

class DesignExtractor {
public:
	DesignExtractor(shared_ptr<Populator> pkb, shared_ptr<Cfg> cfg);
	void extractDesign(shared_ptr<Program> program);

private:
	shared_ptr<Populator> pkbPopulator;
	shared_ptr<Cfg> cfg;
};