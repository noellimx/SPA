//
// Created by Noel Lim on 29/1/22.
//

#include "SimpleAssign.hpp"

std::string SimpleAssign::TTYPE = "assign";


SimpleAssign::SimpleAssign(SimpleVariable *_lhs, InterfaceSimpleFactor *_rhs, int _lineNo)
    : InterfaceSimpleLined(_lineNo) {
  lhs = _lhs;
  rhs = _rhs;
}

std::string SimpleAssign::getType() {
  return SimpleAssign::TTYPE;
}
