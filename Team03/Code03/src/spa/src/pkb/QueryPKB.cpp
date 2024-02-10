#include "QueryPKB.h"

QueryMananger::QueryMananger () {
    em = EntityManager::getInstance();
}

// vector<shared_ptr<Constant>> QueryMananger::getAllConstants() {
//     return em->getAllConstants();
// }

vector<shared_ptr<Variable>> QueryMananger::getAllVariables() {
    return em->getAllVariables();
}

vector<shared_ptr<Procedure>> QueryMananger::getAllProcedures() {
    return em->getAllProcedures();
}

vector<shared_ptr<PrintStatement>> QueryMananger::getAllPrintStatements() {
    return em->getAllPrintStatements();
}

vector<shared_ptr<ReadStatement>> QueryMananger::getAllReadStatements() {
    return em->getAllReadStatements();
}

vector<shared_ptr<Statement>> QueryMananger::getAllStatements() {
    return em->getAllStatements();
}
