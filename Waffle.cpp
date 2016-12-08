//Waffle Implementation

#include "Waffle.h"
#include <iostream>
#include <algorithm>

Waffle::Waffle(){

}
Waffle::~Waffle(){
  //destruction is done internally
}
//login to the mainframe
void Waffle::login(){
  //get the login information of the person
  std::cout<<"\tWHOPPER MAINFRAME"<<std::endl<<std::endl;
  std::cout<<"User:     pFalkenator"<<std::endl;
  std::cout<<"Password: ";
  std::string pass;
  std::getline(std::cin,pass);
  //uppercase the entire thing so i dont hate my life later
  std::transform(pass.begin(), pass.end(),pass.begin(), ::toupper);
  if(pass == "JOSHUA"){
    //if the person is Dr Falken
    std::cout<<"Greetings Professor Falken"<<std::endl;
    looping();
  }
  else{
    //the user is a hacker and recieves some very scary language
    std::cout<<"Your password information was incorrect"<<std::endl;
    std::cout<<"This incident will be reported to the Pentagon System\'s Administrator"<<std::endl;
    std::cout<<"You are being locked out of the program..."<<std::endl;
    return;
  }
}

void Waffle::looping(){
  std::cout<<std::endl<<std::endl<<std::endl;
  std::string inp = "";
  while(inp != "4"){
    std::cout<<"1: CHESS PATH FINDER"<<std::endl;
    std::cout<<"2: CHESS PATH FINDING GAME"<<std::endl;
    std::cout<<"3: KNIGHT\'S TOUR"<<std::endl;
    std::cout<<"4: EXIT"<<std::endl;
    std::cout<<">";
    //get the user's  input
    std::getline(std::cin,inp);
    if(inp == "1"){
      //create a god and make him loop through his possible shit
      paths = new God();
      paths->looper();
      delete paths;
    }
    else if(inp == "2"){
      //Create the class and run the handler
      pb = new Pboard();
      pb->looper();
      delete pb;
    }
    else if(inp == "3"){
      //create the knight tour class and run the handler
      ni = new Ni();
      ni->looper();
      delete ni;
    }
    else if(inp != "4"){
      std::cout<<"Could not process your input... Please re enter your value"<<std::endl;
    }
  }
  //done here
  return;
}
