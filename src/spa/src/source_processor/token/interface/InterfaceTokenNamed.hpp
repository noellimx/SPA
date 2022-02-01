//
// Created by Noel Lim on 1/2/22.
//

#pragma once
#include <string>

class InterfaceTokenNamed {
protected:
  std::string name;

public:

  explicit InterfaceTokenNamed(std::string _name) : name(std::move(_name)) {}
  std::string getName() { return name; };

};

