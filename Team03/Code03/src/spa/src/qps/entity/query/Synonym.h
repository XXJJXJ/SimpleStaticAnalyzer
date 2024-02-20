// ai-gen start(gpt, 1, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
#ifndef SPA_SYNONYM_H
#define SPA_SYNONYM_H

#include "common/EntityType.h"
#include <string>


#include <functional> // Required for std::hash

class Synonym {
private:
    EntityType type;
    std::string name;
public:
    Synonym(EntityType type, const std::string &name);

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

#endif //SPA_SYNONYM_H

// ai-gen end