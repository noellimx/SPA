#include "SourceProcessor.hpp"

// method for processing the source program
// This method currently only inserts the procedure name into the database
// using some highly simplified logic.
// You should modify this method to complete the logic for handling all the required syntax.
void SourceProcessor::process(const std::string& program) {
  // initialize the database
  database::initialize();

  // tokenize the program
  SourceTokenizer tk(program);
  std::vector<Token *> tokens;
  std::vector<InterfaceStatementWithLineNo *> dummy;
  std::map<std::string, Token *> dummy2;
  std::map<std::string, Token *> dummy3;
  tk.tokenize(tokens,dummy,dummy2,dummy3);
//   This logic is highly simplified based on iteration 1 requirements and
//   the assumption that the programs are valid.

}