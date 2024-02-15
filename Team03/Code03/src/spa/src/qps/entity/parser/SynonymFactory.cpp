#include "SynonymFactory.h"
#include <string>
#include <vector>

SynonymFactory::SynonymFactory() {}
SynonymFactory::~SynonymFactory() {}

std::shared_ptr<EntityObject> SynonymFactory::createEntityObject(const std::vector<std::string>& token) {
    //TODO: implement
    EntityType entityType = convertStringToEntityType(token[0]);
	Synonym syn(entityType, token[1]);
    std::shared_ptr<Synonym> sharedSyn = std::make_shared<Synonym>(syn);

	return sharedSyn;
}


EntityType SynonymFactory::convertStringToEntityType(std::string curr) {
    // ai-gen start(gpt, 1, e)
    // https://chat.openai.com/share/56b9766f-27cb-4a36-a0ed-188e5b5a598a

    EntityType entityType{};

    if (curr == "stmt") {
        entityType = EntityType::Stmt;
    }
    else if (curr == "read") {
        entityType = EntityType::Read;
    }
    else if (curr == "print") {
        entityType = EntityType::Print;
    }
    else if (curr == "call") {
        entityType = EntityType::Call;
    }
    else if (curr == "while") {
        entityType = EntityType::While;
    }
    else if (curr == "if") {
        entityType = EntityType::If;
    }
    else if (curr == "assign") {
        entityType = EntityType::Assign;
    }
    else if (curr == "variable") {
        entityType = EntityType::Variable;
    }
    else if (curr == "constant") {
        entityType = EntityType::Constant;
    }
    else if (curr == "procedure") {
        entityType = EntityType::Procedure;
    }
    else if (curr == "Select") {
        entityType == EntityType::Variable; //temporary
    }
    else {
        //None of the above, gives a Unknown Entity type
        entityType = EntityType::Unknown;
    }
    //ai-gen end

    return entityType;
}