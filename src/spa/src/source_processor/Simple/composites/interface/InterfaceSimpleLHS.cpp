//
// Created by Noel Lim on 1/2/22.
//



#include "InterfaceSimpleLHS.hpp"
#include "source_processor/Simple/composites/SimpleAssign.hpp"

bool InterfaceSimpleLHS::isLHSOf(SimpleAssign * sA){
  int lineNo = sA->getLineNo();
  return assign_modifiers.count(lineNo) > 0;
}

void InterfaceSimpleLHS::addAssignmentModifier(SimpleAssign * sA){
  int lineNo = sA->getLineNo();
  assign_modifiers.insert({lineNo, sA});
}