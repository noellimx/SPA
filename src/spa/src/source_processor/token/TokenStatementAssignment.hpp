//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/interface/InterfaceStatementWithLineNo.hpp"
#include "source_processor/token/interface/InterfaceTokenTyped.hpp"
#include "source_processor/token/interface/InterfaceBlockScope.hpp"

#include <iostream>
#include <string>

class TokenStatementAssignment : public InterfaceStatementWithLineNo, public InterfaceTokenTyped, public InterfaceBlockScope{

private:
protected:
  Token *lhs = nullptr;
  Token *rhs = nullptr;

public:
  TokenStatementAssignment() = default;
  TokenStatementAssignment(Token *_lhs,Token *_rhs, int _lineNo) : InterfaceStatementWithLineNo(_lineNo) {
    lhs = _lhs;
    rhs = _rhs;
  }
  ~TokenStatementAssignment() = default;

  static std::string TTYPE;

  std::string getType() final {
    return TokenStatementAssignment::TTYPE;
  }
  Token *getLHS() {
    return lhs;
  }
  Token *getRHS() {
    return rhs;
  }
};


