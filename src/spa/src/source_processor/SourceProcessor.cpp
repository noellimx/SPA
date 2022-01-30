#include "SourceProcessor.hpp"


// method for processing the source program
// This method currently only inserts the procedure name into the database
// using some highly simplified logic.
// You should modify this method to complete the logic for handling all the required syntax.
void SourceProcessor::process(std::string program) {
    // initialize the database
    database::initialize();

    // tokenize the program
    SourceTokenizer tk(program);
    std::vector<Token *> tokens;
    tk.tokenize(tokens);
    // This logic is highly simplified based on iteration 1 requirements and
    // the assumption that the programs are valid.
//    for (Token *token: tokens) {
//
//        std::string type = token->getType();
//        if (type == "procedure") {
//            database::insertProcedure((TokenProcedure *) token);
//        }
//
//
//    }
}