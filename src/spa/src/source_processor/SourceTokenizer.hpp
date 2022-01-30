#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "source_processor/token/Token.hpp"
#include "source_processor/token/TokenProcedure.hpp"
#include "source_processor/token/TokenStatementAssignment.hpp"


// A class to tokenize a program / query string into a vector of tokens
class SourceTokenizer {

private:
    int cursor = 0;
    std::string source;

    bool isNotEndOfSource();

    bool isCursorStartOfWord();

    void moveCursor();

    void moveCursorToEndOfWord();
    void moveCursorToEndOfProcedureName();
    void moveCursorToNextBrace();
    void moveToStatementBreakOrClosingBrace();

public:
    // default constructor
    SourceTokenizer() = delete;

    explicit SourceTokenizer(const std::string &source);

    // destructor
    ~SourceTokenizer();

    // method for tokenizing a program / query string
//    std::vector<Token *> &  tokenize(std::vector<Token *> &tokens);
    void  tokenize(std::vector<Token *> &tokens);
};

