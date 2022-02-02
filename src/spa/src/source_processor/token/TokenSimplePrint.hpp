//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/interface/InterfaceSimpleLined.hpp"
#include "source_processor/token/interface/InterfaceSimpleTyped.hpp"
#include "source_processor/token/interface/InterfaceSimpleBlockScope.hpp"
#include "source_processor/token/interface/InterfaceSimplePrinter.hpp"

#include "TokenSimpleVariable.hpp"

#include <iostream>
#include <string>

class TokenSimplePrint
    : public TokenSimple, public InterfaceSimpleLined, public InterfaceSimpleTyped, public InterfaceSimpleBlockScope, public InterfaceSimplePrinter {

private:

public:
  TokenSimplePrint() = delete;
  explicit TokenSimplePrint(int _lineNo, TokenSimpleVariable * readableVar);
  ~TokenSimplePrint() = default;

  static std::string TTYPE;
  std::string getType() final;
};


