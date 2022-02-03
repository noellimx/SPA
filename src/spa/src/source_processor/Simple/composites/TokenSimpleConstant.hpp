//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/Simple/interface/InterfaceSimpleFactor.hpp"
#include "source_processor/Simple/interface/InterfaceSimpleTyped.hpp"
#include "source_processor/Simple/interface/InterfaceSimpleNamed.hpp"

#include "TokenSimple.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class TokenSimpleConstant : public TokenSimple, public InterfaceSimpleTyped, public InterfaceSimpleNamed, public InterfaceSimpleFactor {

public:
  TokenSimpleConstant() = delete;
  ~TokenSimpleConstant() = default;
  explicit TokenSimpleConstant(std::string _name) : InterfaceSimpleNamed(std::move(_name)) {}
  static std::string TTYPE;
  std::string getType() override;

};


