//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/Token.hpp"
#include <iostream>
#include <string>
#include <utility>

class InterfaceStatementWithLineNo : public Token {
private:
  int lineNo = 0;
public:
  InterfaceStatementWithLineNo() = default;
  explicit InterfaceStatementWithLineNo(int _lineNo) : lineNo(_lineNo){}
  ~InterfaceStatementWithLineNo() = default;

  [[nodiscard]] int getLineNo() const{
    return lineNo;
  }
};


