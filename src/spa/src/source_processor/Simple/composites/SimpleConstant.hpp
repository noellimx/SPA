//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/Simple/composites/interface/InterfaceSimpleFactor.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleTyped.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleNamed.hpp"

#include "SimpleNode.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class SimpleConstant : public SimpleNode, public InterfaceSimpleTyped, public InterfaceSimpleNamed, public InterfaceSimpleFactor {

public:
  SimpleConstant() = delete;
  ~SimpleConstant() = default;
  explicit SimpleConstant(std::string _name) : InterfaceSimpleNamed(std::move(_name)) {}
  static std::string TTYPE;
  std::string getType() override;

};


