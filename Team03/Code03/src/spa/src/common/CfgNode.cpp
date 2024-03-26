#include "CfgNode.h"

void CfgNode::addParentNode(shared_ptr<CfgNode> node) {
    parentNodes.push_back(node);
}

void CfgNode::addStatement(shared_ptr<Statement> statement) {
    statementList.push_back(statement);
}

void CfgNode::addNextNode(bool condition, shared_ptr<CfgNode> node) {
    if (nextNodes.find(condition) != nextNodes.end()) {
        throw SemanticErrorException(
            "Node for condition " + 
            to_string(condition) + 
            "already exists");
    }
    else {
        nextNodes[condition] = move(node);
    }
}

CfgNode::ParentNodes CfgNode::getParentNodes() {
    return parentNodes;
}

StatementList CfgNode::getStatementList() {
    return statementList;
}

CfgNode::NextNodes CfgNode::getNextNodes() {
    return nextNodes;
}