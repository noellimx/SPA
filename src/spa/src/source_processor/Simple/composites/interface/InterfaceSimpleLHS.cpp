//
// Created by Noel Lim on 1/2/22.
//



#include "InterfaceSimpleLHS.hpp"
#include "source_processor/Simple/composites/SimpleAssign.hpp"


bool InterfaceSimpleLHS::isLHSOf(SimpleAssign * token){
  int lineNo = token->getLineNo();
  return assign_modifiers.count(lineNo) > 0;
}

void InterfaceSimpleLHS::addAssignmentModifier(SimpleAssign * token){
  int lineNo = token->getLineNo();

  assign_modifiers.insert({lineNo,token});
}