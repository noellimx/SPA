//
// Created by Noel Lim on 3/2/22.
//

#pragma once

#include "catch.hpp"
#include "database/database.hpp"
#include "source_processor/SimpleParser.hpp"
#include "query_processor/QueryProcessor.hpp"
#include "query_processor/QueryParser.hpp"

namespace TestIteration001_002 {

TEST_CASE("[Test Iteration] 001-2", "001-2") {
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
};

