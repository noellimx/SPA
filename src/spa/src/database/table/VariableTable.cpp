//
// Created by Noel Lim on 28/1/22.
//

#include "VariableTable.hpp"
#include <string>

// Static
VariableTable &VariableTable::GET() { // returns a singleton
  static VariableTable table;
  return table;
}

std::string VariableTable::NAME() {
  return VariableTable::GET().getName();
}

std::string VariableTable::COLUMN_VALUE() {
  return VariableTable::GET().getColValue();
}

// Singleton
VariableTable::VariableTable() {
  _name = "variables";
  _value = "value";
}
std::string VariableTable::getName() {
  return _name;
}

std::string VariableTable::getColValue() {
  return _value;
}

std::string VariableTable::getAttributes() {
  std::string attributeLineNo = VariableTable::getColValue() + "  VARCHAR(255) PRIMARY KEY";
  std::string attributes = "( " + attributeLineNo + " )";
  return attributes;
};


