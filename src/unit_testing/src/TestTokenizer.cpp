

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

  CHECK(2 == tokens.size());
}
}



