

#include "catch.hpp"
#include "source_processor/SimpleParser.hpp"

#include <string>

namespace TestSimpleConstructs {
void require(bool b, std::string &desc) {
  REQUIRE(b);
}

TEST_CASE("[TestSimpleConstructs] A constant token", "") {
  std::string var1 = "b";

  auto *token = new SimpleConstant(var1);
  std::string expectedTokenType = "constant";
  std::string actualTokenType = token->getType();

  CHECK(expectedTokenType == actualTokenType);
}
}

TEST_CASE("[TestSimpleConstructs] A variable token", "") {
  std::string var1 = "abc";

  auto *token = new SimpleVariable(var1);

  std::string expectedTokenType = "variable";
  std::string actualTokenType = token->getType();

  std::map<std::string, SimpleVariable *> variables = std::map<std::string, SimpleVariable *>();

  variables.insert({var1, token});

  CHECK(token == variables.at(var1));
  CHECK(1 == variables.count(var1));
  CHECK(var1 == var1);
  CHECK(expectedTokenType == actualTokenType);
}




