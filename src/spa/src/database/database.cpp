#include "database.hpp"
#include "utils/StreamPlus.hpp"
#include<stdio.h>

sqlite3 *database::dbConnection;
std::vector<std::vector<std::string>> database::dbResults = std::vector<std::vector<std::string>>();

std::vector<Table *> tables = std::vector<Table *>();

char *database::errorMessage;

// method to connect to the database and initialize tables in the database

void database::initializeConnection() {
  if (dbConnection != nullptr) {
    throw "initializeConnection should be invoked once.";
  }

  sqlite3_open(".database.db", &dbConnection);
}

void database::readyTables() {
  tables.push_back(&ProcedureTable::GET());
}
void database::recreateTables() {
  std::string attributes = std::string();
  for (Table *table : tables) {
    attributes.clear();
    std::string dropProcedureTableStatement = "DROP TABLE IF EXISTS " + table->getName() + ";";

    sqlite3_exec(dbConnection, dropProcedureTableStatement.c_str(), NULL, 0, &errorMessage);
    if (errorMessage != nullptr) {
      throw errorMessage + dropProcedureTableStatement;
    }

    std::string createProcedureTableStatement = "CREATE TABLE " + table->getName() + " " + table->getAttributes() + ";";

    sqlite3_exec(dbConnection, createProcedureTableStatement.c_str(), NULL, 0, &errorMessage);
    if (errorMessage != nullptr) {
      throw errorMessage + createProcedureTableStatement;
    }
  }
}

void database::initializeTables() {
  // ready tables we want to create
  database::readyTables();
  // remove tables
  database::recreateTables();
}

void database::initialize() {
  // open a database connection and store the pointer into dbConnection
  try {
    database::initializeConnection();

  } catch (...) {

  }

  database::initializeTables();

}

// method to insert a procedure into the database
void database::insertProcedure(TokenSimpleProcedure *procedure) {
  std::string insertProcedureSQL =
      "INSERT INTO " + ProcedureTable::NAME() + " ('" + ProcedureTable::COLUMN_NAME() + "') VALUES ('"
          + procedure->getName() + "');";
  sqlite3_exec(dbConnection, insertProcedureSQL.c_str(), NULL, 0, &errorMessage);
}

bool database::isProcedureExist(std::string procedureName) {
  dbResults.clear();
  std::string statement =
      "SELECT EXISTS(SELECT 1 FROM " + ProcedureTable::NAME() + " WHERE " + ProcedureTable::COLUMN_NAME() + "=\""
          + procedureName + "\" LIMIT 1)";
  sqlite3_exec(dbConnection, statement.c_str(), callback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    return errorMessage;
  }
  return dbResults[0][0] == "1";
}
// method to get all the procedures from the database
void database::getProcedures(std::vector<std::string> &results) {
  // clear the existing results
  dbResults.clear();

  // retrieve the procedures from the procedure table
  // The callback method is only used when there are results to be returned.
  std::string getProceduresSQL = "SELECT * FROM procedures;";
  sqlite3_exec(dbConnection, getProceduresSQL.c_str(), callback, 0, &errorMessage);

  // postprocess the results from the database so that the output is just a vector of procedure names
  for (std::vector<std::string> dbRow : dbResults) {
    std::string result;
    result = dbRow.at(0);
    results.push_back(result);
  }
}
std::string database::getProcedureCount() {
  dbResults.clear();
  std::string getProceduresSQL = "SELECT COUNT(*) FROM procedures;";
  sqlite3_exec(dbConnection, getProceduresSQL.c_str(), callback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    return errorMessage;
  }
  return dbResults[0][0];
}
// callback method to put one row of results from the database into the dbResults vector
// This method is called each time a row of results is returned from the database
int database::callback(void *NotUsed, int argc, char **argv, char **azColName) {
  NotUsed = 0;
  std::vector<std::string> dbRow;

  // argc is the number of columns for this row of results
  // argv contains the values for the columns
  // Each value is pushed into a vector.
  for (int i = 0; i < argc; i++) {
    dbRow.push_back(argv[i]);
  }

  // The row is pushed to the vector for storing all rows of results
  dbResults.push_back(dbRow);

  return 0;
}
// method to close the database connection
void database::close() {
  sqlite3_close(dbConnection);
}