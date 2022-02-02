//
// Created by Noel Lim on 29/1/22.
//

#pragma once


#include "source_processor/token/Token.hpp"
#include "source_processor/token/TokenVariable.hpp"
#include <iostream>
#include <string>
#include <utility>

class InterfaceAssignment {
private:

protected:
  TokenVariable *lhs = nullptr;
  Token *rhs = nullptr;

public:
  InterfaceAssignment() = default;
  ~InterfaceAssignment() = default;
  TokenVariable *getLHS() {
    return lhs;
  }
  Token *getRHS() {
    return rhs;
  }
};


