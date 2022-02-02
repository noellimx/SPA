//
// Created by Noel Lim on 1/2/22.
//


#include "InterfaceReader.hpp"
#include "source_processor/token/TokenVariable.hpp"

InterfaceReader::InterfaceReader(TokenVariable * _token):readableVar(_token){};

TokenVariable * InterfaceReader::reads() { return readableVar;}

