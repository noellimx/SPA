#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "source_processor/Simple/Simple.hpp"

// A class to tokenize a program / query string into a vector of tokens
class SourceTokenizer {

private:
  int lineNo = 1;
  int cursor = 0;
  std::string source;

  bool isNotEndOfSource();

  void moveCursor();

  void moveCursorToEndOfWord();
  void moveCursorToEndOfProcedureName();
  bool isCursorAtWhitespace();
  void moveCursorToNextBrace();
  void moveCursorAtBeforeWhiteSpaceToAfterWhiteSpace();
  void moveCursorAtWhiteSpaceToAfterWhiteSpace();
  void moveToStatementBreakOrClosingBrace();
protected:
  int getNextLineNo() {
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

  void tokenize(TokenSimpleBag &);
};

