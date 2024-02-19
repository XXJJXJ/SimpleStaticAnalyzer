#include "sp.h"
#include "common/Variable.h"
#include "common/Procedure.h"
#include <common/spa_exception/SpaException.h>

#include <stdio.h>
#include <vector>
#include <fstream>

Sp::Sp() {}

void Sp::ProcessSIMPLE(string fileName) {
    try {
        std::ifstream inputfile(fileName);
        if (!inputfile.is_open()) {
            std::cerr << "Error opening file" << std::endl;
        }
        else {
            shared_ptr<Tokenizer> tokenizer = make_shared<Tokenizer>();
            Tokens tokens = tokenizer->tokenize(inputfile);
            shared_ptr<Parser> parser = make_shared<Parser>();
            shared_ptr<Program> program = parser->parseSource(tokens);
            shared_ptr<DesignExtractor> design_extractor = make_shared<DesignExtractor>();
            design_extractor->extractDesign(program);
            /*Program::ProcedureListContainer procedures = program->getProcedureList();
            vector<shared_ptr<Statement>> statements = procedures[0]->getStatementList();*/
        }
    }
    catch (SpaException& e) {
        std::cout << e.what() << std::endl;
    }
}
