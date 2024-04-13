#include "IfWhilePatternStore.h"


void IfWhilePatternStore::add(shared_ptr<Statement> stmt, shared_ptr<Variable> var) {
    stmtToVar[stmt].insert(var);
}

vector<vector<shared_ptr<Entity>>> IfWhilePatternStore::getPattern() {
    // empty, must be initialized
    if (cache.size() == 0) {
        for (auto & stmtVarPair : stmtToVar) {
            for (auto & var : stmtVarPair.second) {
                cache.push_back({stmtVarPair.first, var});
            }
        }
    }
    return cache;
}

void IfWhilePatternStore::clear() {
    stmtToVar.clear();
    cache.clear();
}

IfWhilePatternStore::~IfWhilePatternStore() {
    clear();
}