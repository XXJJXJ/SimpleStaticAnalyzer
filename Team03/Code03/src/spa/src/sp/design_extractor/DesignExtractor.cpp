#include "DesignExtractor.h"
#include "common/Procedure.h"

DesignExtractor::DesignExtractor(shared_ptr<Populator> pkb) {
	pkbPopulator = pkb;
}

void DesignExtractor::extractDesign(shared_ptr<Program> program) {
	shared_ptr<EntityExtractor> entity_extractor = make_shared<EntityExtractor>(pkbPopulator);
	shared_ptr<AbstractionExtractor> abstraction_extractor = make_shared<AbstractionExtractor>(pkbPopulator);
	Program::ProcedureListContainer procedures = program->getProcedureList();

	for (shared_ptr<Procedure> p : procedures) {
		p->accept(entity_extractor);
		p->accept(abstraction_extractor);
		pkbPopulator->tabulate();
	}
}
