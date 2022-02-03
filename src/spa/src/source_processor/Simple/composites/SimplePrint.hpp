//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/Simple/composites/interface/InterfaceSimpleLined.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleTyped.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleBlockScope.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimplePrinter.hpp"

#include "SimpleVariable.hpp"

#include <iostream>
#include <string>

class SimplePrint
    : public TokenSimple, public InterfaceSimpleLined, public InterfaceSimpleTyped, public InterfaceSimpleBlockScope, public InterfaceSimplePrinter {

private:

public:
  SimplePrint() = delete;
  explicit SimplePrint(int _lineNo, SimpleVariable * readableVar);
  ~SimplePrint() = default;

  static std::string TTYPE;
  std::string getType() final;
};


