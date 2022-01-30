//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/Token.hpp"
#include <iostream>
#include <string>
#include <utility>

class TokenProcedure : public Token {
protected:
public:
  TokenProcedure() = default;
  ~TokenProcedure() = default;
  static std::string NAME() {
    return "procedure";
  };
  std::string getType();
};


