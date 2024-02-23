#include "qps/entity/query/Synonym.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class DeclarationsParser {
public:
    DeclarationsParser();

    ~DeclarationsParser();

    static std::vector<std::shared_ptr<Synonym>> parse(const std::vector<std::string> &tokens,
                                                       std::unordered_map<std::string, EntityType> &synonymMap);

private:
    static EntityType mapTokenToEntityType(const std::string &token);
};