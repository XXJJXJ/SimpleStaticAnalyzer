#include <memory>
#include <string>
#include <vector>
#include "qps/entity/query/Synonym.h"

class SelectionsParser {
public:
	SelectionsParser();
	~SelectionsParser();
	std::vector<std::shared_ptr<Synonym>> parse(std::vector<std::string> tokens);
};