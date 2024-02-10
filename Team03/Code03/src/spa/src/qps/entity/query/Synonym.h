//
// Created by ZHENGTAO JIANG on 8/2/24.
//

#ifndef SPA_SYNONYM_H
#define SPA_SYNONYM_H

#include "qps/entity/designEntity/designEntityType.h"
#include <string>


class Synonym {
private:
    DesignEntityType type;
    std::string name;
public:
    Synonym(DesignEntityType type, const std::string& name);

    [[nodiscard]] DesignEntityType getType() const;

    [[nodiscard]] const std::string& getName() const;
};


#endif //SPA_SYNONYM_H
