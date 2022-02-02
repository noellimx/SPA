//
// Created by Noel Lim on 1/2/22.
//


#include "InterfacePrinter.hpp"
#include "source_processor/token/TokenVariable.hpp"

InterfacePrinter::InterfacePrinter(TokenVariable * _token):printableVar(_token){};

TokenVariable * InterfacePrinter::prints() { return printableVar;}

