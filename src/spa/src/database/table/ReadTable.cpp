//
// Created by Noel Lim on 28/1/22.
//

#include "ReadTable.hpp"
#include <string>

// Static
ReadTable &ReadTable::GET() { // returns a singleton
  static ReadTable table;
  return table;
}

std::string ReadTable::NAME() {
  return ReadTable::GET().getName();
}

std::string ReadTable::COLUMN_LINE_NO() {
  return ReadTable::GET().getColLineNo();
}

// Singleton
ReadTable::ReadTable() {
  _name = "reads";
  _col_lineNo = "line_no";
}
std::string ReadTable::getName() {
  return _name;
}

std::string ReadTable::getColLineNo() {
  return _col_lineNo;
}

std::string ReadTable::getAttributes() {
  std::string attributeLineNo = ReadTable::getColLineNo() + " INT PRIMARY KEY";
  std::string attributes = "( " + attributeLineNo + " )";
  return attributes;
};


