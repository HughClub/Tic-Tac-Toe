#ifndef T3Base
#define T3Base
constexpr int MAGIC_SQUARE[9] = {4, 9, 2, 3, 5, 7, 8, 1, 6};
constexpr int M2Idx[9] = {7, 2, 3, 0, 4, 8, 5, 6, 1};  // Magic to Index
#endif//T3Base
#ifndef __TIC_TAC_TOE__
#define __TIC_TAC_TOE__ 1
#include <vector>
class TicTacToe {
 public:
  enum class Winner : int { X, O, Draw, NotYet };
  enum class Match : bool { Computer, Network };
  const static int INF = 1000;
  const static int WIN = 10;
  using vec = std::vector<int>;
  bool finished(vec const &, vec const &);
  /**
   * @brief 评估当前局势
   */
  int eval(vec &, vec &);
  Winner eval();
  /**
   * @brief find best move
   * @param maximize
   * true:find best for X
   * false:find best for O
   * @return move:range(1,10)
   */
  int findBest(bool maximize);
  /**
   * @brief get current board
   */
  const int* board();
  Winner getLastWinner() const noexcept;
  int getLastOpponentsMove() const noexcept;
  TicTacToe(Match m = Match::Computer);
  Match switchMatch(Match m);
  Winner Step(int,bool start=false);

 private:
  constexpr static int PollingGapMS = 10;
  vec X, O;  // store magic numbers
  int Board[9];
  Winner winner;
  Match matcher;
  int lastOppo;
  bool win(vec &);
  /**
   * @brief calc the score of
   * @param depth the depth of current level
   * @param maximize whether makes the score higher or not
   * decide which player is searching also
   */
  int minmax(vec x, vec o, int depth, bool maximize);
  void clear();
  int getMatchNext();
};
#endif  //__TIC_TAC_TOE__
