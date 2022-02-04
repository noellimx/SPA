//
// Created by Noel Lim on 28/1/22.
//

#include "PrintTable.hpp"
#include <string>

// Static
PrintTable &PrintTable::GET() { // returns a singleton
  static PrintTable table;
  return table;
}

std::string PrintTable::NAME() {
  return PrintTable::GET().getName();
}

std::string PrintTable::COLUMN_LINE_NO() {
  return PrintTable::GET().getColLineNo();
}

// Singleton
PrintTable::PrintTable() {
  _name = "print";
  _col_lineNo = "line_no";
}
std::string PrintTable::getName() {
  return _name;
}

std::string PrintTable::getColLineNo() {
  return _col_lineNo;
}

std::string PrintTable::getAttributes() {
  std::string attributeLineNo = PrintTable::getColLineNo() + " INT PRIMARY KEY";
  std::string attributes = "( " + attributeLineNo + " )";
  return attributes;
};


