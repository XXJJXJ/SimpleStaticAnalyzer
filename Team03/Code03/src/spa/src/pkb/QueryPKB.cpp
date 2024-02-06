#include "QueryPKB.h"

QueryMananger::QueryMananger () {
    em = EntityManager::getInstance();
}

vector<Constant*> QueryMananger::getAllConstants() {
    return em->getAllConstants();
}