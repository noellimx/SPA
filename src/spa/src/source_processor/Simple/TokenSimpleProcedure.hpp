//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/Simple/TokenSimple.hpp"
#include "source_processor/Simple/interface/InterfaceSimpleTyped.hpp"
#include "source_processor/Simple/interface/InterfaceSimpleNamed.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class TokenSimpleProcedure : public TokenSimple, public InterfaceSimpleTyped, public InterfaceSimpleNamed{
protected:
  std::vector<TokenSimple *> children;
public:
  TokenSimpleProcedure() = delete;
  explicit TokenSimpleProcedure(std::string _name) : InterfaceSimpleNamed(std::move(_name)){}
  ~TokenSimpleProcedure() = default;
  static std::string TTYPE;
  std::string getType();

  void addChildToken(TokenSimple * tokenPtr){
    children.push_back(tokenPtr);
  }

  TokenSimple * getChildAtPosition(int npos){
    return children.at(npos);
  }
};


