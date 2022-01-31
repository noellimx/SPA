#pragma once

#include <sstream>
#include <fstream>
#include <iostream>

#include <vector>

#include "SourceTokenizer.hpp"
#include "source_processor/token/Token.hpp"

#include "database/database.hpp"
#include "utils/StreamPlus.hpp"

class SourceProcessor {
public:
    // method for processing the source program
    void process(const std::string& program);
};