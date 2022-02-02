//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/interface/InterfaceSimpleLined.hpp"
#include "source_processor/token/interface/InterfaceSimpleTyped.hpp"
#include "source_processor/token/interface/InterfaceSimpleBlockScope.hpp"
#include "source_processor/token/interface/InterfaceFactor.hpp"
#include "source_processor/token/interface/InterfaceSimpleAssign.hpp"

#include "TokenVariable.hpp"

#include <iostream>
#include <string>

class TokenStatementAssignment
    : public Token,
      public InterfaceSimpleAssign,
      public InterfaceSimpleLined,
      public InterfaceSimpleTyped,
      public InterfaceSimpleBlockScope {

private:

public:
  TokenStatementAssignment() = delete;
  TokenStatementAssignment(TokenVariable *_lhs, InterfaceFactor *_rhs, int _lineNo);
  ~TokenStatementAssignment() = default;

  static std::string TTYPE;
  std::string getType() final;

};


