//
// Created by Noel Lim on 1/2/22.
//


#include "InterfaceSimplePrinter.hpp"
#include "source_processor/Simple/composites/SimpleVariable.hpp"

InterfaceSimplePrinter::InterfaceSimplePrinter(SimpleVariable * _sVar): printableVar(_sVar){};

SimpleVariable * InterfaceSimplePrinter::prints() { return printableVar;}

