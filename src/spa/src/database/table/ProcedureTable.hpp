//
// Created by Noel Lim on 28/1/22.
//

#pragma once

#include "database/table/Schema.hpp"

#include <string>

class ProcedureTable : public Schema {

private:
  ProcedureTable();
  std::string _name;
  std::string _col_name;

public:
  ProcedureTable(ProcedureTable const &) = delete;              // Don't Implement
  void operator=(ProcedureTable const &) = delete; // Don't implement
  static ProcedureTable &GET();
  static std::string NAME();
  static std::string COLUMN_NAME();
  std::string getAttributes() override;
  std::string getName() override;
  std::string getColName();
};


