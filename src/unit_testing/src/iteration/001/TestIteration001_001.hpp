//
// Created by Noel Lim on 3/2/22.
//

#pragma once
#include "catch.hpp"
#include "database/database.hpp"
#include "source_processor/SimpleParser.hpp"
#include "query_processor/QueryProcessor.hpp"
#include "query_processor/QueryParser.hpp"

namespace TestIteration001_001 {

TEST_CASE("[Test Iteration]", "001") {
  GIVEN("A connection to the database") {
    database::initialize();

    WHEN("Source is processed into tokens") {

      std::string proc_name_01 = "main1";
      std::string var_name_01 = "var1";
      std::string var_name_02 = "var2";
      std::string const_value_01 = "1";
      std::string const_value_02 = "2";

      std::string stmt_01_assign = var_name_01 + " = " + const_value_01 + ";";
      std::string stmt_02_assign = var_name_02 + " = " + const_value_02 + ";";

      std::string stmtLst = stmt_01_assign + stmt_02_assign;
      std::string procedure_01 = "procedure " + proc_name_01 + " { " + stmtLst + " }";
      std::string program = procedure_01;

      SimpleParser tkSrc(program);
      Simple tokenBag;
      tkSrc.parse(tokenBag);
      AND_THEN("The summary count of tokens") {
        CHECK(1 == tokenBag.countProcedure());
        CHECK(2 == tokenBag.countAssign());
        CHECK(2 == tokenBag.countVariable());
        CHECK(2 == tokenBag.countConstant());

        AND_THEN("SQL queries") {
          AND_WHEN("Query instance is to select all procedure") {

            std::string design_entity = "procedure";
            std::string synonym = "q";
            std::string declaration = design_entity + " " + synonym + ";";
            std::string select_cl_text = declaration + "Select " + synonym;

            int expectedCountDeclarations = 1;
            int expectedCountSynonymInTuple = 1;
            std::string expectedSynonymToRepresentType = "procedure";
            AND_THEN(
                "Query has " + std::to_string(expectedCountDeclarations) + " synonym " + synonym + "declared as type "
                    + expectedSynonymToRepresentType + " and tuple has "
                    + std::to_string(expectedCountSynonymInTuple) + " synonym.") {
              QueryParser tkQry(select_cl_text);
              Query qr;
              tkQry.parse(qr);
              CHECK(qr.countDeclarations() == expectedCountDeclarations);
              CHECK(qr.getEntityOf(synonym) == expectedSynonymToRepresentType);
              CHECK(qr.countSynonymsInTuple() == expectedCountSynonymInTuple);

              AND_THEN("Query returns a vector with one element ") {
                std::vector<std::string> results;
                QueryProcessor::parseAndEvaluate(select_cl_text, results);
              }
            }
          }
        }
      }
    }

  }

}
};
#include "catch.hpp"

