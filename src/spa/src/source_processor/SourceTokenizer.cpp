#include "SourceTokenizer.hpp"

// constructor
SourceTokenizer::SourceTokenizer(const std::string &_source) : source(std::move(_source)) {
}

// destructor
SourceTokenizer::~SourceTokenizer() = default;

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
void SourceTokenizer::tokenize(std::vector<Token *> &procedureTokens,
                               std::vector<InterfaceStatementWithLineNo *> &statementTokens,
                               std::map<std::string, Token *> &variableTokens,
                               std::map<std::string, Token *> &constantTokens) {
  procedureTokens.clear();
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
        auto *tokenProcedure = new TokenProcedure(procedureName);
        procedureTokens.push_back(tokenProcedure); // The first token of every set is a procedure token.
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
            closingBraceCount) { // while the final closing brace of the procedure body has not been found
          moveCursorFromBeforeWhiteSpaceToAfterWhiteSpace(); // move to the first alphanumeric character.
          int cursorFirstAlphaNumericCharacter = cursor; //
          moveToStatementBreakOrClosingBrace();
          char statementBreakOrClosingBrace = source.at(cursor);
          if (statementBreakOrClosingBrace == '}') {
            closingBraceCount++;
          } else if (statementBreakOrClosingBrace == ';') { // a statement is found
            int cursorEndSemiColon = cursor; // end of statement cursor
            // trim starting whitespace
            int moving = cursorFirstAlphaNumericCharacter;
            while (source.at(moving + 1) != ' ') { // move scoped cursor before whitespace
              moving++;
            }

            // LHS
            std::string lhs = source.substr(cursorFirstAlphaNumericCharacter,
                                            moving - cursorFirstAlphaNumericCharacter + 1);

            if (lhs != "read" || lhs != "print") {
              // assignment statement found .

              // LHS
              std::string var = lhs;
              auto *tokenVar = new TokenVariable(var);
              variableTokens.insert(std::pair<std::string, Token *>(var, tokenVar));

              while (source.at(moving + 1) == ' ') { // move scoped cursor before equal sign
                moving++;
              }
              moving++; // skip = sign

              if (source.at(moving) != '=') {
                std::string ss = std::string{source.at(moving)} + "-";
                throw "After LHS and its following whitespace(s), assignment should have an '=' character. Got: " + ss;
              }

              while (source.at(moving + 1) == ' ') { // move scoped cursor before first word of RHS
                moving++;
              }
              moving++;

              // Check if var or const
              bool rhsIsVarOrConst =
                  true; // assume rhs is a simple expression ( in this case is a simple term, also in turn is a simple factor)
              for (int i = moving; i < cursorEndSemiColon; i++) {
                char charRHS = source.at(i);
                if (charRHS == '+' || charRHS == '-' || charRHS == '/' || charRHS == '*' || charRHS == '%') {
                  rhsIsVarOrConst = false;
                  break;
                }
              }

              Token *tokenRHS = nullptr;

              if (rhsIsVarOrConst) {
                int cursorStartOfSimpleWordRHS = moving;
                char charStartOfSimpleWordRHS = source.at(cursorStartOfSimpleWordRHS);

                while (source.at(moving + 1) != ';') { // move scoped cursor before whitespace (end of rhs word) or eol ;
                  if(source.at(moving + 1) == ' ') break;
                  moving++;
                }

                std::string rhs = source.substr(cursorStartOfSimpleWordRHS,
                                                moving - cursorStartOfSimpleWordRHS + 1);
                if (isdigit(charStartOfSimpleWordRHS)) { // rhs is a constant
                  tokenRHS = new TokenConstant(rhs);
                  constantTokens.insert({rhs, tokenRHS});
                } else if (isalpha(charStartOfSimpleWordRHS)) { // rhs is a variable
                } else {
                  throw "Should not get here. Simple factor should start with alphanumeric" + std::string{charStartOfSimpleWordRHS} + "|" + rhs;
                }
                int thisLineNo = this->getNextLineNo();
                auto *tokenAssignment =
                    new TokenStatementAssignment(variableTokens.at(var), constantTokens.at(rhs), thisLineNo);
                tokenAssignment->setBlockScope(tokenProcedure);
                statementTokens.push_back(tokenAssignment);
                tokenProcedure->addChildToken(tokenAssignment);

              } else {

              }

            }
          }
        }
      }
    }
    moveCursor(); // move cursor to prevent endless loop;
  }
}

