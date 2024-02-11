

#ifndef SPA_SYNONYM_H
#define SPA_SYNONYM_H

#include "common/EntityType.h"
#include <string>


class Synonym {
private:
    EntityType type;
    std::string name;
public:
    Synonym(EntityType type, const std::string& name);

    [[nodiscard]] EntityType getType() const;

    [[nodiscard]] const std::string& getName() const;
};


#endif //SPA_SYNONYM_H
