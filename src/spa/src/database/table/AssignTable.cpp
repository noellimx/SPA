//
// Created by Noel Lim on 28/1/22.
//

#include "AssignTable.hpp"
#include <string>

// Static
AssignTable &AssignTable::GET() { // returns a singleton
  static AssignTable table;
  return table;
}

std::string AssignTable::NAME() {
  return AssignTable::GET().getName();
}

std::string AssignTable::COLUMN_LINE_NO() {
  return AssignTable::GET().getColLineNo();
}

// Singleton
AssignTable::AssignTable() {
  _name = "assigns";
  _col_lineNo = "line_no";
}
std::string AssignTable::getName() {
  return _name;
}

std::string AssignTable::getColLineNo() {
  return _col_lineNo;
}

std::string AssignTable::getAttributes() {
  std::string attributeLineNo = AssignTable::getColLineNo() + " INT PRIMARY KEY";
  std::string attributes = "( " + attributeLineNo + " )";
  return attributes;
};


