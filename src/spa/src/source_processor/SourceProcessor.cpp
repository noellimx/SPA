#include "SourceProcessor.hpp"


void SourceProcessor::process(const std::string& program) {
  // initialize the database


  // tokenize the program
  SourceTokenizer tk(program);
  std::vector<TokenProcedure *> tokens;
  std::map<int, InterfaceStatementWithLineNo *> dummy;
  std::map<std::string, TokenVariable *> dummy2;
  std::map<std::string, TokenConstant *> dummy3;
  tk.tokenize(tokens,dummy,dummy2,dummy3);
//   This logic is highly simplified based on iteration 1 requirements and
//   the assumption that the programs are valid.

}