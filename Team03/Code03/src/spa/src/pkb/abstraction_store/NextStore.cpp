#include "NextStore.h"

bool NextStore::add(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
    directMap[stmt1].insert(stmt2);
    // toposort similar to callStore, but for statements and save it for getTransitive
    nonRoots.insert(stmt2);
    if (roots.find(stmt2) != roots.end()) {
        roots.erase(stmt2);
    }
    if (nonRoots.find(stmt1) == nonRoots.end()) {
        roots.insert(stmt1);
    }
    return true;
}

unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> NextStore::getTransitiveMap() {
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> nextStarMap;
    for (auto & first : roots) {
        dfsAdd(first, nextStarMap);
    }
    return nextStarMap;
}

vector<vector<shared_ptr<Entity>>> NextStore::getTransitive() {
    // dfs add, using preprocessed roots
    // map resets every call, no caching allowed ¯\_(ツ)_/¯
    return getStmtPairs(getTransitiveMap());
}

vector<shared_ptr<Statement>> flattenStmtList(StatementList stmtList) {
    vector<shared_ptr<Statement>> res;
    for (auto & stmt : stmtList) {
        res.push_back(stmt);
        switch (stmt->getStatementType())
        {
        case EntityType::While:
        {
            auto whileStmt = dynamic_pointer_cast<WhileStatement>(stmt);
            auto flattenContainer = flattenStmtList(whileStmt->getStatementList());
            res.insert(res.end(), flattenContainer.begin(), flattenContainer.end());
            break;
        }
        case EntityType::If:
        {
            auto ifStmt = dynamic_pointer_cast<IfStatement>(stmt);
            auto flattenThenContainer = flattenStmtList(ifStmt->getThenStatementList());
            res.insert(res.end(), flattenThenContainer.begin(), flattenThenContainer.end());
            auto flattenElseContainer = flattenStmtList(ifStmt->getElseStatementList());
            res.insert(res.end(), flattenElseContainer.begin(), flattenElseContainer.end());
            break;
        }
        default:
            break;
        }
    }
    return res;
}

/*
Idea is to traverse the "main" branch, while statement requires special handling

while statement, recurse on main branch first, then get the set of all statements within the while statement
and add all stmt within as next* of itself, those from the main branch as well

if statement seems different, but actually can be treated just the same as other statements, optimization present to
reduce duplicate calculation
*/
unordered_set<shared_ptr<Statement>> NextStore::dfsAdd(
    shared_ptr<Statement> stmt,
    unordered_map<shared_ptr<Statement>,unordered_set<shared_ptr<Statement>>>& accumulatedResults) 
{
    // optimize a little, for the if statement then block and else block eventually reach the same next*
    if (accumulatedResults.find(stmt) != accumulatedResults.end()) {
        return accumulatedResults[stmt];
    }
    unordered_set<shared_ptr<Statement>> res;
    switch (stmt->getStatementType()) {
    case EntityType::While: {
        auto nexts = directMap[stmt];
        for (auto & n : nexts) {
            // start of while loop, we should have only 2 options, 1 is stmt# + 1, one is much greater, always go for the greater
            if (n->getStatementNumber() == stmt->getStatementNumber() + 1) {
                // we skip the while internals first
                continue;
            }
            auto futureNexts = dfsAdd(n, accumulatedResults);
            res.insert(futureNexts.begin(), futureNexts.end());
            res.insert(n);
        }
        // while loop special, should add itself
        res.insert(stmt);
        // cast it to while
        shared_ptr<WhileStatement> whileStmt = dynamic_pointer_cast<WhileStatement>(stmt);
        auto stmtList = whileStmt->getStatementList();
        // Need to flatten this stmtList for nested if whiles
        auto flattenedStmtList = flattenStmtList(stmtList);
        // add all statement within while to this set
        res.insert(flattenedStmtList.begin(), flattenedStmtList.end()); 
        // since its a while statement, it can reach itself and the same "future"
        for (auto &internalStmt : flattenedStmtList) {
            accumulatedResults[internalStmt] = res;
        }
        break;
    }
    default: {
        // other statement types
        // calls, print, read, assign should only have 1 direction (unless inside a while loop, which we should have skipped in the while clause^ above)
        // ifs have 2 direction, but logic can be generalized as such
        auto nexts = directMap[stmt];
        // if has 2, traverse both then & else block: it is fine even if it has internal while, should be appropriately taken care of
        // should only have 1 for non-if statement types
        for (auto & n : nexts) {
            auto futureNexts = dfsAdd(n, accumulatedResults);
            res.insert(futureNexts.begin(), futureNexts.end());
            res.insert(n);
        }
    }
    }
    accumulatedResults[stmt] = res;
    return res;
}

void NextStore::clear() {
    StmtStmtStore::clear();
    roots.clear();
    nonRoots.clear();
}

NextStore::~NextStore() {
    clear();
}