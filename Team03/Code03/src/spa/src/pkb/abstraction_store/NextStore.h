#pragma once

#include <unordered_map>
#include <unordered_set>
#include "common/Entity.h"
#include "common/statement/WhileStatement.h"
#include "common/statement/IfStatement.h"
#include "common/spa_exception/SemanticErrorException.h"
#include "StmtStmtStore.h"

using namespace std;

class NextStore : public StmtStmtStore {
private:
    unordered_set<shared_ptr<Statement>> nonRoots;
    unordered_set<shared_ptr<Statement>> roots;
    unordered_set<shared_ptr<Statement>> dfsAdd(shared_ptr<Statement> stmt,unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>>& accumulatedResults);
public:
    bool add(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) override;
    // New additions/specializations for Next*
    vector<vector<shared_ptr<Entity>>> getTransitive() override;
    void clear() override;
    ~NextStore();
};