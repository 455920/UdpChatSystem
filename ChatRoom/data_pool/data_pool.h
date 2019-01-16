#pragma once 
#include <semaphore.h>//信号量
#include <string>
#include <vector>

#define NUM 256

class data_pool
{
  public:
      data_pool(int cap_=NUM);
      ~data_pool();
      void get_message(std::string &out_message);
      void put_message(const std::string &in_message);
  private:
      //数组模拟的环形队列
    std::vector<std::string> pool;
    int cap;//容量
    sem_t space_sem;
    sem_t message_sem;
    int consume_step;
    int product_step;
      
};
