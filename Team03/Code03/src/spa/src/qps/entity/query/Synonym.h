// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
#ifndef SPA_SYNONYM_H
#define SPA_SYNONYM_H

#include "common/EntityType.h"
#include <string>
#include <unordered_map>
#include <unordered_set>


#include <functional> // Required for std::hash

class Synonym {
private:
    EntityType type;
    std::string name;
public:
    Synonym(EntityType type, const std::string &name);
    Synonym(const std::string& synonymName, const std::unordered_map<std::string, EntityType>& synonymMap);

    [[nodiscard]] EntityType getType() const;

    [[nodiscard]] const std::string &getName() const;

    bool operator==(const Synonym &other) const;

};

// Define the hash function for Synonym within the std namespace
namespace std {
    template<>
    struct hash<Synonym> {
        size_t operator()(const Synonym &synonym) const {
            // Combine the hash of the name and the type for the Synonym
            return hash<string>()(synonym.getName())
                   ^ (hash<int>()(static_cast<int>(synonym.getType())) << 1);
        }
    };
}

struct SynonymPtrHash {
    size_t operator()(const std::shared_ptr<Synonym>& synonym) const {
        // Example hash function; adjust based on Synonym's attributes
        return std::hash<std::string>()(synonym->getName());
    }
};

struct SynonymPtrEqual {
    bool operator()(const std::shared_ptr<Synonym>& lhs, const std::shared_ptr<Synonym>& rhs) const {
        // Example equality function; adjust based on Synonym's attributes
        return lhs->getName() == rhs->getName();
    }
};

using SynonymPtrSet = std::unordered_set<std::shared_ptr<Synonym>, SynonymPtrHash, SynonymPtrEqual>;

#endif //SPA_SYNONYM_H

// ai-gen end