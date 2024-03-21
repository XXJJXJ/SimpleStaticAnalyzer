#include "CfgNode.h"

void CfgNode::addParent(shared_ptr<CfgNode> node) {
    parentNodes.push_back(node);
}

void CfgNode::addStatementNode(shared_ptr<Statement> statement) {
    statements.push_back(statement);
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

CfgNode::StatementList CfgNode::getStatements() {
    return statements;
}

CfgNode::NextNodes CfgNode::getNextNodes() {
    return nextNodes;
}