#include "PopulatePKB.h"

Populator::Populator()  {
    em = EntityManager::getInstance();
}

bool Populator::addProcedure(Procedure proc) {
    return true;
}
bool Populator::addPrintStatement(PrintStatement stmt) {
    return true;
}
bool Populator::addReadStatement(ReadStatement stmt) {
    return true;
}
// bool Populator::addAssignStatement(Statement stmt) {
//     return true;
// }
// bool Populator::addCallStatement(Statement stmt) {
//     return true;
// }
// bool Populator::addIfStatement(Statement stmt) {
//     return true;
// }
// bool Populator::addWhileStatement(Statement stmt) {
//     return true;
// }
// bool Populator::addConstant(Constant* c) {
//     return em->addConstant(c);
// }