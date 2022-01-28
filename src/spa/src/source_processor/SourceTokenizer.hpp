#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

// A class to tokenize a program / query string into a vector of tokens
class SourceTokenizer {

public:
	// default constructor
    SourceTokenizer();

	// destructor
	~SourceTokenizer();

	// method for tokenizing a program / query string
	void tokenize(string text, vector<string>& tokens);
};

