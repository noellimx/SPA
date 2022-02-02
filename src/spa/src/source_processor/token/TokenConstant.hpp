//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/interface/InterfaceFactor.hpp"
#include "source_processor/token/interface/InterfaceTokenTyped.hpp"
#include "source_processor/token/interface/InterfaceTokenNamed.hpp"

#include "source_processor/token/Token.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class TokenConstant : public Token, public InterfaceTokenTyped, public InterfaceTokenNamed, public InterfaceFactor {

public:
  TokenConstant() = delete;
  ~TokenConstant() = default;
  explicit TokenConstant(std::string _name) : InterfaceTokenNamed(std::move(_name)) {}
  static std::string TTYPE;
  std::string getType() override;

};


