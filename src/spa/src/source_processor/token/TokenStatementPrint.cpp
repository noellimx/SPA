//
// Created by Noel Lim on 29/1/22.
//

#include "TokenStatementPrint.hpp"

TokenStatementPrint::TokenStatementPrint(int _lineNo, TokenVariable * readableVar) : InterfaceStatementWithLineNo(_lineNo), InterfacePrinter(readableVar) {
}

std::string TokenStatementPrint::TTYPE = "print";
std::string TokenStatementPrint::getType() {
  return TokenStatementPrint::TTYPE;
}