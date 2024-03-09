#include "PatternManager.h"

// Initialize the static instance to nullptr
shared_ptr<PatternManager> PatternManager::instance = nullptr;

shared_ptr<PatternManager> PatternManager::getInstance() {
    if (!instance) {
        PatternManager* pm = new PatternManager();
        instance = make_shared<PatternManager>(*pm);
    }
    return instance;
}

bool PatternManager::hasAssignPattern(string& expr, bool hasWildcard) {
    expr.erase(remove_if(expr.begin(), expr.end(), ::isspace), expr.end());
    return assignPatternStore.hasAssignPattern(expr, hasWildcard);
}
vector<shared_ptr<Entity>> PatternManager::getAssignPattern(string& targetVar, string& expr, bool hasWildcard) {
    expr.erase(remove_if(expr.begin(), expr.end(), ::isspace), expr.end());
    auto temp = assignPatternStore.getAssignPattern(targetVar, expr, hasWildcard);
    vector<shared_ptr<Entity>> res;
    res.insert(res.end(), temp.begin(), temp.end());
    return res;
}
vector<shared_ptr<Entity>> PatternManager::findAssignPattern(vector<shared_ptr<AssignStatement>>& allAssign, string& targetVar, string& expr, bool hasWildcard) {
    expr.erase(remove_if(expr.begin(), expr.end(), ::isspace), expr.end());
    auto temp = assignPatternStore.findAssignPattern(allAssign, targetVar, expr, hasWildcard);
    vector<shared_ptr<Entity>> res;
    res.insert(res.end(), temp.begin(), temp.end());
    return res;
}

void PatternManager::addIfWhileUses(shared_ptr<Statement> stmt, shared_ptr<Variable> var) {
    switch (stmt->getType())
    {
    case EntityType::While: whilePatternStore.add(stmt, var); return;
    case EntityType::If: ifPatternStore.add(stmt, var); return;
    default:
        // Nothing happens
        return;
    }
}
// If related
vector<vector<shared_ptr<Entity>>> PatternManager::getIfPattern() {
    return ifPatternStore.getPattern();
}
// While related
vector<vector<shared_ptr<Entity>>> PatternManager::getWhilePattern() {
    return whilePatternStore.getPattern();
}

void PatternManager::clearStore() {
    assignPatternStore.clear();
    ifPatternStore.clear();
    whilePatternStore.clear();
}

void PatternManager::clear() {
    if (!instance) {
        return;
    }
    instance->clearStore();
}