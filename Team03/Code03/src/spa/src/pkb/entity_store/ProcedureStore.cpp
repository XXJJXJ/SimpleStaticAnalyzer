#include "ProcedureStore.h"

bool ProcedureStore::add(shared_ptr<Procedure> procedure) {
    // check if it exists, procedures should not have duplicate 
    if (nameToProcMap.find(procedure->getProcedureName()) != nameToProcMap.end()) {
        return false;
    }
    nameToProcMap[procedure->getProcedureName()] = procedure;
    return true;
}

vector<shared_ptr<Procedure>> ProcedureStore::getAll() const {
    vector<shared_ptr<Procedure>> allProcedures;
    for (const auto& pair : nameToProcMap) {
        allProcedures.push_back(pair.second);
    }
    return allProcedures;
}

// getByProcName(string name)

void ProcedureStore::clear() {
    // clean the maps
    nameToProcMap.clear();
}

ProcedureStore::~ProcedureStore() {
    clear();
}