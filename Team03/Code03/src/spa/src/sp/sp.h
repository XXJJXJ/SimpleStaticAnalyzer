#pragma once

#include "sp/tokenizer/Tokenizer.h"
#include "sp/design_extractor/DesignExtractor.h"

using namespace std;

class Sp {
public:
	Sp();
	bool ProcessSIMPLE(string fileName);
};