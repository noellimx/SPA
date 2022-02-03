//
// Created by Noel Lim on 3/2/22.
//

#pragma once

#include "database/database.hpp"
#include "query_processor/Query/Query.hpp"

class QueryEvaluator {

public:
  QueryEvaluator() = default;
  ~QueryEvaluator() = default;;

  static void evaluate(Query &query, std::vector<std::string> & results) {
    std::vector<std::string> thisResults;
    std::string design_entity_0 = query.getEntityOfResultCl(0); // check the design entity of first element of result-cl

    database::queryAllNamesOf(design_entity_0, thisResults);
    for(std::string & thisResult: thisResults){
      results.push_back(thisResult);
    }
  }
};

