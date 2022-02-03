#pragma once

#include <sstream>
#include <fstream>
#include <iostream>

#include <vector>

#include "SourceParser.hpp"
#include "source_processor/Simple/composites/TokenSimple.hpp"

#include "database/database.hpp"
#include "utils/StreamPlus.hpp"

class SourceProcessor {
public:
    // method for processing the source program
    static void process(const std::string& program);
};