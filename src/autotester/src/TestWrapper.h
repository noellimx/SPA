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

  static std::string getSimpleText(std::string & filePath){
    std::ifstream fs(filePath);
    std::stringstream buffer;
    buffer << fs.rdbuf();
    return buffer.str();
  }
 public:
  // default constructor
  TestWrapper();
  
  // destructor
  ~TestWrapper();
  
  // method for parsing the SIMPLE source
  virtual void parse(std::string simpleFileName);
  
  // method for evaluating a query
  virtual void evaluate(std::string query, std::list<std::string>& results);
};

#endif
