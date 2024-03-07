#include "DesignExtractor.h"
#include "common/Procedure.h"

DesignExtractor::DesignExtractor(shared_ptr<Populator> pkb, shared_ptr<Cfg> cfg_) {
	pkbPopulator = pkb;
	cfg = cfg_;
}

void DesignExtractor::extractDesign(shared_ptr<Program> program) {
	shared_ptr<EntityExtractor> entityExtractor = make_shared<EntityExtractor>(pkbPopulator);
	shared_ptr<AbstractionExtractor> abstractionExtractor = make_shared<AbstractionExtractor>(pkbPopulator);
	shared_ptr<CfgExtractor> cfgExtractor = make_shared<CfgExtractor>(cfg);
	Program::ProcedureListContainer procedures = program->getProcedureList();

	for (shared_ptr<Procedure> p : procedures) {
		p->accept(entityExtractor);
		p->accept(abstractionExtractor);
		p->accept(cfgExtractor);
		pkbPopulator->tabulate();
	}
}
