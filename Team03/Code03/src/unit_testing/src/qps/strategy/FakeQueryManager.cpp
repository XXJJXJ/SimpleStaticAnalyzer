#include <map>
#include <vector>
#include <memory>
#include "pkb/QueryPKB.h"

// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/5a9de667-07bb-4d68-86ec-9b4e16053517
class FakeQueryManager : public QueryManager {
private:
    std::map<std::string, std::vector<std::shared_ptr<Entity>>> fakeResponses;

public:
    FakeQueryManager() = default;

    // Template method remains unchanged, as it's generic enough
    template<typename T>
    void addFakeResponse(const std::string& entityType, std::vector<std::shared_ptr<T>> response) {
        std::vector<std::shared_ptr<Entity>> genericResponse;
        for (auto& item : response) {
            genericResponse.push_back(std::static_pointer_cast<Entity>(item));
        }
        fakeResponses[entityType] = genericResponse;
    }

    // Specific overrides for Procedure and Variable
    std::vector<std::shared_ptr<Procedure>> getAllProcedures() override {
        auto it = fakeResponses.find("Procedure");
        if (it != fakeResponses.end()) {
            // Convert back to specific shared_ptr type
            std::vector<std::shared_ptr<Procedure>> specificResponse;
            for (auto& entity : it->second) {
                specificResponse.push_back(std::static_pointer_cast<Procedure>(entity));
            }
            return specificResponse;
        }
        return {};
    }

    std::vector<std::shared_ptr<Variable>> getAllVariables() override {
        auto it = fakeResponses.find("Variable");
        if (it != fakeResponses.end()) {
            // Convert back to specific shared_ptr type
            std::vector<std::shared_ptr<Variable>> specificResponse;
            for (auto& entity : it->second) {
                specificResponse.push_back(std::static_pointer_cast<Variable>(entity));
            }
            return specificResponse;
        }
        return {};
    }

    // Optionally, implement other getAll* methods if needed, returning empty vectors
};

// ai-gen end