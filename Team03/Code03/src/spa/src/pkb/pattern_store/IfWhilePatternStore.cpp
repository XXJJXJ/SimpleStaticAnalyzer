#include "IfWhilePatternStore.h"

void IfWhilePatternStore::add(shared_ptr<Statement> stmt, const string var) {
    cout << "Trying to adding while/ifs " << stmt->getStatementNumber() << " " << stmt->getProcedureName() << " " << var << endl;
    // unordered_map<shared_ptr<Statement>, unordered_set<string>> stmtToVar;
    stmtToVar[stmt].insert(var);
    cout << "No error supposedly" << endl;
}

vector<shared_ptr<Entity>> IfWhilePatternStore::getPattern(const string& targetVar) {
    vector<shared_ptr<Entity>> res;
    for (auto & stmtVarPair : stmtToVar) {
        if (targetVar == "" || (stmtVarPair.second.find(targetVar) != stmtVarPair.second.end())) {
            res.push_back(stmtVarPair.first);
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