#include "QueryTokenizer.hpp"

// constructor
QueryTokenizer::QueryTokenizer() {}

// destructor
QueryTokenizer::~QueryTokenizer() {}

// method to tokenize a program / query string
// it currently tokenizes the string into a vector of 
// words (any alphanumeric sequence of characters starting with a letter, e.g., "num1"),
// numbers (any numeric sequence of characters, e.g., "1001"),
// and punctuations (any other non-space characters, e.g., "=", ";", "{", "}").
// it should be extended as needed to handle additional SIMPLE / PQL grammar rules.
void QueryTokenizer::tokenize(std::string &text, Query &qr) {

  int cursor = 0;
  while (cursor < text.length()) {
    // parse declaration by declaration
    while (isspace(cursor)) { // move to first alphanumeric of design entity
      cursor++;
    }

    int cursorFirstCharacterOfDesignEntity = cursor;
    if (!isalpha(text.at(cursorFirstCharacterOfDesignEntity))) {
      throw "Design Entity starts with alphanumeric character";
    }

    while (isalpha(text.at(cursor + 1)) || isdigit(text.at(cursor + 1))) { // move to last alphanumeric of design entity
      cursor++;
    }

    int cursorLastCharacterOfDesignEntity = cursor;

    std::string design_entity = text.substr(cursorFirstCharacterOfDesignEntity,
                                            cursorLastCharacterOfDesignEntity - cursorFirstCharacterOfDesignEntity + 1);

    cursor++; // move out of design-entity
    while (text.at(cursor) != ';') {
      while (isspace(text.at(cursor))) { // move to first alphanumeric next synonym
        cursor++;
      }
      int cursorFirstCharacterOfSynonym = cursor;
      if (!isalpha(text.at(cursorFirstCharacterOfSynonym))) {
        throw "Synonym starts with alphanumeric character";
      }
      while (isalpha(text.at(cursor + 1)) || isdigit(text.at(cursor + 1))) { // move to last alphanumeric of synonym
        cursor++;
      }
      int cursorLastCharacterOfSynonym = cursor;

      std::string synonym = text.substr(cursorFirstCharacterOfSynonym,
                                              cursorLastCharacterOfSynonym - cursorFirstCharacterOfSynonym + 1);

    }
  }

}
