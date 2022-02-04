#include "SimpleParser.hpp"

// constructor
SimpleParser::SimpleParser(const std::string &_source) : source(std::move(_source)) {
}

// destructor
SimpleParser::~SimpleParser() = default;

bool SimpleParser::isNotEndOfSource() {
  return cursor < source.length();
}

bool SimpleParser::isCursorAtWhitespace() {
  return isspace(source.at(cursor));
}

void SimpleParser::moveCursorAtBeforeWhiteSpaceToAfterWhiteSpace() {

  char ch = source.at(cursor);
  if (isspace(ch)) {
    throw "Method should be called only if the current character is non-whitespace";
  }
  moveCursor();
  ch = source.at(cursor);
  if (!isspace(ch)) {
    throw "Method should be called only if first lookahead is be a white space";
  }
  while (isspace(ch)) {
    moveCursor();
    ch = source.at(cursor);
  }
}
void SimpleParser::moveCursorAtWhiteSpaceToAfterWhiteSpace() {
  char ch = source.at(cursor);
  if (!isspace(ch)) {
    throw "Character at cursor should be a white space";
  }
  while (isspace(ch)) {
    moveCursor();
    ch = source.at(cursor);
  }
}

void SimpleParser::moveCursor() {
  cursor += 1;
}

void SimpleParser::moveCursorToEndOfWord() {
  char ch = source.at(cursor + 1); // look ahead so cursor will stop at the final alphanumeric of the word.
  while (isalpha(ch) || isdigit(ch)) {
    moveCursor();
    ch = source.at(cursor + 1);
  }
}

void SimpleParser::moveCursorToEndOfProcedureName() {
  SimpleParser::moveCursorToEndOfWord();
}

void SimpleParser::moveCursorToNextBrace() {
  char ch = source.at(cursor); // look ahead so cursor will stop at the final alphanumeric of the word.
  while (!(ch == '{' || ch == '}')) {
    moveCursor();
    ch = source.at(cursor);
  }
}

void SimpleParser::moveToStatementBreakOrClosingBrace() {
  char ch = source.at(cursor); // look ahead so cursor will stop at the final alphanumeric of the word.
  while (!(ch == ';' || ch == '}')) {
    moveCursor();
    ch = source.at(cursor);
  }
}

