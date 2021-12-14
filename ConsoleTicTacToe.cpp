#ifndef T3Base
#define T3Base
constexpr int MAGIC_SQUARE[9] = {4, 9, 2, 3, 5, 7, 8, 1, 6};
constexpr int M2Idx[9] = {7, 2, 3, 0, 4, 8, 5, 6, 1};  // Magic to Index
#endif                                                 // T3Base
#pragma once
#include "ConsoleTicTacToe.h"
#include "Tools.hpp"
#include <algorithm>
#include <cstdarg>
#include <iostream>


void ConsoleTicTacToe::showBoard() {
  for (int i = 0; i < 3; ++i) {
    puts("----------");
    for (int j = 0; j < 3; ++j) {
      putchar('|');
      putchar(Board[i * 3 + j]);
      putchar(' ');
    }
    puts("|");
  }
  puts("----------");
}

ConsoleTicTacToe::Winner ConsoleTicTacToe::play() {
  //clear();
  int pos;
  do {
    showBoard();
    // get self input [1,9]
    pos = getSelfNext();

    Board[pos - 1] = 'X';
    X.push_back(MAGIC_SQUARE[pos - 1]);

    // get match next [1,9]
    pos = getMatchNext();
    if (pos != 0) {
      Board[M2Idx[pos - 1]] = 'O';
      O.push_back(pos);
    }
  } while (!(win(X) || win(O) || finished(X, O)));
  board();
  switch (eval(X, O)) {
    case WIN:
      return winner = Winner::X;
    case -WIN:
      return winner = Winner::O;
    default:
      return winner = Winner::Draw;
  }
}
int ConsoleTicTacToe::getMatchNext() { return findBest(false); }
int ConsoleTicTacToe::getSelfNext() {
  int pos;
  bool first = true;
  do {
    if (!first) puts("Invalid Move");
    first = false;
    std::cout << "[1..9]=> ";
    std::cin >> pos;
  } while ((!(pos > 0 && pos < 10)) || In(MAGIC_SQUARE[pos - 1], {X, O}));
  return pos;
}