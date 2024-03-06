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
            shared_ptr<Populator> pkbPopulator = make_shared<Populator>();
            shared_ptr<Tokenizer> tokenizer = make_shared<Tokenizer>();
            shared_ptr<Cfg> cfg = make_shared<Cfg>();
            Tokens tokens = tokenizer->tokenize(inputfile);
            shared_ptr<Parser> parser = make_shared<Parser>();
            shared_ptr<Program> program = parser->parseSource(tokens);
            shared_ptr<DesignExtractor> designExtractor = make_shared<DesignExtractor>(pkbPopulator, cfg);
            designExtractor->extractDesign(program);
        }
    }
    catch (SpaException& e) {
        std::cout << e.what() << std::endl;
    }
}

// FOR TESTING PURPOSES
shared_ptr<Program> Sp::triggerTokenizerAndParser(std::string simple_string) {
    std::regex token_regex(
        R"(\bprocedure\b|\bwhile\b|\bif\b|\bthen\b|\belse\b|\bcall\b|\bread\b|\bprint\b|\btrue\b|\bfalse\b|\+|-|\*|/|%|==|!=|<|<=|>|>=|\(|\)|\{|\}|;|\=|\"|&&|\|\||!|((?!;)[a-zA-Z0-9]+))");
    std::sregex_iterator iter(simple_string.begin(), simple_string.end(), token_regex);
    std::sregex_iterator end;
    Tokens tokens;
    shared_ptr<Tokenizer> tokenizer = make_shared<Tokenizer>();
    while (iter != end) {
        tokens.push_back(tokenizer->stringToToken(iter->str()));
        ++iter;
    }
    shared_ptr<Parser> parser = make_shared<Parser>();
    return parser->parseSource(tokens);
}
