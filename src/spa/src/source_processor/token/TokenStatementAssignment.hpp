//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/interface/InterfaceStatementWithLineNo.hpp"
#include "source_processor/token/interface/InterfaceTokenTyped.hpp"
#include "source_processor/token/interface/InterfaceBlockScope.hpp"
#include "source_processor/token/interface/InterfaceFactor.hpp"

#include "TokenVariable.hpp"

#include <iostream>
#include <string>

class TokenStatementAssignment : public InterfaceStatementWithLineNo, public InterfaceTokenTyped, public InterfaceBlockScope{

private:
protected:
  TokenVariable *lhs = nullptr;
  Token *rhs = nullptr;

public:
  TokenStatementAssignment() = default;
  TokenStatementAssignment(TokenVariable *_lhs,Token *_rhs, int _lineNo) : InterfaceStatementWithLineNo(_lineNo) {
    lhs = _lhs;
    rhs = _rhs;
  }
  ~TokenStatementAssignment() = default;

  static std::string TTYPE;

  std::string getType() final {
    return TokenStatementAssignment::TTYPE;
  }
  TokenVariable *getLHS() {
    return lhs;
  }
  Token *getRHS() {
    return rhs;
  }
};


