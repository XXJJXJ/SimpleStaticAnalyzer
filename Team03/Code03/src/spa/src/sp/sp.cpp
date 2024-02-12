#include "sp.h"
#include <common/Program.h>
#include <sp/parser/Parser.h>
#include <common/spa_exception/SpaException.h>
#include "sp/tokenizer/Tokenizer.h"

#include <iostream>
#include <filesystem>

Sp::Sp() {}

bool Sp::ProcessSIMPLE(string fileName) {
    try {
        ifstream inputfile(fileName);
        if (!inputfile.is_open()) {
            std::cerr << "Error opening file" << std::endl;
        }
        else {
            shared_ptr<Tokenizer> tokenizer = make_shared<Tokenizer>();
            vector<shared_ptr<Token>> tokens = tokenizer->tokenize(inputfile);
            shared_ptr<Parser> parser = make_shared<Parser>();
            shared_ptr<Program> program = parser->parseSource(tokens);
            Program::ProcedureListContainer procedures = program->getProcedureList();
            vector<shared_ptr<Statement>> statements = procedures[0]->getStatementList();
            return true;
        }
    }
    catch (SpaException& e) {
        std::cout << e.what() << std::endl;
        return false;
    }
}
