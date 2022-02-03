//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/Simple/composites/interface/InterfaceSimpleLined.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleTyped.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleBlockScope.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleFactor.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleAssign.hpp"

#include "TokenSimpleVariable.hpp"

#include <iostream>
#include <string>

class TokenSimpleAssignment
    : public TokenSimple,
      public InterfaceSimpleAssign,
      public InterfaceSimpleLined,
      public InterfaceSimpleTyped,
      public InterfaceSimpleBlockScope {

private:

public:
  TokenSimpleAssignment() = delete;
  TokenSimpleAssignment(TokenSimpleVariable *_lhs, InterfaceSimpleFactor *_rhs, int _lineNo);
  ~TokenSimpleAssignment() = default;

  static std::string TTYPE;
  std::string getType() final;

};


