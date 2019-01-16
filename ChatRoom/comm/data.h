#pragma once 

#include <iostream>

//nick_name("zs"),school("XUST"),message("nihao"),type -> ""
//JSON的格式     "{nick_name : "zs",school:"XUST",message:"nihao",type:"None"}"
//JSON自动把上面的字符串转化成下面的字符串

class data 
{
  public:
    data(); 
    //序列化
    void serialize();
    //反序列化
    void unserialize();
    ~data();
  private:
    std::string nick_name;
    std::string school;
    std::string message;
    std::string type;
};
