//
// Created by Noel Lim on 1/2/22.
//



#include "InterfaceLeftHandSide.hpp"
#include "source_processor/token/TokenStatementAssignment.hpp"


bool InterfaceLeftHandSide::isLHSOf(TokenStatementAssignment * token){
  int lineNo = token->getLineNo();
  return assign_modifiers.count(lineNo) > 0;
}

void InterfaceLeftHandSide::addAssignmentModifier(TokenStatementAssignment * token){
  int lineNo = token->getLineNo();

  assign_modifiers.insert({lineNo,token});
}