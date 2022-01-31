//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/Token.hpp"
#include <iostream>
#include <string>
#include <utility>

class TokenStatementBreakBySemiColon : public Token {
private:
  int lineNo = 0;
public:
  TokenStatementBreakBySemiColon() = default;
  explicit TokenStatementBreakBySemiColon(int _lineNo) : lineNo(_lineNo){}
  ~TokenStatementBreakBySemiColon() = default;
  std::string getType() override;

  [[nodiscard]] int getLineNo() const{
    return lineNo;
  }
};


