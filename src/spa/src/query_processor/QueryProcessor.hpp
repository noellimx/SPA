#pragma once

#include <string>
#include <vector>
#include "database/database.hpp"


class QueryProcessor {
public:
	// default constructor
	QueryProcessor();

	// destructor
	~QueryProcessor();

	// method for evaluating a query
	void evaluate(std::string query, std::vector<std::string>& results);
};