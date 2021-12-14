#include <graphics.h>

#include "T3module.h"
constexpr static double Sqrt3 = 1.732;
bool In(Point const& p, Rect const& region) {
    return (p.x >= region.origin.x && p.x < region.origin.x + region.width) &&
            (p.y >= region.origin.y && p.y < region.origin.y + region.height);
}

bool Point::In() const noexcept { return x >= 0 && y >= 0; }
bool Point::In(Rect const& region) const noexcept {
    return ::In(*this, region);
}

Rect::Rect(int x, int y, int wid, int heig)
    : origin{x, y}, width(wid), height(heig) {}
int Rect::block(Point const& p, int wb, int hb) {
    if (p.In(*this)) {
    int x = p.x - origin.x, y = p.y - origin.y;
    int xblk = width / wb, yblk = height / hb;
    if (x % xblk == 0 || y % yblk == 0) {
        return -1;
    } else {
        return y / yblk * wb + x / xblk;
    }
    } else
    return -2;
}
Point Rect::RegionCenterPoint() const noexcept {
    return Point{origin.x + width / 2, origin.y + height / 2};
}

Rect const& Rect::getRegion(int num, int hdiv, int vdiv) const noexcept {
  int h = num % hdiv, v = num / hdiv;
  int width = this->width / hdiv, height = this->height / vdiv;
  int ox = origin.x + width * h, oy = origin.y + height*v;
  return Rect(ox, oy, width, height);
}

Point Rect::RegionCenterPoint(Rect const&r) noexcept { return r.RegionCenterPoint(); }

Square::Square(int x, int y, int width) : Rect{x, y, width, width} {}
int Square::block(Point const& p, int blk) { return Rect::block(p, blk, blk); }

void DrawCross(int x, int y, double len ) {
    constexpr static unsigned long DColor = 0x34409D;
    setlinecolor(DColor);
    double Xdelta = len / 4, Ydelta = len / 4 * Sqrt3;
    line(x + Xdelta, y - Ydelta, x - Xdelta,
        y + Ydelta);  // draw slash
    line(x + Xdelta, y + Ydelta, x - Xdelta,
        y - Ydelta);  // draw backslash
}
void DrawCircle(int x, int y, double len) { 
    constexpr static unsigned long DColor = 0x39AC3B;
    setlinecolor(DColor);
    circle(x, y, len); 
}
int inTicTacToeRegion(Point cursor, Rect T3, int xblock, int yblock) {
    return T3.block(cursor, xblock, yblock);
}
int inTicTacToeRegion(Point cursor, Rect T3, int blocks) {
    return T3.block(cursor, blocks, blocks);
}