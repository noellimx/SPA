#pragma once

#include <string>
#include <vector>
#include "query_processor/aggregator/Query.hpp"

// A class to tokenize a program / query string into a vector of tokens
class QueryTokenizer {

public:
  // default constructor
  QueryTokenizer();

  // destructor
  ~QueryTokenizer();

  // method for tokenizing a program / query string
  void tokenize(std::string & text, Query &);
};

