//
// Created by Noel Lim on 1/2/22.
//



#include "InterfaceSimpleLHS.hpp"
#include "source_processor/token/TokenSimpleAssignment.hpp"


bool InterfaceSimpleLHS::isLHSOf(TokenSimpleAssignment * token){
  int lineNo = token->getLineNo();
  return assign_modifiers.count(lineNo) > 0;
}

void InterfaceSimpleLHS::addAssignmentModifier(TokenSimpleAssignment * token){
  int lineNo = token->getLineNo();

  assign_modifiers.insert({lineNo,token});
}