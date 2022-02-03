//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/Simple/composites/interface/InterfaceSimpleTyped.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleNamed.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleFactor.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleLHS.hpp"

#include "TokenSimple.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class SimpleVariable : public TokenSimple, public InterfaceSimpleTyped, public InterfaceSimpleNamed, public InterfaceSimpleFactor, public InterfaceSimpleLHS {
protected:
  std::string name;
  static std::string TTYPE;
public:
  SimpleVariable() = delete;
  ~SimpleVariable() = default;
  explicit SimpleVariable(std::string _name) : InterfaceSimpleNamed(std::move(_name)){}
  std::string getType() override;
};


