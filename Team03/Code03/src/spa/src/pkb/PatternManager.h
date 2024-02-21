#pragma once

#include <memory>
#include "pattern_store/AssignPatternStore.h"

using namespace std;

class PatternManager {
private:
    PatternManager() {}
    static shared_ptr<PatternManager> instance;

    AssignPatternStore assignPatternStore;
    
public:
    static shared_ptr<PatternManager> getInstance();
    void clearStore();
    static void clear();
    // Assign relateed
    bool hasAssignPattern(string expr, bool hasWildcard);
    vector<shared_ptr<AssignStatement>> getAssignPattern(string targetVar, string expr, bool hasWildcard);
    vector<shared_ptr<AssignStatement>> findAssignPattern(vector<shared_ptr<AssignStatement>> allAssign, string targetVar, string expr, bool hasWildcard);
};