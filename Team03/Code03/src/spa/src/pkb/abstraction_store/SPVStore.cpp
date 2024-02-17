#include "SPVStore.h"

bool SPVStore::add(shared_ptr<Statement> stmt, shared_ptr<Variable> var) {
    string stmtType = stmt->getStatementType();
    allStmts[stmt].insert(var);
    // duplicates
    procedureToVar[stmt->getProcedureName()].insert(var);
    if (stmtType == StatementType::assignType) {
        assignStmts[stmt].insert(var);
    } else if (stmtType == StatementType::printType) {
        printStmts[stmt].insert(var);
    } else if (stmtType == StatementType::callType) {
        callStmts[stmt].insert(var);
    } else if (stmtType == StatementType::readType) {
        readStmts[stmt].insert(var);
    } else if (stmtType == StatementType::ifType || stmtType == StatementType::whileType) {
        ifWhileStmts[stmt].insert(var);
    } else {
        // unknown statement type
        return false;
    }
    return true;
};

unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> SPVStore::getByAssign() {
    return assignStmts;
};
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> SPVStore::getByPrint() {
    return printStmts;
};
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> SPVStore::getByRead() {
    return readStmts;
};
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> SPVStore::getByIfWhileStmt() {
    return ifWhileStmts;
};
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> SPVStore::getByCall() {
    return callStmts;
};
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> SPVStore::getByAllStmt() {
    return allStmts;
};
unordered_map<string, set<shared_ptr<Variable>>> SPVStore::getByProcedure() {
    return procedureToVar;
};
void SPVStore::clear() {
    allStmts.clear();
    assignStmts.clear();
    printStmts.clear();
    readStmts.clear();
    ifWhileStmts.clear();
    callStmts.clear();
    procedureToVar.clear();
};
SPVStore::~SPVStore() {
    clear();
};