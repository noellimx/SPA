
#include "database/database.hpp"

#include "catch.hpp"

// Each cpp is a set of test cases for a specific component.
namespace TestDatabase {
void require(bool b, std::string &desc) {
  REQUIRE(b);
}

// The name of a test case should be unique and meaningful.
TEST_CASE("[TestDatabase]Table Procedure", "[Database.Procedure]") {
  std::string testName = "[Test]DatabaseProcedure";
  // Insert 3 procedure names. Expects exactly 3 procedure names stored in database.
  database::initialize();

  std::string procedureName1 = "procedure1";
  std::string procedureName2 = "procedure2";

  auto * proc1 = new TokenProcedure(procedureName1);
  auto * proc2 = new TokenProcedure(procedureName2);

  database::insertProcedure(proc1);
  database::insertProcedure(proc2);
  CHECK(database::isProcedureExist(proc1->getName()));
  CHECK(database::isProcedureExist(proc2->getName()));

}
}



