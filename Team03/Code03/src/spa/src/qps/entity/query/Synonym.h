//
// Created by ZHENGTAO JIANG on 8/2/24.
//

#ifndef SPA_SYNONYM_H
#define SPA_SYNONYM_H

#include "DesignEntityType.h"
#include <string>


class Synonym {
private:
    DesignEntityType type;
    std::string name;
public:
    Synonym(DesignEntityType type, const std::string& name);

    DesignEntityType getType() const;

    const std::string& getName() const;
};


#endif //SPA_SYNONYM_H
