//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/Simple/composites/TokenSimple.hpp"
#include "source_processor/Simple/composites/SimpleVariable.hpp"
#include <iostream>
#include <string>
#include <utility>

class InterfaceSimpleAssign {
private:

protected:
  SimpleVariable *lhs = nullptr;
  InterfaceSimpleFactor *rhs = nullptr;

public:
  InterfaceSimpleAssign() = default;
  ~InterfaceSimpleAssign() = default;
  SimpleVariable *getLHS() {
    return lhs;
  }
  InterfaceSimpleFactor *getRHS() {
    return rhs;
  }
};


