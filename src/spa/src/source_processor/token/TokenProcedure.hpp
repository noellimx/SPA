//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/Token.hpp"
#include "source_processor/token/interface/InterfaceSimpleTyped.hpp"
#include "source_processor/token/interface/InterfaceSimpleNamed.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class TokenProcedure : public Token, public InterfaceSimpleTyped, public InterfaceSimpleNamed{
protected:
  std::vector<Token *> children;
public:
  TokenProcedure() = delete;
  explicit TokenProcedure(std::string _name) : InterfaceSimpleNamed(std::move(_name)){}
  ~TokenProcedure() = default;
  static std::string TTYPE;
  std::string getType();

  void addChildToken(Token * tokenPtr){
    children.push_back(tokenPtr);
  }

  Token * getChildAtPosition(int npos){
    return children.at(npos);
  }
};


