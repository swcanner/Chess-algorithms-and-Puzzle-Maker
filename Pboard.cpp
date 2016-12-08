//Puzzle board implementation

#include "Pboard.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <sstream>

Pboard::Pboard(){
  srand(time(NULL));
  mvs = 0;
}
Pboard::~Pboard(){
  //deletion handled outside this
}

//handler
void Pboard::looper(){
  std::cout<<"     KNIGHT PATH FINDER GAME"<<std::endl;
  std::cout<<"All Puzzles are Randomly Generated..."<<std::endl<<std::endl;
  std::string inp = "";
  //loop until the user wants to exit
  while(inp != "-1"){
    std::cout<<"What difficulty of puzzle do you wish to try (-1 to exit to Mainframe): "<<std::endl;
    std::cout<<"1: Easy"<<std::endl;
    std::cout<<"2: Medium"<<std::endl;
    std::cout<<"3: Hard"<<std::endl;
    std::cout<<">";
    std::getline(std::cin,inp);
    if(inp == "1"){
      std::cout<<"Rules are: You can move the Knight anywhere as long as:"<<std::endl;
      std::cout<<"\t\tit is in the confines of its movement"<<std::endl;
      //EASY Mode
      //set up the Board
      randEasy();
      std::string funky = "";
      while(funky != "3"){
        //reset the position of the original tower
        b->reverttowers();
        std::string rq = "";
        int move = 0;
        while(b->findstart() != b->find(b->gettarget()) && rq != "-1"){
          b->printBoard();
          std::cout<<"Move: "<<move<<std::endl;
          std::cout<<"Where do you wish to move the Knight (Row,Col; ex. A1) (-1 to quit): ";
          std::getline(std::cin, rq);
          if(movableEasy(rq)){
            std::string coor = b->checkcoor(rq);
            b->move(b->findstart(),b->find(coor));
            move++;
          }
          else if(rq != "-1"){
            std::cout<<"Could not process your request."<<std::endl;
            std::cout<<"Position is either not able to be moved into or you did not enter an appropriate value"<<std::endl<<std::endl;
          }
        }
        if(rq != "-1" && move <= mvs){
          //User chose not to quit and reached the destination in minimum number of moves
          std::cout<<"You reached the destination in "<<move<<" moves"<<std::endl;
          std::cout<<"That is the minimum possible number of moves"<<std::endl;
          std::cout<<"YOU WIN"<<std::endl;
          std::cout<<"Returning to the Puzzle Menu"<<std::endl<<std::endl;
          funky = "3";
        }
        else{
          //User either quit or did not reach it in the appropriate number of moves
          if(rq != "-1"){
            //User reached the destination
            std::cout<<"You reached the destination in "<<move<<" moves"<<std::endl;
          }
          std::cout<<"The minimum possible number of moves from the start to the destination is: "<<mvs<<std::endl;
          std::cout<<"Would you like to: "<<std::endl;
          std::cout<<"1: Retry"<<std::endl;
          std::cout<<"2: See the path"<<std::endl;
          std::cout<<"3: Exit to the Puzzle Menu"<<std::endl;
          std::cout<<">";
          std::getline(std::cin,funky);
          while(funky != "1" && funky != "2" && funky != "3"){
            std::cout<<funky<<std::endl;
            std::cout<<"Could not process your request... Please enter a cooresponding integer value"<<std::endl;
            std::cout<<"Would you like to: "<<std::endl;
            std::cout<<"1: Retry"<<std::endl;
            std::cout<<"2: See the path"<<std::endl;
            std::cout<<"3: Exit to the Puzzle Menu"<<std::endl;
            std::cout<<">";
            std::getline(std::cin,funky);
          }
          //funky is 1, we just rinse and repeat as done in the beginning
          if(funky == "2"){
            //revert, re-find the path, and show it
            b->reverttowers();
            std::string pq = b->pathquick();
            b->reverttowers();
            b->showpath(pq);
            std::cout<<"Would you wish to redo the puzzle?"<<std::endl;
            std::cout<<"1: Yes"<<std::endl;
            std::cout<<"2: No"<<std::endl;
            std::cout<<">";
            std::string yeah;
            std::getline(std::cin,yeah);
            while(yeah != "1" && yeah != "2"){
              std::cout<<"Could not process your request..."<<std::endl;
              std::cout<<"Please enter a cooresponding integer value"<<std::endl;
              std::cout<<"Would you wish to redo the puzzle?"<<std::endl;
              std::cout<<"1: Yes"<<std::endl;
              std::cout<<"2: No"<<std::endl;
              std::cout<<">";
              std::getline(std::cin,yeah);
            }
            if(yeah == "1"){
              //redo the puzzle
              funky = "0a";
            }
            else{
              //make sure funky gets outa hurr
              funky = "3";
            }
          }
          //funky is 3, EXIT
        }
      }
      //destroy the board
      delete b;
    }
    else if(inp == "2"){
      std::cout<<"Rules are: You can move the Knight anywhere as long as:"<<std::endl;
      std::cout<<"\t\tit is in the confines of its movement"<<std::endl;
      std::cout<<"\t\tit does not attack any opponent pieces"<<std::endl;
      //EASY Mode
      //set up the Board
      randMed();
      std::string funky = "";
      while(funky != "3"){
        //reset the position of the original tower
        b->reverttowers();
        std::string rq = "";
        int move = 0;
        while(b->findstart() != b->find(b->gettarget()) && rq != "-1"){
          b->printBoard();
          std::cout<<"Move: "<<move<<std::endl;
          std::cout<<"Where do you wish to move the Knight (Row,Col; ex. A1) (-1 to quit): ";
          std::getline(std::cin, rq);
          if(movableMed(rq)){
            std::string coor = b->checkcoor(rq);
            b->move(b->findstart(),b->find(coor));
            move++;
          }
          else if(rq != "-1"){
            std::cout<<"Could not process your request."<<std::endl;
            std::cout<<"Position is either not able to be moved into or you did not enter an appropriate value"<<std::endl<<std::endl;
          }
        }
        if(rq != "-1" && move <= mvs){
          //User chose not to quit and reached the destination in minimum number of moves
          std::cout<<"You reached the destination in "<<move<<" moves"<<std::endl;
          std::cout<<"That is the minimum possible number of moves"<<std::endl;
          std::cout<<"YOU WIN"<<std::endl;
          std::cout<<"Returning to the Puzzle Menu"<<std::endl<<std::endl;
          funky = "3";
        }
        else{
          //User either quit or did not reach it in the appropriate number of moves
          if(rq != "-1"){
            //User reached the destination
            std::cout<<"You reached the destination in "<<move<<" moves"<<std::endl;
          }
          std::cout<<"The minimum possible number of moves from the start to the destination is: "<<mvs<<std::endl;
          std::cout<<"Would you like to: "<<std::endl;
          std::cout<<"1: Retry"<<std::endl;
          std::cout<<"2: See the path"<<std::endl;
          std::cout<<"3: Exit to the Puzzle Menu"<<std::endl;
          std::cout<<">";
          std::getline(std::cin,funky);
          while(funky != "1" && funky != "2" && funky != "3"){
            std::cout<<"Could not process your request... Please enter a cooresponding integer value"<<std::endl;
            std::cout<<"Would you like to: "<<std::endl;
            std::cout<<"1: Retry"<<std::endl;
            std::cout<<"2: See the path"<<std::endl;
            std::cout<<"3: Exit to the Puzzle Menu"<<std::endl;
            std::cout<<">";
            std::getline(std::cin,funky);
          }
          //funky is 1, we just rinse and repeat as done in the beginning
          if(funky == "2"){
            //revert, re-find the path, and show it
            b->reverttowers();
            std::string pq = b->pathquickaround();
            b->reverttowers();
            b->showpath(pq);
            std::cout<<"Would you wish to redo the puzzle?"<<std::endl;
            std::cout<<"1: Yes"<<std::endl;
            std::cout<<"2: No"<<std::endl;
            std::cout<<">";
            std::string yeah;
            std::getline(std::cin,yeah);
            while(yeah != "1" && yeah != "2"){
              std::cout<<"Could not process your request..."<<std::endl;
              std::cout<<"Please enter a cooresponding integer value"<<std::endl;
              std::cout<<"Would you wish to redo the puzzle?"<<std::endl;
              std::cout<<"1: Yes"<<std::endl;
              std::cout<<"2: No"<<std::endl;
              std::cout<<">";
              std::getline(std::cin,yeah);
            }
            if(yeah == "1"){
              //redo the puzzle
              funky = "0a";
            }
            else{
              //funky music white boy
              //PLAY THAT FUNKY MUSIC LOUDDDD
              funky = "3";
            }
          }
          //funky is 3, EXIT
        }
      }
      //destroy the board
      delete b;
    }
    else if(inp == "3"){
      std::cout<<"Rules are: You can move the Knight anywhere as long as:"<<std::endl;
      std::cout<<"\t\tit is in the confines of its movement"<<std::endl;
      std::cout<<"\t\tit does not attack any opponent pieces"<<std::endl;
      std::cout<<"\t\tit does not enter any opponenent area of attack"<<std::endl;
      //EASY Mode
      //set up the Board
      randHard();
      //I have no idea why this while loop is necessary for it is included in randhard, but it is so IM PUTTING IT HERE
      while(b->pathquickmiss() == ""){
        delete b;
        randHard();
      }
      std::string funky = "";
      while(funky != "3"){
        //reset the position of the original tower
        b->reverttowers();
        std::string rq = "";
        int move = 0;
        while(b->findstart() != b->find(b->gettarget()) && rq != "-1"){
          b->printBoard();
          std::cout<<"Move: "<<move<<std::endl;
          std::cout<<"Where do you wish to move the Knight (Row,Col; ex. A1) (-1 to quit): ";
          std::getline(std::cin, rq);
          if(movableHard(rq)){
            //std::cout<<"MOVFD"<<std::endl;
            std::string coor = b->checkcoor(rq);
            b->move(b->findstart(),b->find(coor));
            move++;
          }
          else if(rq != "-1"){
            std::cout<<"Could not process your request."<<std::endl;
            std::cout<<"Position is either not able to be moved into or you did not enter an appropriate value"<<std::endl<<std::endl;
          }
        }
        if(rq != "-1" && move <= mvs){
          //User chose not to quit and reached the destination in minimum number of moves
          std::cout<<"You reached the destination in "<<move<<" moves"<<std::endl;
          std::cout<<"That is the minimum possible number of moves"<<std::endl;
          std::cout<<"YOU WIN"<<std::endl;
          std::cout<<"Returning to the Puzzle Menu"<<std::endl<<std::endl;
          funky = "3";
        }
        else{
          //User either quit or did not reach it in the appropriate number of moves
          if(rq != "-1"){
            //User reached the destination
            std::cout<<"You reached the destination in "<<move<<" moves"<<std::endl;
          }
          std::cout<<"The minimum possible number of moves from the start to the destination is: "<<mvs<<std::endl;
          std::cout<<"Would you like to: "<<std::endl;
          std::cout<<"1: Retry"<<std::endl;
          std::cout<<"2: See the path"<<std::endl;
          std::cout<<"3: Exit to the Puzzle Menu"<<std::endl;
          std::cout<<">";
          std::getline(std::cin,funky);
          while(funky != "1" && funky != "2" && funky != "3"){
            std::cout<<"Could not process your request... Please enter a cooresponding integer value"<<std::endl;
            std::cout<<"Would you like to: "<<std::endl;
            std::cout<<"1: Retry"<<std::endl;
            std::cout<<"2: See the path"<<std::endl;
            std::cout<<"3: Exit to the Puzzle Menu"<<std::endl;
            std::cout<<">";
            std::getline(std::cin,funky);
          }
          //funky is 1, we just rinse and repeat as done in the beginning
          if(funky == "2"){
            //revert, re-find the path, and show it
            b->reverttowers();
            std::string pq = b->pathquickmiss();
            b->reverttowers();
            b->showpath(pq);
            std::cout<<"Would you wish to redo the puzzle?"<<std::endl;
            std::cout<<"1: Yes"<<std::endl;
            std::cout<<"2: No"<<std::endl;
            std::cout<<">";
            std::string yeah;
            std::getline(std::cin,yeah);
            while(yeah != "1" && yeah != "2"){
              std::cout<<"Could not process your request..."<<std::endl;
              std::cout<<"Please enter a cooresponding integer value"<<std::endl;
              std::cout<<"Would you wish to redo the puzzle?"<<std::endl;
              std::cout<<"1: Yes"<<std::endl;
              std::cout<<"2: No"<<std::endl;
              std::cout<<">";
              std::getline(std::cin,yeah);
            }
            if(yeah == "1"){
              //redo the puzzle
              funky = "0a";
            }
            else{
              //get the funky out of here (funky is 3)
              funky = "3";
            }
          }
          //funky is 3, EXIT
        }
      }
      //destroy the board
      delete b;
    }
    else if(inp != "-1"){
      std::cout<<"Could not process your request... Please enter an integer value as seen below"<<std::endl<<std::endl;
    }
  }
  std::cout<<"Exiting to Mainframe..."<<std::endl<<std::endl;
}

