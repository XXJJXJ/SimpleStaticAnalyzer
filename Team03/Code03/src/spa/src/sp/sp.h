#pragma once

#include "sp/tokenizer/Tokenizer.h"
#include "sp/design_extractor/DesignExtractor.h"
#include <common/Program.h>
#include <sp/parser/Parser.h>
#include <common/spa_exception/SpaException.h>
#include "sp/tokenizer/Tokenizer.h"
#include "pkb/PopulatePKB.h"

using namespace std;

class Sp {
public:
	Sp();
	void ProcessSIMPLE(string fileName);
};