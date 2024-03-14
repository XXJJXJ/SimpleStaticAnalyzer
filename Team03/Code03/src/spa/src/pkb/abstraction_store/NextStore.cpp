#include "NextStore.h"

bool NextStore::add(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
    directMap[stmt1].insert(stmt2);
    return true;
}

vector<vector<shared_ptr<Entity>>> NextStore::getTransitive() {
    // toposort similar to callStore, but for statements
    unordered_set<shared_ptr<Statement>> nonRoots;
    unordered_set<shared_ptr<Statement>> roots;
    for (auto & _pair : directMap) {
        for (auto & next : _pair.second) {
            nonRoots.insert(next);
            if (roots.find(next) != roots.end()) {
                roots.erase(next);
            }
        }
        if (nonRoots.find(_pair.first) == nonRoots.end()) {
            roots.insert(_pair.first);
        }
    }
    // dfs add, with while statement tailoring
    unordered_map<shared_ptr<Statement>, unordered_set<shared_ptr<Statement>>> nextStarMap;
    for (auto & first : roots) {
        dfsAdd(first, nextStarMap);
    }
    return getStmtPairs(nextStarMap);
    // map resets every call, no caching allowed ¯\_(ツ)_/¯
}


/*
Idea is to traverse the "main" branch, while statement requires special handling

while statement, recurse on main branch first, then get the set of all statements within,
the while statement and all stmt within is next* the statements

if statement seems different, but actually can be treated just the same as other statements, optimization present to
reduce calculation duplication
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
        // add all statement within while to this set
        res.insert(stmtList.begin(), stmtList.end()); 
        // since its a while statement, it can reach itself and the same "future"
        for (auto &internalStmt : stmtList) {
            accumulatedResults[internalStmt] = res;
        }
        break;
    }
    default: {
        // other statement types
        // calls, print, read, assign should only have 1 direction (unless inside a while loop, which we should have skipped in the while clause^ above)
        // ifs have 2 direction, but logic can be generalized as such
        auto nexts = directMap[stmt];
        // if has 2, traverse both / it is fine even if it has internal while, should be appropriately taken care of
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
    directMap.clear();
    transitiveMap.clear(); // should have nth, but clear jic
}

NextStore::~NextStore() {
    clear();
}