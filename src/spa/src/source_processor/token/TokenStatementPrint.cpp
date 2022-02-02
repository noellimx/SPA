//
// Created by Noel Lim on 29/1/22.
//

#include "TokenStatementPrint.hpp"

std::string TokenStatementPrint::TTYPE = "print";

TokenStatementPrint::TokenStatementPrint(int _lineNo, TokenVariable *readableVar)
    : InterfaceSimpleLined(_lineNo), InterfacePrinter(readableVar) {
}

std::string TokenStatementPrint::getType() {
  return TokenStatementPrint::TTYPE;
}