#pragma once 

#include <iostream>
#include <ncurses.h>

class window 
{
  public:
    window();
    //画头部窗口
    void draw_header();
    //画输出窗口
    void draw_output();
    //画朋友列表窗口
    void draw_flist();
    //画输入窗口
    void draw_input();
    ~window();
  private:
    WINDOW *header;
    WINDOW *output;
    WINDOW *flist;
    WINDOW *input;
};
