#include "window.h"

window::window()
{
 initscr();
}

void window::put_string_to_window(WINDOW* win,int y,int x,const std::string &msg)
{
  mvwaddstr(win,y,x,msg.c_str()); 
}

void window::get_string_from_window(WINDOW* win,std::string &msg)
{
  char buf[1024]={0};
   wgetnstr(win,buf,sizeof(buf)); 
   msg = buf;
}


//刷新窗口
void window::refresh_win(WINDOW* win)
{
  wrefresh(win);
}

void window::draw_header()
{
  int  y =0;
  int  x =0;
  int  h =LINES/5;
  int w = COLS;
  header = newwin(h,w,y,x);
  //对header画出边框
  box(header,'*','.');//0 0 是改变窗口风格
}

void window::draw_output()
{
  int  y =LINES/5;
  int  x =0;
  int  h =LINES*3/5;
  int w = COLS*3/4;
  output = newwin(h,w,y,x);
  box(output,'*','.');//0 0 是改变窗口风格

}
void window::draw_flist()
{
  int  y =LINES/5;
  int  x =COLS*3/4;
  int  h =LINES*3/5;
  int w = COLS/4;
  flist = newwin(h,w,y,x);
  box(flist,'*','.');//0 0 是改变窗口风格
}
void window::draw_input()
{
  int  y =LINES*4/5;
  int  x =0;
  int  h =LINES/5;
  int w = COLS;
  input = newwin(h,w,y,x);
  box(input,'^','.');//0 0 是改变窗口风格
}
window::~window()
{
  delwin(header);
  delwin(output);
  delwin(flist);
  delwin(input);
  endwin();//结束之前画的窗口
}

void* act_1(void *arg);


int main()
{
  window w;
  w.draw_input();
  std::string message ="Please Enter#";
  std::string str;
  int x,y;
  int i=1;
  while(1)
  {
    w.draw_input();
    w.put_string_to_window(w.input,1,2,message);
    w.refresh_win(w.input);
    w.get_string_from_window(w.input,str);
  }
}



//  window w;
//  w.draw_output();
//  w.refresh_win(w.output);
//  int x,y;
//  int i=1;
//  std::string message = "for test ...";
//  while(1)
//  {
//    getmaxyx(w.output,y,x);
//    w.put_string_to_window(w.output,i++,2,message);
//    w.refresh_win(w.output);
//    if(i>= y-1)
//    {
//      i=1;
//      w.draw_output();
//    }
//    usleep(100000);
//  }
//  return 0;

void* act_1(void *arg)
{
  window w;
  w.draw_header();

  std::string title = "Welcome To My Chat System";
  int x,y;
  int i=1;
  int dir=0;//方向标志位
  w.refresh_win(w.header);
  while(1)
  {
    w.draw_header();
    //得到窗口的坐标
    getmaxyx(w.header,y,x);
    w.put_string_to_window(w.header,y/2,i,title);
    w.refresh_win(w.header);
   
   if(i>=x- title.size()-1)
   {
     dir =1;
   }

    if(i<1) //改变方向
    {
      dir=0;
    }

    if(dir)
    {
      i--;
    }
    else 
    {
      i++;
    }

    usleep(100000);

  }
}
