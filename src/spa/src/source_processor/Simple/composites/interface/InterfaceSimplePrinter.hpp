//
// Created by Noel Lim on 1/2/22.
//

#pragma once


class SimpleVariable;
class InterfaceSimplePrinter {
  SimpleVariable * printableVar;
public:
  InterfaceSimplePrinter() = default;

  explicit InterfaceSimplePrinter(SimpleVariable * );

  SimpleVariable * prints();
};

