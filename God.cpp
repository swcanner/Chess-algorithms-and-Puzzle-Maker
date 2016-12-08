#include "God.h"
#include <iostream>
#include <sstream>

//constructor
God::God(){
  //initialize values
  pq = "";
  pqm = "";
  pqa = "";
  pqr = "";
  //looper();
};
God::~God(){
  delete base;
};

void God::start(){

  std::cout<<"WALKING FAST, DIJKSTRA\'s PATH, AND I\'M HOMEBOUND"<<std::endl;
  std::cout<<"\tA Chess Path finding algorithm"<<std::endl<<std::endl<<std::endl;

  std::cout<<"**KEY: \"*\" denotes the chess piece we want to see the path of"<<std::endl;
  std::cout<<"       \"#\" denotes the final destination of the chess peice"<<std::endl;
  std::cout<<"       A piece without any ** around it is an enemy piece"<<std::endl<<std::endl<<std::endl;

  std::cout<<"What size board do you want to use for your pathfinding pleasure?"<<std::endl;
  std::cout<<"Minimum 4x4"<<std::endl;
  std::cout<<"Maximum 25x25"<<std::endl;
  std::cout<<"Default 8x8"<<std::endl;
  std::cout<<"Rows: ";

  std::string r;

  std::getline(std::cin,r);

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
  base = new Board(ro,co);
  base->setup();
  //std::cout<<"Ended the setup completely"<<std::endl;

  //pathe();
  //std::cout<<"LOL"<<std::endl;
};
void God::pathe(){
  //reinitialize the strings
  pq = "";
  pqm = "";
  pqa = "";
  pqr = "";
  std::cout<<"Computing paths";

  pq = base->pathquick();
  base->reverttowers();

  std::cout<<".";
  pqm = base->pathquickmiss();
  base->reverttowers();
  std::cout<<".";

  pqa = base->pathquickattack();
  base->reverttowers();

  pqr = base->pathquickaround();
  base->reverttowers();
  std::cout<<"."<<std::endl;;
  std::cout<<"Computation complete"<<std::endl<<std::endl;
};
void God::displaypaths(){
  std::stringstream convert;
  convert.clear();
  convert.str("");
  int inp = 47;
  while(inp != -1){
    int a = 1;
    if(pq != ""){
      std::cout<<a<<": Quickest path"<<std::endl;
      a++; //The grade I deserve on this project
    }
    if(pqm != ""){
      std::cout<<a<<": Quickest path avoiding enemies and area of attack"<<std::endl;
      a++;
    }
    if(pqa != ""){
      std::cout<<a<<": Quickest path avoiding area of attack"<<std::endl;
      a++;
    }
    if(pqr != ""){
      std::cout<<a<<": Quickest path avoiding enemies"<<std::endl;
    }
    if(a == 1){
      std::cout<<"No paths were found. Please press -1 to exit"<<std::endl;
    }
    std::cout<<"Which of the above paths would you like to see (-1 to exit): ";
    std::string inps;
    std::getline(std::cin, inps);
    convert.clear();
    convert.str("");
    convert<<inps;
    convert>>inp;
    std::cout<<"\n\n\n"<<std::endl;
    base->printBoard();
    if(inp == 1){
      if(pq != ""){
        base->showpath(pq);
      }
      else if(pqm != ""){
        base->showpath(pqm);
      }
      else if(pqa != ""){
        base->showpath(pqa);
      }
      else if(pqr != ""){
        base->showpath(pqr);
      }
    }
    else if(inp == 2){
      if(pq != ""){
        if(pqm != ""){
          base->showpath(pqm);
        }
        else if(pqa != ""){
          base->showpath(pqa);
        }
        else if(pqr != ""){
          base->showpath(pqr);
        }
      }
      else if(pqm != ""){
        if(pqa != ""){
          base->showpath(pqa);
        }
        else if(pqr != ""){
          base->showpath(pqr);
        }
      }
      else{
        if(pqr != ""){
          base ->showpath(pqr);
        }
      }
    }
    else if(inp == 3){
      if(pq != ""){
        if(pqm != ""){
          if(pqa != ""){
            base->showpath(pqa);
          }
          else if(pqr != ""){
            base->showpath(pqr);
          }
        }
        else if(pqa != ""){
          if(pqr != ""){
            base->showpath(pqr);
          }
        }
      }
      else if(pqm != "" && pqa != ""){
        if(pqr != ""){
          base->showpath(pqr);
        }
      }
    }
    else if(inp == 4){
      if(pq != "" && pqm != "" && pqa != ""){
        if(pqr != ""){
          base->showpath(pqr);
        }
      }
    }

    if(inp > a || inp < -1 || inp == 0){
      std::cout<<"Could not process your request; please enter a related integer value"<<std::endl;
    }
    base->reverttowers();
  }
  return;
};
void God::looper(){
  int inp = 0;
  //set up the board and then find the path
  start();
  pathe();
  displaypaths();
  while(inp != 3){
    std::cout<<"Would you like to 1: Reconfigure your "<<base->getrow()<<"x"<<base->getcol()<<" board"<<std::endl;
    std::cout<<"                  2: Make a new board"<<std::endl;
    std::cout<<"                  3: Exit"<<std::endl;
    std::cout<<">";
    std::stringstream convert;
    std::string inps;
    //get user input and put it into int form because why not?
    std::getline(std::cin, inps);
    convert.clear();
    convert.str("");
    convert<<inps;
    convert>>inp;
    if(inp == 1){
      //reconfigure the board and find the path
      base->reconfig();
      pq = "";
      pqm = "";
      pqa = "";
      pqr = "";
      //base->reset();
      //base->setup();
      pathe();
      displaypaths();
    }
    else if(inp == 2){
      //delete the board and start from scratch
      delete base;
      //rinse and repeat...
      start();
      pq = "";
      pqm = "";
      pqa = "";
      pqr = "";
      pathe();
      displaypaths();
    }
    else if(inp != 3){
      std::cout<<"Could not process your request"<<std::endl;
    }
  }
  std::cout<<"Returning to WHOPPER MAINFRAME menu..."<<std::endl<<std::endl;
};
