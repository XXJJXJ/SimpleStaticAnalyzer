#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "common/Statement.h"
#include "spa_exception/SemanticErrorException.h"

using namespace std;

class CfgNode {
public:
	typedef vector<shared_ptr<CfgNode>> ParentNodes;
	typedef vector<shared_ptr<Statement>> StatementList;
	typedef unordered_map<bool, shared_ptr<CfgNode>> NextNodes;
	void addParent(shared_ptr<CfgNode> node);
	void addStatementNode(shared_ptr<Statement> statement);
	void addNextNode(bool condition, shared_ptr<CfgNode> node);
	ParentNodes getParentNodes();
	vector<shared_ptr<Statement>> getStatements();
	NextNodes getNextNodes();

private:
	ParentNodes parentNodes;
	StatementList statements;
	NextNodes nextNodes;
};