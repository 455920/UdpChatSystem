#include <unistd.h>
#include "udp_server.h"
#include <pthread.h>

void Usage(std::string proc)
{
  std::cout<<"Usage:"<<proc<<"port"<<std::endl;
}


void *recv_message(void *arg)
{
  udp_server *sp = (udp_server*)arg;
  std::string message;
  while(1)
  {
    sp->recv_data(message);
    std::cout<<"debug:"<<message<<std::endl;
  }
}

void *send_message(void* arg)
{
  udp_server *sp = (udp_server*)arg;
  while(1)
  {
    sp->broadcast();
    sleep(1);
  }
}

int main(int argc,char *argv[])
{
  if(argc !=2 )
  {
    Usage(argv[0]);
    return 1;
  }

  udp_server ser(atoi(argv[1]));
  ser.init_server();

  //一个线程用来收,一个用来发
  pthread_t  r,s;
  //传入服务器对象
  pthread_create(&r,NULL,recv_message,(void*)&ser);
  pthread_create(&r,NULL,send_message,(void*)&ser);
  pthread_join(r,NULL);
  pthread_join(r,NULL);
}
