//
// Created by Noel Lim on 1/2/22.
//


#pragma once

#include <map>

class TokenStatementAssignment;
class InterfaceLeftHandSide {

private:
  std::map<int,TokenStatementAssignment *> assign_modifiers;
public:
  InterfaceLeftHandSide() = default;

  bool isLHSOf(TokenStatementAssignment * token);
  void addAssignmentModifier(TokenStatementAssignment * token);

};

