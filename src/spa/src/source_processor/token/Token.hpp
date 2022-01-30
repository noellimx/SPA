//
// Created by Noel Lim on 29/1/22.
//

#pragma once

#include <string>
#include <iostream>

#include <utility>

class Token {

protected:
public:
  Token() = default;
  ~Token() = default;
  virtual std::string getType(){return "";};
  virtual std::string getName(){return "";};
};


