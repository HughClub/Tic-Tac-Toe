# Tic-Tac-Toe
 Tic-Tac-Toe(井字棋) with EasyX (C++)



两种实现

-   EasyX点击事件
-   控制台输入

解题思路源自<https://github.com/liuxinyu95/unplugged/blob/master/appendix/answer/ans-zh-cn.tex>



一个VS C++项目，应该只能在Windows上运行。



逻辑目录结构

-   include
    -   T3module.h(对应实现在T3Component.cpp 懒得改名了)
    -   TicTacToeBase.h 虚基类 实现了大部分公有操作，属性全为protected
    -   ConsoleTicTacToe.h
    -   TicTacToe.h
    -   Tools.hpp
-   src
    -   T3Component.cpp
    -   TicTacToeBase.cpp
    -   ConsoleTicTacToe.cpp
    -   TicTacToe.cpp
-   main.cpp



