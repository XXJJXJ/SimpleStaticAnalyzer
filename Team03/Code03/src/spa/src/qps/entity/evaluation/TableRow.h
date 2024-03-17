// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/69b2d8ce-dffd-44f8-b7ab-48a128e89a6a
// prompt: https://chat.openai.com/share/eadbc02c-9e25-4f11-b2bb-c215c525d944
#ifndef SPA_TABLEROW_H
#define SPA_TABLEROW_H


#include "common/Entity.h"
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <functional>

// Class to represent a row in the table.
class TableRow {
private:
    vector<shared_ptr<Entity>> values; // Stores the values of the row

public:
    explicit TableRow(const vector<shared_ptr<Entity>>& v);
    [[nodiscard]] const vector<shared_ptr<Entity>>& getValues() const;
    bool operator==(const TableRow& other) const;
    [[nodiscard]] string toString() const;
    [[nodiscard]] std::shared_ptr<Entity> getByIndex(int index) const; // New function for direct access
    friend class HeaderTable; // Allows HeaderTable to access private members of TableRow
    bool operator<(const TableRow& other) const;
};
// ai-gen end


// ai-gen start(gpt, 0, e)
// prompt: https://chat.openai.com/share/327ddcad-1334-492d-998a-c324af935205
namespace std {
    template<>
    struct hash<TableRow> {
        std::size_t operator()(const TableRow& row) const {
            std::size_t h = 0;
            for (const auto& entity : row.getValues()) {
                // Hash combining for Entity, considering both name and type
                std::size_t nameHash = std::hash<std::string>()(entity->getName());
                std::size_t typeHash = std::hash<EntityType>()(entity->getType());

                // Combine the hashes.
                std::size_t combinedHash = nameHash ^ (typeHash << 1);

                // Fold combinedHash into h
                h ^= combinedHash + 0x9e3779b9 + (h << 6) + (h >> 2);
            }
            return h;
        }
    };
}
// ai-gen end

#endif //SPA_TABLEROW_H

