//
// Created by Noel Lim on 3/2/22.
//


#pragma once

#include <vector>

#include "query_processor/Declaration.hpp"
class result_cl {

public:
  std::vector<Declaration *> tuple;
  result_cl() = default;
  ~result_cl() = default;
  void addToTuple(Declaration *d) {
    tuple.push_back(d);
  }
};

