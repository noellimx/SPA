//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/interface/InterfaceStatementWithLineNo.hpp"
#include "source_processor/token/interface/InterfaceTokenTyped.hpp"
#include "source_processor/token/interface/InterfaceBlockScope.hpp"
#include "source_processor/token/interface/InterfacePrinter.hpp"

#include "TokenVariable.hpp"

#include <iostream>
#include <string>

class TokenStatementPrint
    : public Token, public InterfaceStatementWithLineNo, public InterfaceTokenTyped, public InterfaceBlockScope, public InterfacePrinter {

private:

public:
  TokenStatementPrint() = default;
  explicit TokenStatementPrint(int _lineNo, TokenVariable * readableVar);
  ~TokenStatementPrint() = default;

  static std::string TTYPE;
  std::string getType() final;
};


