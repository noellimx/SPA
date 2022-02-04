#include "database.hpp"
#include "utils/StreamPlus.hpp"
#include "database/table/PrintTable.hpp"

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
  tables.push_back(&AssignTable::GET());
  tables.push_back(&PrintTable::GET());
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

// Mother of All inserts
void database::insertSimple(Simple &simple) {
  auto *procedures = simple.getProcedures();
  for (auto it = procedures->begin(); it != procedures->end(); ++it) {
    database::insertProcedure(*it);
  }

  auto *assigns = simple.getAssigns();
  for (auto it = assigns->begin(); it != assigns->end(); ++it) {
    database::insertAssign(it->second);
  }

  auto *reads = simple.getPrints();
  for (auto it = reads->begin(); it != reads->end(); ++it) {
    database::insertPrint(it->second);
  }

}
// method to insert a procedure into the database
void database::insertProcedure(SimpleProcedure *procedure) {
  std::string insertProcedureSQL =
      "INSERT INTO " + ProcedureTable::NAME() + " ('" + ProcedureTable::COLUMN_NAME() + "') VALUES ('"
          + procedure->getName() + "');";
  sqlite3_exec(dbConnection, insertProcedureSQL.c_str(), NULL, 0, &errorMessage);
}
// method to insert an assign into the database
void database::insertAssign(SimpleAssign * assignment) {
  std::string insertProcedureSQL =
      "INSERT INTO " + AssignTable::NAME() + " ('" + AssignTable::COLUMN_LINE_NO() + "') VALUES ('"
          + std::to_string(assignment->getLineNo()) + "');";
  sqlite3_exec(dbConnection, insertProcedureSQL.c_str(), NULL, 0, &errorMessage);
}

// method to insert an assign into the database
void database::insertPrint(SimplePrint * assignment) {
  std::string insertProcedureSQL =
      "INSERT INTO " + PrintTable::NAME() + " ('" + PrintTable::COLUMN_LINE_NO() + "') VALUES ('"
          + std::to_string(assignment->getLineNo()) + "');";
  sqlite3_exec(dbConnection, insertProcedureSQL.c_str(), NULL, 0, &errorMessage);
}

bool database::isProcedureExist(const std::string &procedureName) {
  _db_results.clear();
  std::string statement =
      "SELECT EXISTS(SELECT 1 FROM " + ProcedureTable::NAME() + " WHERE " + ProcedureTable::COLUMN_NAME() + "=\""
          + procedureName + "\" LIMIT 1)";
  sqlite3_exec(dbConnection, statement.c_str(), resultCallback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    return errorMessage;
  }
  return _db_results[0][0] == "1";
}
int database::getProcedureCount() {
  _db_results.clear();
  std::string getProceduresSQL = "SELECT COUNT(*) FROM procedures;";
  sqlite3_exec(dbConnection, getProceduresSQL.c_str(), resultCallback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    return -1;
  }

  auto firstRow = _db_results[0];
  auto firstRowFirstColumnVal = firstRow[0];
  return std::stoi(firstRowFirstColumnVal);
}

int database::getAssignCount() {
  _db_results.clear();

  std::string getProceduresSQL = "SELECT COUNT(*) FROM " + AssignTable::NAME() +";";
  sqlite3_exec(dbConnection, getProceduresSQL.c_str(), resultCallback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    return -1;
  }

  auto firstRow = _db_results[0];
  auto firstRowFirstColumnVal = firstRow[0];
  return std::stoi(firstRowFirstColumnVal);
}

int database::getPrintCount() {
  _db_results.clear();

  std::string sql = "SELECT COUNT(*) FROM " + PrintTable::NAME() +";";
  sqlite3_exec(dbConnection, sql.c_str(), resultCallback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    return -1;
  }

  auto firstRow = _db_results[0];
  auto firstRowFirstColumnVal = firstRow[0];
  return std::stoi(firstRowFirstColumnVal);
}

void database::selectAssignLinesAll(std::vector<std::string> &results) {
  results.clear();
  _db_results.clear();
  std::string getProceduresSQL = "SELECT " + AssignTable::COLUMN_LINE_NO() + " FROM " + AssignTable::NAME() + ";";
  sqlite3_exec(dbConnection, getProceduresSQL.c_str(), resultCallback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    throw errorMessage;
  }
  for (std::vector<std::string> &_db_result : _db_results) {
    std::string result;
    result = _db_result.at(0);
    results.push_back(result);
  }

}

void database::selectPrintLinesAll(std::vector<std::string> &results) {
  results.clear();
  _db_results.clear();
  std::string getProceduresSQL = "SELECT " + PrintTable::COLUMN_LINE_NO() + " FROM " + PrintTable::NAME() + ";";
  sqlite3_exec(dbConnection, getProceduresSQL.c_str(), resultCallback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    throw errorMessage;
  }
  for (std::vector<std::string> &_db_result : _db_results) {
    std::string result;
    result = _db_result.at(0);
    results.push_back(result);
  }

}
void database::selectProcedureNamesAll(std::vector<std::string> &results) {
  results.clear();
  _db_results.clear();
  std::string getProceduresSQL = "SELECT " + ProcedureTable::COLUMN_NAME() + " FROM " + ProcedureTable::NAME() + ";";

  sqlite3_exec(dbConnection, getProceduresSQL.c_str(), database::resultCallback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    throw errorMessage;
  }


  for (std::vector<std::string> &_db_result : _db_results) {
    std::string result;
    result = _db_result.at(0);
    results.push_back(result);
  }
}

// callback method to put one row of results from the database into the dbResults vector
// This method is called each time a row of results is returned from the database
int database::resultCallback(void *NotUsed, int columnCount, char **argv, char **azColName) {
  NotUsed = 0;
  std::vector<std::string> dbRow;

  for (int i = 0; i < columnCount; i++) {
    dbRow.push_back(argv[i]);
  }

  _db_results.push_back(dbRow);

  return 0;
}
void database::close() {
  sqlite3_close(dbConnection);
}