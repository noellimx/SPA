

#include "catch.hpp"
#include "source_processor/SourceTokenizer.hpp"

#include <string>

namespace TestTokenizer {
void require(bool b, std::string &desc) {
  REQUIRE(b);
}

TEST_CASE("[TestTokenizer]Tokenize1SourceExpect1NaiveProcedure", "[Tokenize1Procedure]") {

  std::string expectedProcedureName = "main";

  std::string expectedVar1Name = "var1";
  std::string expectedConst = "0";
  std::string statement1 = expectedVar1Name + " = " + expectedConst + ";"; // line 1
  int expectedStatement1LineNo = 1;
  std::string source = "procedure " + expectedProcedureName + " { " + statement1 + " }";

  // Act
  // Tokenize source.
  std::vector<Token *> procedureTokens;
  std::vector<TokenStatementBreakBySemiColon *> statementTokens;
  std::map<std::string, Token *> variableTokens;

  SourceTokenizer tk(source);
  tk.tokenize(procedureTokens, statementTokens, variableTokens);

  // Assert

  // actualToken0 : procedure
  auto *tokenProcedurePtr = (TokenProcedure *) procedureTokens.at(0);
  std::string Token0typeActual = tokenProcedurePtr->getType();
  std::string Token0ProcedureNameActual = tokenProcedurePtr->getName();

  CHECK(Token0typeActual == "procedure");
  CHECK(Token0ProcedureNameActual == expectedProcedureName);

  auto *firstStatementOfProcedure = (TokenStatementAssignment *) tokenProcedurePtr->getChildAtPosition(0);
  auto *lhsOfFirstStatement = (TokenStatementAssignment *) firstStatementOfProcedure->getLHS();

  // tokenStatement : statement1
  std::string expectedLHSTtype = "variable";
  Token *tokenLHSFromMap = variableTokens.at(expectedVar1Name);

  CHECK(expectedLHSTtype == tokenLHSFromMap->getType());
  CHECK(lhsOfFirstStatement
            == tokenLHSFromMap); // LHS of the first statement of the first procedure found by traversing is the same variable accessed by variable map.
  CHECK(expectedStatement1LineNo == statementTokens.at(0)->getLineNo());

  // Count Summary Check
  CHECK(1 == procedureTokens.size());
  CHECK(1 == variableTokens.size());
}

TEST_CASE("[TestTokenizer] A variable token", "") {
  std::string var1 = "abc";

  std::cout << var1.size() << std::endl;

  auto *token = new TokenVariable(var1);
  std::cout << var1.size() << std::endl;

  std::string expectedTokenType = "assignment";
  std::string actualTokenType = token->getType();

  std::map<std::string, Token *> variables = std::map<std::string, Token *>();
  std::cout << var1.size() << std::endl;

  variables.insert({var1, token});

  CHECK(token == variables.at(var1));
  CHECK(1 == variables.count(var1));
  CHECK(var1 == var1);
  CHECK(expectedTokenType == actualTokenType);
}

TEST_CASE("[TestTokenizer] A constant token", "") {
  std::string var1 = "b";

  auto *token = new TokenConstant(var1);
  std::string expectedTokenType = "constant";
  std::string actualTokenType = token->getType();

  CHECK(expectedTokenType == actualTokenType);
}
}



