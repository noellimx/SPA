

#include "catch.hpp"
#include "source_processor/SourceTokenizer.hpp"

#include <string>

// Each cpp is a set of test cases for a specific component.
namespace TestTokenizer {
void require(bool b, std::string &desc) {
  REQUIRE(b);
}

// The name of a test case should be unique and meaningful.
TEST_CASE("[Test]Tokenize1SourceExpect1NaiveProcedure", "[Tokenize1Procedure]") {
  std::string source = "procedure main { a = 0; }";
  SourceTokenizer tk(source);
  std::vector<Token *> tokens;
  tk.tokenize(tokens);

  Token * actualToken0 = tokens.at(0);
  std::string Token0typeActual = actualToken0->getType();
  std::string Token0typeExpected = "procedure";

  TokenProcedure * tokenProcedurePtr = (TokenProcedure *)actualToken0;
  std::string Token0ProcedureNameActual = actualToken0->getName();
  Token * Token0ProcedureChild0Actual = tokenProcedurePtr->getChildAtPosition(0);
  std::string Token0ProcedureNameExpected = "main";

  Token * actualToken1 = tokens.at(1);
  std::string Token1typeActual = actualToken1->getType();
  std::string Token1typeExpected = "assignment";

  CHECK(Token0typeActual == Token0typeExpected);
  CHECK(Token0ProcedureNameActual == Token0ProcedureNameExpected);
  CHECK(actualToken1 == Token0ProcedureChild0Actual);

  CHECK(Token1typeActual == Token1typeExpected);
  CHECK(2 == tokens.size());
}
}



