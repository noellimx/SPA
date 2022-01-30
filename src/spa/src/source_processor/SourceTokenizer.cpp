#include "SourceTokenizer.hpp"

// constructor
SourceTokenizer::SourceTokenizer(const std::string &_source) : source(_source) {
}

// destructor
SourceTokenizer::~SourceTokenizer() {}

bool SourceTokenizer::isNotEndOfSource() {
    return cursor < source.length();
}

bool SourceTokenizer::isCursorStartOfWord() {
    char ch = source.at(cursor);
    return isalpha(ch);
}

void SourceTokenizer::moveCursorFromBeforeWhiteSpaceToAfterWhiteSpace() {
    char ch = source.at(cursor + 1);
    if (ch != ' ') {
        throw "First lookahead should be a white space";
    }
    while (ch == ' ') {
        moveCursor();
        ch = source.at(cursor + 1);
    }
    moveCursor();
}

void SourceTokenizer::moveCursor() {
    cursor++;
}


void SourceTokenizer::moveCursorToEndOfWord() {
    char ch = source.at(cursor + 1); // look ahead so cursor will stop at the final alphanumeric of the word.
    while (isalpha(ch) || isdigit(ch)) {
        moveCursor();
        ch = source.at(cursor + 1);
    }
}

void SourceTokenizer::moveCursorToEndOfProcedureName() {
    SourceTokenizer::moveCursorToEndOfWord();
}

void SourceTokenizer::moveCursorToNextBrace() {
    char ch = source.at(cursor); // look ahead so cursor will stop at the final alphanumeric of the word.
    while (!(ch == '{' || ch == '}')) {
        moveCursor();
        ch = source.at(cursor);
    }
}

void SourceTokenizer::moveToStatementBreakOrClosingBrace() {
    char ch = source.at(cursor); // look ahead so cursor will stop at the final alphanumeric of the word.
    while (!(ch == ';' || ch == '}')) {
        moveCursor();
        ch = source.at(cursor);
    }
}

// method to tokenize a program / query std::string
// it currently tokenizes the std::string into a vector of 
// words (any alphanumeric sequence of characters starting with a letter, e.g., "num1"),
// numbers (any numeric sequence of characters, e.g., "1001"),
// and punctuations (any other non-space characters, e.g., "=", ";", "{", "}").
// it should be extended as needed to handle additional SIMPLE / PQL grammar rules.
void SourceTokenizer::tokenize(std::vector<Token *> &tokens) {
    tokens.clear();
    while (isNotEndOfSource()) {
        if (isCursorStartOfWord()) {
            int cursorStartWord = cursor;
            moveCursorToEndOfWord();
            int cursorEndWord = cursor;
            std::string word = source.substr(cursorStartWord, cursorEndWord - cursorStartWord + 1);
            if ("procedure" == word) {
                moveCursorFromBeforeWhiteSpaceToAfterWhiteSpace(); // Move to space.
                int cursorStartProcedureName = cursor;
                moveCursorToEndOfProcedureName();
                int cursorEndProcedureEnd = cursor;
                std::string procedureName = source.substr(cursorStartProcedureName,
                                                          cursorEndProcedureEnd - cursorStartProcedureName + 1);
                auto *token = new TokenProcedure(procedureName);
                tokens.push_back(token); // The first token of every set is a procedure token.
                moveCursor(); // move out of procedure name
                char delimiterBetweenProcedureNameAndBody = source.at(cursor);
                if (delimiterBetweenProcedureNameAndBody != ' ') {
                    throw "procedure name and body should be minimally delimited by space ";
                }

                moveCursorToNextBrace();
                int cursorBodyOpeningBrace = cursor;
                int openingBraceCount = 1; // Cursor at the opening brace
                int closingBraceCount = 0;
                if (source.at(cursor) != '{') {
                    throw "after delimiter between procedure name and body, first character should be {";
                }

                while (openingBraceCount !=
                       closingBraceCount) { // while the final bracket of the procedure body has not been found
                    moveCursor();
                    int cursorStartStatement = cursor;
                    moveToStatementBreakOrClosingBrace();
                    char statementBreakOrClosingBrace = source.at(cursor);
                    if (statementBreakOrClosingBrace == '}') {
                        closingBraceCount++;
                    } else if (statementBreakOrClosingBrace == ';') {
                        int cursorEndStatement = cursor;
                        std::string stmt = source.substr(cursorStartStatement,
                                                         cursorEndStatement - cursorStartStatement + 1);
                        auto *tkstmt = new TokenStatementAssignment();
                        tokens.push_back(tkstmt);
                    }
                }
            }
        }
        moveCursor(); // move cursor to prevent endless loop;
    }
}

