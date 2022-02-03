#include "QueryParser.hpp"
#include "Declaration.hpp"

QueryParser::~QueryParser() = default;

// NOTE: this is inner help function for tokenize()
// returns when cursor is at 't' of Select
void QueryParser::_tokenizeDeclarations(Query &qr) {

  bool isSelectKeyWordFound = false;
  int cc = 0;
  while (!isSelectKeyWordFound) {
    cc++;

    while (isspace(text.at(_cursor))) { // move to first alphanumeric of design entity
      _cursor++;
    }

    int cursorFirstCharacterOfDesignEntity = _cursor;

    if (!isalpha(text.at(cursorFirstCharacterOfDesignEntity))) {
      throw "Design Entity starts with alphanumeric character";
    }

    while (isalpha(text.at(_cursor + 1))
        || isdigit(text.at(_cursor + 1))) { // move to last alphanumeric of design entity
      _cursor++;
    }

    int cursorLastCharacterOfDesignEntity = _cursor;

    std::string firstWordOfQueryLine = text.substr(cursorFirstCharacterOfDesignEntity,
                                                   cursorLastCharacterOfDesignEntity
                                                       - cursorFirstCharacterOfDesignEntity + 1);
    if (firstWordOfQueryLine == "Select") {
      return;
    }

    std::string design_entity = firstWordOfQueryLine;
    _cursor++; // move out of design-entity
    while (true) {
      while (isspace(text.at(_cursor))) { // move to first alphanumeric next synonym
        _cursor++;
      }
      int cursorFirstCharacterOfSynonym = _cursor;
      if (!isalpha(text.at(cursorFirstCharacterOfSynonym))) {
        throw "Synonym starts with alphanumeric character";
      }
      while (isalpha(text.at(_cursor + 1)) || isdigit(text.at(_cursor + 1))) { // move to last alphanumeric of synonym
        _cursor++;
      }
      int cursorLastCharacterOfSynonym = _cursor;

      std::string synonym = text.substr(cursorFirstCharacterOfSynonym,
                                        cursorLastCharacterOfSynonym - cursorFirstCharacterOfSynonym + 1);

      auto *declaration = new Declaration(design_entity, synonym);
      qr.addDeclaration(declaration);

      _cursor++; // move out of synonym

      while (!(text.at(_cursor) == ',' || text.at(_cursor) == ';')) { // go to next demarcator
        _cursor++;
      }

      char demarcator = text.at(_cursor);

      _cursor++; // move out of declaration

      if (demarcator == ',') {
      } else if (demarcator == ';') {

        break; // no more synonyms
      } else {

      }
    }
  }
}
// NOTE: this is inner help function for tokenize()
void QueryParser::_tokenizeSelectCl(Query &qr) {
  if (text.at(_cursor) != 't') {
    throw "This method should only be invoked when cursor position is at 't' of Select keyword";
  }
  _cursor++;

  if (!isspace(text.at(_cursor))) {
    throw "After Select keyword should be whitespace";
  }
  while (isspace(text.at(_cursor))) { // go to start of tuple
    _cursor++;
  }

  int cursorStartOfTuple = _cursor;

  if (text.at(cursorStartOfTuple) == '<') {

  } else { // tuple has one synonym
    int cursorStartOfSelectSynonym = cursorStartOfTuple;
    int moving = cursorStartOfSelectSynonym;

    while ((moving + 1) < text.length() && isalpha(text.at(moving + 1))) { // move to last alphanumeric of synonym
      moving++;
    }

    std::string selectSyn = text.substr(cursorStartOfSelectSynonym, moving - cursorStartOfSelectSynonym + 1);
    qr.addSynonymToResultCl(selectSyn);
  }
}
void QueryParser::tokenize(Query &qr) {
  QueryParser::_tokenizeDeclarations(qr);
  QueryParser::_tokenizeSelectCl(qr);
}
