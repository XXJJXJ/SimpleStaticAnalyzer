#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "common/Statement.h"
#include "spa_exception/SemanticErrorException.h"

using namespace std;

class CfgNode {
public:
	typedef unordered_map<bool, shared_ptr<CfgNode>> BooleanToCfgNodeMap;
	typedef vector<shared_ptr<CfgNode>> CfgNodeContainer;
	void addNextNode(bool isTrue, shared_ptr<CfgNode> node);
	void addStatement(shared_ptr<Statement> statement);
	void addParent(const shared_ptr<CfgNode>& node);
	BooleanToCfgNodeMap getNextNodes();
	vector<shared_ptr<Statement>> getStatements();
	CfgNodeContainer getParentNodes();

private:
	BooleanToCfgNodeMap nextNodes;
	vector<shared_ptr<Statement>> statements;
	CfgNodeContainer parentNodes;
};