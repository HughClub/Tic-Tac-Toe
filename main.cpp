#include <graphics.h>

#include <iostream>
#include <string>

#include "T3module.h"
#include "TicTacToe.h"
#include "ConsoleTicTacToe.h"
void PutAlphaImage(int img_x, int img_y, IMAGE* pSrcImg);
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
void PutAlphaImage(int img_x, int img_y, IMAGE* pSrcImg) {
  DWORD* dst = GetImageBuffer();
  DWORD* src = GetImageBuffer(pSrcImg);
  int src_width = pSrcImg->getwidth();
  int src_height = pSrcImg->getheight();
  int dst_width = getwidth();
  int dst_height = getheight();

  int im_width, im_height;
  if (img_x + src_width > dst_width)
    im_width = dst_width - img_x;
  else
    im_width = src_width;
  if (img_y + src_height > dst_height)
    im_height = dst_height - img_y;
  else
    im_height = src_height;

  if (img_x < 0) {
    src = src - img_x;
    im_width = im_width + img_x;
    img_x = 0;
  }
  if (img_y < 0) {
    src = src - src_width * img_y;
    im_height = im_height + img_y;
    img_y = 0;
  }
  dst = dst + dst_width * img_y + img_x;

  for (int i = 0; i < im_height; i++) {
    for (int j = 0; j < im_width; j++) {
      int src_r = ((src[j] & 0xff0000) >> 16);
      int src_g = ((src[j] & 0xff00) >> 8);
      int src_b = src[j] & 0xff;
      int src_a = ((src[j] & 0xff000000) >> 24);
      int dst_r = ((dst[j] & 0xff0000) >> 16);
      int dst_g = ((dst[j] & 0xff00) >> 8);
      int dst_b = dst[j] & 0xff;
      dst[j] = ((src_r + dst_r * (255 - src_a) / 255) << 16) |
               ((src_g + dst_g * (255 - src_a) / 255) << 8) |
               (src_b + dst_b * (255 - src_a) / 255);
    }
    dst = dst + dst_width;
    src = src + src_width;
  }
}