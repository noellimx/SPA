#pragma once
#include <sstream>
#include <fstream>
#include <iostream>

#include <vector>

#include "SourceTokenizer.h"

#include "database/database.h"
#include "utils/StreamPlus.h"

using namespace std;

class SourceProcessor {
public:
	// method for processing the source program
	void process(std::string program);
};