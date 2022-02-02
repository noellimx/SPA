//
// Created by Noel Lim on 1/2/22.
//

#pragma once


class TokenVariable;
class InterfacePrinter {
  TokenVariable * printableVar;
public:
  InterfacePrinter() = default;

  explicit InterfacePrinter(TokenVariable * );

  TokenVariable * prints();
};

