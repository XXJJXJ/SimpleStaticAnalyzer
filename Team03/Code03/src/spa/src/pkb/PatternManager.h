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
<<<<<<< HEAD
    vector<shared_ptr<AssignStatement>> getAssignPattern(string& targetVar, string& expr, bool hasWildcard);
    vector<shared_ptr<AssignStatement>> findAssignPattern(vector<shared_ptr<AssignStatement>>& allAssign, string& targetVar, string& expr, bool hasWildcard);
    
    void addIfWhileUses(shared_ptr<Statement> stmt, shared_ptr<Variable> var);
    // If related
    vector<vector<shared_ptr<Entity>>> getIfPattern();
    // While related
    vector<vector<shared_ptr<Entity>>> getWhilePattern();
=======
    vector<vector<shared_ptr<Entity>>> getAssignPattern(string& expr, bool hasWildcard);
    vector<vector<shared_ptr<Entity>>> findAssignPattern(vector<shared_ptr<AssignStatement>>& allAssign, string& expr, bool hasWildcard);
>>>>>>> master
};