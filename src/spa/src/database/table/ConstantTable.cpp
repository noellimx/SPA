//
// Created by Noel Lim on 28/1/22.
//

#include "ConstantTable.hpp"
#include <string>

// Static
ConstantTable &ConstantTable::GET() { // returns a singleton
  static ConstantTable table;
  return table;
}

std::string ConstantTable::NAME() {
  return ConstantTable::GET().getName();
}

std::string ConstantTable::COLUMN_VALUE() {
  return ConstantTable::GET().getColValue();
}

// Singleton
ConstantTable::ConstantTable() {
  _name = "constants";
  _value = "value";
}
std::string ConstantTable::getName() {
  return _name;
}

std::string ConstantTable::getColValue() {
  return _value;
}

std::string ConstantTable::getAttributes() {
  std::string attributeLineNo = ConstantTable::getColValue() + " INT PRIMARY KEY";
  std::string attributes = "( " + attributeLineNo + " )";
  return attributes;
};


