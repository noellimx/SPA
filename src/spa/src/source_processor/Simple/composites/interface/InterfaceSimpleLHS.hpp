//
// Created by Noel Lim on 1/2/22.
//


#pragma once

#include <map>

class SimpleAssign;
class InterfaceSimpleLHS {

private:
  std::map<int, SimpleAssign *> assign_modifiers;
public:
  InterfaceSimpleLHS() = default;

  bool isLHSOf(SimpleAssign * sA);
  void addAssignmentModifier(SimpleAssign * sA);

};

