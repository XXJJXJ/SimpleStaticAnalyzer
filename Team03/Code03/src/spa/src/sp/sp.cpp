#include "Sp.h"
#include "common/Variable.h"
#include "common/Procedure.h"

#include <stdio.h>
#include <vector>
#include <fstream>

Sp::Sp() {}

bool Sp::ProcessSIMPLE(string fileName) {
    try {
        std::ifstream inputfile(fileName);
        if (!inputfile.is_open()) {
            std::cerr << "Error opening file" << std::endl;
            return false;
        }
        else {
            shared_ptr<Tokenizer> tokenizer = make_shared<Tokenizer>();
            vector<shared_ptr<Token>> tokens = tokenizer->tokenize(inputfile);
            shared_ptr<Parser> parser = make_shared<Parser>();
            shared_ptr<Program> program = parser->parseSource(tokens);
            shared_ptr<DesignExtractor> design_extractor = make_shared<DesignExtractor>();
            design_extractor->extractDesign(program);
            /*Program::ProcedureListContainer procedures = program->getProcedureList();
            vector<shared_ptr<Statement>> statements = procedures[0]->getStatementList();*/

            QueryManager qm;
            vector<shared_ptr<Variable>> varStore = qm.getAllVariables();
            vector<shared_ptr<Procedure>> procStore = qm.getAllProcedures();
            vector<shared_ptr<ReadStatement>> readStore = qm.getAllReadStatements();
            vector<shared_ptr<PrintStatement>> printStore = qm.getAllPrintStatements();
            
            std::cout << "Procedure:" << procStore.front()->getProcedureName() << std::endl;
                std::cout << "variable:" << varStore.front()->getName() << std::endl;
                std::cout << "read statement no.:" << readStore.front()->getStatementNumber() << std::endl;
                std::cout << "print statement no.:" << printStore.front()->getStatementNumber() << std::endl;

            return varStore.front()->getName() == "x";
        }
    }
    catch (SpaException& e) {
        std::cout << e.what() << std::endl;
        return false;
    }
}
