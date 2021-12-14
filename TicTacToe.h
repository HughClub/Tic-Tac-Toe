#ifndef __TIC_TAC_TOE__
#define __TIC_TAC_TOE__ 1
#include "TicTacToeBase.h"
class TicTacToe:public TicTacToeBase {
 public:
  int getLastOpponentsMove() const noexcept;
  TicTacToe();
  Match switchMatch(Match m);
  /**
   * @brief assume input in [1,9]
  */
  [[DEPRECATED]]Winner Step(int,bool start=false);
  int getMatchNext();
  /**
   *  @return  position in range[1,9]
  */ 
  int getSelfNext();
  static void DrawGameBoard();
  Winner play();
 private:
  int lastOppo; // [1,9]
  /**
   * @param position : [1,9]
  */
  bool MoveCheck(int position) const noexcept;
};
#endif  //__TIC_TAC_TOE__
