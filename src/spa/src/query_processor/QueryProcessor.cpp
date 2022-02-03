#include "QueryProcessor.hpp"

#include <utility>
#include "QueryParser.hpp"
#include "query_processor/Query/Query.hpp"

QueryProcessor::~QueryProcessor() = default;

void QueryProcessor::parseAndEvaluate(std::string select_cl_text, std::vector<std::string> &results) {
  results.clear();

  // parse select_cl_text -> Query
  QueryParser tk(select_cl_text);
  Query qr;
  tk.parse(qr);

  //todo execute Query
  std::vector<std::string> databaseResults;

  for (const std::string &databaseResult : databaseResults) {
    results.push_back(databaseResult);
  }
}