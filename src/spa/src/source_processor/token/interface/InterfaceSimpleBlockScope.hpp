//
// Created by Noel Lim on 1/2/22.
//


#pragma once

#include "source_processor/token/Token.hpp"

class InterfaceSimpleBlockScope {
  Token *scope = nullptr;
public:
  InterfaceSimpleBlockScope() = default;
  void setBlockScope(Token *_scope) {
    scope = _scope;
  }
  Token *getBlockScope() {
    return scope;
  }
};

