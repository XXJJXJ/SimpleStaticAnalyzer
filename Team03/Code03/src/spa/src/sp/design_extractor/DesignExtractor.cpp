#include <algorithm>

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
	auto procToCfgNodeMap = cfg->getProcedureNodes();
	for (auto iter = procToCfgNodeMap.begin(); iter != procToCfgNodeMap.end(); ++iter) {
		auto currNode = iter->second;
		vector <shared_ptr<CfgNode>> visited;
		shared_ptr<Statement> prevNodeStatement = NULL;
		nodeTraversalHelper(currNode, visited, prevNodeStatement);
	}
}

void DesignExtractor::nodeTraversalHelper(shared_ptr<CfgNode> currNode, vector<shared_ptr<CfgNode>> visited, shared_ptr<Statement> prevNodeStatement) {
	auto statementList = currNode->getStatementList();
	shared_ptr<Statement> currNodeLastStatement = NULL;
	if (count(visited.begin(), visited.end(), currNode) <= 0) {
		if (statementList.size() != 0) {
			if (prevNodeStatement != NULL) pkbPopulator->addNext(prevNodeStatement, statementList[0]);

			for (size_t i = 0; i < statementList.size(); ++i) {
				if (i == (statementList.size() - 1)) {
					prevNodeStatement = statementList[i];
					currNodeLastStatement = statementList[i];
				}
				else pkbPopulator->addNext(statementList[i], statementList[i + 1]);
			}
		}
		visited.push_back(currNode);
		auto nextNodes = currNode->getNextNodes();
		if (nextNodes.find(true) != nextNodes.end()) {
			nodeTraversalHelper(nextNodes[true], visited, prevNodeStatement);
		}

		prevNodeStatement = currNodeLastStatement;
		if (nextNodes.find(false) != nextNodes.end()) {
			nodeTraversalHelper(nextNodes[false], visited, prevNodeStatement);
		}
	}
	else {
		if (statementList.size() != 0) {
			if (prevNodeStatement != NULL) {
				pkbPopulator->addNext(prevNodeStatement, statementList[0]);
			}
			prevNodeStatement = statementList[0];
		}
	}
}
