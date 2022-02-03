//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/Simple/composites/interface/InterfaceSimpleLined.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleTyped.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleBlockScope.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleFactor.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleAssign.hpp"

#include "SimpleVariable.hpp"

#include <iostream>
#include <string>

class SimpleAssign
    : public SimpleNode,
      public InterfaceSimpleAssign,
      public InterfaceSimpleLined,
      public InterfaceSimpleTyped,
      public InterfaceSimpleBlockScope {

private:

public:
  SimpleAssign() = delete;
  SimpleAssign(SimpleVariable *_lhs, InterfaceSimpleFactor *_rhs, int _lineNo);
  ~SimpleAssign() = default;

  static std::string TTYPE;
  std::string getType() final;

};


