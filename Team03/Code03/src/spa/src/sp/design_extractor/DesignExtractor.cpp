#pragma once

#include "DesignExtractor.h"
#include "common/Procedure.h"

void DesignExtractor::extractDesign(shared_ptr<Program> program) {
	shared_ptr<EntityExtractor> entity_extractor = make_shared<EntityExtractor>();
	Program::ProcedureListContainer procedures = program->getProcedureList();

	for (shared_ptr<Procedure> p : procedures) {
		p->accept(entity_extractor);
	}
}
