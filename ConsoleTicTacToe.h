#pragma once
#include "TicTacToeBase.h"

class ConsoleTicTacToe:public TicTacToeBase {
 public:
  Winner play();

  int getMatchNext();
  int getSelfNext();
  void showBoard();
};
