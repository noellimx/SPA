#pragma once

#include <string>
#include <vector>
#include "query_processor/Query/Query.hpp"

// A class to tokenize a program / query string into a vector of tokens
class QueryParser {

private:
  int _cursor = 0;
  std::string text;
public:
  // default constructor
  QueryParser() = delete;
  QueryParser(std::string queryTxt) : text(std::move(queryTxt)) {}

  // destructor
  ~QueryParser();

  // method for tokenizing a program / query string
  void _parseDeclarationsInto(Query &qr);
  void _parseSelectClInto(Query &qr);
  void parseInto(Query &qr);
};

