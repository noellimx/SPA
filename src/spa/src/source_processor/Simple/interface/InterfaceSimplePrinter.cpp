//
// Created by Noel Lim on 1/2/22.
//


#include "InterfaceSimplePrinter.hpp"
#include "source_processor/Simple/TokenSimpleVariable.hpp"

InterfaceSimplePrinter::InterfaceSimplePrinter(TokenSimpleVariable * _token): printableVar(_token){};

TokenSimpleVariable * InterfaceSimplePrinter::prints() { return printableVar;}

