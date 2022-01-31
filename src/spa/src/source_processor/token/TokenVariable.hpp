//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/TokenFactor.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <utility>

class TokenVariable : public Token {
protected:
  std::string name;
public:
  TokenVariable() = delete;
  explicit TokenVariable(std::string _name) :name(std::move(_name)){}
  ~TokenVariable() = default;
  static std::string TYPE() {
    return "variable";
  };
  std::string getType() override {
    return TokenVariable::TYPE();
  };
  std::string getName() override{
    return name;
  };



};


