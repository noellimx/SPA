//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/interface/InterfaceStatementWithLineNo.hpp"
#include "source_processor/token/interface/InterfaceTokenTyped.hpp"
#include "source_processor/token/interface/InterfaceBlockScope.hpp"
#include "source_processor/token/interface/InterfaceFactor.hpp"
#include "source_processor/token/interface/InterfaceAssignment.hpp"

#include "TokenVariable.hpp"

#include <iostream>
#include <string>

class TokenStatementAssignment
    : public Token,
      public InterfaceAssignment,
      public InterfaceStatementWithLineNo,
      public InterfaceTokenTyped,
      public InterfaceBlockScope {

private:

public:
  TokenStatementAssignment() = delete;
  TokenStatementAssignment(TokenVariable *_lhs, InterfaceFactor *_rhs, int _lineNo);
  ~TokenStatementAssignment() = default;

  static std::string TTYPE;
  std::string getType() final;

};


