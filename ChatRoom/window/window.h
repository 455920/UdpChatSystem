#pragma once 
#include <unistd.h>

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

    void put_string_to_window(WINDOW* win,int y,int x,const std::string &msg);
    
    void refresh_win(WINDOW* win);

     
    void get_string_from_window(WINDOW* win,std::string &msg);
    ~window();
  //private:
    WINDOW *header;
    WINDOW *output;
    WINDOW *flist;
    WINDOW *input;
};
