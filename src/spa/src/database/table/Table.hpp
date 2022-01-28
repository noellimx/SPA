

#pragma once
#include <string>
#include <vector>


class Table {

public:
    virtual std::string getName() = 0;
    virtual std::string getAttributes() = 0;
};