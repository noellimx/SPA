
#include "database/database.hpp"

#include "catch.hpp"

// Each cpp is a set of test cases for a specific component.
namespace TestDatabase {
    void require(bool b, std::string &desc) {
        REQUIRE(b);
    }

    // The name of a test case should be unique and meaningful.
    TEST_CASE("[Test]DatabaseProcedure", "[Database.Procedure]") {
        std::string testName = "[Test]DatabaseProcedure";
        // Insert 3 procedure names. Expects exactly 3 procedure names stored in database.
        database::initialize();

        std::string procedureName1 = "procedure1";
        std::string procedureName2 = "procedure2";
        std::string procedureName3 = "procedure3";
//        TokenProcedure proc1 = TokenProcedure(std::move(procedureName1));
//        TokenProcedure proc2 = TokenProcedure(std::move(procedureName2));
//        TokenProcedure proc3 = TokenProcedure(std::move(procedureName3));

  TokenProcedure proc1 = TokenProcedure();
  TokenProcedure proc2 = TokenProcedure();
  TokenProcedure proc3 = TokenProcedure();
//        database::insertProcedure(&proc1);
//        database::insertProcedure(&proc2);
//        database::insertProcedure(&proc3);
//
//        CHECK(database::isProcedureExist(std::move(procedureName1)));
//        CHECK(database::isProcedureExist(std::move(procedureName2)));
//        CHECK(database::isProcedureExist(std::move(procedureName3)));
//        CHECK(database::getProcedureCount() == "3");
//
//        std::cout << "End of " << testName << std::endl;
    }
}



