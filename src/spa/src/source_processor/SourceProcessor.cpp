#include "SourceProcessor.hpp"


// method for processing the source program
// This method currently only inserts the procedure name into the database
// using some highly simplified logic.
// You should modify this method to complete the logic for handling all the required syntax.
void SourceProcessor::process(std::string program) {
	// initialize the database
	database::initialize();

	// tokenize the program
    SourceTokenizer tk;
	std::vector<std::string> tokens;
	tk.tokenize(program, tokens);
    std::cout << tokens << std::endl;
	// This logic is highly simplified based on iteration 1 requirements and
	// the assumption that the programs are valid.
	std::string procedureName = tokens.at(1);
    std::cout << "tokens.at(1)" << std::endl;
    std::cout << tokens.at(1) << std::endl;
	// insert the procedure into the database
	database::insertProcedure(procedureName);
}