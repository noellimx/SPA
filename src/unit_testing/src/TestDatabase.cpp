
#include "database/database.hpp"

#include "catch.hpp"
using namespace std;

// Each cpp is a set of test cases for a specific component.
namespace TestDatabase {
    void require(bool b, string & desc) {
        REQUIRE(b);
    }

    // The name of a test case should be unique and meaningful.
    TEST_CASE("CheckDatabaseProcedure","[Check Database Procedure]") {
        // initialize the database and insert a procedure
        database::initialize();

        std::string procedureName1 = "procedure1";
        std::string procedureName2 = "procedure2";
        std::string procedureName3 = "procedure3";
        database::insertProcedure(procedureName1);
        database::insertProcedure(procedureName2);
        database::insertProcedure(procedureName3);

        // retrieve the procedures from the database
        vector<string> dbResults;
        database::getProcedures(dbResults);

        // create the test output string from the procedures retrieved
        string testOutput;
        for (unsigned int i = 0; i < dbResults.size(); i++)
        {
            testOutput.append(dbResults.at(i) + "$");
        }

        string isProcedure1Exist = database::isProcedureExist(procedureName1);
        string isProcedure2Exist = database::isProcedureExist(procedureName2);
        string isProcedure3Exist = database::isProcedureExist(procedureName3);

        CHECK("1" == isProcedure1Exist);
        CHECK("1" == isProcedure2Exist);
        CHECK("1" == isProcedure3Exist);
    }
}



