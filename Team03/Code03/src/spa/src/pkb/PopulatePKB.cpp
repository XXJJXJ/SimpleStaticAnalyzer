#include "PopulatePKB.h"

Populator::Populator() {
    em = EntityManager::getInstance();
    am = AbstractionManager::getInstance();
    pm = PatternManager::getInstance();
}
void Populator::clear() {
    EntityManager::clear();
    AbstractionManager::clear();
    PatternManager::clear();
}

bool Populator::addVariable(shared_ptr<Variable> var) {
    return em->addVariable(var);
}
bool Populator::addProcedure(shared_ptr<Procedure>  proc) {
    return em->addProcedure(proc);
}
bool Populator::addPrintStatement(shared_ptr<PrintStatement> stmt) {
    return em->addPrintStatement(stmt);
}
bool Populator::addReadStatement(shared_ptr<ReadStatement> stmt) {
    return em->addReadStatement(stmt);
}

bool Populator::addConstant(shared_ptr<Constant> c) {
    return em->addConstant(c);
}
bool Populator::addAssignStatement(shared_ptr<AssignStatement> stmt) {
    return em->addAssignStatement(stmt);
}
bool Populator::addCallStatement(shared_ptr<CallStatement> stmt) {
    callTempStore.push_back({stmt->getProcedureName(), stmt->getTargetProcedureName()});
    return em->addCallStatement(stmt);
}
bool Populator::addIfStatement(shared_ptr<IfStatement> stmt) {
    return em->addIfStatement(stmt);
}
bool Populator::addWhileStatement(shared_ptr<WhileStatement> stmt) {
    return em->addWhileStatement(stmt);
}

bool Populator::addFollow(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
    return am->addFollow(stmt1, stmt2);
}
bool Populator::addParent(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
    return am->addParent(stmt1, stmt2);
}
bool Populator::addUses(shared_ptr<Statement> stmt, shared_ptr<Variable> var) {
    if (stmt->isOfType(EntityType::While) || stmt->isOfType(EntityType::If)) {
        pm->addIfWhileUses(stmt, var);
    }
    return am->addUses(stmt, var);
}
bool Populator::addModifies(shared_ptr<Statement> stmt, shared_ptr<Variable> var) {
    return am->addModifies(stmt, var);
}
bool Populator::addNext(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
    return am->addNext(stmt1, stmt2);
}

void Populator::tabulate() {
    for (auto & _pair : callTempStore) {
        auto calledProcedure = em->getProcByName(_pair.second);
        if (calledProcedure == nullptr) {
            throw SemanticErrorException("Called procedure not found: " + _pair.second);
        }
        am->addCalls(em->getProcByName(_pair.first), calledProcedure);
    }
    auto callStmts = em->getAllCallStatements();
    am->tabulate(callStmts);
    callTempStore.clear();
}