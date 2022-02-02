//
// Created by Noel Lim on 1/2/22.
//

#pragma once


class TokenSimpleVariable;
class InterfaceSimplePrinter {
  TokenSimpleVariable * printableVar;
public:
  InterfaceSimplePrinter() = default;

  explicit InterfaceSimplePrinter(TokenSimpleVariable * );

  TokenSimpleVariable * prints();
};

