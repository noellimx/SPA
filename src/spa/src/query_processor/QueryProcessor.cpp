#include "QueryProcessor.hpp"
#include "QueryParser.hpp"
#include "query_processor/Query/Query.hpp"

// constructor
QueryProcessor::QueryProcessor() = default;

// destructor
QueryProcessor::~QueryProcessor() = default;

void QueryProcessor::evaluate(std::string query, std::vector<std::string> &output) {
  output.clear();

  QueryParser tk(query);
  Query qr;
  tk.tokenize(qr);

  std::vector<std::string> databaseResults;

  for (const std::string &databaseResult : databaseResults) {
    output.push_back(databaseResult);
  }
}