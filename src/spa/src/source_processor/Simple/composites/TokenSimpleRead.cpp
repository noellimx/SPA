//
// Created by Noel Lim on 29/1/22.
//

#include "TokenSimpleRead.hpp"

std::string TokenSimpleRead::TTYPE = "read";

TokenSimpleRead::TokenSimpleRead(int _lineNo, SimpleVariable * readableVar) : InterfaceSimpleLined(_lineNo), InterfaceSimpleReader(readableVar) {
}

std::string TokenSimpleRead::getType() {
  return TokenSimpleRead::TTYPE;
}