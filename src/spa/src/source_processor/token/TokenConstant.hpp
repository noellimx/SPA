//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/TokenFactor.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <utility>

class TokenConstant : public Token {
protected:
  std::string name;
public:
  TokenConstant() = delete;
  explicit TokenConstant(std::string _name) : name(std::move(_name)) {}
  ~TokenConstant() = default;
  static std::string TYPE() {
    return "constant";
  };
  std::string getType() override {
    return TokenConstant::TYPE();
  };
  std::string getName() override {
    return name;
  };
};


