#include "QueryPKB.h"

QueryManager::QueryManager () {
    am = AbstractionManager::getInstance();
    em = EntityManager::getInstance();
    pm = PatternManager::getInstance();
}

void QueryManager::clear() {
    EntityManager::clear();
    AbstractionManager::clear();
}

vector<shared_ptr<Constant>> QueryManager::getAllConstants() {
    return em->getAllConstants();
}

vector<shared_ptr<Variable>> QueryManager::getAllVariables() {
    return em->getAllVariables();
}

vector<shared_ptr<Procedure>> QueryManager::getAllProcedures() {
    return em->getAllProcedures();
}

vector<shared_ptr<PrintStatement>> QueryManager::getAllPrintStatements() {
    return em->getAllPrintStatements();
}

vector<shared_ptr<ReadStatement>> QueryManager::getAllReadStatements() {
    return em->getAllReadStatements();
}

vector<shared_ptr<Statement>> QueryManager::getAllStatements() {
    return em->getAllStatements();
}

vector<shared_ptr<AssignStatement>> QueryManager::getAllAssignStatements() {
    return em->getAllAssignStatements();
}

vector<shared_ptr<CallStatement>> QueryManager::getAllCallStatements() {
    return em->getAllCallStatements();
}

vector<shared_ptr<IfStatement>> QueryManager::getAllIfStatements() {
    return em->getAllIfStatements();
}

vector<shared_ptr<WhileStatement>> QueryManager::getAllWhileStatements() {
    return em->getAllWhileStatements();
}

// Abstractions
unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> QueryManager::getFollowS() {
    return am->getFollowS();
};
unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> QueryManager::getFollowT() {
    return am->getFollowT();
};

unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> QueryManager::getParentS() {
    return am->getParentS();
};
unordered_map<shared_ptr<Statement>, set<shared_ptr<Statement>>> QueryManager::getParentT() {
    return am->getParentT();
};

unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> QueryManager::getUseByAssign() {
    return am->getUseByAssign();
};
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> QueryManager::getUseByPrint() {
    return am->getUseByPrint();
}; 
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> QueryManager::getUseByCall() {
    return am->getUseByCall();
};
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> QueryManager::getUseByIfWhile() {
    return am->getUseByIfWhile();
};
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> QueryManager::getUseAll() {
    return am->getUseAll();
};
unordered_map<string, set<shared_ptr<Variable>>> QueryManager::getUseByProcedure() {
    return am->getUseByProcedure();
};

unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> QueryManager::getModifyByAssign() {
    return am->getModifyByAssign();
};
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> QueryManager::getModifyByRead() {
    return am->getModifyByRead();
};
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> QueryManager::getModifyByCall() {
    return am->getModifyByCall();
};
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> QueryManager::getModifyByIfWhile() {
    return am->getModifyByIfWhile();
};
unordered_map<shared_ptr<Statement>, set<shared_ptr<Variable>>> QueryManager::getModifyAll() {
    return am->getModifyAll();
};
unordered_map<string, set<shared_ptr<Variable>>> QueryManager::getModifyByProcedure() {
    return am->getModifyByProcedure();
};

vector<shared_ptr<AssignStatement>> QueryManager::getAssignPattern(string targetVariable, string expr, bool hasWildcard) {
    if (pm->hasAssignPattern(expr, hasWildcard)) {
        return pm->getAssignPattern(targetVariable, expr, hasWildcard);
    } else {
        auto allAssign = em->getAllAssignStatements();
        return pm->findAssignPattern(allAssign, targetVariable, expr, hasWildcard); // will cache results
    }
}
