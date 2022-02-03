//
// Created by Noel Lim on 1/2/22.
//


#pragma once

#include "source_processor/Simple/composites/SimpleNode.hpp"

class InterfaceSimpleBlockScope {
  SimpleNode *scope = nullptr;
public:
  InterfaceSimpleBlockScope() = default;
  void setBlockScope(SimpleNode *_scope) {
    scope = _scope;
  }
  SimpleNode *getBlockScope() {
    return scope;
  }
};

