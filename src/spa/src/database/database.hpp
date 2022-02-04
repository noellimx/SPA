#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "sqlite3.h"
#include "database/table/Schema.hpp"
#include "database/table/ProcedureTable.hpp"
#include "database/table/AssignTable.hpp"
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
  static void insertSimple(Simple &);

  static void insertProcedure(SimpleProcedure *);
  static void insertAssign(SimpleAssign *);
  static void insertPrint(SimplePrint *);

  // CRUD - READ
  static void queryAllNamesOf(std::string design_entity, std::vector<std::string> &results) {

    std::vector<std::string> thisResults;
    if (design_entity == "procedure") {
      database::selectProcedureNamesAll(thisResults);
    } else if (design_entity == "assign") {
      database::selectAssignLinesAll(thisResults);
    }else if (design_entity == "print") {
      database::selectPrintLinesAll(thisResults);
    }

    for (std::string &thisResult : thisResults) {
      results.push_back(thisResult);
    }
  }

  static bool isProcedureExist(const std::string &procedureName);
  static int getProcedureCount();
  static void selectProcedureNamesAll(std::vector<std::string> &);
  static void selectAssignLinesAll(std::vector<std::string> &);
  static void selectPrintLinesAll(std::vector<std::string> &);

  static int getAssignCount();
  static int getPrintCount();
};

