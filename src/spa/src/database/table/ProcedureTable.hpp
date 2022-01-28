//
// Created by Noel Lim on 28/1/22.
//

#pragma once

#include <string>

class ProcedureTable {

private:
    ProcedureTable();
    std::string _name;

    static ProcedureTable& GET();

    std::string getName();
public:
    ProcedureTable(ProcedureTable const&) = delete;              // Don't Implement
    void operator=(ProcedureTable const&) = delete; // Don't implement

    static std::string NAME();

};


