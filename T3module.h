#pragma once
#ifndef __TIC_TAC_TOE_MODULE__
#define __TIC_TAC_TOE_MODULE__ 1
/**
 * @brief Draw Cross Line;
 * Two lines span half of the Y-axis angle
 * default as 40
 * @param x : the cross center X value
 * @param y : the cross center Y value
 * @param len : the length of each line
 */
void DrawCross(int x, int y, double len = getheight()/4);
void DrawCircle(int x, int y, double len = getheight() / 6);
struct Rect;
struct Point {
  int x, y;
  bool In() const noexcept;
  bool In(Rect const& region) const noexcept;
};
struct Rect {
  Point origin;
  int width, height;
  Rect(int x, int y, int wid, int h);
  int block(Point const& p, int wb, int hb);
  Point RegionCenterPoint()const noexcept;
  Rect const& getRegion(int num,int hdiv=3, int vdiv=3) const noexcept;
  static Point RegionCenterPoint(Rect const&) noexcept;
};
struct Square : Rect {
  Square(int x, int y, int width);
  int block(Point const& p, int blk);
};
int inTicTacToeRegion(Point cursor, Rect T3, int xblock, int yblock);
int inTicTacToeRegion(Point cursor, Rect T3, int blocks);
#endif  //__TIC_TAC_TOE_MODULE__