#pragma once


#include <iostream>
#include <string>
#include <set>

#include <Entity.h>
#include <Store.h>
using namespace std;

class EntityManager {
private:
    // Private constructor to prevent external instantiation
    EntityManager() {}
    // Private static instance of the class
    static EntityManager* instance;

protected:
    Store<Constant> constantStore;
    Store<string> variableStore;
private:
    void clearStore();
public:
    // Public method to get the instance of the class
    static EntityManager* getInstance();
    // Destructor to delete the instance
    bool addConstant(Constant* c);
    vector<Constant*> getAllConstants();
    // bool addVariable(string var);
    // vector<string> getAllVariables();
    static void clear();
    ~EntityManager();
};