//
// Created by Noel Lim on 3/2/22.
//

#pragma once

#include "catch.hpp"
#include "database/database.hpp"
#include "source_processor/SimpleParser.hpp"
#include "query_processor/QueryProcessor.hpp"
#include "query_processor/QueryParser.hpp"
#include "query_processor/QueryEvaluator.hpp"

namespace TestIteration001_002 {

TEST_CASE("[Test Iteration] Asserting Result: 1 Procedure") {
  GIVEN("A connection to the database") {
    database::initialize();

    WHEN("A SIMPLE text and PQL query") {
      // Simple Text
      std::string proc_name_01 = "main";
      std::string var_name_01 = "x";
      std::string const_value_01 = "1";

      std::string stmt_01_assign = var_name_01 + " = " + const_value_01 + ";";

      std::string stmtLst = stmt_01_assign;
      std::string procedure_01 = "procedure " + proc_name_01 + " {\n"
                                                               "    " + stmtLst + "\n"
                                                                                  "}";
      std::string simple_text = procedure_01;
      AND_WHEN("SIMPLE text is parsed") {
        SimpleParser simpleParser(simple_text);
        Simple simple;
        simpleParser.parse(simple);
        AND_THEN("The summary count of composites in simple instance") {
          CHECK(1 == simple.countProcedure());
          CHECK(1 == simple.countAssign());
          CHECK(1 == simple.countVariable());
          CHECK(1 == simple.countConstant());
        }

        AND_WHEN("Simple instance is inserted into database") {
          database::insertSimple(simple);

          CHECK(database::getProcedureCount() == 1);

          // PQL query
          std::string design_entity = "procedure";
          std::string synonym = "p";
          std::string select_cl_text = design_entity + " " + synonym + "; Select " + synonym;


          AND_WHEN(
              "Query is parsed.") {
            int expectedCountDeclarations = 1;
            int expectedCountSynonymInTuple = 1;
            std::string expectedSynonymToRepresentType = "procedure";
            QueryParser tkQry(select_cl_text);
            Query qr;
            tkQry.parse(qr);
            CHECK(qr.countDeclarations() == expectedCountDeclarations);
            CHECK(qr.getEntityOf(synonym) == expectedSynonymToRepresentType);
            CHECK(qr.countSynonymsInTuple() == expectedCountSynonymInTuple);

            AND_THEN("The database query result is " + proc_name_01) {
              std::vector<std::string> results;
              QueryProcessor::parseAndEvaluate(select_cl_text, results);
              CHECK(results.size() == 1);
              CHECK(results.at(0) == proc_name_01);
            }
          }
        }
      }
    }
  }
}

TEST_CASE("[Test Iteration] 001-2 Asserting Result: Give and get 1 Assign") {
  GIVEN("A connection to the database") {
    database::initialize();

    WHEN("A SIMPLE text and PQL query") {
      // Simple Text
      std::string proc_name_01 = "main";
      std::string var_name_01 = "x";
      std::string const_value_01 = "1";

      std::string stmt_01_assign = var_name_01 + " = " + const_value_01 + ";";

      std::string stmtLst = stmt_01_assign;
      std::string procedure_01 = "procedure " + proc_name_01 + " {\n"
                                                               "    " + stmtLst + "\n"
                                                                                  "}";
      std::string simple_text = procedure_01;
      AND_WHEN("SIMPLE text is parsed") {
        SimpleParser simpleParser(simple_text);
        Simple simple;
        simpleParser.parse(simple);
        AND_THEN("The summary count of composites in simple instance") {
          CHECK(1 == simple.countProcedure());
          CHECK(1 == simple.countAssign());
          CHECK(1 == simple.countVariable());
          CHECK(1 == simple.countConstant());
        }

        AND_WHEN("Simple instance is inserted into database") {
          database::insertSimple(simple);

          CHECK(database::getAssignCount() == 1);

          // PQL query
          std::string design_entity = "assign";
          std::string synonym = "a";
          std::string select_cl_text = design_entity + " " + synonym + "; Select " + synonym;

          AND_WHEN(
              "Query is parsed.") {
            int expectedCountDeclarations = 1;
            int expectedCountSynonymInTuple = 1;
            std::string expectedSynonymToRepresentType = design_entity;
            QueryParser tkQry(select_cl_text);
            Query qr;
            tkQry.parse(qr);
            CHECK(qr.countDeclarations() == expectedCountDeclarations);
            CHECK(qr.getEntityOf(synonym) == expectedSynonymToRepresentType);
            CHECK(qr.countSynonymsInTuple() == expectedCountSynonymInTuple);

            AND_THEN("The database query result is 1") {
              std::vector<std::string> results;
              QueryProcessor::parseAndEvaluate(select_cl_text, results);
              CHECK(results.size() == 1);
              CHECK(results.at(0) == std::to_string(1));
            }
          }
        }
      }
    }
  }
}

TEST_CASE("[Test Iteration] 001-2 Asserting Result: Give and get 1 Print") {
  GIVEN("A connection to the database") {
    database::initialize();

    WHEN("A SIMPLE text and PQL query") {
      // Simple Text
      std::string proc_name_01 = "main";
      std::string var_name_01 = "x";
      std::string const_value_01 = "1";

      std::string stmt_01_print = "print " + var_name_01 + ";";

      std::string stmtLst = stmt_01_print;
      std::string procedure_01 = "procedure " + proc_name_01 + " {\n"
                                                               "    " + stmtLst + "\n"
                                                                                  "}";
      std::string simple_text = procedure_01;
      AND_WHEN("SIMPLE text is parsed") {
        SimpleParser simpleParser(simple_text);
        Simple simple;
        simpleParser.parse(simple);
        AND_THEN("The summary count of composites in simple instance") {
          CHECK(1 == simple.countProcedure());
          CHECK(0 == simple.countAssign());
          CHECK(1 == simple.countPrint());
          CHECK(1 == simple.countVariable());
          CHECK(0 == simple.countConstant());
        }

        AND_WHEN("Simple instance is inserted into database") {
          database::insertSimple(simple);

          CHECK(database::getPrintCount() == 1);

          // PQL query
          std::string design_entity = "print";
          std::string synonym = "pp";
          std::string select_cl_text = design_entity + " " + synonym + "; Select " + synonym;

          AND_WHEN(
              "Query is parsed.") {
            int expectedCountDeclarations = 1;
            int expectedCountSynonymInTuple = 1;
            std::string expectedSynonymToRepresentType = design_entity;
            QueryParser tkQry(select_cl_text);
            Query qr;
            tkQry.parse(qr);
            CHECK(qr.countDeclarations() == expectedCountDeclarations);
            CHECK(qr.getEntityOf(synonym) == expectedSynonymToRepresentType);
            CHECK(qr.countSynonymsInTuple() == expectedCountSynonymInTuple);

            AND_THEN("The database query result is line number 1") {
              std::vector<std::string> results;
              QueryEvaluator::evaluate(qr, results);
              CHECK(results.size() == 1);
              CHECK(results.at(0) == std::to_string(1));
            }
          }
        }
      }
    }
  }
}

TEST_CASE("[Test Iteration] 001-2 Asserting Result: Give and get 1 Read") {
  GIVEN("A connection to the database") {
    database::initialize();

    WHEN("A SIMPLE text and PQL query") {
      // Simple Text
      std::string proc_name_01 = "main";
      std::string var_name_01 = "x";
      std::string const_value_01 = "1";

      std::string stmt_01_read = "read " + var_name_01 + ";";

      std::string stmtLst = stmt_01_read;
      std::string procedure_01 = "procedure " + proc_name_01 + " {\n"
                                                               "    " + stmtLst + "\n"
                                                                                  "}";
      std::string simple_text = procedure_01;

      // PQL query
      std::string design_entity = "read";
      std::string synonym = "read123REsynonym";
      std::string select_cl_text = design_entity + " " + synonym + "; Select " + synonym;

      AND_WHEN("SIMPLE text is parsed") {
        SimpleParser simpleParser(simple_text);
        Simple simple;
        simpleParser.parse(simple);
        AND_THEN("The summary count of composites in simple instance") {
          CHECK(1 == simple.countProcedure());
          CHECK(0 == simple.countAssign());
          CHECK(0 == simple.countPrint());
          CHECK(1 == simple.countRead());
          CHECK(1 == simple.countVariable());
          CHECK(0 == simple.countConstant());
        }

        AND_WHEN("Simple instance is inserted into database") {
          database::insertSimple(simple);

          CHECK(database::getReadCount() == 1);
          CHECK(database::getPrintCount() == 0);

          AND_WHEN(
              "Query is parsed.") {
            int expectedCountDeclarations = 1;
            int expectedCountSynonymInTuple = 1;
            std::string expectedSynonymToRepresentType = design_entity;
            QueryParser tkQry(select_cl_text);
            Query qr;
            tkQry.parse(qr);
            CHECK(qr.countDeclarations() == expectedCountDeclarations);
            CHECK(qr.getEntityOf(synonym) == expectedSynonymToRepresentType);
            CHECK(qr.countSynonymsInTuple() == expectedCountSynonymInTuple);

            AND_THEN("The database query result is line number 1") {
              std::vector<std::string> results;
              QueryEvaluator::evaluate(qr, results);
              CHECK(results.size() == 1);
              CHECK(results.at(0) == std::to_string(1));
            }
          }
        }
      }
    }
  }
}

TEST_CASE("[Test Iteration] 001-2 Asserting Result: Give 1 assigment and get 1 Variable + 1 constant") {
  GIVEN("A connection to the database") {
    database::initialize();

    WHEN("A SIMPLE text and PQL query") {
      // Simple Text
      std::string proc_name_01 = "main";
      std::string var_name_01 = "variable0TARGET0";
      std::string const_value_01 = "123123123123123";

      std::string stmt_01_assign = var_name_01 + " = " + const_value_01 + ";";

      std::string stmtLst = stmt_01_assign;
      std::string procedure_01 = "procedure " + proc_name_01 + " {\n"
                                                               "    " + stmtLst + "\n"
                                                                                  "}";
      std::string simple_text = procedure_01;

      // PQL query
      std::string design_entity_const = "const";
      std::string synonym_const = "const123const123";
      std::string select_cl_text_const = design_entity_const + " " + synonym_const + "; Select " + synonym_const;

      std::string design_entity_val = "variable";
      std::string synonym_val = "var123var";
      std::string select_cl_text_val = design_entity_val + " " + synonym_val + "; Select " + synonym_val;

      AND_WHEN("SIMPLE text is parsed") {
        SimpleParser simpleParser(simple_text);
        Simple simple;
        simpleParser.parse(simple);

        int expectedReadCount = 0;

        AND_THEN("The summary count of composites in simple instance") {

          CHECK(1 == simple.countProcedure());
          CHECK(1 == simple.countAssign());
          CHECK(0 == simple.countPrint());
          CHECK(expectedReadCount == simple.countRead());
          CHECK(1 == simple.countVariable());
          CHECK(1 == simple.countConstant());
        }

        AND_WHEN("Simple instance is inserted into database") {

          database::insertSimple(simple);

          CHECK(database::getReadCount() == expectedReadCount);
          CHECK(database::getPrintCount() == 0);
          CHECK(database::getAssignCount() == 1);
          CHECK(database::getConstantCount() == 1);
          CHECK(database::getVariableCount() == 1);
          AND_WHEN(
              "Query " + select_cl_text_const + " is parsed.") {
            int expectedCountDeclarations = 1;
            int expectedCountSynonymInTuple = 1;
            std::string expectedSynonymToRepresentType = design_entity_const;
            QueryParser tkQry(select_cl_text_const);
            Query qr;
            tkQry.parse(qr);
            CHECK(qr.countDeclarations() == expectedCountDeclarations);
            CHECK(qr.getEntityOf(synonym_const) == expectedSynonymToRepresentType);
            CHECK(qr.countSynonymsInTuple() == expectedCountSynonymInTuple);
            AND_THEN("The database query result is const val " + const_value_01) {
              std::vector<std::string> results;
              QueryEvaluator::evaluate(qr, results);
              CHECK(results.size() == 1);
              CHECK(results.at(0) == const_value_01);
            }
          }

          AND_WHEN(
              "Query " + select_cl_text_val + " is parsed.") {
            int expectedCountDeclarations = 1;
            int expectedCountSynonymInTuple = 1;
            std::string expectedSynonymToRepresentType = design_entity_val;
            QueryParser tkQry(select_cl_text_val);
            Query qr;
            tkQry.parse(qr);
            CHECK(qr.countDeclarations() == expectedCountDeclarations);
            CHECK(qr.getEntityOf(synonym_val) == expectedSynonymToRepresentType);
            CHECK(qr.countSynonymsInTuple() == expectedCountSynonymInTuple);
            AND_THEN("The database query result is var name " + var_name_01) {
              std::vector<std::string> results;
              QueryEvaluator::evaluate(qr, results);
              CHECK(results.size() == 1);
              CHECK(results.at(0) == var_name_01);
            }
          }

        }
      }
    }
  }
}

};

