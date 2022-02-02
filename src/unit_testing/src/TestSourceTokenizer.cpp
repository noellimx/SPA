

#include "catch.hpp"
#include "source_processor/SourceTokenizer.hpp"
#include "source_processor/token/TokenStatementPrint.hpp"

#include <string>

namespace TestTokenizer {
void require(bool b, std::string &desc) {
  REQUIRE(b);
}

SCENARIO("[TestTokenizer]", "One Procedure With 1 assignment statement") {
  GIVEN("A simple source.") {
    std::string proc_name = "main";

    std::string var_name = "var1";
    std::string const_value = "0";

    /* stmt : assign */
    std::string stmt_01_assign = var_name + " = " + const_value + ";"; // line 1
    std::string program = /* procedure 'procedure' proc_name '{' stmt '}'*/
        "procedure " + proc_name + " { " + stmt_01_assign + " }";

    WHEN("The source is tokenized") {

      std::vector<TokenProcedure *> procedureTokens;
      std::map<int, TokenStatementAssignment *> statementTokens;
      std::map<std::string, TokenVariable *> variableTokens;
      std::map<std::string, TokenConstant *> constantTokens;
      std::map<int, TokenStatementRead *> readTokens;
      std::map<int, TokenStatementPrint *> printTokens;

      SourceTokenizer tk(program);
      tk.tokenize(procedureTokens, statementTokens, variableTokens, constantTokens, readTokens,printTokens);

      THEN("Summary count of tokens") {
        // Count Summary Check
        CHECK(1 == procedureTokens.size());
        CHECK(1 == statementTokens.size());
        CHECK(1 == variableTokens.size());
        CHECK(1 == constantTokens.size());
      }

      THEN("The procedure token has a name of: " + proc_name) {
        auto *tokenProcedurePtr = (TokenProcedure *) procedureTokens.at(0);
        std::string actualProcedureType = tokenProcedurePtr->getType();
        std::string proc_name_actual = tokenProcedurePtr->getName();

        CHECK(actualProcedureType == "procedure");
        CHECK(proc_name_actual == proc_name);
        AND_THEN("The statement token has a block scope of the procedure.") {

          auto *firstStatementOfProcedure = (TokenStatementAssignment *) tokenProcedurePtr->getChildAtPosition(0);
          auto *scopeOfFirstStatementOfProcedure = firstStatementOfProcedure->getBlockScope();

          CHECK(scopeOfFirstStatementOfProcedure == tokenProcedurePtr);

          AND_THEN("Statement token is found in statementTokens and line number is recorded") {
            int targetStatementNo = 1;
            CHECK(firstStatementOfProcedure == statementTokens.at(targetStatementNo));
          }AND_THEN(
              "LHS of the first statement of the first procedure found by traversing is the same variable accessed by variable map.") {
            auto *lhsOfFirstStatement = firstStatementOfProcedure->getLHS();
            auto *tokenLHSFromMap = variableTokens.at(var_name);
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

SCENARIO("[TestTokenizer] One Procedure with 1 read and 1 print statement uses the same variable") {
  GIVEN("A simple source.") {
    std::string proc_name = "main";

    std::string var_name = "var1";

    /* stmtLst: : stmt[2] */
    std::string stmt_01_read = "read " + var_name + ";"; // line 1
    std::string stmt_02_print = "print " + var_name + ";"; // line 2
    std::string stmtLst = stmt_01_read + stmt_02_print;

    std::string program = /* procedure 'procedure' proc_name '{' stmt '}'*/
        "procedure " + proc_name + " { " + stmtLst + " }";
    WHEN("The source is tokenized") {

      std::vector<TokenProcedure *> procedureTokens;
      std::map<int, TokenStatementAssignment *> assignmentTokens;
      std::map<std::string, TokenVariable *> variableTokens;
      std::map<std::string, TokenConstant *> constantTokens;
      std::map<int, TokenStatementRead *> readTokens;
      std::map<int, TokenStatementPrint *> printTokens;

      SourceTokenizer tk(program);
      tk.tokenize(procedureTokens, assignmentTokens, variableTokens, constantTokens, readTokens, printTokens);

      THEN("Summary count of tokens") {
        // Count Summary Check
        CHECK(1 == procedureTokens.size());
        CHECK(assignmentTokens.empty());
        CHECK(1 == variableTokens.size());
        CHECK(constantTokens.empty());
        CHECK(1 == readTokens.size());
      }

      THEN("The procedure token has a name of: " + proc_name) {
        auto *tokenProcedurePtr = (TokenProcedure *) procedureTokens.at(0);
        std::string tokenProcedure = tokenProcedurePtr->getType();
        std::string actualProcedureName = tokenProcedurePtr->getName();

        CHECK(tokenProcedure == "procedure");
        CHECK(actualProcedureName == proc_name);


//
        AND_WHEN("The print and read variable is the same,") {
          CHECK(var_name == "var1");

          auto *var_name_read = variableTokens.at(var_name);
          auto *var_name_printed = var_name_read;

          AND_THEN("line 1 1) is in readTokens accessible by line no and 2) read token keeps record of the read variable.") {

            int expectedReadLineNo = 1;
            auto *stmt_01_read_Token = readTokens.at(expectedReadLineNo);


            CHECK(stmt_01_read_Token->reads() == var_name_read);

            AND_THEN("line 2 1) is in printTokens accessible by line no and 2) print token keeps record of the read variable.") {

              int expectedPrintLineNo = 2;
              auto *stmt_02_print_Token = printTokens.at(expectedPrintLineNo);
              CHECK(stmt_02_print_Token->prints() == var_name_printed);

            }
          }
        }
      }
    }
  }
}
SCENARIO("[TestTokenizer] One Procedure With 2 identical assignment statements") {
  GIVEN("A simple source.") {
    std::string proc_name = "main";

    std::string var_name = "var1";
    std::string const_value = "0";

    /* stmt : assign */
    /* stmtLst: : stmt[2] */
    std::string stmt_01_assign = var_name + " = " + const_value + ";"; // line 1
    std::string stmt_02_assign = stmt_01_assign; // line 2

    std::string source = /* procedure 'procedure' proc_name '{' stmt '}'*/
        "procedure " + proc_name + " { " + stmt_01_assign + stmt_02_assign + " }";

    WHEN("The source is tokenized") {

      std::vector<TokenProcedure *> procedureTokens;
      std::map<int, TokenStatementAssignment *> assignmentTokens;
      std::map<std::string, TokenVariable *> variableTokens;
      std::map<std::string, TokenConstant *> constantTokens;
      std::map<int, TokenStatementRead *> readTokens;
      std::map<int, TokenStatementPrint *> printTokens;

      SourceTokenizer tk(source);
      tk.tokenize(procedureTokens, assignmentTokens, variableTokens, constantTokens, readTokens,printTokens);

      THEN("Summary count of tokens") {
        // Count Summary Check
        CHECK(1 == procedureTokens.size());
        CHECK(2 == assignmentTokens.size());
        CHECK(1 == variableTokens.size());
        CHECK(1 == constantTokens.size());
      }

      THEN("The procedure token has a name of: " + proc_name) {
        auto *tokenProcedurePtr = (TokenProcedure *) procedureTokens.at(0);
        std::string actualTokenProcedureType = tokenProcedurePtr->getType();
        std::string actualProcedureName = tokenProcedurePtr->getName();

        CHECK(actualTokenProcedureType == "procedure");
        CHECK(actualProcedureName == proc_name);
        AND_THEN("The statement tokens has a block scope of the procedure.") {

          auto *firstStatementOfProcedure = (TokenStatementAssignment *) tokenProcedurePtr->getChildAtPosition(0);
          auto *scopeOfFirstStatementOfProcedure = firstStatementOfProcedure->getBlockScope();

          CHECK(scopeOfFirstStatementOfProcedure == tokenProcedurePtr);

          AND_THEN("Statement token is found in statementTokens and line number is recorded") {
            int targetStatementNo = 1;
            CHECK(firstStatementOfProcedure == assignmentTokens.at(targetStatementNo));
          }AND_THEN(
              "LHS $" + var_name
                  + "$ should be LHS of statement 1 and 2. The relationship should be obtained from the variable token") {
            auto *tokenVarFromMap = variableTokens.at(var_name);
            auto *tokenLine1FromMap = assignmentTokens.at(1);
            auto *tokenLine2FromMap = assignmentTokens.at(2);
            std::string expectedLHSTtype = "variable";
            // sanity check
            CHECK(expectedLHSTtype == tokenVarFromMap->getType());
            CHECK(((TokenStatementAssignment *) tokenLine1FromMap)->getLHS()->getName() == tokenVarFromMap->getName());

            // check this
            CHECK(tokenVarFromMap->isLHSOf((TokenStatementAssignment *) tokenLine1FromMap));
            CHECK(tokenVarFromMap->isLHSOf((TokenStatementAssignment *) tokenLine2FromMap));
          }
        }
      }
    }
  }
}
}



