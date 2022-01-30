//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include "source_processor/token/Token.hpp"
#include <iostream>
#include <string>
#include <utility>

class TokenProcedure : public Token {
protected:
  std::string name;
public:
  TokenProcedure() = delete;
  explicit TokenProcedure(std::string& _name) :name(std::move(_name)){}
  ~TokenProcedure() = default;
  static std::string TYPE() {
    return "procedure";
  };
  std::string getType();
  std::string getName(){
    return name;
  };
};


