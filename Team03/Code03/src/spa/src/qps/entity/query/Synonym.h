#ifndef SPA_SYNONYM_H
#define SPA_SYNONYM_H

#include "common/EntityType.h"
#include "qps/entity/parser/EntityObject.h"
#include <string>


class Synonym : public EntityObject {
private:
    EntityType type;
    std::string name;
public:
    Synonym(EntityType type, const std::string& name);

    [[nodiscard]] EntityType getType() const;

    [[nodiscard]] const std::string& getName() const;

    bool operator==(const Synonym& other) const;
};


#endif //SPA_SYNONYM_H
