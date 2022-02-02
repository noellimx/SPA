#include "SourceProcessor.hpp"


void SourceProcessor::process(const std::string& program) {

  SourceTokenizer tk(program);
  std::vector<TokenProcedure *> tokens;
}