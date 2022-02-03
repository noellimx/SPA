//
// Created by Noel Lim on 29/1/22.
//

#include "SimplePrint.hpp"

std::string SimplePrint::TTYPE = "print";

SimplePrint::SimplePrint(int _lineNo, SimpleVariable *readableVar)
    : InterfaceSimpleLined(_lineNo), InterfaceSimplePrinter(readableVar) {
}

std::string SimplePrint::getType() {
  return SimplePrint::TTYPE;
}