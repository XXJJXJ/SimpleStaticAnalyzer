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

public:
    FakeQueryManager() = default;

    // Override to add responses for specific entity types
    template<typename T>
    void addFakeResponse(EntityType entityType, std::vector<std::shared_ptr<T>> response) {
        // Convert T (derived from Entity) vector to Entity vector
        std::vector<std::shared_ptr<Entity>> genericResponse(response.begin(), response.end());
        fakeResponses[entityType] = genericResponse;
    }

    void addFakeFollows(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
        fakeFollows.push_back({stmt1, stmt2});
    }

    void addFakeFollowsT(shared_ptr<Statement> stmt1, shared_ptr<Statement> stmt2) {
        fakeFollowsT.push_back({stmt1, stmt2});
    }

    // New method to get all entities by type
    std::vector<std::shared_ptr<Entity>> getAllEntitiesByType(EntityType entityType) override {
        auto it = fakeResponses.find(entityType);
        if (it != fakeResponses.end()) {
            return it->second;
        }
        return {};
    }

    vector<vector<shared_ptr<Entity>>> getFollowS() override {
        return fakeFollows;
    }

    vector<vector<shared_ptr<Entity>>> getFollowT() override {
        return fakeFollowsT;
    }

    // Implement other necessary virtual functions from QueryManager
};
// ai-gen end