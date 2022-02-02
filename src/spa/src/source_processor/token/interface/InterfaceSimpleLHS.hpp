//
// Created by Noel Lim on 1/2/22.
//


#pragma once

#include <map>

class TokenSimpleAssignment;
class InterfaceSimpleLHS {

private:
  std::map<int, TokenSimpleAssignment *> assign_modifiers;
public:
  InterfaceSimpleLHS() = default;

  bool isLHSOf(TokenSimpleAssignment * token);
  void addAssignmentModifier(TokenSimpleAssignment * token);

};

