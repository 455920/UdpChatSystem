#include "udp_client.h"
#include <signal.h>
#include "window.h"
#include "data.h"

using namespace std;


bool flag_quit=0;

std::vector<std::string> friends;

static void add_user(std::string &f)
{
  std::vector<std::string>::iterator iter = friends.begin();
  for(;iter!=friends.end();iter++)
  {
    if(f==*iter)
    {
      return;
    }
  }
  friends.push_back(f);
}



//定义一个结构体方便线程使用
typedef struct 
{
   udp_client *clientp;
   window* winp;
   std::string nick_name;
   std::string school;
}client_t;
client_t cw; 

void send_quit(int sig)
{
  data d;
  d.nick_name = cw.nick_name;
  d.school = cw.school;
  d.message="quit";
  d.type="quit";
  std::string out_string;
  d.serialize(out_string);
  cw.clientp->send_data(out_string); 
  flag_quit=1;
}


static void del_user(std::string& f)
{
  std::vector<std::string>::iterator iter = friends.begin();
  for(;iter!=friends.end();iter++)
  {
    if(*iter==f)
    {
        friends.erase(iter); 
        return;
    }   
  }
}

void* run_header(void *arg)
{
  client_t* cw = (client_t*)arg;
  window* w = cw->winp;
  w->draw_header();

  std::string title = "Welcome To My Chat System";
  int x,y;
  int i=1;
  int dir=0;//方向标志位
  w->refresh_win(w->header);
  while(1)
  {
    w->draw_header();
    //得到窗口的坐标
    getmaxyx(w->header,y,x);
    w->put_string_to_window(w->header,y/2,i,title);
    w->refresh_win(w->header);
   
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

void* run_output_flist(void *arg)
{
  client_t* cw = (client_t*)arg;
  window* w = cw->winp;
  udp_client *cp =cw->clientp;
  w->draw_output();
  w->draw_flist();
  w->refresh_win(w->flist);
  w->refresh_win(w->output);
  int x,y;
  int i=1;
  data d;//用于序列化的对象
  std::string show_string;
  std::string out_string;
  while(1)
  {
     cp->recv_data(out_string);
     d.unserialize(out_string);//获得的数据反序列化
  
       show_string = d.nick_name;
       show_string +="-";
       show_string +=d.school;
       if(d.type=="quit")
         del_user(show_string);
       else
         add_user(show_string);
    
       show_string +="#";
       show_string +=d.message;
       getmaxyx(w->output,y,x);
       w->put_string_to_window(w->output,i++,2,show_string);
       w->refresh_win(w->output);
       if(i>= y-1)
       {
        i=1;
         w->draw_output();
      }
      

     //每次都重新绘制好友列表
     w->draw_flist();
     int j=0;
     for(;j<friends.size();j++)
     {
       w->put_string_to_window(w->flist,j+1,2,friends[j]); 
     }
     w->refresh_win(w->flist);
  }
}

void* run_input(void *arg)
{
  client_t* cw = (client_t*)arg;
  window* w = cw->winp;
  udp_client* cp=cw->clientp;
  w->draw_input();
  std::string tips ="Please Enter#";
  std::string str;
  std::string out_string;
  data d;
  int x,y;
  int i=1;
  while(1)
  {
    w->put_string_to_window(w->input,1,2,tips);
    w->refresh_win(w->input);
    w->get_string_from_window(w->input,str);
    
    d.nick_name =cw->nick_name;
    d.school = cw->school;
    d.message = str;
    d.type ="None";
    //序列化
    d.serialize(out_string);
    //发送数据
    cp->send_data(out_string);
  
    //重新画窗口
    w->draw_input();
  }
}


void Usage(std::string proc)
{
  std::cout<<proc<<"server_ip server_port"<<std::endl;
}

int main(int argc,char * argv[])
{
  if(argc!=3)
  {
    Usage(argv[0]);
    return 1;
  }

  signal(SIGINT,send_quit);
  
  udp_client cli(argv[1],atoi(argv[2]));
  std::cout<<"Please Enter Your Nick Name>";
  std::cin>>cw.nick_name;
  std::cout<<"Please Enter Your School>";
  std::cin>>cw.school;
  window w;
  cli.init_client();
  cw.clientp=&cli;
  cw.winp=&w;
  std::string message;


  // 


 pthread_t header,output_flist,input;
 pthread_create(&header,NULL,run_header,(void*)&cw);//传参比较合理
 pthread_create(&input,NULL,run_input,(void*)&cw);
 pthread_create(&output_flist,NULL,run_output_flist,(void*)&cw);
 
  while(!flag_quit)
  {
    sleep(1);
  }
  pthread_cancel(header);
  pthread_cancel(output_flist);
  pthread_cancel(input);
  return 0;
}
