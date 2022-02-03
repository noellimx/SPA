#include "TestWrapper.h"
#include "source_processor/SimpleProcessor.hpp"
#include "database/database.hpp"
#include "query_processor/QueryProcessor.hpp"

AbstractWrapper *WrapperFactory::wrapper = 0;
AbstractWrapper *WrapperFactory::createWrapper() {
  if (wrapper == 0)
    wrapper = new TestWrapper;
  return wrapper;
}

volatile bool AbstractWrapper::GlobalStop = false;

TestWrapper::TestWrapper() = default;

void TestWrapper::parse(std::string simpleFilePath) {
  std::string simpleText = TestWrapper::getSimpleText(simpleFilePath);
  SimpleProcessor::process(simpleText);
}

void TestWrapper::evaluate(std::string query, std::list<std::string> &results) {
  std::vector<std::string> output;

  QueryProcessor qp;
//  qp.evaluate(query, output);

  for (std::string result : output) {
    results.push_back(result);
  }
}