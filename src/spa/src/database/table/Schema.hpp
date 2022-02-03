

#pragma once
#include <string>
#include <vector>


class Schema {

public:
    virtual std::string getName() = 0;
    virtual std::string getAttributes() = 0;
};