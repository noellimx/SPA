//
// Created by Noel Lim on 28/1/22.
//

#pragma once

#include "database/table/Schema.hpp"

#include <string>

class ConstantTable : public Schema {

private:
  ConstantTable();
  std::string _name;
  std::string _value;

public:
  ConstantTable(ConstantTable const &) = delete;              // Don't Implement
  void operator=(ConstantTable const &) = delete; // Don't implement
  static ConstantTable &GET();
  static std::string NAME();
  static std::string COLUMN_VALUE();
  std::string getAttributes() override;
  std::string getName() override;
  std::string getColValue();
};


