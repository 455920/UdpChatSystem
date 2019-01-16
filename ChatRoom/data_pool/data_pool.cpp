#include "data_pool.h"

//缺省参数在声明处
data_pool::data_pool(int cap_):
  cap(cap_),pool(cap_),consume_step(0),product_step(0)
{
  sem_init(&space_sem,0,cap_);
  sem_init(&message_sem,0,0);
}


data_pool::~data_pool()
{
  sem_destroy(&space_sem);
  sem_destroy(&message_sem);
}

//消费者和生产者都是从0开始
//消费者
void data_pool::get_message(std::string& out_message)
{
  sem_wait(&message_sem);
  out_message = pool[consume_step];
  sem_post(&space_sem);
  ++consume_step;
  consume_step%=cap;
}



//生产者
void data_pool::put_message(const std::string &in_message)
{
  sem_wait(&space_sem);
  pool[product_step]=in_message;
  sem_post(&message_sem);
  ++product_step;
  product_step%=cap;
}
