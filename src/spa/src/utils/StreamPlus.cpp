//
// Created by Noel Lim on 24/1/22.
//

#include "StreamPlus.h"

std::ostream& operator<<(std::ostream& os, const std::vector<std::string> & elements)
{
    for(const std::string & element : elements){
        std::cout << element << std::endl;
    }
    return os;
}