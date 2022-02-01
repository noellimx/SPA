//
// Created by Noel Lim on 1/2/22.
//


#pragma once

#include "source_processor/token/Token.hpp"

class InterfaceBlockScope {
  Token *scope = nullptr;
public:
  InterfaceBlockScope() = default;
  void setBlockScope(Token *_scope) {
    scope = _scope;
  }
  Token *getBlockScope() {
    return scope;
  }
};

