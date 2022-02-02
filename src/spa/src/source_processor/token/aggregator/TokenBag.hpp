//
// Created by Noel Lim on 2/2/22.
//

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "source_processor/token/TokenProcedure.hpp"
#include "source_processor/token/TokenStatementAssignment.hpp"
#include "source_processor/token/TokenVariable.hpp"
#include "source_processor/token/TokenConstant.hpp"
#include "source_processor/token/TokenStatementRead.hpp"
#include "source_processor/token/TokenStatementPrint.hpp"

class TokenBag {
private:
  std::vector<TokenProcedure *> procedureTokens;
  std::map<int, TokenStatementAssignment *> assignTokens;
  std::map<std::string, TokenVariable *> variableTokens;
  std::map<std::string, TokenConstant *> constantTokens;
  std::map<int, TokenStatementRead *> readTokens;
  std::map<int, TokenStatementPrint *> printTokens;
public:
  void addProcedure(TokenProcedure *token) {
    procedureTokens.push_back(token);
  }
  TokenProcedure *getProcedure(int i) {
    return procedureTokens.at(i);
  }
  void addVariable(TokenVariable *token) {
    std::string var_name = token->getName();
    variableTokens.insert({var_name, token});
  }

  TokenVariable *getVariable(const std::string &var_name) {
    return variableTokens.at(var_name);
  }

  void addRead(TokenStatementRead *token) {
    int lineNo = token->getLineNo();
    readTokens.insert({lineNo, token});
  }
  TokenStatementRead *getRead(int i) {
    return readTokens.at(i);
  }

  TokenStatementPrint *getPrint(int i) {
    return printTokens.at(i);
  }
  void addPrint(TokenStatementPrint *token) {
    int lineNo = token->getLineNo();
    printTokens.insert({lineNo, token});
  }

  void addConstant(TokenConstant *token) {
    std::string name = token->getName();
    constantTokens.insert({name, token});
  }

  InterfaceFactor *getFactor(const std::string &factor) {
    char firstChar = factor.at(0);
    if (isdigit(firstChar)) {
      return constantTokens.at(factor);
    } else {
      return variableTokens.at(factor);
    }
  }
  void addAssign(TokenStatementAssignment *token) {
    int lineNo = token->getLineNo();
    assignTokens.insert({lineNo, token});
  }
  TokenStatementAssignment *getAssign(int lineNo) {
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
