//
// Created by Noel Lim on 1/2/22.
//

#pragma once


class SimpleVariable;
class InterfaceSimpleReader {
  SimpleVariable * readableVar;
public:
  InterfaceSimpleReader() = default;

  explicit InterfaceSimpleReader(SimpleVariable * );

  SimpleVariable * reads();
};

