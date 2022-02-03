#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "sqlite3.h"
#include "database/table/Table.hpp"
#include "database/table/ProcedureTable.hpp"
#include "source_processor/Simple/composites/SimpleProcedure.hpp"

// The Database has to be a static class due to various constraints.
// It is advisable to just add the insert / get functions based on the given examples.
class database {
public:
    database() = delete;

    // method to connect to the database and initialize tables in the database
    static void initializeConnection();
    static void initialize();

    static void close();

    static void insertProcedure(SimpleProcedure *);

    static bool isProcedureExist(std::string procedureName);
    static void selectProcedureNamesAll(std::vector<std::string> &);
    static int getProcedureCount();

private:

    // the connection pointer to the database
    static sqlite3 *dbConnection;
    // a vector containing the results from the database
    static std::vector<std::vector<std::string>> _db_results;
    // the error message from the database
    static char *errorMessage;

    static void readyTables();
    static void recreateTables();
    static void initializeTables();

    // callback method to put one row of results from the database into the dbResults vector
    // This method is called each time a row of results is returned from the database
    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};

