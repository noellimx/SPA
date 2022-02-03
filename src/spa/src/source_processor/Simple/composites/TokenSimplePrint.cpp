//
// Created by Noel Lim on 29/1/22.
//

#include "TokenSimplePrint.hpp"

std::string TokenSimplePrint::TTYPE = "print";

TokenSimplePrint::TokenSimplePrint(int _lineNo, TokenSimpleVariable *readableVar)
    : InterfaceSimpleLined(_lineNo), InterfaceSimplePrinter(readableVar) {
}

std::string TokenSimplePrint::getType() {
  return TokenSimplePrint::TTYPE;
}