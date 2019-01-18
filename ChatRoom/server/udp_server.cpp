#include "udp_server.h"




udp_server::udp_server(int _port):port(_port)
{
}


void udp_server::init_server()
{
  sock = socket(AF_INET,SOCK_DGRAM,0);
  if(sock<0)
  {
    std::cerr<<"socket error!"<<std::endl;
    return;
  }
    
  struct sockaddr_in local;
  local.sin_family=AF_INET;
  local.sin_port =htons(port);
  local.sin_addr.s_addr=htonl(INADDR_ANY);

  if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
  {
    std::cerr<<"bind error!"<<std::endl;
    return;
  }
}

udp_server::~udp_server()
{
    
}

//我们认为收到都是一个字符串
void udp_server::recv_data(std::string &out_string)
{
  char buf[SIZE];
  struct sockaddr_in peer;
  socklen_t len = sizeof(peer);
  ssize_t s = recvfrom(sock,buf,SIZE-1,0,(struct sockaddr*)&peer,&len);
  if(s>0)
  {
    buf[s]=0;
    out_string=buf;
    //把数据放入数据池
    pool.put_message(out_string);
    //map本身就有查重
    online.insert(std::pair<uint32_t,struct sockaddr_in>(peer.sin_addr.s_addr,peer));
  }
  else 
  {
         
  }
}

void udp_server::send_data(const std::string &in_string,const struct sockaddr_in &peer)
{
  sendto(sock,in_string.c_str(),in_string.size(),0,(struct sockaddr*)&peer,sizeof(peer)); 
}

 void udp_server::broadcast()
{ 
    //从池子里拿出数据
    std::string message;
    pool.get_message(message);
    std::map<uint32_t,struct sockaddr_in>::iterator iter = online.begin(); 
    for(;iter!=online.end();iter++)
    {
      send_data(message,iter->second);
    }
}
