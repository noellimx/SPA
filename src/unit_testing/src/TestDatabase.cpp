
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
TEST_CASE("[TestDatabase]Table Procedure", "[Database.Procedure]") {

  std::string procedureName1 = "procedure1";
  std::string procedureName2 = "procedure2";

  auto *proc1 = new TokenProcedure(procedureName1);
  auto *proc2 = new TokenProcedure(procedureName2);

  database::insertProcedure(proc1);
  database::insertProcedure(proc2);
  CHECK(database::isProcedureExist(proc1->getName()));
  CHECK(database::isProcedureExist(proc2->getName()));

}

}



