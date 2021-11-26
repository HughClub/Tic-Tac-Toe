#pragma once
#include<vector>

class ConsoleTicTacToe {
 public:
  enum class Winner : int { X, O, Draw, NotYet };
  const static int INF = 1000;
  const static int WIN = 10;
  using vec = std::vector<int>;
  Winner play();
  bool finished(vec const &, vec const &);
  /**
   * @brief ������ǰ����
   */
  int eval(vec &, vec &);
  /**
   * @brief find best position for next
   */
  int findBest(bool maximize);
  /**
   * @brief show current board
   */
  void board();
  Winner getLastWinner() const noexcept;


 private:
  constexpr static int PollingGapMS = 10;
  vec X, O;  // store magic numbers
  int Board[9];
  Winner winner;
  bool win(vec &);
  /**
   * @brief calc the score of currnt step
   * @param depth the depth of current level
   * @param maximize whether makes the score higher or not
   * decide which player is searching, too
   */
  int minmax(vec x, vec o, int depth, bool maximize);
  void clear();
  int getMatchNext();
  int getSelfNext();
};
