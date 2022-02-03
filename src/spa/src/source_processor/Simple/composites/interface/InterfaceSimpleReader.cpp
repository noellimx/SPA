//
// Created by Noel Lim on 1/2/22.
//


#include "InterfaceSimpleReader.hpp"
#include "source_processor/Simple/composites/SimpleVariable.hpp"

InterfaceSimpleReader::InterfaceSimpleReader(SimpleVariable * _token): readableVar(_token){};

SimpleVariable * InterfaceSimpleReader::reads() { return readableVar;}

