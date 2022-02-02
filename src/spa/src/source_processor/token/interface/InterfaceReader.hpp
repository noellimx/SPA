//
// Created by Noel Lim on 1/2/22.
//

#pragma once


class TokenVariable;
class InterfaceReader {
  TokenVariable * readableVar;
public:
  InterfaceReader() = default;

  explicit InterfaceReader(TokenVariable * );

  TokenVariable * reads();
};

