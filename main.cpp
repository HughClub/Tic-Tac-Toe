#include <graphics.h>

#include <iostream>
#include <string>

#include "T3module.h"
#include "TicTacToe.h"
#include "ConsoleTicTacToe.h"
void PutAlphaImage(int img_x, int img_y, IMAGE* pSrcImg);
void test() {
  ConsoleTicTacToe CT;
  CT.play();
}
void UI() {
  initgraph(261, 261);
  IMAGE bg,ImgX,ImgO;
  loadimage(&bg, _T("res/BoardBg.png"));
  putimage(0, 0, &bg);
  loadimage(&ImgX, _T("res/X.png"));
  loadimage(&ImgO, _T("res/O.png"));
  TicTacToe T3;
  bool NotEnd = true, start = true;
  ExMessage m;  // 定义消息变量
  setlinecolor(BLACK);
  Game::Rect rect{0, 0, 261, 261};
  int pos;  // the area you click
  int Xblk = 3, Yblk = 3;
  int Xdelta = getwidth() / Xblk, Ydelta = getheight() / Yblk;
  while (NotEnd) {
    // 获取一条鼠标或按键消息
    m = getmessage(EM_MOUSE | EM_KEY);

    switch (m.message) {
      case WM_LBUTTONDOWN:
        // printf("(%d,%d) in %d\n", m.x, m.y, rect.block({m.x, m.y}, 3, 3));
        // outtextxy(15, 15, _T('0' + rect.block({m.x, m.y}, 3, 3)));
        pos = rect.block({m.x, m.y}, 3, 3);
        try {
            NotEnd = T3.Step(pos, start) == TicTacToe::Winner::NotYet;
            PutAlphaImage(pos%3*Xdelta,pos/3*Ydelta,&ImgX);
            pos=T3.findBest(false);
            PutAlphaImage(pos % 3 * Xdelta, pos / 3 * Ydelta, &ImgO);
            start = false;
        } catch (std::runtime_error const&) {
            // 音效
        }
        // Game::cross(m.x, m.y, );
        // circle();
        break;

      case WM_KEYDOWN:
        if (m.vkcode == VK_ESCAPE) return ;  // 按 ESC 键退出程序
    }
  }
  closegraph();
}
int main() {
  //test();
  UI();
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