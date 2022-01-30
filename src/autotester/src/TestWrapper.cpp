#include "TestWrapper.h"
#include "source_processor/SourceProcessor.hpp"
#include "database/database.hpp"
#include "query_processor/QueryProcessor.hpp"

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper *WrapperFactory::wrapper = 0;
AbstractWrapper *WrapperFactory::createWrapper() {
  if (wrapper == 0)
    wrapper = new TestWrapper;
  return wrapper;
}
// do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
  // read the source program from the file
  std::ifstream fs(filename);
  std::stringstream buffer;
  buffer << fs.rdbuf();
  std::string program = buffer.str();

  // call the source processor to process it
  std::cout << program << std::endl;
  SourceProcessor sp;
  sp.process(program);
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string> &results) {
  std::vector<std::string> output;

  // call the query processor to process a single query
  QueryProcessor qp;
  qp.evaluate(query, output);

  // convert a vector of results to a list of results
  for (std::string result : output) {
    results.push_back(result);
  }
}