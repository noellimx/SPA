
#include "database/database.hpp"

#include "catch.hpp"
using namespace std;

// Each cpp is a set of test cases for a specific component.
namespace TestDatabase {
    void require(bool b, string & desc) {
        REQUIRE(b);
    }

    // The name of a test case should be unique and meaningful.
    TEST_CASE("[Test]DatabaseProcedure","[Database.Procedure]") {
        // Insert 3 procedure names. Expects exactly 3 procedure names stored in database.
        database::initialize();

        std::string procedureName1 = "procedure1";
        std::string procedureName2 = "procedure2";
        std::string procedureName3 = "procedure3";
        database::insertProcedure(procedureName1);
        database::insertProcedure(procedureName2);
        database::insertProcedure(procedureName3);

        string isProcedure1Exist = database::isProcedureExist(procedureName1);
        string isProcedure2Exist = database::isProcedureExist(procedureName2);
        string isProcedure3Exist = database::isProcedureExist(procedureName3);

        CHECK("1" == isProcedure1Exist);
        CHECK("1" == isProcedure2Exist);
        CHECK("1" == isProcedure3Exist);
        CHECK(database::getProcedureCount() == "3");
    }
}



