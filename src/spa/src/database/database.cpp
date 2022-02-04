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
  tables.push_back(&AssignTable::GET());
  tables.push_back(&PrintTable::GET());
  tables.push_back(&ReadTable::GET());
  tables.push_back(&ConstantTable::GET());
  tables.push_back(&VariableTable::GET());
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
  for (auto &procedure : *procedures) {
    database::insertProcedure(procedure);
  }

  auto *assigns = simple.getAssigns();
  for (auto &assign : *assigns) {
    database::insertAssign(assign.second);
  }

  auto *prints = simple.getPrints();
  for (auto &print : *prints) {
    database::insertPrint(print.second);
  }
  auto *reads = simple.getReads();
  for (auto &read : *reads) {
    database::insertRead(read.second);
  }

  auto *constants = simple.getConstants();
  for (auto &constant : *constants) {
    database::insertConstant(constant.second);
  }
  auto *variables = simple.getVariables();
  for (auto &variable : *variables) {
    database::insertVariables(variable.second);
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
void database::insertAssign(SimpleAssign *assignment) {
  std::string insertProcedureSQL =
      "INSERT INTO " + AssignTable::NAME() + " ('" + AssignTable::COLUMN_LINE_NO() + "') VALUES ('"
          + std::to_string(assignment->getLineNo()) + "');";
  sqlite3_exec(dbConnection, insertProcedureSQL.c_str(), NULL, 0, &errorMessage);
}

// method to insert an assign into the database
void database::insertPrint(SimplePrint *print) {
  std::string insertProcedureSQL =
      "INSERT INTO " + PrintTable::NAME() + " ('" + PrintTable::COLUMN_LINE_NO() + "') VALUES ('"
          + std::to_string(print->getLineNo()) + "');";
  sqlite3_exec(dbConnection, insertProcedureSQL.c_str(), NULL, 0, &errorMessage);
}

void database::insertRead(SimpleRead *read) {
  std::string insertProcedureSQL =
      "INSERT INTO " + ReadTable::NAME() + " ('" + ReadTable::COLUMN_LINE_NO() + "') VALUES ('"
          + std::to_string(read->getLineNo()) + "');";
  sqlite3_exec(dbConnection, insertProcedureSQL.c_str(), NULL, 0, &errorMessage);
}
void database::insertConstant(SimpleConstant *constant) {
  std::string insertProcedureSQL =
      "INSERT INTO " + ConstantTable::NAME() + " ('" + ConstantTable::COLUMN_VALUE() + "') VALUES ('"
          + constant->getName() + "');";
  sqlite3_exec(dbConnection, insertProcedureSQL.c_str(), NULL, 0, &errorMessage);

  if (errorMessage) {
    throw "[insertConstant]" + std::string{errorMessage};
  }
}

void database::insertVariables(SimpleVariable *constant) {
  std::string insertProcedureSQL =
      "INSERT INTO " + VariableTable::NAME() + " ('" + VariableTable::COLUMN_VALUE() + "') VALUES ('"
          + constant->getName() + "');";
  sqlite3_exec(dbConnection, insertProcedureSQL.c_str(), NULL, 0, &errorMessage);

  if (errorMessage) {
    throw "[insertConstant]" + std::string{errorMessage};
  }
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

  std::string getProceduresSQL = "SELECT COUNT(*) FROM " + AssignTable::NAME() + ";";
  sqlite3_exec(dbConnection, getProceduresSQL.c_str(), resultCallback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    return -1;
  }

  auto firstRow = _db_results[0];
  auto firstRowFirstColumnVal = firstRow[0];
  return std::stoi(firstRowFirstColumnVal);
}

int database::getConstantCount() {
  _db_results.clear();

  std::string getProceduresSQL = "SELECT COUNT(*) FROM " + ConstantTable::NAME() + ";";
  sqlite3_exec(dbConnection, getProceduresSQL.c_str(), resultCallback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    throw errorMessage;
    return -1;
  }

  auto firstRow = _db_results[0];
  auto firstRowFirstColumnVal = firstRow[0];
  return std::stoi(firstRowFirstColumnVal);
}

int database::getVariableCount() {
  _db_results.clear();

  std::string getProceduresSQL = "SELECT COUNT(*) FROM " + VariableTable::NAME() + ";";
  sqlite3_exec(dbConnection, getProceduresSQL.c_str(), resultCallback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    throw errorMessage;
    return -1;
  }

  auto firstRow = _db_results[0];
  auto firstRowFirstColumnVal = firstRow[0];
  return std::stoi(firstRowFirstColumnVal);
}

int database::getPrintCount() {
  _db_results.clear();

  std::string sql = "SELECT COUNT(*) FROM " + PrintTable::NAME() + ";";
  sqlite3_exec(dbConnection, sql.c_str(), resultCallback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    return -1;
  }

  auto firstRow = _db_results[0];
  auto firstRowFirstColumnVal = firstRow[0];
  return std::stoi(firstRowFirstColumnVal);
}
int database::getReadCount() {
  _db_results.clear();

  std::string sql = "SELECT COUNT(*) FROM " + ReadTable::NAME() + ";";
  sqlite3_exec(dbConnection, sql.c_str(), resultCallback, 0, &errorMessage);
  if (errorMessage != nullptr) {
    return -1;
  }

  auto firstRow = _db_results[0];
  auto firstRowFirstColumnVal = firstRow[0];
  return std::stoi(firstRowFirstColumnVal);
}

int database::getReadLimit1() {
  _db_results.clear();

  std::string sql = "SELECT " + ReadTable::COLUMN_LINE_NO() + " FROM " + ReadTable::NAME() + " LIMIT 1;";
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
void database::selectReadNamesAll(std::vector<std::string> &results) {
  results.clear();
  _db_results.clear();
  std::string getProceduresSQL = "SELECT " + ReadTable::COLUMN_LINE_NO() + " FROM " + ReadTable::NAME() + ";";
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
void database::selectConstValAll(std::vector<std::string> &results) {
  results.clear();
  _db_results.clear();
  std::string getProceduresSQL = "SELECT " + ConstantTable::COLUMN_VALUE() + " FROM " + ConstantTable::NAME() + ";";
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

void database::selectVariableValAll(std::vector<std::string> &results) {
  results.clear();
  _db_results.clear();
  std::string getProceduresSQL = "SELECT " + VariableTable::COLUMN_VALUE() + " FROM " + VariableTable::NAME() + ";";
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