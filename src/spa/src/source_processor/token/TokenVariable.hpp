//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/interface/InterfaceTokenTyped.hpp"
#include "source_processor/token/interface/InterfaceSimpleNamed.hpp"
#include "source_processor/token/interface/InterfaceFactor.hpp"
#include "source_processor/token/interface/InterfaceLeftHandSide.hpp"

#include "source_processor/token/Token.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class TokenVariable : public Token, public InterfaceTokenTyped, public InterfaceSimpleNamed, public InterfaceFactor, public InterfaceLeftHandSide {
protected:
  std::string name;
  static std::string TTYPE;
public:
  TokenVariable() = delete;
  ~TokenVariable() = default;
  explicit TokenVariable(std::string _name) : InterfaceSimpleNamed(std::move(_name)){}
  std::string getType() override;
};


