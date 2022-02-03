#pragma once

#include <string>
#include <vector>
#include "query_processor/aggregator/Query.hpp"

// A class to tokenize a program / query string into a vector of tokens
class QueryTokenizer {

private:
  int _cursor = 0;
  std::string text;
public:
  // default constructor
  QueryTokenizer() = delete;
  QueryTokenizer(std::string queryTxt) : text(std::move(queryTxt)) {}

  // destructor
  ~QueryTokenizer();

  // method for tokenizing a program / query string
  void _tokenizeDeclarations(Query &);
  void _tokenizeSelectCl(Query &);
  void tokenize(Query &);
};

