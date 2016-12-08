//main.cpp

#include "Waffle.h"
#include <iostream>

int main(){

  Waffle* rogord = new Waffle();
  rogord->login();
  delete rogord;

  std::cout<<"FIN"<<std::endl;
  return 0;
}
