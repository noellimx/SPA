//
// Created by Noel Lim on 29/1/22.
//

#include "TokenStatementRead.hpp"

std::string TokenStatementRead::TTYPE = "read";

TokenStatementRead::TokenStatementRead(int _lineNo, TokenVariable * readableVar) : InterfaceSimpleLined(_lineNo), InterfaceReader(readableVar) {
}

std::string TokenStatementRead::getType() {
  return TokenStatementRead::TTYPE;
}