//
// Created by Noel Lim on 2/2/22.
//

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "source_processor/Simple/composites/TokenSimpleProcedure.hpp"
#include "source_processor/Simple/composites/TokenSimpleAssignment.hpp"
#include "source_processor/Simple/composites/SimpleVariable.hpp"
#include "source_processor/Simple/composites/TokenSimpleConstant.hpp"
#include "source_processor/Simple/composites/TokenSimpleRead.hpp"
#include "source_processor/Simple/composites/TokenSimplePrint.hpp"

class TokenSimpleBag {
private:
  std::vector<TokenSimpleProcedure *> procedureTokens;
  std::map<int, TokenSimpleAssignment *> assignTokens;
  std::map<std::string, SimpleVariable *> variableTokens;
  std::map<std::string, TokenSimpleConstant *> constantTokens;
  std::map<int, TokenSimpleRead *> readTokens;
  std::map<int, TokenSimplePrint *> printTokens;
public:
  void addProcedure(TokenSimpleProcedure *token) {
    procedureTokens.push_back(token);
  }
  TokenSimpleProcedure *getProcedure(int i) {
    return procedureTokens.at(i);
  }
  void addVariable(SimpleVariable *token) {
    std::string var_name = token->getName();
    variableTokens.insert({var_name, token});
  }

  SimpleVariable *getVariable(const std::string &var_name) {
    return variableTokens.at(var_name);
  }

  void addRead(TokenSimpleRead *token) {
    int lineNo = token->getLineNo();
    readTokens.insert({lineNo, token});
  }
  TokenSimpleRead *getRead(int i) {
    return readTokens.at(i);
  }

  TokenSimplePrint *getPrint(int i) {
    return printTokens.at(i);
  }
  void addPrint(TokenSimplePrint *token) {
    int lineNo = token->getLineNo();
    printTokens.insert({lineNo, token});
  }

  void addConstant(TokenSimpleConstant *token) {
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
  void addAssign(TokenSimpleAssignment *token) {
    int lineNo = token->getLineNo();
    assignTokens.insert({lineNo, token});
  }
  TokenSimpleAssignment *getAssign(int lineNo) {
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
