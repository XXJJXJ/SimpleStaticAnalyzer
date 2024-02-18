#include "DeclarationsParser.h"
#include "common/EntityType.h"

DeclarationsParser::DeclarationsParser() {}
DeclarationsParser::~DeclarationsParser() {}
std::vector<std::shared_ptr<Synonym>> DeclarationsParser::parse(const std::vector<std::string>& tokens, std::unordered_map<std::string, EntityType>& synonymMap) {
	//Todo: implement
	std::vector<std::shared_ptr<Synonym>> declarations = {};
	Synonym syn(EntityType::Variable, "variable");
	std::shared_ptr<Synonym> sharedSyn = std::make_shared<Synonym>(syn);
	declarations.push_back(sharedSyn);

	//Todo: populate the map with the synonym name and type

	return declarations;
}