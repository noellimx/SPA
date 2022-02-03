#include "QueryProcessor.hpp"
#include "QueryTokenizer.hpp"
#include "query_processor/aggregator/Query.hpp"

// constructor
QueryProcessor::QueryProcessor() = default;

// destructor
QueryProcessor::~QueryProcessor() = default;

void QueryProcessor::evaluate(std::string query, std::vector<std::string> &output) {
  output.clear();

  QueryTokenizer tk(query);
  Query qr;
  tk.tokenize(qr);

  std::vector<std::string> databaseResults;

  for (const std::string &databaseResult : databaseResults) {
    output.push_back(databaseResult);
  }
}