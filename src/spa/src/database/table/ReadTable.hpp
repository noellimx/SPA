//
// Created by Noel Lim on 28/1/22.
//

#pragma once

#include "database/table/Schema.hpp"

#include <string>

class ReadTable : public Schema {

private:
  ReadTable();
  std::string _name;
  std::string _col_lineNo;

public:
  ReadTable(ReadTable const &) = delete;              // Don't Implement
  void operator=(ReadTable const &) = delete; // Don't implement
  static ReadTable &GET();
  static std::string NAME();
  static std::string COLUMN_LINE_NO();
  std::string getAttributes() override;
  std::string getName() override;
  std::string getColLineNo();
};


