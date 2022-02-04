#include "QueryProcessor.hpp"

#include <utility>
#include "QueryParser.hpp"
#include "query_processor/Query/Query.hpp"
#include "QueryEvaluator.hpp"

QueryProcessor::~QueryProcessor() = default;

void QueryProcessor::parseAndEvaluate(std::string select_cl_text, std::vector<std::string> &results) {
  results.clear();
  // parse select_cl_text -> Query
  QueryParser queryParser(std::move(select_cl_text));
  Query qr;
  queryParser.parseInto(qr);
  //todo execute Query
  std::vector<std::string> thisResults;

  QueryEvaluator::evaluate(qr, thisResults);

  for (const std::string &thisResult : thisResults) {
    results.push_back(thisResult);
  }
}