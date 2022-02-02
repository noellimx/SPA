//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/interface/InterfaceTokenTyped.hpp"
#include "source_processor/token/interface/InterfaceTokenNamed.hpp"
#include "source_processor/token/interface/InterfaceFactor.hpp"
#include "source_processor/token/interface/InterfaceLHS.hpp"

#include "source_processor/token/Token.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class TokenVariable : public Token, public InterfaceTokenTyped, public InterfaceTokenNamed, public InterfaceFactor, public InterfaceLHS {
protected:
  std::string name;
  static std::string TTYPE;
public:
  TokenVariable() = default;
  ~TokenVariable() = default;
  explicit TokenVariable(std::string _name) :InterfaceTokenNamed(std::move(_name)){}
  std::string getType() override;
};