void SimpleParser::parseInto(Simple &simple) {
  while (isNotEndOfSource()) {
    if (isCursorAtWhitespace()) {
      moveCursorAtWhiteSpaceToAfterWhiteSpace();
    } // move to the first alphanumeric character of each procedure.

    int cursorStartWord = cursor;
    moveCursorToEndOfWord();
    int cursorEndWord = cursor;
    std::string word = source.substr(cursorStartWord, cursorEndWord - cursorStartWord + 1);
    if (!("procedure" == word)) {
      throw "procedure should start with the keyword procedure";
    }
    moveCursorAtBeforeWhiteSpaceToAfterWhiteSpace();
    int cursorStartProcedureName = cursor;
    moveCursorToEndOfProcedureName();
    int cursorEndProcedureEnd = cursor;
    std::string procedureName = source.substr(cursorStartProcedureName,
                                              cursorEndProcedureEnd - cursorStartProcedureName + 1);
    auto *sp = new SimpleProcedure(procedureName);
    simple.addProcedure(sp); // The first token of every set is a procedure token.
    moveCursor(); // move out of procedure name
    char delimiterBetweenProcedureNameAndBody = source.at(cursor);
    if (!isspace(delimiterBetweenProcedureNameAndBody)) {
      throw "procedure name and body should be minimally delimited by space ";
    }

    moveCursorToNextBrace(); // Cursor at the opening brace of body
    int cursorBodyOpeningBrace = cursor;
    int openingBraceCount = 1;
    int closingBraceCount = 0;
    if (source.at(cursor) != '{') {
      throw "after delimiter between procedure name and body, first character should be {";
    }
    moveCursor();// move cursor out of opening brace (start of body)

    while (openingBraceCount !=
        closingBraceCount) { // while the final closing brace of the procedure body has not been found

      if (isCursorAtWhitespace()) {
        moveCursorAtWhiteSpaceToAfterWhiteSpace();
      } // move to the first alphanumeric character.

      int cursorFirstAlphaNumericCharacter = cursor; //
      moveToStatementBreakOrClosingBrace();
      char statementBreakOrClosingBrace = source.at(cursor);
      if (statementBreakOrClosingBrace == '}') {
        closingBraceCount += 1;
      } else if (statementBreakOrClosingBrace == ';') { // a statement is found
        int cursorEndSemiColon = cursor; // end of statement cursor

        int moving = cursorFirstAlphaNumericCharacter;
        while (!isspace(source.at(moving + 1))) { // move scoped cursor end of alphanumeric word before whitespace
          moving += 1;
        }

        // LHS
        std::string firstWord = source.substr(cursorFirstAlphaNumericCharacter,
                                              moving - cursorFirstAlphaNumericCharacter + 1);
        if (firstWord == "read" || firstWord == "print") {

          int thisLineNo = this->getNextLineNo();

          moving += 1; // move to first whitespace after keyword read
          while (isspace(source.at(moving))) { // move scoped cursor to first alphanumeric of RHS
            moving += 1;
          }

          int cursorStartReadableVar = moving;
          char charRHS = source.at(cursorStartReadableVar);
          if (isalpha(charRHS)) {
          } else {
            throw "first character of variable to read should be alphabet";
          }

          while (isalpha(source.at(moving + 1))
              || isdigit(source.at(moving + 1))) { // move scoped cursor to last alphanumeric of RHS
            moving += 1;
          }

          std::string var_name = source.substr(cursorStartReadableVar,
                                               moving - cursorStartReadableVar + 1);
          auto *sVar = new SimpleVariable(var_name);

          simple.addVariable(sVar);

          auto *targetSVar = simple.getVariable(var_name);
          if (firstWord == "read") {
            auto *sRead = new SimpleRead(thisLineNo, targetSVar);
            simple.addRead(sRead);
          } else if (firstWord == "print") {
            auto *sPrint = new SimplePrint(thisLineNo, targetSVar);
            simple.addPrint(sPrint);
          }
        } else {
          // assignment statement found .

          // LHS
          std::string lhs = firstWord;

          auto *sVar_LHS = new SimpleVariable(lhs);
          simple.addVariable(sVar_LHS);

          moving += 1; // move out of alphanumeric word
          while (isspace(source.at(moving))) { // move scoped cursor from end of alphanumeric word to equal sign
            moving += 1;
          }

          if (source.at(moving) != '=') {
            std::string ss = "|" + std::to_string(moving) + "|";
            throw " 167 After LHS and its following whitespace(s), assignment should have an '=' character. Got: |"
                + firstWord + "|";
          }

          moving += 1; // skip = sign

          while (isspace(source.at(moving))) { // move scoped cursor to first alphanumeric of RHS
            moving += 1;
          }

          // Check if var or const
          bool rhsIsVarOrConst =
              true; // assume rhs is a simple expression ( in this case is a simple term, also in turn is a simple factor)
          for (int i = moving; i < cursorEndSemiColon; i += 1) {
            char charRHS = source.at(i);
            if (charRHS == '+' || charRHS == '-' || charRHS == '/' || charRHS == '*' || charRHS == '%') {
              rhsIsVarOrConst = false;
              break;
            }
          }
          if (rhsIsVarOrConst) {
            int cursorStartOfSimpleWordRHS = moving;
            char charStartOfSimpleWordRHS = source.at(cursorStartOfSimpleWordRHS);

            while (source.at(moving + 1)
                != ';') { // move scoped cursor before whitespace (end of rhs word) or eol ;
              if (isspace(source.at(moving + 1)))
                break;
              moving += 1;
            }

            std::string rhsFactor = source.substr(cursorStartOfSimpleWordRHS,
                                                  moving - cursorStartOfSimpleWordRHS + 1);

            if (isdigit(charStartOfSimpleWordRHS)) { // rhs is a constant
              auto *sConstant = new SimpleConstant(rhsFactor);
              simple.addConstant(sConstant);
            } else if (isalpha(charStartOfSimpleWordRHS)) { // rhs is a variable
            } else {
              throw "Should not get here. Simple factor should start with alphanumeric"
                  + std::string{charStartOfSimpleWordRHS} + "|" + rhsFactor;
            }
            int thisLineNo = this->getNextLineNo();

            auto *sAssign =
                new SimpleAssign(simple.getVariable(lhs), simple.getFactor(rhsFactor), thisLineNo);
            sAssign->setBlockScope(sp);
            simple.getVariable(lhs)->addAssignmentModifier(sAssign);

            simple.addAssign(sAssign);
            sp->addChildNode(sAssign);

          } else {
          }
        }
      }
      moveCursor(); // move cursor out of declaration ; or scope }.
    }
  }
}

