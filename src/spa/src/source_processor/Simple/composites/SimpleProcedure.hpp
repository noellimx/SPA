//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "SimpleNode.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleTyped.hpp"
#include "source_processor/Simple/composites/interface/InterfaceSimpleNamed.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <utility>

class SimpleProcedure : public SimpleNode, public InterfaceSimpleTyped, public InterfaceSimpleNamed{
protected:
  std::vector<SimpleNode *> children;
public:
  SimpleProcedure() = delete;
  explicit SimpleProcedure(std::string _name) : InterfaceSimpleNamed(std::move(_name)){}
  ~SimpleProcedure() = default;
  static std::string TTYPE;
  std::string getType() override;

  void addChildNode(SimpleNode * sN_ptr){
    children.push_back(sN_ptr);
  }

  SimpleNode * getChildAtPosition(int npos){
    return children.at(npos);
  }
};


