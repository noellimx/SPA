#pragma once

#include <string>
#include <vector>
#include "database/database.hpp"

class QueryProcessor {
public:
  QueryProcessor() = delete;
  ~QueryProcessor();

  static void parseAndEvaluate(std::string select_cl_text, std::vector<std::string> &results);
};