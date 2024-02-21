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

bool PatternManager::hasAssignPattern(string expr, bool hasWildcard) {
    expr.erase(remove_if(expr.begin(), expr.end(), ::isspace), expr.end());
    return assignPatternStore.hasAssignPattern(expr, hasWildcard);
}
vector<shared_ptr<AssignStatement>> PatternManager::getAssignPattern(string targetVar, string expr, bool hasWildcard) {
    expr.erase(remove_if(expr.begin(), expr.end(), ::isspace), expr.end());
    return assignPatternStore.getAssignPattern(targetVar, expr, hasWildcard);
}
vector<shared_ptr<AssignStatement>> PatternManager::findAssignPattern(vector<shared_ptr<AssignStatement>> allAssign, string targetVar, string expr, bool hasWildcard) {
    expr.erase(remove_if(expr.begin(), expr.end(), ::isspace), expr.end());
    return assignPatternStore.findAssignPattern(allAssign, targetVar, expr, hasWildcard);
}

void PatternManager::clearStore() {
    assignPatternStore.clear();
}

void PatternManager::clear() {
    if (!instance) {
        return;
    }
    instance->clearStore();
}