//
// Created by Noel Lim on 1/2/22.
//


#include "InterfaceSimpleReader.hpp"
#include "source_processor/token/TokenSimpleVariable.hpp"

InterfaceSimpleReader::InterfaceSimpleReader(TokenSimpleVariable * _token): readableVar(_token){};

TokenSimpleVariable * InterfaceSimpleReader::reads() { return readableVar;}

