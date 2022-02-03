//
// Created by Noel Lim on 2/2/22.
//

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "source_processor/Simple/composites/SimpleProcedure.hpp"
#include "source_processor/Simple/composites/SimpleAssign.hpp"
#include "source_processor/Simple/composites/SimpleVariable.hpp"
#include "source_processor/Simple/composites/SimpleConstant.hpp"
#include "source_processor/Simple/composites/SimpleRead.hpp"
#include "source_processor/Simple/composites/SimplePrint.hpp"


#pragma once
class TokenSimpleBag {
private:
  std::vector<SimpleProcedure *> procedureTokens;
  std::map<int, SimpleAssign *> assignTokens;
  std::map<std::string, SimpleVariable *> variableTokens;
  std::map<std::string, SimpleConstant *> constantTokens;
  std::map<int, SimpleRead *> readTokens;
  std::map<int, SimplePrint *> printTokens;
public:
  void addProcedure(SimpleProcedure *token) {
    procedureTokens.push_back(token);
  }
  SimpleProcedure *getProcedure(int i) {
    return procedureTokens.at(i);
  }
  void addVariable(SimpleVariable *token) {
    std::string var_name = token->getName();
    variableTokens.insert({var_name, token});
  }

  SimpleVariable *getVariable(const std::string &var_name) {
    return variableTokens.at(var_name);
  }

  void addRead(SimpleRead *token) {
    int lineNo = token->getLineNo();
    readTokens.insert({lineNo, token});
  }
  SimpleRead *getRead(int i) {
    return readTokens.at(i);
  }

  SimplePrint *getPrint(int i) {
    return printTokens.at(i);
  }
  void addPrint(SimplePrint *token) {
    int lineNo = token->getLineNo();
    printTokens.insert({lineNo, token});
  }

  void addConstant(SimpleConstant *token) {
    std::string name = token->getName();
    constantTokens.insert({name, token});
  }

  InterfaceSimpleFactor *getFactor(const std::string &factor) {
    char firstChar = factor.at(0);
    if (isdigit(firstChar)) {
      return constantTokens.at(factor);
    } else {
      return variableTokens.at(factor);
    }
  }
  void addAssign(SimpleAssign *token) {
    int lineNo = token->getLineNo();
    assignTokens.insert({lineNo, token});
  }
  SimpleAssign *getAssign(int lineNo) {
    return assignTokens.at(lineNo);
  }
  unsigned long countProcedure() {
    return procedureTokens.size();
  }
  unsigned long countAssign() {
    return assignTokens.size();
  }
  unsigned long countVariable() {
    return variableTokens.size();
  }

  unsigned long countConstant() {
    return constantTokens.size();
  }

  unsigned long countRead() {
    return readTokens.size();
  }
  unsigned long countPrint() {
    return printTokens.size();
  }
};
