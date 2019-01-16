#include "data.h"
data::data()
{

}
    //序列化
void data::serialize(std::string &out_string)
{
  Json::Value root;
  root["nick_name"]=nick_name;
  root["school"]=school;
  root["message"]=message;
  root["type"]=type;
#ifndef FAST 
  Json::writer w;
#else 
  Json::StyledWriter w;
#endif
  out_string = w.write(root);//序列化成一个字符串
}
    //反序列化
void data::unserialize(std::string &in_string)
{
   Json::Value root;
   Json::Reader r;
   r.parse(in_string,root,false);//反序列化
   nick_name = root["nick_name"].asString();
   school = root["school"].asString();
   message = root["message"].asSring();
   type =root["type"].asString(); 
}

data::~data()
{

}


int main()
{
  data d;
  d.nick_name = "平凡";
  d.school="XUST";
  d.message="hello";
  d.type="None";
  std::string out_string;
  d.serialize(out_string);//序列化成out_string
  std::cout<<out_string<<std::endl;
}