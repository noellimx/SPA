//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/Token.hpp"
#include "source_processor/token/interface/InterfaceTokenTyped.hpp"
#include "source_processor/token/interface/InterfaceTokenNamed.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class TokenProcedure : public Token, public InterfaceTokenTyped, public InterfaceTokenNamed{
protected:
  std::vector<Token *> children;
public:
  TokenProcedure() = delete;
  explicit TokenProcedure(std::string _name) :InterfaceTokenNamed(std::move(_name)){}
  ~TokenProcedure() = default;
  static std::string TYPE() {
    return "procedure";
  };
  std::string getType() override {
    return TokenProcedure::TYPE();
  }



  void addChildToken(Token * tokenPtr){
    children.push_back(tokenPtr);
  }

  Token * getChildAtPosition(int npos){
    return children.at(npos);
  }
};


