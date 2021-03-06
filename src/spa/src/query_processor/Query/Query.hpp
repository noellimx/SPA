//
// Created by Noel Lim on 3/2/22.
//


#pragma once

#include <string>
#include <map>
#include <vector>
#include "query_processor/Query/composites/Declaration.hpp"
class Query {
  std::map<std::string, Declaration *> declarations;

  std::vector<Declaration *> result_cl;
public:
  Query() = default;
  ~Query() = default;

  void addDeclaration(Declaration *d) {
    declarations.insert({d->getSynonym(), d});
  }

  unsigned long countDeclarations() {
    return declarations.size();
  }

  Declaration *getDeclaration( std::string syn) {
    try{
      return declarations.at(syn);

    }catch(...){

      throw "[getDeclaration] Declaration not found";
    }
  }

  void addSynonymToResultCl(const std::string &syn) {
    auto *dec = getDeclaration(syn); // sanity check that synonym is found in declaration
    result_cl.push_back(dec);
  }

  unsigned long countSynonymsInTuple() {
    return result_cl.size();
  }

  std::string getEntityOf(std::string synonym) {
    return declarations.at(synonym)->getType();
  }

  std::string getEntityOfResultCl(int i){
    return result_cl.at(i)->getType();
  }
};

