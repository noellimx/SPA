

#include "catch.hpp"
#include "source_processor/SourceParser.hpp"

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

      SourceParser tk(program);
      TokenSimpleBag tokenBag;
      tk.tokenize(tokenBag);

      THEN("Summary count of tokens") {
        // Count Summary Check
        CHECK(1 == tokenBag.countProcedure());
        CHECK(1 == tokenBag.countAssign());
        CHECK(1 == tokenBag.countVariable());
        CHECK(1 == tokenBag.countConstant());
      }

      THEN("The procedure token has a name of: " + proc_name) {
        auto *tokenProcedurePtr = tokenBag.getProcedure(0);
        std::string actualProcedureType = tokenProcedurePtr->getType();
        std::string proc_name_actual = tokenProcedurePtr->getName();

        CHECK(actualProcedureType == "procedure");
        CHECK(proc_name_actual == proc_name);
        AND_THEN("The statement token has a block scope of the procedure.") {

          auto *firstStatementOfProcedure = (SimpleAssign *) tokenProcedurePtr->getChildAtPosition(0);
          auto *scopeOfFirstStatementOfProcedure = firstStatementOfProcedure->getBlockScope();

          CHECK(scopeOfFirstStatementOfProcedure == tokenProcedurePtr);

          AND_THEN("Statement token is found in statementTokens and line number is recorded") {
            int targetStatementNo = 1;
            CHECK(firstStatementOfProcedure == tokenBag.getAssign(targetStatementNo));
          }AND_THEN(
              "LHS of the first statement of the first procedure found by traversing is the same variable accessed by variable map.") {
            auto *lhsOfFirstStatement = firstStatementOfProcedure->getLHS();
            auto *tokenLHSFromMap = tokenBag.getVariable(var_name);
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

      SourceParser tk(program);
      TokenSimpleBag tokenBag;
      tk.tokenize(tokenBag);

      THEN("Summary count of tokens") {
        // Count Summary Check
        CHECK(1 == tokenBag.countProcedure());
        CHECK(0 == tokenBag.countAssign());
        CHECK(1 == tokenBag.countVariable());
        CHECK(0 == tokenBag.countConstant());
        CHECK(1 == tokenBag.countRead());
        CHECK(1 == tokenBag.countPrint());
      }

      THEN("The procedure token has a name of: " + proc_name) {
        auto *tokenProcedurePtr = tokenBag.getProcedure(0);
        std::string tokenProcedure = tokenProcedurePtr->getType();
        std::string actualProcedureName = tokenProcedurePtr->getName();

        CHECK(tokenProcedure == "procedure");
        CHECK(actualProcedureName == proc_name);


//
        AND_WHEN("The print and read variable is the same,") {
          CHECK(var_name == "var1");

          auto *var_name_read = tokenBag.getVariable(var_name);
          auto *var_name_printed = var_name_read;

          AND_THEN(
              "line 1 1) is in readTokens accessible by line no and 2) read token keeps record of the read variable.") {

            int expectedReadLineNo = 1;
            auto *stmt_01_read_Token = tokenBag.getRead(expectedReadLineNo);

            CHECK(stmt_01_read_Token->reads() == var_name_read);

            AND_THEN(
                "line 2 1) is in printTokens accessible by line no and 2) print token keeps record of the read variable.") {

              int expectedPrintLineNo = 2;
              auto *stmt_02_print_Token = tokenBag.getPrint(expectedPrintLineNo);
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
    std::string stmtLst = stmt_01_assign + stmt_02_assign;
    std::string program = /* procedure 'procedure' proc_name '{' stmt '}'*/
        "procedure " + proc_name + " { " + stmtLst + " }";

    WHEN("The source is tokenized") {

      SourceParser tk(program);
      TokenSimpleBag tokenBag;
      tk.tokenize(tokenBag);

      THEN("Summary count of tokens") {

        CHECK(1 == tokenBag.countProcedure());
        CHECK(2 == tokenBag.countAssign());
        CHECK(1 == tokenBag.countVariable());
        CHECK(1 == tokenBag.countConstant());

      }

      THEN("The procedure token has a name of: " + proc_name) {
        auto *tokenProcedurePtr = tokenBag.getProcedure(0);
        std::string actualTokenProcedureType = tokenProcedurePtr->getType();
        std::string actualProcedureName = tokenProcedurePtr->getName();

        CHECK(actualTokenProcedureType == "procedure");
        CHECK(actualProcedureName == proc_name);
        AND_THEN("The statement tokens has a block scope of the procedure.") {

          auto *firstStatementOfProcedure = (SimpleAssign *) tokenProcedurePtr->getChildAtPosition(0);
          auto *scopeOfFirstStatementOfProcedure = firstStatementOfProcedure->getBlockScope();

          CHECK(scopeOfFirstStatementOfProcedure == tokenProcedurePtr);

          AND_THEN("Statement token is found in statementTokens and line number is recorded") {
            int targetStatementNo = 1;
            CHECK(firstStatementOfProcedure == tokenBag.getAssign(targetStatementNo));
          }AND_THEN(
              "LHS $" + var_name
                  + "$ should be LHS of statement 1 and 2. The relationship should be obtained from the variable token") {
            auto *tokenVarFromMap = tokenBag.getVariable(var_name);
            auto *tokenLine1FromMap = tokenBag.getAssign(1);
            auto *tokenLine2FromMap = tokenBag.getAssign(2);
            std::string expectedLHSTtype = "variable";
            // sanity check
            CHECK(expectedLHSTtype == tokenVarFromMap->getType());
            CHECK(((SimpleAssign *) tokenLine1FromMap)->getLHS()->getName() == tokenVarFromMap->getName());

            // check this
            CHECK(tokenVarFromMap->isLHSOf((SimpleAssign *) tokenLine1FromMap));
            CHECK(tokenVarFromMap->isLHSOf((SimpleAssign *) tokenLine2FromMap));
          }
        }
      }
    }
  }
}
}



