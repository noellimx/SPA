#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "sqlite3.h"
#include "database/table/Schema.hpp"
#include "database/table/ProcedureTable.hpp"
#include "source_processor/Simple/composites/SimpleProcedure.hpp"
#include "source_processor/Simple/Simple.hpp"

// The Database has to be a static class due to various constraints.

class database {

private:

  static sqlite3 *dbConnection;
  static std::vector<std::vector<std::string>> _db_results;
  static char *errorMessage;

  static std::vector<Schema *> tables;

  // callback method to put one row of results from the database into the dbResults vector
  // This method is called each time a row of results is returned from the database
  static int resultCallback(void *NotUsed, int columnCount, char **argv, char **azColName);

public:
  database() = delete;

  // Setup
  static void initializeConnection();

  static void readyTables();
  static void recreateTables();
  static void initializeTables();

  static void initialize();
  // Tear Down
  static void close();

  // CRUD - CREATE
  static void insertSimple(Simple &) {}
  static void insertProcedure(SimpleProcedure *);
  // CRUD - READ
  static bool isProcedureExist(const std::string &procedureName);
  static void selectProcedureNamesAll(std::vector<std::string> &);
  static int getProcedureCount();

};

