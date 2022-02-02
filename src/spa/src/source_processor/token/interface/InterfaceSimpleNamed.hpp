//
// Created by Noel Lim on 1/2/22.
//

#pragma once
#include <string>

class InterfaceSimpleNamed {
protected:
  std::string name;

public:
  InterfaceSimpleNamed() = default;
  ~InterfaceSimpleNamed() = default;
  explicit InterfaceSimpleNamed(std::string _name) : name(std::move(_name)) {}
  std::string getName() { return name; };

};

