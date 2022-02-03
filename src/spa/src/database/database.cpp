#include "database.hpp"
#include "utils/StreamPlus.hpp"

sqlite3 *database::dbConnection;
std::vector<std::vector<std::string>> database::_db_results = std::vector<std::vector<std::string>>();
char *database::errorMessage;

std::vector<Schema *> database::tables = std::vector<Schema *>();

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
  for (Schema *table : tables) {
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
void database::insertProcedure(SimpleProcedure *procedure) {
  std::string insertProcedureSQL =
      "INSERT INTO " + ProcedureTable::NAME() + " ('" + ProcedureTable::COLUMN_NAME() + "') VALUES ('"
          + procedure->getName() + "');";
  sqlite3_exec(dbConnection, insertProcedureSQL.c_str(), NULL, 0, &errorMessage);
}

bool database::isProcedureExist(const std::string &procedureName) {
  _db_results.clear();
  std::string statement =
      "SELECT EXISTS(SELECT 1 FROM " + ProcedureTable::NAME() + " WHERE " + ProcedureTable::COLUMN_NAME() + "=\""
          + procedureName + "\" LIMIT 1)";
  sqlite3_exec(dbConnection, statement.c_str(), callback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    return errorMessage;
  }
  return _db_results[0][0] == "1";
}

void database::selectProcedureNamesAll(std::vector<std::string> &results) {
  results.clear();

  _db_results.clear();
  std::string getProceduresSQL = "SELECT " + ProcedureTable::COLUMN_NAME() + " FROM procedures;";

  sqlite3_exec(dbConnection, getProceduresSQL.c_str(), database::callback, 0, &errorMessage);

  for (std::vector<std::string> dbRow : _db_results) {
    std::string result;
    result = dbRow.at(0);
    results.push_back(result);
  }
}
int database::getProcedureCount() {
  _db_results.clear();
  std::string getProceduresSQL = "SELECT COUNT(*) FROM procedures;";
  sqlite3_exec(dbConnection, getProceduresSQL.c_str(), callback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    return -1;
  }

  auto firstRow = _db_results[0];
  auto firstRowFirstColumnVal = firstRow[0];
  return std::stoi(firstRowFirstColumnVal);
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
  _db_results.push_back(dbRow);

  return 0;
}
// method to close the database connection
void database::close() {
  sqlite3_close(dbConnection);
}