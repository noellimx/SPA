//
// Created by Noel Lim on 3/2/22.
//

#pragma once

#include <string>
class Declaration {
private:
  std::string type; // the design entity this represents
  std::string synonym;
public:
  Declaration() = delete;
  ~Declaration() = default;
  Declaration(std::string, std::string);
  std::string getSynonym(){
    return synonym;
  }

  std::string getType(){
    return type;
  }
};

