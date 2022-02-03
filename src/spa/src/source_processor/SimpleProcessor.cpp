#include "SimpleProcessor.hpp"

void SimpleProcessor::parseAndPersist(const std::string &simple_text) {

  // parsing simple_text -> Simple instance
  SimpleParser simpleParser(simple_text);
  Simple simple;
  simpleParser.parse(simple);

  //todo persisting simple_text into sql
  database::insertSimple(simple);
}