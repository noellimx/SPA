//
// Created by Noel Lim on 28/1/22.
//

#pragma once

#include "database/table/Schema.hpp"

#include <string>

class PrintTable : public Schema {

private:
  PrintTable();
  std::string _name;
  std::string _col_lineNo;

public:
  PrintTable(PrintTable const &) = delete;              // Don't Implement
  void operator=(PrintTable const &) = delete; // Don't implement
  static PrintTable &GET();
  static std::string NAME();
  static std::string COLUMN_LINE_NO();
  std::string getAttributes() override;
  std::string getName() override;
  std::string getColLineNo();
};


