#pragma once
#include "ConsoleTicTacToe.h"
#include "Tools.hpp"
#include <algorithm>
#include <cstdarg>
#include <iostream>

bool ConsoleTicTacToe::win(vec& player) {
  if (player.size() < 3) return false;
  std::sort(player.begin(), player.end());
  vec::const_iterator lhs, rhs, cur = player.begin();
  int sum = 0;
  for (unsigned i = 0; i < player.size() - 2; ++i) {
    lhs = cur + 1;
    rhs = player.end() - 1;
    while (lhs < rhs) {
      sum = *cur + *lhs + *rhs;
      if (sum == 15) {
        return true;
      } else if (sum < 15) {
        ++lhs;
      } else {
        --rhs;
      }
    }
    ++cur;
  }
  return false;
}
bool ConsoleTicTacToe::finished(vec const& x, vec const& o) {
  return x.size() + o.size() == 9;
}

int ConsoleTicTacToe::eval(vec& x, vec& o) {
  if (win(x)) {
    return WIN;
  }
  if (win(o)) {
    return -WIN;
  }
  return 0;
}

int ConsoleTicTacToe::minmax(vec x, vec o, int depth, bool maximize) {
  int score = eval(x, o);
  if (score == WIN) {
    return score - depth;
  } else if (score == -WIN) {
    return score + depth;
  }
  if (finished(x, o)) {
    return 0;
  }
  int best = maximize ? -INF : INF;
  for (int i : MAGIC_SQUARE) {
    if (NotIn(i, {x, o})) {
      if (maximize) {
        best = std::max(best, minmax(i + x, o, depth + 1, !maximize));
      } else {
        best = std::min(best, minmax(x, i + o, depth + 1, !maximize));
      }
    }
  }
  return best;
}

int ConsoleTicTacToe::findBest(bool maximize) {
  int best = maximize ? -INF : INF;
  int move = 0, val;
  for (int i : MAGIC_SQUARE) {
    if (NotIn(i, {X, O})) {
      if (maximize) {
        val = minmax(i + X, O, 0, !maximize);
        if (val > best) {
          best = val;
          move = i;
        }
      } else {
        val = minmax(X, i + O, 0, !maximize);
        if (val < best) {
          best = val;
          move = i;
        }
      }
    }
  }
  return move;
}

void ConsoleTicTacToe::board() {
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
  clear();
  int pos;
  do {
    board();
    // get self input
    pos = getSelfNext();

    Board[pos - 1] = 'X';
    X.push_back(MAGIC_SQUARE[pos - 1]);

    // get match next
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
void ConsoleTicTacToe::clear() {
  memset(Board, ' ', sizeof(Board));
  X.clear();
  O.clear();
  winner = Winner::NotYet;
}
ConsoleTicTacToe::Winner ConsoleTicTacToe::getLastWinner() const noexcept {
  return winner;
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