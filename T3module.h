#pragma once
#ifndef __TIC_TAC_TOE_MODULE__
#define __TIC_TAC_TOE_MODULE__ 1
namespace Game {
/**
 * @brief Draw Cross Line;
 * Two lines span half of the Y-axis angle
 * default as 40
 * @param x : the cross center X value
 * @param y : the cross center Y value
 * @param len : the length of each line
 */
void cross(int x, int y, double len);
struct Rect;
struct Point {
  int x, y;
  bool In() const noexcept;
  bool In(Rect const& region) const noexcept;
};
struct Rect {
  Point origin;
  int width, height;
  Rect(int x, int y, int wid, int heig);
  int block(Point const& p, int wb, int hb);
};
struct Square : Rect {
  Square(int x, int y, int width);
  int block(Point const& p, int blk);
};
int inTicTacToeRegion(Point cursor, Rect T3, int xblock, int yblock);
int inTicTacToeRegion(Point cursor, Rect T3, int blocks);
}  // namespace Game
#endif  //__TIC_TAC_TOE_MODULE__