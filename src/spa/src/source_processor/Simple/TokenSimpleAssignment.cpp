//
// Created by Noel Lim on 29/1/22.
//

#include "TokenSimpleAssignment.hpp"

std::string TokenSimpleAssignment::TTYPE = "assign";


TokenSimpleAssignment::TokenSimpleAssignment(TokenSimpleVariable *_lhs, InterfaceSimpleFactor *_rhs, int _lineNo)
    : InterfaceSimpleLined(_lineNo) {
  lhs = _lhs;
  rhs = _rhs;
}

std::string TokenSimpleAssignment::getType() {
  return TokenSimpleAssignment::TTYPE;
}
