//#define debug 1
#pragma once
#include "TicTacToe.h"
#include "Tools.hpp"
#include <algorithm>
#include <cstdarg>
#include <iostream>

int printf_d(const char* fmt, ...) {
#ifdef debug
  int _Result;
  va_list _ArgList;
  va_start(_ArgList, fmt);
  _Result = vfprintf(stdout, fmt, _ArgList);
  va_end(_ArgList);
  return _Result;
#else
  return 0;
#endif
}

bool TicTacToe::win(vec& player) {
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
bool TicTacToe::finished(vec const& x, vec const& o) {
  return x.size() + o.size() == 9;
}

int TicTacToe::eval(vec& x, vec& o) {
  if (win(x)) {
    return WIN;
  }
  if (win(o)) {
    return -WIN;
  }
  return 0;
}
TicTacToe::Winner TicTacToe::eval() {
  switch (eval(X, O)) {
    case WIN:
      return winner = Winner::X;
    case -WIN:
      return winner = Winner::O;
    default:
      return winner = Winner::Draw;
  }
}

int TicTacToe::minmax(vec x, vec o, int depth, bool maximize) {
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
    if (NotIn(i, x) && NotIn(i, o)) {
      if (maximize) {
        best = std::max(best, minmax(i + x, o, depth + 1, !maximize));
      } else {
        best = std::min(best, minmax(x, i + o, depth + 1, !maximize));
      }
    }
  }
  return best;
}

int TicTacToe::findBest(bool maximize) {
  int best = maximize ? -INF : INF;
  int move = 0, val;
  for (int i : MAGIC_SQUARE) {
    if (NotIn(i, X) && NotIn(i, O)) {
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
/**
 * @brief show current board
 */
const int* TicTacToe::board() { return Board; }

void TicTacToe::clear() {
  memset(Board, ' ', sizeof(Board));
  lastOppo = -1;
  X.clear();
  O.clear();
  winner = Winner::NotYet;
}
TicTacToe::Winner TicTacToe::getLastWinner() const noexcept { return winner; }
TicTacToe::TicTacToe(Match m)
    : matcher(m), winner(Winner::NotYet){
  memset(Board, ' ', sizeof(Board));
}
TicTacToe::Match TicTacToe::switchMatch(Match m) {
  Match prev = matcher;
  matcher = m;
  return prev;
}
int TicTacToe::getMatchNext() {
  switch (matcher) {
    case Match::Computer:
      return findBest(false);
    case Match::Network:
      // todo network com
      return 0;
  }
}

int TicTacToe::getLastOpponentsMove() const noexcept { return lastOppo; }

TicTacToe::Winner TicTacToe::Step(int position,bool start) {
  if (start) { clear(); }
  Winner w = eval();
  if (w != Winner::NotYet) {
    return w;
  }
  int magic=MAGIC_SQUARE[position - 1];
  if ((!(position > 0 && position < 10)) ||
      (In(magic, X)&&In(magic,O))) {
    throw std::runtime_error("invalid move");
  } else {
    Board[position - 1] = 'X';
    X.push_back(MAGIC_SQUARE[position - 1]);
    int oppo = getMatchNext();
    if (oppo != 0) {
      lastOppo = oppo;
      Board[M2Idx[oppo - 1]] = 'O';
      O.push_back(oppo);
    }
  }return eval();
}