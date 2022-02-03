//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/Simple/TokenSimple.hpp"
#include "source_processor/Simple/TokenSimpleVariable.hpp"
#include <iostream>
#include <string>
#include <utility>

class InterfaceSimpleAssign {
private:

protected:
  TokenSimpleVariable *lhs = nullptr;
  InterfaceSimpleFactor *rhs = nullptr;

public:
  InterfaceSimpleAssign() = default;
  ~InterfaceSimpleAssign() = default;
  TokenSimpleVariable *getLHS() {
    return lhs;
  }
  InterfaceSimpleFactor *getRHS() {
    return rhs;
  }
};


