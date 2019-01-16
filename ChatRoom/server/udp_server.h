#pragma once 
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <map>
#include "data_pool.h"
#define SIZE 1024


class udp_server
{
  public:
    udp_server(int port);
   ~udp_server();
   //初始化
    void init_server();
    //接收数据
    void recv_data(std::string &out_string);

    //发送数据
    //广播数据
    void broadcast();  
 private:
    void send_data(const std::string &in_string,const struct sockaddr_in &peer);

  private:
    int sock;
    int port;
    data_pool pool;
    std::map<uint32_t,struct sockaddr_in> online;//在线人数的表
};
