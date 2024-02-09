#include "PopulatePKB.h"

Populator::Populator()  {
    em = EntityManager::getInstance();
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

// bool Populator::addConstant(shared_ptr<Constant> c) {
//     return true;
// }
// bool Populator::addAssignStatement(shared_ptr<AssignStatement> stmt) {
//     return true;
// }
// bool Populator::addCallStatement(shared_ptr<CallStatement> stmt) {
//     return true;
// }
// bool Populator::addIfStatement(shared_ptr<IfStatement> stmt) {
//     return true;
// }
// bool Populator::addWhileStatement(shared_ptr<WhileStatement> stmt) {
//     return true;
// }