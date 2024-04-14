#include <memory>
#include <vector>
class Synonym;
class BaseTable;

class TableFactory {
public:
    static std::shared_ptr<BaseTable> createTable(
        const std::vector<std::shared_ptr<Synonym>> &synonyms,
        const BaseTable &baseTable);
};


