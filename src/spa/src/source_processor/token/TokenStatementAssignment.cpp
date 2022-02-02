//
// Created by Noel Lim on 29/1/22.
//

#include "TokenStatementAssignment.hpp"




std::string TokenStatementAssignment::TTYPE= "assignment";
TokenStatementAssignment::TokenStatementAssignment(TokenVariable *_lhs,Token *_rhs, int _lineNo) : InterfaceStatementWithLineNo(_lineNo) {
    lhs = _lhs;
    rhs = _rhs;
}

std::string TokenStatementAssignment::getType()  {
return TokenStatementAssignment::TTYPE;
}