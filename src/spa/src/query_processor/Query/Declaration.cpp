//
// Created by Noel Lim on 3/2/22.
//

#include "Declaration.hpp"


Declaration::Declaration(std::string _type,std::string _synonym) : type(std::move(_type)), synonym(std::move(_synonym)) {}