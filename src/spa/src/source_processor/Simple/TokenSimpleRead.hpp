//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/Simple/interface/InterfaceSimpleLined.hpp"
#include "source_processor/Simple/interface/InterfaceSimpleTyped.hpp"
#include "source_processor/Simple/interface/InterfaceSimpleBlockScope.hpp"
#include "source_processor/Simple/interface/InterfaceSimpleFactor.hpp"
#include "source_processor/Simple/interface/InterfaceSimpleReader.hpp"

#include "TokenSimpleVariable.hpp"

#include <iostream>
#include <string>

class TokenSimpleRead
    : public TokenSimple, public InterfaceSimpleLined, public InterfaceSimpleTyped, public InterfaceSimpleBlockScope, public InterfaceSimpleReader {

private:

public:
  TokenSimpleRead() = delete;
  explicit TokenSimpleRead(int _lineNo, TokenSimpleVariable * readableVar);
  ~TokenSimpleRead() = default;

  static std::string TTYPE;
  std::string getType() final;
};


