#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <list>

#include "AbstractWrapper.h"

class TestWrapper : public AbstractWrapper {

private:

  static std::string getSimpleText(std::string &filePath) {
    std::ifstream fs(filePath);
    std::stringstream buffer;
    buffer << fs.rdbuf();
    return buffer.str();
  }
public:
  TestWrapper();
  ~TestWrapper() = default;

  // SIMPLE
  void parse(std::string) override;
  // SQL
  void evaluate(std::string, std::list<std::string> &) override;
};

#endif
