//
// Created by Noel Lim on 24/1/22.
//

#include "StreamPlus.h"

std::ostream& operator<<(std::ostream& os, const std::vector<std::string> & elements)
{
    int length = elements.size();
    std::cout << "[ ";
    int i = 0;
    for(i = 0; i < length - 1; i++){
        std::cout << elements[i] << " . ";
    }
    std::cout << elements[i] << " ]" << std::endl;;
    return os;
}