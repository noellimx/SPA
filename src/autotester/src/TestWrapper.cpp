#include "TestWrapper.h"
#include "source_processor/SourceProcessor.hpp"
#include "database/database.hpp"
#include "query_processor/QueryProcessor.hpp"


AbstractWrapper *WrapperFactory::wrapper = 0;
AbstractWrapper *WrapperFactory::createWrapper() {
  if (wrapper == 0)
    wrapper = new TestWrapper;
  return wrapper;
}

volatile bool AbstractWrapper::GlobalStop = false;


TestWrapper::TestWrapper() {

}


void TestWrapper::parse(std::string filename) {

  std::ifstream fs(filename);
  std::stringstream buffer;
  buffer << fs.rdbuf();
  std::string program = buffer.str();

  SourceProcessor sp;
  sp.process(program);
}


void TestWrapper::evaluate(std::string query, std::list<std::string> &results) {
  std::vector<std::string> output;

  QueryProcessor qp;
  qp.evaluate(query, output);

  for (std::string result : output) {
    results.push_back(result);
  }
}