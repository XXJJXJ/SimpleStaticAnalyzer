#include "ProcedureStore.h"

bool ProcedureStore::add(shared_ptr<Procedure> procedure) {
    // check if it exists, procedures should not have duplicate 
    if (nameToProcMap.find(procedure->getName()) != nameToProcMap.end()) {
        return false;
    }
    nameToProcMap[procedure->getName()] = procedure;
    return true;
}

vector<shared_ptr<Procedure>> ProcedureStore::getAll() {
    if (allProcedures.size() == 0) {
        for (const auto& pair : nameToProcMap) {
            allProcedures.push_back(pair.second);
        }
    }
    return allProcedures;
}

shared_ptr<Procedure> ProcedureStore::get(const string& name) {
    if (nameToProcMap.find(name) != nameToProcMap.end()) {
        return nameToProcMap[name];
    }
    return nullptr;
}

void ProcedureStore::clear() {
    // clean the maps
    nameToProcMap.clear();
    allProcedures.clear();
}

ProcedureStore::~ProcedureStore() {
    clear();
}