#include "udp_client.h"

using namespace std;



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
  cli.init_client();

  std::string message;

  while(1)
  {
    std::cout<<"Please Enter#";
    std::cin>>message;
    cli.send_data(message);
  }



  return 0;
}
