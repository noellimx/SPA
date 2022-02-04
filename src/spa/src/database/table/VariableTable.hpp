//
// Created by Noel Lim on 28/1/22.
//

#pragma once

#include "database/table/Schema.hpp"

#include <string>

class VariableTable : public Schema {

private:
  VariableTable();
  std::string _name;
  std::string _value;

public:
  VariableTable(VariableTable const &) = delete;              // Don't Implement
  void operator=(VariableTable const &) = delete; // Don't implement
  static VariableTable &GET();
  static std::string NAME();
  static std::string COLUMN_VALUE();
  std::string getAttributes() override;
  std::string getName() override;
  std::string getColValue();
};


