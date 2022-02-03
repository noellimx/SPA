#pragma once


#include <iostream>

#include <vector>

#include "SimpleParser.hpp"
#include "source_processor/Simple/composites/SimpleNode.hpp"

#include "database/database.hpp"
#include "utils/StreamPlus.hpp"

class SimpleProcessor {
public:
    static void parseAndPersist(const std::string& simple_text);
};