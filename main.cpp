#include <graphics.h>

#include <iostream>
#include <string>

#include "T3module.h"
#include "TicTacToe.h"
#include "ConsoleTicTacToe.h"
void Console() {
  ConsoleTicTacToe CT;
  CT.play();
}
void UI() {
  initgraph(480, 480);
  TicTacToe T3;
  T3.play();
  switch (T3.getLastWinner()) {
    case TicTacToeBase::Winner::Draw:
      puts("draw");
      break;
    case TicTacToeBase::Winner::X:
      puts("X");
      break;
    case TicTacToeBase::Winner::O:
      puts("O");
      break;
  }
  closegraph();
}
void UI_test() {
  initgraph(480, 480);
  Rect i0(0, 0, getwidth(), getheight());
  for (int i = 0; i < 9; ++i) {
    i0 = Rect(0, 0, getwidth(), getheight()).getRegion(i);
    Point p = i0.RegionCenterPoint();
    printf("region:%d,x:%d,y:%d\n",i,p.x,p.y);
  }
  closegraph();
}

int main() {
  //test();
  //std::vector<int> vi(9, ' ');
  //std::cout << vi.size() << std::endl;
  UI();
  //UI_test();
  return 0;
}