// TableFactory.cpp
#include "TableFactory.h"
#include "BaseTable.h"
#include "BooleanTable.h"
#include "HeaderTable.h"

std::shared_ptr<BaseTable> TableFactory::createTable(
    const std::vector<std::shared_ptr<Synonym>> &synonyms, const BaseTable &baseTable) {
    if (synonyms.empty()) {
        return std::make_shared<BooleanTable>(baseTable);
    } else {
        return HeaderTable::fromBaseTable(baseTable, synonyms);
    }
}