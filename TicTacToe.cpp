//#define debug 1
#pragma once

#include <graphics.h>

#include <algorithm>
#include <cstdarg>
#include <iostream>
#include <conio.h>

#include "TicTacToe.h"
#include "Tools.hpp"
#include "T3module.h"

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
      // deprecated
      return 0;
  }
}

int TicTacToe::getSelfNext() {
  static Rect screen(0, 0, getwidth(), getheight());
  int pos;
  do {
    ExMessage msg = getmessage(EM_MOUSE|EM_KEY);
      if (msg.message == WM_KEYUP) {
      }
      while ((msg.message != WM_LBUTTONUP && msg.message != WM_RBUTTONUP) ||
             msg.message == WM_KEYUP) {
        msg = getmessage(EM_MOUSE|EM_KEY);
      }
    switch (msg.message) {
        case WM_KEYUP:
        if (msg.vkcode==VK_ESCAPE) throw "";
        else if (msg.vkcode=='5') throw 0;
    }
      pos = screen.block(Point{msg.x,msg.y}, 3, 3);
  } while (!MoveCheck(pos+1));
    return pos+1;
}

void TicTacToe::DrawGameBoard() {
  int height = getheight(), width = getwidth();
  int hdis = height / 3, wdis = width / 3;
  //BeginBatchDraw();
  // horizonal lines
  line(0, hdis, width, hdis);
  line(0, hdis*2, width, hdis*2);
  // vertical lines
  line(wdis, 0, wdis, height);
  line(wdis * 2, 0, wdis * 2, height);
  //EndBatchDraw();
}

TicTacToe::Winner TicTacToe::play() {
  static Rect screen(0, 0, getwidth(), getheight());
  bool start = true;
  Winner rel = Winner::NotYet;
    #pragma region old
  //  do {
  //    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) throw std::runtime_error("exit");
  //    if (GetAsyncKeyState('5') & 0x8000) return Winner::NotYet;
  //    DrawGameBoard();
  //    int pos = getSelfNext();
  //    printf("self : %d\n",pos);
  //    Point center = screen.getRegion(pos).RegionCenterPoint();
  //    DrawCross(center.x,center.y);
  //    rel=Step(pos,start);
  //    printf("oppo : %d\n", lastOppo);
  //    center = screen.getRegion(lastOppo).RegionCenterPoint();
  //    DrawCircle(center.x,center.y);
  //    if (start) start = false;
  //  }
  //  while (rel==Winner::NotYet);
  //  return rel; 
    #pragma endregion
  //clear();
  int pos;
  DrawGameBoard();
  do {
    // get self input [1,9]
    pos = getSelfNext();

    Board[pos-1] = 'X';
    X.push_back(MAGIC_SQUARE[pos-1]);
    Point center = screen.getRegion(pos-1).RegionCenterPoint();
    DrawCross(center.x,center.y);
    // get match next
    printf("X:%d ",pos);
    pos = getMatchNext(); // magic number in [1,9]
    if (pos != 0) {
      int midx = M2Idx[pos - 1];
      printf("O:%d\n", midx);
      lastOppo = midx;
      Board[midx] = 'O';
      O.push_back(pos); // directly store the value
      center = screen.getRegion(midx).RegionCenterPoint();
      DrawCircle(center.x, center.y);
    }
  } while (!(win(X) || win(O) || finished(X, O)));
  switch (eval(X, O)) {
    case WIN:
      return winner = Winner::X;
    case -WIN:
      return winner = Winner::O;
    default:
      return winner = Winner::Draw;
  }
}

bool TicTacToe::MoveCheck(int position) const noexcept { 
    int magic = MAGIC_SQUARE[position - 1];
  return !((!(position > 0 && position < 10)) || (In(magic, X) && In(magic, O))); 
}

int TicTacToe::getLastOpponentsMove() const noexcept { return lastOppo; }

TicTacToe::TicTacToe() : lastOppo(-1) {}

TicTacToe::Winner TicTacToe::Step(int position,bool start) {
    if (start) { clear(); }
    Winner w = eval();
    if (w != Winner::NotYet) {
      return w;
    }
    Board[position-1] = 'X';
    X.push_back(MAGIC_SQUARE[position-1]);
    int oppo = getMatchNext(); // [1,9]
    if (oppo != 0) {
        lastOppo = oppo;
        Board[M2Idx[oppo - 1]] = 'O';
        O.push_back(oppo);
    }
  return eval();
}