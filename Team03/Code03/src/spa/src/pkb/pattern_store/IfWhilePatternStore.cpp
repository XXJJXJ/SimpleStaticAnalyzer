#include "IfWhilePatternStore.h"


void IfWhilePatternStore::add(shared_ptr<Statement> stmt, shared_ptr<Variable> var) {
    stmtToVar[stmt].insert(var);
}

vector<vector<shared_ptr<Entity>>> IfWhilePatternStore::getPattern() {
    vector<vector<shared_ptr<Entity>>> res;
    for (auto & stmtVarPair : stmtToVar) {
        for (auto & var : stmtVarPair.second) {
            res.push_back({stmtVarPair.first, var});
        }
    }
    return res;
}

void IfWhilePatternStore::clear() {
    stmtToVar.clear();
}

IfWhilePatternStore::~IfWhilePatternStore() {
    clear();
}