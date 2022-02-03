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
  SimpleProcessor::parseAndPersist(simpleText);
}

// query_text is select-cl
void TestWrapper::evaluate(std::string select_cl, std::list<std::string> &results) {
  std::vector<std::string> output;
  QueryProcessor::parseAndEvaluate(select_cl, output);

  for (const std::string &result : output) {
    results.push_back(result);
  }
}