//changer
char Pboard::intToType(int a){
  if(a == 0){
    return 'P';
  }
  else if(a == 1){
    return 'R';
  }
  else if(a == 2){
    return 'H';
  }
  else if(a == 3){
    return 'B';
  }
  else if(a == 4){
    return 'Q';
  }
  else if(a == 5){
    return 'K';
  }
  else{
    return 'H';
  }
}

void Pboard::baseRand(int r, int c){
  std::stringstream convert;
  convert.clear();
  convert.str("");
  //create our hero- the knight
  //get a random row the hero is in and the column
  int rh = rand() % (r - 1) + 1;
  std::string rowh;
  convert<<rh;
  convert>>rowh;
  int ch = rand() % (c - 1) + 1;
  std::string colh = b->getcolsstr(ch);
  //find the current tower in the position
  Tower* t = b->find(colh + rowh)->getTower();
  //set the tower to our hero
  t->settype('H');
  t->makealive();
  t->makefriend();

  //get the destination
  convert.clear();
  convert.str("");
  int drh = rand() % (r - 1) + 1;
  std::string drowh;
  convert<<drh;
  convert>>drowh;
  int dch = rand() % (c - 1) + 1;
  std::string dcolh = b->getcolsstr(dch);
  //while it is the same as the start position, redo it
  while(dcolh + drowh == colh + rowh){
    convert.clear();
    convert.str("");
    drh = rand() % (r - 1) + 1;
    convert<<drh;
    convert>>drowh;
    dch = rand() % (c - 1) + 1;
    dcolh = b->getcolsstr(dch);
  }
  //set the destination as our target
  b->settarget(dcolh + drowh);
  b->setoldtowers();
}
void Pboard::randEasy(){
  //keep the board a size of 6
  b = new Board(6,6);
  baseRand(6,6);
  //make the horse go through it
  std::string p = b->pathquick();
  //get the distance from here to there- same as the amount of moves
  mvs = b->find(b->gettarget())->getdistance();
}
void Pboard::enemRand(int num, int r, int c){
  std::stringstream convert;
  for(int i = 0; i < num; i++){
    convert.clear();
    convert.str("");
    int er = rand() % (r - 1) + 1;
    std::string erow;
    convert<<er;
    convert>>erow;
    int ec = rand() % (c - 1) + 1;
    std::string ecol = b->getcolsstr(ec);
    std::string coor = ecol + erow;
    if(b->find(coor)->gettarget() || b->find(coor)->getTower()->getalive()){
      //cant change it
      i--;
    }
    else{
      int ty = rand() % 6;
      char type = intToType(ty);
      //We have the type and position; LETS CHANGE IT NOW
      Tower* t = b->find(coor)->getTower();
      //set the tower to our hero
      t->settype(type);
      t->makealive();
      t->makeenemy();
    }
  }
  b->setoldtowers();
}
void Pboard::randMed(){
  //create an 8x8 board and hardcore do this
  b = new Board(8,8);
  //set positions
  baseRand(8,8);
  //add enemies in
  enemRand(7,8,8);
  std::string p = b->pathquickaround();
  //check if the path exists
  while(p == ""){
    delete b;
    //redo the above till we get it right
    b = new Board(8,8);
    baseRand(8,8);
    enemRand(5,8,8);
    p = b->pathquickaround();
  }
  mvs = b->find(b->gettarget())->getdistance();
}
void Pboard::randHard(){
  //Same as Med, but bigger board and more enemies
  b = new Board(10,10);
  baseRand(10,10);
  enemRand(15,10,10);
  b->setoldtowers();
  std::string p = b->pathquickmiss();
  mvs = b->find(b->gettarget())->getdistance();
  //check if the path exists
  while(mvs < 3){
    delete b;
    //redo the above till we get it right
    b = new Board(10,10);
    baseRand(10,10);
    enemRand(15,10,10);
    b->setoldtowers();
    p = "";
    p = b->pathquickmiss();
    mvs = 0;
    if(p != ""){
      //b->printaoms();
      mvs = b->find(b->gettarget())->getdistance();
    }
  //  std::cout<<"Mvs: "<<mvs<<std::endl;
  }
  mvs = b->find(b->gettarget())->getdistance();
}

//Movability
bool Pboard::movableEasy(std::string coor){
  //check if the position actually exists
  std::string rcoor = b->checkcoor(coor);
  if(rcoor != "NULL"){
    Node* pos = b->find(rcoor);
    //check if the position is reachable by the previous position
    //get current position of our hero the knight
    Node* start = b->findstart();
    for(int i = 0; i < start->getmoves(); i++){
      //position is possible to move into
      if(start->path(i,1) == pos){
        return true;
      }
    }
  }
  //cannot move into said position
  return false;
}
bool Pboard::movableMed(std::string coor){
  if(movableEasy(coor)){
    std::string rcoor = b->checkcoor(coor);
    Node* pos = b->find(rcoor);
    //if there is no enemy there then we can move
    if(pos->enempresent() == false){
      return true;
    }
  }
  return false;
}
bool Pboard::movableHard(std::string coor){
  if(movableMed(coor)){
    std::string rcoor = b->checkcoor(coor);
    Node* pos = b->find(rcoor);
    //if the position is not an area of attack we can move
    if(pos->getenemyaom() == false){
      return true;
    }
  }
  return false;
}
