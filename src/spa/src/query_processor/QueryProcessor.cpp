#include "QueryProcessor.hpp"
#include "QueryTokenizer.hpp"
#include "query_processor/aggregator/Query.hpp"

// constructor
QueryProcessor::QueryProcessor() = default;

// destructor
QueryProcessor::~QueryProcessor() = default;

void QueryProcessor::evaluate(std::string query, std::vector<std::string> &output) {
  output.clear();

  QueryTokenizer tk;
  Query qr;
  tk.tokenize(query, qr);


  std::vector<std::string> databaseResults;



  // post process the results to fill in the output vector
  for (std::string databaseResult : databaseResults) {
    output.push_back(databaseResult);
  }
}