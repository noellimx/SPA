//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/interface/InterfaceStatementWithLineNo.hpp"
#include "source_processor/token/interface/InterfaceTokenTyped.hpp"
#include "source_processor/token/interface/InterfaceBlockScope.hpp"
#include "source_processor/token/interface/InterfaceFactor.hpp"
#include "source_processor/token/interface/InterfaceReader.hpp"

#include "TokenVariable.hpp"

#include <iostream>
#include <string>

class TokenStatementRead
    : public Token, public InterfaceStatementWithLineNo, public InterfaceTokenTyped, public InterfaceBlockScope, public InterfaceReader {

private:

public:
  TokenStatementRead() = default;
  explicit TokenStatementRead(int _lineNo, TokenVariable * readableVar);
  ~TokenStatementRead() = default;

  static std::string TTYPE;
  std::string getType() final;
};


