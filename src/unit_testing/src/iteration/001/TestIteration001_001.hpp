//
// Created by Noel Lim on 3/2/22.
//

#pragma once
#include "catch.hpp"
#include "database/database.hpp"
#include "source_processor/SourceTokenizer.hpp"
#include "query_processor/QueryProcessor.hpp"

namespace TestIteration001_001 {




TEST_CASE("[Test PQL] A growing program", "") {
  GIVEN("A connection to the database"){
    database::initialize();

    WHEN("Source is processed into tokens"){

      std::string proc_name_01 = "main1";
      std::string var_name_01 = "var1";
      std::string var_name_02 = "var2";
      std::string const_value_01 = "1";
      std::string const_value_02 = "2";

      std::string stmt_01_assign = var_name_01 + " = " + const_value_01 + ";";
      std::string stmt_02_assign =  var_name_02 + " = " + const_value_02 + ";";

      std::string stmtLst = stmt_01_assign + stmt_02_assign;
      std::string procedure_01 = "procedure " + proc_name_01 + " { " + stmtLst + " }";
      std::string program = procedure_01;


      SourceTokenizer tk(program);
      TokenBag tokenBag;
      tk.tokenize(tokenBag);
      AND_THEN("The summary count of tokens"){
        CHECK(1 == tokenBag.countProcedure());
        CHECK(2 == tokenBag.countAssign());
        CHECK(2 == tokenBag.countVariable());
        CHECK(2 == tokenBag.countConstant());

        AND_THEN("SQL queries"){
          AND_WHEN("Query is simple select procedure" ){
            AND_THEN("Returns"){

              std::string expectedProcName = proc_name_01;
              std::string declaration = "procedure";
              std::string synonym = "p";
              std::string select_cl = declaration + " " + synonym + ";" + "Select " + synonym;
              std::vector<std::string> result;
              QueryProcessor qp;
              qp.evaluate(select_cl,result);
              CHECK(result.size() == 1);
            }

          }

        }
      }
    }

  }



}
};
#include "catch.hpp"

