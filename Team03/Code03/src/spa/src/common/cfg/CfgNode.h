#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "common/Util.h"
#include "common/statement/Statement.h"
#include "common/spa_exception/SemanticErrorException.h"

using namespace std;

class CfgNode {
public:
    typedef vector<shared_ptr<CfgNode>> ParentNodes;
    typedef unordered_map<bool, shared_ptr<CfgNode>> NextNodes;
    void addParentNode(shared_ptr<CfgNode> node);
    void addStatement(shared_ptr<Statement> statement);
    void addNextNode(bool condition, shared_ptr<CfgNode> node);
    ParentNodes getParentNodes();
    StatementList getStatementList();
    NextNodes getNextNodes();

private:
    ParentNodes parentNodes;
    StatementList statementList;
    NextNodes nextNodes;
};