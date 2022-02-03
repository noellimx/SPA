

#include "catch.hpp"
#include "source_processor/SimpleParser.hpp"

#include <string>

namespace TestSourceParser {
void require(bool b, std::string &desc) {
  REQUIRE(b);
}

SCENARIO("[TestSourceParser]", "One Procedure With 1 assignment statement") {
  GIVEN("A simple source.") {
    std::string proc_name = "main";

    std::string var_name = "var1";
    std::string const_value = "0";

    /* stmt : assign */
    std::string stmt_01_assign = var_name + " = " + const_value + ";"; // line 1
    std::string program = /* procedure 'procedure' proc_name '{' stmt '}'*/
        "procedure " + proc_name + " { " + stmt_01_assign + " }";

    WHEN("The source is tokenized") {

      SimpleParser tk(program);
      Simple simple;
      tk.parse(simple);

      THEN("Summary count of tokens") {
        // Count Summary Check
        CHECK(1 == simple.countProcedure());
        CHECK(1 == simple.countAssign());
        CHECK(1 == simple.countVariable());
        CHECK(1 == simple.countConstant());
      }

      THEN("The procedure token has a name of: " + proc_name) {
        auto *tokenProcedurePtr = simple.getProcedure(0);
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
            CHECK(firstStatementOfProcedure == simple.getAssign(targetStatementNo));
          }AND_THEN(
              "LHS of the first statement of the first procedure found by traversing is the same variable accessed by variable map.") {
            auto *lhsOfFirstStatement = firstStatementOfProcedure->getLHS();
            auto *tokenLHSFromMap = simple.getVariable(var_name);
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

SCENARIO("[TestSourceParser] One Procedure with 1 read and 1 print statement uses the same variable") {
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

      SimpleParser tk(program);
      Simple simple;
      tk.parse(simple);

      THEN("Summary count of tokens") {
        // Count Summary Check
        CHECK(1 == simple.countProcedure());
        CHECK(0 == simple.countAssign());
        CHECK(1 == simple.countVariable());
        CHECK(0 == simple.countConstant());
        CHECK(1 == simple.countRead());
        CHECK(1 == simple.countPrint());
      }

      THEN("The procedure token has a name of: " + proc_name) {
        auto *tokenProcedurePtr = simple.getProcedure(0);
        std::string tokenProcedure = tokenProcedurePtr->getType();
        std::string actualProcedureName = tokenProcedurePtr->getName();

        CHECK(tokenProcedure == "procedure");
        CHECK(actualProcedureName == proc_name);


//
        AND_WHEN("The print and read variable is the same,") {
          CHECK(var_name == "var1");

          auto *var_name_read = simple.getVariable(var_name);
          auto *var_name_printed = var_name_read;

          AND_THEN(
              "line 1 1) is in readTokens accessible by line no and 2) read token keeps record of the read variable.") {

            int expectedReadLineNo = 1;
            auto *stmt_01_sRead = simple.getRead(expectedReadLineNo);

            CHECK(stmt_01_sRead->reads() == var_name_read);

            AND_THEN(
                "line 2 1) is in printTokens accessible by line no and 2) print token keeps record of the read variable.") {

              int expectedPrintLineNo = 2;
              auto *stmt_02_sPrint = simple.getPrint(expectedPrintLineNo);
              CHECK(stmt_02_sPrint->prints() == var_name_printed);

            }
          }
        }
      }
    }
  }
}
SCENARIO("[TestSourceParser] One Procedure With 2 identical assignment statements") {
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

      SimpleParser tk(program);
      Simple simple;
      tk.parse(simple);

      THEN("Summary count of tokens") {

        CHECK(1 == simple.countProcedure());
        CHECK(2 == simple.countAssign());
        CHECK(1 == simple.countVariable());
        CHECK(1 == simple.countConstant());

      }

      THEN("The procedure token has a name of: " + proc_name) {
        auto *sProcedurePtr = simple.getProcedure(0);
        std::string actualProcedureType = sProcedurePtr->getType();
        std::string actualProcedureName = sProcedurePtr->getName();

        CHECK(actualProcedureType == "procedure");
        CHECK(actualProcedureName == proc_name);
        AND_THEN("The statement tokens has a block scope of the procedure.") {

          auto *firstStatementOfProcedure = (SimpleAssign *) sProcedurePtr->getChildAtPosition(0);
          auto *scopeOfFirstStatementOfProcedure = firstStatementOfProcedure->getBlockScope();

          CHECK(scopeOfFirstStatementOfProcedure == sProcedurePtr);

          AND_THEN("Statement token is found in statementTokens and line number is recorded") {
            int targetStatementNo = 1;
            CHECK(firstStatementOfProcedure == simple.getAssign(targetStatementNo));
          }AND_THEN(
              "LHS $" + var_name
                  + "$ should be LHS of statement 1 and 2. The relationship should be obtained from the variable token") {
            auto *sVarFromMap = simple.getVariable(var_name);
            auto *sLine1FromMap = simple.getAssign(1);
            auto *sLine2FromMap = simple.getAssign(2);
            std::string expectedLHSTtype = "variable";
            // sanity check
            CHECK(expectedLHSTtype == sVarFromMap->getType());
            CHECK(((SimpleAssign *) sLine1FromMap)->getLHS()->getName() == sVarFromMap->getName());

            // check this
            CHECK(sVarFromMap->isLHSOf((SimpleAssign *) sLine1FromMap));
            CHECK(sVarFromMap->isLHSOf((SimpleAssign *) sLine2FromMap));
          }
        }
      }
    }
  }
}
}



