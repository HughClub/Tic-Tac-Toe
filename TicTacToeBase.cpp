#include "TicTacToeBase.h"

#include <algorithm>

#include "Tools.hpp"


bool TicTacToeBase::finished(vec const &x, vec const &o) { return x.size() + o.size() == 9; }

int TicTacToeBase::eval(vec &x, vec &o) {
    if (win(x)) {
        return WIN;
    }
    if (win(o)) {
        return -WIN;
    }
    return 0;
}

TicTacToeBase::Winner TicTacToeBase::eval() {
    switch (eval(X, O)) {
        case WIN:
            return winner = Winner::X;
        case -WIN:
            return winner = Winner::O;
        default:
            return winner = Winner::Draw;
    }
}
int TicTacToeBase::findBest(bool maximize) {
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

const vec &TicTacToeBase::board() {return Board;}
TicTacToeBase::Winner TicTacToeBase::getLastWinner() const noexcept {
  return winner;
}

bool TicTacToeBase::win(vec &player) noexcept {
    if (player.size() < 3)
        return false;
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

int TicTacToeBase::minmax(vec x, vec o, int depth, bool maximize) {
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
void TicTacToeBase::clear() {Board.clear();}