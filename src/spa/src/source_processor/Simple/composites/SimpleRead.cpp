//
// Created by Noel Lim on 29/1/22.
//

#include "SimpleRead.hpp"

std::string SimpleRead::TTYPE = "read";

SimpleRead::SimpleRead(int _lineNo, SimpleVariable * readableVar) : InterfaceSimpleLined(_lineNo), InterfaceSimpleReader(readableVar) {
}

std::string SimpleRead::getType() {
  return SimpleRead::TTYPE;
}