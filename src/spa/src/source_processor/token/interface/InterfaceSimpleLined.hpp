//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/Token.hpp"
#include <iostream>
#include <string>
#include <utility>

class InterfaceSimpleLined {
private:
  int lineNo = 0;
public:
  InterfaceSimpleLined() = default;
  explicit InterfaceSimpleLined(int _lineNo) : lineNo(_lineNo){}
  ~InterfaceSimpleLined() = default;

  [[nodiscard]] int getLineNo() const{
    return lineNo;
  }
};


