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
class Simple {
private:
  std::vector<SimpleProcedure *> *procedures = new std::vector<SimpleProcedure *>();
  std::map<int, SimpleAssign *> *assigns = new std::map<int, SimpleAssign *>();
  std::map<std::string, SimpleVariable *> *variables = new std::map<std::string, SimpleVariable *>();
  std::map<std::string, SimpleConstant *> *constants = new std::map<std::string, SimpleConstant *>();
  std::map<int, SimpleRead *> *reads = new std::map<int, SimpleRead *>;
  std::map<int, SimplePrint *> *prints = new std::map<int, SimplePrint *>;
public:

  void addProcedure(SimpleProcedure *sP) {
    procedures->push_back(sP);
  }

  std::vector<SimpleProcedure *> *getProcedures() {
    return procedures;
  }

  std::map<int, SimpleAssign *> *getAssigns() {
    return assigns;
  }

  SimpleProcedure *getProcedure(int i) {
    return procedures->at(i);
  }
  void addVariable(SimpleVariable *sV) {
    std::string var_name = sV->getName();
    variables->insert({var_name, sV});
  }
  SimpleVariable *getVariable(const std::string &var_name) {
    return variables->at(var_name);
  }
  void addRead(SimpleRead *sR) {
    int lineNo = sR->getLineNo();
    reads->insert({lineNo, sR});
  }

  SimpleRead *getRead(int i) {
    return reads->at(i);
  }

  std::map<int, SimpleRead *> *getReads() {
    return reads;
  }

  std::map<std::string, SimpleConstant *> *getConstants() {
    return constants;
  }

  std::map<std::string, SimpleVariable *> *getVariables() {
    return variables;
  }

  void addConstant(SimpleConstant *sC) {
    std::string name = sC->getName();
    constants->insert({name, sC});
  }

  void addPrint(SimplePrint *sP) {
    int lineNo = sP->getLineNo();
    prints->insert({lineNo, sP});
  }
  SimplePrint *getPrint(int i) {
    return prints->at(i);
  }
  std::map<int, SimplePrint *> *getPrints() {
    return prints;
  }

  InterfaceSimpleFactor *getFactor(const std::string &factor) {
    char firstChar = factor.at(0);
    if (isdigit(firstChar)) {
      return constants->at(factor);
    } else {
      return variables->at(factor);
    }
  }
  void addAssign(SimpleAssign *sA) {
    int lineNo = sA->getLineNo();
    assigns->insert({lineNo, sA});
  }
  SimpleAssign *getAssign(int lineNo) {
    return assigns->at(lineNo);
  }
  unsigned long countProcedure() {
    return procedures->size();
  }
  unsigned long countAssign() {
    return assigns->size();
  }
  unsigned long countVariable() {
    return variables->size();
  }

  unsigned long countConstant() {
    return constants->size();
  }

  unsigned long countRead() {
    return reads->size();
  }
  unsigned long countPrint() {
    return prints->size();
  }
};
