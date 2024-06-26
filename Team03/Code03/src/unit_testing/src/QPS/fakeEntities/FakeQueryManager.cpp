#include <map>
#include <vector>
#include <memory>
#include "pkb/QueryPKB.h"
#include "common/Entity.h"

// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a

class FakeQueryManager : public QueryManager {
private:
    // Mapping from EntityType as a string to a vector of Entity shared pointers
    std::map<EntityType, std::vector<std::shared_ptr<Entity>>> fakeResponses;

    vector<vector<shared_ptr<Entity>>> fakeFollows;
    vector<vector<shared_ptr<Entity>>> fakeFollowsT;

    vector<vector<shared_ptr<Entity>>> fakeParents;
    vector<vector<shared_ptr<Entity>>> fakeParentT;

    vector<vector<shared_ptr<Entity>>> fakeUses;

    vector<vector<shared_ptr<Entity>>> fakeModifies;
    vector<vector<shared_ptr<Entity>>> fakeCalls;
    vector<vector<shared_ptr<Entity>>> fakeCallsT;

    vector<vector<shared_ptr<Entity>>> fakeAssignsWithPattern;
    vector<vector<shared_ptr<Entity>>> fakeIfPattern;
    vector<vector<shared_ptr<Entity>>> fakeWhilePattern;

    vector<vector<shared_ptr<Entity>>> fakeNext;
    vector<vector<shared_ptr<Entity>>> fakeNextT;

    vector<vector<shared_ptr<Entity>>> fakeAffects;

public:
    FakeQueryManager() = default;

    // Override to add responses for specific entity types
    template<typename T>
    void addFakeResponse(EntityType entityType, std::vector<std::shared_ptr<T>> response) {
        // Convert T (derived from Entity) vector to Entity vector
        std::vector<std::shared_ptr<Entity>> genericResponse(response.begin(), response.end());
        fakeResponses[entityType] = genericResponse;
    }

    // Specifies the return value of getAssignPattern()
    void setFakeAssignsWithPattern(vector<vector<shared_ptr<Entity>>> stmt) {
        fakeAssignsWithPattern = stmt;
    }

    vector<vector<shared_ptr<Entity>>> getAssignPattern(string useless2, bool useless3) override {
        return fakeAssignsWithPattern;
    }

    void setAllFakeVariable(vector<shared_ptr<Entity>> var) {
        fakeResponses[EntityType::Variable] = var;
    }

    void addFakeFollows(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
        fakeFollows.push_back({stmt1, stmt2});
    }

    void addFakeFollowsT(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
        fakeFollowsT.push_back({stmt1, stmt2});
    }

    void addFakeParent(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
        fakeParents.push_back({stmt1, stmt2});
    }

    void addFakeParentT(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
        fakeParentT.push_back({stmt1, stmt2});
    }
  
    void addFakeUses(shared_ptr<Statement> stmt, shared_ptr<Variable> var) {
        fakeUses.push_back({ stmt, var });
    }

    void addFakeModifies(shared_ptr<Statement> stmt, shared_ptr<Variable> var) {
        fakeModifies.push_back({ stmt, var });
    }

    void addFakeCalls(shared_ptr<Procedure> caller, shared_ptr<Procedure> callee) {
        fakeCalls.push_back({caller, callee});
    }

    void addFakeCallsT(shared_ptr<Procedure> caller, shared_ptr<Procedure> callee) {
        fakeCallsT.push_back({caller, callee});
    }

    void addFakeIfPattern(shared_ptr<Entity> stmt, shared_ptr<Entity> var) {
        fakeIfPattern.push_back({stmt, var});
    }

    void addFakeWhilePattern(shared_ptr<Entity> stmt, shared_ptr<Entity> var) {
        fakeWhilePattern.push_back({stmt, var});
    }

    void addFakeNext(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
        fakeNext.push_back({stmt1, stmt2});
    }

    void addFakeNextT(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
        fakeNextT.push_back({stmt1, stmt2});
    }

    void addFakeAffects(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
        fakeAffects.push_back({stmt1, stmt2});
    }

    // New method to get all entities by type
    std::vector<std::shared_ptr<Entity>> getAllEntitiesByType(EntityType entityType)
    override {
        auto it = fakeResponses.find(entityType);
        if (it != fakeResponses.end()) {
            return it->second;
        }
        return {};
    }

    vector<vector<shared_ptr<Entity>>> getFollowS()
    override {
        return fakeFollows;
    }

    vector<vector<shared_ptr<Entity>>> getFollowT() override {
        return fakeFollowsT;
    }

    vector<vector<shared_ptr<Entity>>> getParentS() override {
        return fakeParents;
    }

    vector<vector<shared_ptr<Entity>>> getParentT() override {
        return fakeParentT;
    }
  
    vector<vector<shared_ptr<Entity>>> getUseByType(EntityType entType) override {
        return fakeUses;
    }

    vector<vector<shared_ptr<Entity>>> getModifyByType(EntityType entType) override {
        return fakeModifies;
    }

    vector<vector<shared_ptr<Entity>>> getCallS() override {
        return fakeCalls;
    }

    vector<vector<shared_ptr<Entity>>> getCallT() override {
        return fakeCallsT;
    }

    vector<vector<shared_ptr<Entity>>> getIfPattern() override {
        return fakeIfPattern;
    }

    vector<vector<shared_ptr<Entity>>> getWhilePattern() override {
        return fakeWhilePattern;
    }

    vector<vector<shared_ptr<Entity>>> getNextS() override {
        return fakeNext;
    }

    vector<vector<shared_ptr<Entity>>> getNextT() override {
        return fakeNextT;
    }

    vector<vector<shared_ptr<Entity>>> getAffects() override {
        return fakeAffects;
    }
    // Implement other necessary virtual functions from QueryManager
};
// ai-gen end