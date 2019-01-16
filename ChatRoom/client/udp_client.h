#pragma once 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/types.h>
#define SIZE 1024


class udp_client
{
  public:
    udp_client(std::string server_ip,int server_port);
   ~udp_client();
   //初始化
    void init_client();
    //接收数据
    void recv_data(std::string &out_string);

    //发送数据
    void send_data(const std::string &in_string);

  private:
    int sock;
    struct sockaddr_in server;//服务器的ip地址
};
