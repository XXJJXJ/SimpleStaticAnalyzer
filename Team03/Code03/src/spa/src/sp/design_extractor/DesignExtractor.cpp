#include "DesignExtractor.h"
#include "common/Procedure.h"

DesignExtractor::DesignExtractor(shared_ptr<Populator> pkb) {
	pkbPopulator = pkb;
}

void DesignExtractor::extractDesign(shared_ptr<Program> program) {
	shared_ptr<EntityExtractor> entityExtractor = make_shared<EntityExtractor>(pkbPopulator);
	shared_ptr<AbstractionExtractor> abstractionExtractor = make_shared<AbstractionExtractor>(pkbPopulator);
	shared_ptr<Cfg> cfg = make_shared<Cfg>();
	shared_ptr<CfgExtractor> cfgExtractor = make_shared<CfgExtractor>(cfg);
	Program::ProcedureListContainer procedures = program->getProcedureList();

	for (shared_ptr<Procedure> p : procedures) {
		p->accept(entityExtractor);
		p->accept(abstractionExtractor);
		p->accept(cfgExtractor);
	}
	extractNextRelation(cfg);
	pkbPopulator->tabulate();
}

void DesignExtractor::extractNextRelation(shared_ptr<Cfg> cfg) {
	auto procToCfgNodeMap = cfg->getCfgRootNodes();
	for (auto iter = procToCfgNodeMap.begin(); iter != procToCfgNodeMap.end(); ++iter) {
		auto currNode = iter->second;
		auto nextNodes = currNode->getNextNodes();
		shared_ptr<Statement> prevNodeStatement = NULL;

		while (nextNodes.find(true) != nextNodes.end()) {
			auto nextNode = nextNodes[true];
			auto statementList = currNode->getStatements();

			if (statementList.size() != 0) {
				if (prevNodeStatement != NULL) {
					pkbPopulator->addNext(prevNodeStatement, statementList[0]);
				}

				if (statementList.size() > 1) {
					for (size_t i = 0; i < statementList.size() - 1; ++i) {
						pkbPopulator->addNext(statementList[i], statementList[i + 1]);
						if ((i + 1) == (statementList.size() - 1)) prevNodeStatement = statementList[i + 1];
					}
				}
				else {
					prevNodeStatement = statementList[0];
				}
			}
			currNode = nextNode;
			nextNodes = currNode->getNextNodes();
		}
	}
}
