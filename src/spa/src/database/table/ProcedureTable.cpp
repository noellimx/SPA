//
// Created by Noel Lim on 28/1/22.
//

#include "ProcedureTable.hpp"
#include <string>

// Static
ProcedureTable& ProcedureTable::GET() { // returns a singleton
    static ProcedureTable table;
    return table;
}

std::string ProcedureTable::NAME(){
    return ProcedureTable::GET().getName();
}


std::string ProcedureTable::COLUMN_NAME(){
    return ProcedureTable::GET().getColName();
}

// Singleton
ProcedureTable::ProcedureTable() {
    _name = "procedures";
    _col_name = "name";
}
std::string ProcedureTable::getName(){
    return _name;
}

std::string ProcedureTable::getColName(){
    return _col_name;
}

std::string ProcedureTable::getAttributes(){
    std::string attributeName = "name VARCHAR(255) PRIMARY KEY";
    std::string attributes = "( " + attributeName + " )";
    return attributes;
};


