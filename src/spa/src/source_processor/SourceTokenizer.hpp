#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "source_processor/token/Token.hpp"
#include "source_processor/token/TokenProcedure.hpp"
#include "source_processor/token/TokenStatementAssignment.hpp"
#include "source_processor/token/TokenVariable.hpp"
#include "source_processor/token/TokenConstant.hpp"

// A class to tokenize a program / query string into a vector of tokens
class SourceTokenizer {

private:
  int lineNo = 1;
  int cursor = 0;
  std::string source;

  std::map<std::string,Token *> variables = std::map<std::string,Token *>();

  bool isNotEndOfSource();

  bool isCursorStartOfWord();

  void moveCursor();

  void moveCursorToEndOfWord();
  void moveCursorToEndOfProcedureName();
  void moveCursorToNextBrace();
  void moveCursorFromBeforeWhiteSpaceToAfterWhiteSpace();
  void moveToStatementBreakOrClosingBrace();
protected:
  int getNextLineNo () {
    int current = lineNo;
    lineNo++;
    return current;
  }
public:
  // default constructor
  SourceTokenizer() = delete;

  explicit SourceTokenizer(const std::string &source);

  // destructor
  ~SourceTokenizer();

  void tokenize(std::vector<Token *> &, std::vector<TokenStatementBreakBySemiColon *> &, std::map<std::string,Token *> &, std::map<std::string,Token *> &);
};

