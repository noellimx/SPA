#pragma once

#include <string>
#include <vector>


// A class to tokenize a program / query string into a vector of tokens
class QueryTokenizer {

public:
	// default constructor
    QueryTokenizer();

	// destructor
	~QueryTokenizer();

	// method for tokenizing a program / query string
	void tokenize(std::string text, std::vector<std::string>& tokens);
};

