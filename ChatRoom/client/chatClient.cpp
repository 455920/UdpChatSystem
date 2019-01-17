#include "udp_client.h"
#include "window.h"

using namespace std;

//定义一个结构体方便线程使用
typedef struct 
{
   udp_client *clientp;
   window* winp;
}client_t;
client_t cw; 

void* run_header(void *arg)
{
  client_t* cw = (client_t*)arg;
  window* w = cw->winp;
}

void* run_output(void *arg)
{
  client_t* cw = (client_t*)arg;
  window* w = cw->winp;

}

void* run_input(void *arg)
{
  client_t* cw = (client_t*)arg;
  window* w = cw->winp;

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
  udp_client cli(argv[1],atoi(argv[2]));
  window w;
  cli.init_client();
  cw.clientp=&cli;
  cw.winp=&w;
  std::string message;

 pthread_t header,output,flist,input;
 pthread_create(&header,NULL,run_header,(void*)&cw);//传参比较合理
 pthread_create(&input,NULL,run_input,(void*)&cw);
 pthread_create(&output,NULL,run_output,(void*)&cw);
 
 pthread_join(header,NULL);
 pthread_join(input,NULL);
 pthread_join(output,NULL);

  return 0;
}
