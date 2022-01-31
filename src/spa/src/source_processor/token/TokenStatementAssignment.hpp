//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/TokenStatementBreakBySemiColon.hpp"
#include <iostream>
#include <string>

class TokenStatementAssignment : public TokenStatementBreakBySemiColon {

private:
protected:
  Token *lhs = nullptr;
  Token *rhs = nullptr;
  Token *scope = nullptr;
public:
  TokenStatementAssignment() = default;
  TokenStatementAssignment(Token *_lhs,Token *_rhs, int _lineNo) : TokenStatementBreakBySemiColon(_lineNo) {
    lhs = _lhs;
    rhs = _rhs;
  }
  ~TokenStatementAssignment() = default;
  static std::string TYPE() {
    return "assignment";
  }
  std::string getType() final {
    return TokenStatementAssignment::TYPE();
  }
  Token *getLHS() {
    return lhs;
  }
  Token *getRHS() {
    return rhs;
  }

  void setScope(Token *_scope) {
    scope = _scope;
  }
  Token *getScope() {
    return scope;
  }

};


