#include "CfgNode.h"

void CfgNode::addNextNode(bool isTrue, shared_ptr<CfgNode>& node) {
    if (nextNodes.find(isTrue) != nextNodes.end()) {
        throw SemanticErrorException("CfgNode already has a node for condition " + to_string(isTrue));
    }
    nextNodes[isTrue] = move(node);
}

void CfgNode::addStatement(int statementNumber) {
    statementNumbers.push_back(statementNumber);
}

void CfgNode::addParent(const shared_ptr<CfgNode>& node) {
    parentNodes.emplace_back(node);
}

CfgNode::BooleanToCfgNodeMap CfgNode::getNextNodes() {
    return nextNodes;
}

vector<int> CfgNode::getStatementNumbers() {
    return statementNumbers;
}

CfgNode::CfgNodeContainer CfgNode::getParentNodes() {
    return parentNodes;
}