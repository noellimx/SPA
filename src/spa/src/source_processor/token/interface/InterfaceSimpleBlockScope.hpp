//
// Created by Noel Lim on 1/2/22.
//


#pragma once

#include "source_processor/token/TokenSimple.hpp"

class InterfaceSimpleBlockScope {
  TokenSimple *scope = nullptr;
public:
  InterfaceSimpleBlockScope() = default;
  void setBlockScope(TokenSimple *_scope) {
    scope = _scope;
  }
  TokenSimple *getBlockScope() {
    return scope;
  }
};

