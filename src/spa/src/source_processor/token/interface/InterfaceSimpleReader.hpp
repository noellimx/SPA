//
// Created by Noel Lim on 1/2/22.
//

#pragma once


class TokenSimpleVariable;
class InterfaceSimpleReader {
  TokenSimpleVariable * readableVar;
public:
  InterfaceSimpleReader() = default;

  explicit InterfaceSimpleReader(TokenSimpleVariable * );

  TokenSimpleVariable * reads();
};

