//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/Token.hpp"
#include "source_processor/token/TokenVariable.hpp"
#include <iostream>
#include <string>
#include <utility>

class InterfaceSimpleAssign {
private:

protected:
  TokenVariable *lhs = nullptr;
  InterfaceFactor *rhs = nullptr;

public:
  InterfaceSimpleAssign() = default;
  ~InterfaceSimpleAssign() = default;
  TokenVariable *getLHS() {
    return lhs;
  }
  InterfaceFactor *getRHS() {
    return rhs;
  }
};

