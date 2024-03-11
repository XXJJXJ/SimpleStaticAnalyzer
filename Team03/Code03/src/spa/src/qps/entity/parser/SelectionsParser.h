#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "qps/entity/query/Synonym.h"

class SelectionsParser {
public:
	SelectionsParser();
	~SelectionsParser();
	std::vector<std::shared_ptr<Synonym>> parse(const std::vector<std::string>& tokens, const std::unordered_map<std::string, EntityType>& synonymMap);
private:
	static bool isBoolean(const std::vector<std::string>& tokens, const std::unordered_map<std::string, EntityType>& synonymMap);
};