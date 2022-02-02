#include "QueryProcessor.hpp"
#include "QueryTokenizer.hpp"

// constructor
QueryProcessor::QueryProcessor() = default;

// destructor
QueryProcessor::~QueryProcessor() = default;


void QueryProcessor::evaluate(std::string query, std::vector<std::string>& output) {
	output.clear();

    QueryTokenizer tk;
  std::vector<std::string> tokens;
	tk.tokenize(query, tokens);

	// check what type of synonym is being declared
  std::string synonymType = tokens.at(0);

	// create a vector for storing the results from database
  std::vector<std::string> databaseResults;

	// call the method in database to retrieve the results
	// This logic is highly simplified based on iteration 1 requirements and
	// the assumption that the queries are valid.
	if (synonymType == "procedure") {
		database::getProcedures(databaseResults);
	}

	// post process the results to fill in the output vector
	for (std::string databaseResult : databaseResults) {
		output.push_back(databaseResult);
	}
}