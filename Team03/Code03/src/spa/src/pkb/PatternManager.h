#pragma once

#include <memory>
#include "pattern_store/AssignPatternStore.h"
#include "pattern_store/IfWhilePatternStore.h"

using namespace std;

class PatternManager {
private:
    PatternManager() {}
    static shared_ptr<PatternManager> instance;

    AssignPatternStore assignPatternStore;
    IfWhilePatternStore ifPatternStore;
    IfWhilePatternStore whilePatternStore;
    
public:
    static shared_ptr<PatternManager> getInstance();
    void clearStore();
    static void clear();
    // Assign related
    bool hasAssignPattern(string& expr, bool hasWildcard);
    vector<shared_ptr<Entity>> getAssignPattern(string& targetVar, string& expr, bool hasWildcard);
    vector<shared_ptr<Entity>> findAssignPattern(vector<shared_ptr<AssignStatement>>& allAssign, string& targetVar, string& expr, bool hasWildcard);
    
    void addIfWhileUses(shared_ptr<Statement> stmt, const string& var);
    // If related
    vector<shared_ptr<Entity>> getIfPattern(string& targetVar);
    // While related
    vector<shared_ptr<Entity>> getWhilePattern(string& targetVar);
};