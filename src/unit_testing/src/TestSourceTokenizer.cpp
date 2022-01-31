

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
  std::string source = /* procedure 'procedure' proc_name '{' stmt '}'*/
      "procedure " + expectedProcedureName + " { " + statement1 + " }";

  // Act
  // Tokenize source.
  std::vector<Token *> procedureTokens;
  std::vector<TokenStatementBreakBySemiColon *> statementTokens;
  std::map<std::string, Token *> variableTokens;
  std::map<std::string, Token *> constantTokens;

  SourceTokenizer tk(source);
  tk.tokenize(procedureTokens, statementTokens, variableTokens, constantTokens);

  // Assert

  // actualToken0 : procedure
  auto *tokenProcedurePtr = (TokenProcedure *) procedureTokens.at(0);
  std::string Token0typeActual = tokenProcedurePtr->getType();
  std::string Token0ProcedureNameActual = tokenProcedurePtr->getName();

  CHECK(Token0typeActual == "procedure");
  CHECK(Token0ProcedureNameActual == expectedProcedureName);

  auto *firstStatementOfProcedure = (TokenStatementAssignment *) tokenProcedurePtr->getChildAtPosition(0);
  auto *scopeOfFirstStatementOfProcedure = firstStatementOfProcedure->getScope();
  auto *lhsOfFirstStatement = firstStatementOfProcedure->getLHS();

  // tokenStatement : statement1
  std::string expectedLHSTtype = "variable";
  Token *tokenLHSFromMap = variableTokens.at(expectedVar1Name);

  CHECK(expectedLHSTtype == tokenLHSFromMap->getType());
  CHECK(lhsOfFirstStatement
            == tokenLHSFromMap); // LHS of the first statement of the first procedure found by traversing is the same variable accessed by variable map.
  CHECK(expectedStatement1LineNo == statementTokens.at(0)->getLineNo());
  CHECK(scopeOfFirstStatementOfProcedure == tokenProcedurePtr);

  // Count Summary Check
  CHECK(1 == procedureTokens.size());
  CHECK(1 == variableTokens.size());
}

TEST_CASE("[TestTokenizer]Tokenize1SourceExpect1NaiveProcedure - statement", "[Tokenize1Procedure]") {

  std::string expectedProcedureName = "main";

  std::string expectedVar1Name = "var1";
  std::string expectedConst = "4";
  std::string statement1 = expectedVar1Name + " = " + expectedConst + " ;"; // line 1
  std::string source = /* procedure 'procedure' proc_name '{' stmt '}'*/
      "procedure " + expectedProcedureName + " { " + statement1 + " }";

  // Act
  // Tokenize source.
  std::vector<Token *> procedureTokens;
  std::vector<TokenStatementBreakBySemiColon *> statementTokens;
  std::map<std::string, Token *> variableTokens;
  std::map<std::string, Token *> constantTokens;

  SourceTokenizer tk(source);
  tk.tokenize(procedureTokens, statementTokens, variableTokens, constantTokens);

  // Assert

  // actualToken0 : procedure
  auto *tokenProcedurePtr = (TokenProcedure *) procedureTokens.at(0);
  std::string Token0typeActual = tokenProcedurePtr->getType();
  std::string Token0ProcedureNameActual = tokenProcedurePtr->getName();

  auto *firstStatementOfProcedure = (TokenStatementAssignment *) tokenProcedurePtr->getChildAtPosition(0);

  // we are testing this.
  auto *lhsOfFirstStatement = firstStatementOfProcedure->getLHS();
  auto *rhsOfFirstStatement = firstStatementOfProcedure->getRHS();

  // tokenStatement : statement1
  std::string expectedLHSType = "variable";
  Token *tokenLHSFromMap = variableTokens.at(expectedVar1Name);

  std::string expectedRHSType = "constant";
  Token *tokenRHSFromMap = constantTokens.at(expectedConst);

  CHECK(expectedLHSType == tokenLHSFromMap->getType());
  CHECK(lhsOfFirstStatement
            == tokenLHSFromMap); // LHS of the first statement of the first procedure found by traversing is the same variable accessed by variable map.
  CHECK(expectedRHSType == tokenRHSFromMap->getType());
  CHECK(rhsOfFirstStatement == tokenRHSFromMap);
  // Count Summary Check
  CHECK(1 == procedureTokens.size());
  CHECK(1 == statementTokens.size());
  CHECK(1 == variableTokens.size());
  CHECK(1 == constantTokens.size());
}

TEST_CASE("[TestTokenizer] A variable token", "") {
  std::string var1 = "abc";

  auto *token = new TokenVariable(var1);

  std::string expectedTokenType = "variable";
  std::string actualTokenType = token->getType();

  std::map<std::string, Token *> variables = std::map<std::string, Token *>();

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



