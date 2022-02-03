
#include "database/database.hpp"

#include "catch.hpp"

namespace TestDatabase {
void require(bool b, std::string &desc) {
  REQUIRE(b);
}
TEST_CASE("[TestDatabase]Connection should throw if initialize connection twice.") {
  database::initialize();
  CHECK_THROWS(database::initializeConnection());
}
TEST_CASE("[TestDatabase]Table Procedure", "Simple Procedures") {
  database::initialize();

  std::string procedureName1 = "procedure1";
  std::string procedureName2 = "procedure2";

  auto *proc1 = new SimpleProcedure(procedureName1);
  auto *proc2 = new SimpleProcedure(procedureName2);

  database::insertProcedure(proc1);
  database::insertProcedure(proc2);

  CHECK("procedure1" == proc1->getName());
  CHECK(database::isProcedureExist(proc1->getName()));
  CHECK(database::isProcedureExist(proc2->getName()));
  AND_WHEN("procedure names are retrieved") {
    std::vector<std::string> procedureNames;

    database::selectProcedureNamesAll(procedureNames);
    AND_THEN("two counts of procedure names"){
      CHECK(procedureNames.size() == 2);
      CHECK(database::getProcedureCount() == 2);
      AND_THEN("The procedure names are returned"){
        if (procedureNames.at(0) == procedureName1) { // without loss of generality
          CHECK(procedureNames.at(0) == procedureName1);
          CHECK(procedureNames.at(1) == procedureName2);
        } else {
          CHECK(procedureNames.at(1) == procedureName1);
          CHECK(procedureNames.at(0) == procedureName2);
        }
      }
    }



  }
}

}



