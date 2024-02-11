#include "QueryManager.hpp"

class FakeQueryManager : public QueryManager {
    std::map<EntityType, std::vector<std::shared_ptr<Entity>>> fakeResponses;

public:
    void addFakeResponse(EntityType type, std::vector<std::shared_ptr<Entity>> response) {
        fakeResponses[type] = response;
    }

    std::vector<std::shared_ptr<Entity>> getEntitiesByType(EntityType entityType) override {
        auto it = fakeResponses.find(entityType);
        if (it != fakeResponses.end()) {
            return it->second;
        }
        return {}; // Return empty vector if no response was set up for this type
    }
};
