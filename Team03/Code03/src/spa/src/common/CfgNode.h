#pragma once

#include <string>
#include <unordered_map>

#include "spa_exception/SemanticErrorException.h"

using namespace std;

class CfgNode {
public:
	typedef unordered_map<bool, shared_ptr<CfgNode>> BooleanToCfgNodeMap;
	typedef vector<shared_ptr<CfgNode>> CfgNodeContainer;
	void addNextNode(bool isTrue, shared_ptr<CfgNode>& node);
	void addStatement(int statementNumber);
	void addParent(const shared_ptr<CfgNode>& node);
	BooleanToCfgNodeMap getNextNodes();
	vector<int> getStatementNumbers();
	CfgNodeContainer getParentNodes();

private:
	BooleanToCfgNodeMap nextNodes;
	vector<int> statementNumbers;
	CfgNodeContainer parentNodes;
};