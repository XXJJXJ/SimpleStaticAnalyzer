#include "ProcedureStore.h"

bool ProcedureStore::add(shared_ptr<Procedure> procedure) {
    // check if it exists, procedures should not have duplicate 
    if (nameToProcMap.find(procedure->getName()) != nameToProcMap.end()) {
        return false;
    }
    nameToProcMap[procedure->getName()] = procedure;
    return true;
}

vector<shared_ptr<Procedure>> ProcedureStore::getAll() const {
    vector<shared_ptr<Procedure>> allProcedures;
    for (const auto& pair : nameToProcMap) {
        allProcedures.push_back(pair.second);
    }
    return allProcedures;
}

shared_ptr<Procedure> ProcedureStore::getProcByName(const string& name) {
    return nameToProcMap[name];
}

void ProcedureStore::clear() {
    // clean the maps
    nameToProcMap.clear();
}

ProcedureStore::~ProcedureStore() {
    clear();
}