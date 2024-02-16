#include "DeclarationsParser.h"
#include "common/EntityType.h"

DeclarationsParser::DeclarationsParser() {}
DeclarationsParser::~DeclarationsParser() {}
std::vector<std::shared_ptr<Synonym>> DeclarationsParser::parse(std::vector<std::string> tokens) {
	//Todo: implement
	std::vector<std::shared_ptr<Synonym>> declarations = {};
	Synonym syn(EntityType::Variable, "variable");
	std::shared_ptr<Synonym> sharedSyn = std::make_shared<Synonym>(syn);
	declarations.push_back(sharedSyn);

	return declarations;
}