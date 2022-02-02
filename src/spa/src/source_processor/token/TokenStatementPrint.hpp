//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/interface/InterfaceSimpleLined.hpp"
#include "source_processor/token/interface/InterfaceSimpleTyped.hpp"
#include "source_processor/token/interface/InterfaceSimpleBlockScope.hpp"
#include "source_processor/token/interface/InterfacePrinter.hpp"

#include "TokenVariable.hpp"

#include <iostream>
#include <string>

class TokenStatementPrint
    : public Token, public InterfaceSimpleLined, public InterfaceSimpleTyped, public InterfaceSimpleBlockScope, public InterfacePrinter {

private:

public:
  TokenStatementPrint() = delete;
  explicit TokenStatementPrint(int _lineNo, TokenVariable * readableVar);
  ~TokenStatementPrint() = default;

  static std::string TTYPE;
  std::string getType() final;
};


