#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Util.h"
#include "common/Statement.h"
#include "spa_exception/SemanticErrorException.h"

using namespace std;

class CfgNode {
public:
	typedef vector<shared_ptr<CfgNode>> ParentNodes;
	typedef unordered_map<bool, shared_ptr<CfgNode>> NextNodes;
	void addParentNode(shared_ptr<CfgNode> node);
	void addStatement(shared_ptr<Statement> statement);
	void addNextNode(shared_ptr<CfgNode> node, bool condition);
	ParentNodes getParentNodes();
	StatementList getStatementList();
	NextNodes getNextNodes();

private:
	ParentNodes parentNodes;
	StatementList statementList;
	NextNodes nextNodes;
};