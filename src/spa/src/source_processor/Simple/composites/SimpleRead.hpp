//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/Simple/composites/interface/InterfaceSimpleLined.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleTyped.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleBlockScope.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleFactor.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleReader.hpp"

#include "SimpleVariable.hpp"

#include <iostream>
#include <string>

class SimpleRead
    : public TokenSimple, public InterfaceSimpleLined, public InterfaceSimpleTyped, public InterfaceSimpleBlockScope, public InterfaceSimpleReader {

private:

public:
  SimpleRead() = delete;
  explicit SimpleRead(int _lineNo, SimpleVariable * readableVar);
  ~SimpleRead() = default;

  static std::string TTYPE;
  std::string getType() final;
};


