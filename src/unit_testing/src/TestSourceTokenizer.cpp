

#include "catch.hpp"
#include "source_processor/SourceTokenizer.hpp"

#include <string>

namespace TestTokenizer {
void require(bool b, std::string &desc) {
  REQUIRE(b);
}

SCENARIO("[TestTokenizer]", "One Procedure With 1 assignment statement") {
  GIVEN("A simple source.") {
    std::string expectedProcedureName = "main";

    std::string expectedVar1Name = "var1";
    std::string expectedConst = "0";
    std::string statement1 = expectedVar1Name + " = " + expectedConst + ";"; // line 1
    std::string source = /* procedure 'procedure' proc_name '{' stmt '}'*/
        "procedure " + expectedProcedureName + " { " + statement1 + " }";

    WHEN("The source is tokenized") {

      std::vector<TokenProcedure *> procedureTokens;
      std::map<int, InterfaceStatementWithLineNo *> statementTokens;
      std::map<std::string, TokenVariable *> variableTokens;
      std::map<std::string, TokenConstant *> constantTokens;

      SourceTokenizer tk(source);
      tk.tokenize(procedureTokens, statementTokens, variableTokens, constantTokens);

      THEN("Summary count of tokens") {
        // Count Summary Check
        CHECK(1 == procedureTokens.size());
        CHECK(1 == statementTokens.size());
        CHECK(1 == variableTokens.size());
        CHECK(1 == constantTokens.size());
      }

      THEN("The procedure token has a name of: " + expectedProcedureName) {
        auto *tokenProcedurePtr = (TokenProcedure *) procedureTokens.at(0);
        std::string Token0typeActual = tokenProcedurePtr->getType();
        std::string Token0ProcedureNameActual = tokenProcedurePtr->getName();

        CHECK(Token0typeActual == "procedure");
        CHECK(Token0ProcedureNameActual == expectedProcedureName);
        AND_THEN("The statement token has a block scope of the procedure.") {

          auto *firstStatementOfProcedure = (TokenStatementAssignment *) tokenProcedurePtr->getChildAtPosition(0);
          auto *scopeOfFirstStatementOfProcedure = firstStatementOfProcedure->getBlockScope();

          CHECK(scopeOfFirstStatementOfProcedure == tokenProcedurePtr);

          AND_THEN("Statement token is found in statementTokens and line number is recorded") {
            int targetStatementNo = 1;
            CHECK(firstStatementOfProcedure == statementTokens.at(targetStatementNo));
          }
          AND_THEN(
              "LHS of the first statement of the first procedure found by traversing is the same variable accessed by variable map.") {
            auto *lhsOfFirstStatement = firstStatementOfProcedure->getLHS();
            auto *tokenLHSFromMap = variableTokens.at(expectedVar1Name);
            std::string expectedLHSTtype = "variable";
            CHECK(expectedLHSTtype == tokenLHSFromMap->getType());
            CHECK(lhsOfFirstStatement
                      == tokenLHSFromMap);
          }

        }
      }
    }
  }
}

}



