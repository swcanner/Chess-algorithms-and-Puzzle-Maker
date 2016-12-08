//Ni.cpp
//Implementation of the KNIGHTS WHO SAY NI class

#include "Ni.h"
#include <iostream>
#include <sstream>

//Im something, from nothing
Ni::Ni(){
  path = "";
  start = "";
}
Ni::~Ni(){
  //nothing done here, board is deleted in looper
}

//HANDLER
void Ni::setup(){
  std::cout<<"Welcome to the Knights Who Say NI\'s Tour"<<std::endl<<std::endl;

  std::cout<<"You setup a board size greater than 3x3 or less than 26x26"<<std::endl;
  std::cout<<"Pick a spot, and we show you the way for a knight to get to every spot on"<<std::endl;
  std::cout<<"        the board without touching any spot twice; IF SUCH A PATH EXISTS"<<std::endl;
  std::cout<<"A normal board is 8x8"<<std::endl;
  std::cout<<"Rows: ";
  //Literally stolen from the God Class...
  std::string r;

  std::getline (std::cin,r);

  int ro = 0;
  std::stringstream convert;
  //converts the int to a string
  convert.clear();
  convert.str("");
  convert<<r;
  convert>>ro;

  if(ro < 4){
    std::cout<<"Could not properly process your request-\neither below the integer value of noninteger value entered"<<std::endl;
    std::cout<<"Reverting to default value of 8 rows"<<std::endl;
    ro = 8;
  }
  else if(ro > 25){
    std::cout<<"Row Number exceeded maximum value"<<std::endl;
    std::cout<<"Reverting to maximum value of 25 rows"<<std::endl;
    ro = 25;
  }

  std::string c;
  int co;
  std::cout<<"Columns: ";
  std::getline(std::cin,c);

  convert.clear();
  convert.str("");
  convert<<c;
  convert>>co;

  if(co < 4){
    std::cout<<"Could not properly process your request-\neither below the integer value of noninteger value entered"<<std::endl;
    std::cout<<"Reverting to default value of 8 columns"<<std::endl;
    co = 8;
  }
  if(co > 25){
    std::cout<<"Column Number is exceeds maximum value"<<std::endl;
    std::cout<<"Reverting to maximum value of 25 columns"<<std::endl;
    co = 25;
  }
  b = new Board(ro,co);

  b->printBoard();
  //get postion of the knight at the start
  std::cout<<"Where do you want the knight to start (Format: Row,Col; ex. A1)?"<<std::endl;
  std::cout<<">";
  std::string coor;
  std::getline(std::cin,coor);
  while(b->checkcoor(coor) == "NULL"){
    std::cout<<"Could not process your request"<<std::endl;
    std::cout<<"Please enter in the start of the knight (ex. A1)"<<std::endl;
    std::cout<<">";
    std::getline(std::cin,coor);
  }
  //set the knight at that postion as a knight, alive, and friendly
  coor = b->checkcoor(coor);
  start = coor;
  Tower* tow = b->find(coor)->getTower();
  tow->makealive();
  tow->settype('H');
  tow->makefriend();
  b->setoldtowers();
}
void Ni::reconfig(){
  b->reverttowers();
  b->printBoard();
  std::cout<<"Current position of knight: "<<b->findstart()->getposition()<<std::endl;
  //get where they want to change the position to
  std::cout<<"What position do you want the knight to be placed (ex. A1)?"<<std::endl;
  std::cout<<">";
  std::string coor;
  std::getline(std::cin,coor);
  while(b->checkcoor(coor) == "NULL"){
    std::cout<<"Could not process your request"<<std::endl;
    std::cout<<"Please enter in the start position of the knight (ex. A1)"<<std::endl;
    std::cout<<">";
    std::getline(std::cin,coor);
  }
  coor = b->checkcoor(coor);
  start = coor;
  //move the piece and update the old towers
  b->move(b->findstart(),b->find(coor));
  b->setoldtowers();
}
void Ni::compute(){
  b->clean();
  b->reverttowers();
  std::cout<<"Computing.";
  path = b->kpath(b->findstart());
  std::cout<<".."<<std::endl;
  b->reverttowers();
  if(b->checkPM()){
    std::cout<<"Path was found"<<std::endl;
  }
  else{
    std::cout<<"Such a path does not exist"<<std::endl;
  }
}
void Ni::looper(){
  setup();
  compute();
  std::string lol = "";
  if(b->checkPM() == false){
    lol = " attempted";
  }
  //reset everything cuz it gets all weird
  b->reset();
  //put back our hero in its starting position
  Tower* t = b->find(start)->getTower();
  t->makealive();
  t->settype('H');
  t->makefriend();
  std::string inp = "";
  b->setoldtowers();
  while(inp != "4"){
    b->reverttowers();
    b->printBoard();
    std::cout<<"Would you like to: "<<std::endl;
    std::cout<<"\t1: See the"<<lol<<" path"<<std::endl;
    std::cout<<"\t2: Change the start position of the Knight"<<std::endl;
    std::cout<<"\t3: Change Board Size"<<std::endl;
    std::cout<<"\t4: Exit to Mainframe"<<std::endl;
    std::cout<<">";
    std::getline(std::cin,inp);
    if(inp == "1"){
      b->showpath(path);
    }
    else if(inp == "2"){
      reconfig();
      compute();
      b->reset();
      //put back our hero in its starting position
      Tower* t = b->find(start)->getTower();
      t->makealive();
      t->settype('H');
      t->makefriend();
      b->setoldtowers();
      lol = "";
      if(b->checkPM() == false){
        lol = " attempted";
      }
    }
    else if(inp == "3"){
      delete b;
      setup();
      compute();
      b->reset();
      //put back our hero in its starting position
      Tower* t = b->find(start)->getTower();
      t->makealive();
      t->settype('H');
      t->makefriend();
      b->setoldtowers();
      lol = "";
      if(b->checkPM() == false){
        lol = " attempted";
      }
    }
    else if(inp != "4"){
      std::cout<<"Could not process your request..."<<std::endl;
      std::cout<<"Please enter a cooresponding integer value"<<std::endl;
    }
  }
  delete b;
  std::cout<<"Exiting to Mainframe..."<<std::endl;
}
