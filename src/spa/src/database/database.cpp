#include "database.hpp"
#include "utils/StreamPlus.hpp"

sqlite3* database::dbConnection;
std::vector<std::vector<std::string>> database::dbResults = std::vector<std::vector<std::string>>();

std::vector<Table *> tables = std::vector<Table *>();


char* database::errorMessage;

// method to connect to the database and initialize tables in the database

void database::initializeConnection() {
    sqlite3_open(".database.db", &dbConnection);
}


void database::readyTables(){
    tables.push_back(&ProcedureTable::GET());
}
void database::clearTables(){
    for(Table * table : tables){
        std::string dropProcedureTableStatement = "DROP TABLE IF EXISTS " + table->getName() + ";";
        sqlite3_exec(dbConnection, dropProcedureTableStatement.c_str(), NULL, 0, &errorMessage);
        if(errorMessage != nullptr){
            std::cout << errorMessage << std::endl;
            throw errorMessage;
        }
    }
}


void database::createTables(){
    std::string attributes = std::string();
    for(Table * table : tables){
        attributes.clear();
        std::string createProcedureTableStatement = "CREATE TABLE " +table->getName()+" "+table->getAttributes() + ";";
        std::cout << createProcedureTableStatement << std::endl;
        sqlite3_exec(dbConnection, createProcedureTableStatement.c_str(), NULL, 0, &errorMessage);
        if(errorMessage != nullptr){
            throw errorMessage;
        }
    }
}


void database::initialize() {
	// open a database connection and store the pointer into dbConnection
    database::initializeConnection();

    // table reconstruction
    database::readyTables();
    database::clearTables();
    database::createTables();
}

// method to insert a procedure into the database
void database::insertProcedure(std::string procedureName) {
    std::string insertProcedureSQL = "INSERT INTO "+ProcedureTable::NAME()  + " ('" + ProcedureTable::COLUMN_NAME() + "') VALUES ('" + procedureName + "');";
    sqlite3_exec(dbConnection, insertProcedureSQL.c_str(), NULL, 0, &errorMessage);
}

std::string database::isProcedureExist(std::string procedureName) {
    dbResults.clear();
    std::string statement = "SELECT EXISTS(SELECT 1 FROM " + ProcedureTable::NAME() +  " WHERE " + ProcedureTable::COLUMN_NAME() + "=\""+procedureName+"\" LIMIT 1)";
    sqlite3_exec(dbConnection, statement.c_str(), callback, 0, &errorMessage);
    if(errorMessage != nullptr){
        return errorMessage;
    }
    return dbResults[0][0];
}
// method to get all the procedures from the database
void database::getProcedures(std::vector<std::string>& results){
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

// callback method to put one row of results from the database into the dbResults vector
// This method is called each time a row of results is returned from the database
int database::callback(void* NotUsed, int argc, char** argv, char** azColName) {
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