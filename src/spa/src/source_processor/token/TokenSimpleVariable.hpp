//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/interface/InterfaceSimpleTyped.hpp"
#include "source_processor/token/interface/InterfaceSimpleNamed.hpp"
#include "source_processor/token/interface/InterfaceSimpleFactor.hpp"
#include "source_processor/token/interface/InterfaceSimpleLHS.hpp"

#include "source_processor/token/TokenSimple.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class TokenSimpleVariable : public TokenSimple, public InterfaceSimpleTyped, public InterfaceSimpleNamed, public InterfaceSimpleFactor, public InterfaceSimpleLHS {
protected:
  std::string name;
  static std::string TTYPE;
public:
  TokenSimpleVariable() = delete;
  ~TokenSimpleVariable() = default;
  explicit TokenSimpleVariable(std::string _name) : InterfaceSimpleNamed(std::move(_name)){}
  std::string getType() override;
};


