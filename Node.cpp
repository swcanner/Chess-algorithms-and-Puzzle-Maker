#include "Node.h"
#include <iostream>
#include <cstdlib>

//IM SOMETHING FROM NOTHING
//YOU ARE MY FUSE: IT GOES ON ON ON
Node::Node(){
    //This is the head
    pos = "A0";
    pm = 0;
    t = new Tower();
    oldTower = new Tower();
    oldTower->supersetter(t->getposition(), t->getalive(), t->getfriend(), t->gettype());
    distance = -1;
    visit = false;
    mv = false;
    target = false;
    enemyaom = false;
    up = NULL;
    right = NULL;
    left = NULL;
    down = NULL;
};
Node::Node(std::string p, Node* le, Node* u){
    //sets the towers, the left Node, and upper node; rest are null
    pos = p;
    t = new Tower(p);
    oldTower = new Tower();
    oldTower->supersetter(t->getposition(), t->getalive(), t->getfriend(), t->gettype());
    distance = -1;
    visit = false;
    mv = false;
    target = false;
    enemyaom = false;
    up = u;
    //set the upper node's down node to this
    if(up != NULL){
      up->setdown(this);
    }
    right = NULL;
    //set the left node's right node to this
    left = le;
    if(left != NULL){
      left->setright(this);
    }
    down = NULL;
    pm = 0;
};
Node::~Node(){
    //destroy the towers
    delete t;
    delete oldTower;
};


//Getters

/*
*PURPOSE:
*PARAMS:
*RETURNS:
*/
Tower* Node::getTower(){
    return t; //used for accessing the tower's stuff in the board class if necessary
};
Tower* Node::getOldTower(){
  return oldTower;
}
Node* Node::getup(){
    return up;
};
Node* Node::getright(){
    return right;
};
Node* Node::getleft(){
    return left;
};
Node* Node::getdown(){
    return down;
};
int Node::getdistance(){
    return distance;
};
int Node::getseq(){
    return seq;
};
bool Node::getvisit(){
    return visit;
};
bool Node::getmv(){
    return mv;
};
bool Node::gettarget(){
    return target;
};
bool Node::getenemyaom(){
    return enemyaom;
};
bool Node::enempresent(){
  //if the Node has an alive tower that is not a friend, an enemy is present
    if(t->getalive()){
        if(t->getfriend() == false){
            return true;
        }
    }
    return false;
};
std::string Node::getposition(){
    return pos;
};
std::string Node::getpos(){
    return pos;
};
std::string Node::getcol(){
  return pos.substr(0,1);
}
std::string Node::getrow(){
  return pos.substr(1);
}

//Setters
void Node::killtower(){
    t->kill();
};
void Node::setposition(std::string p){
    pos = p;
    t->setposition(p);
};
void Node::setTower(std::string p, bool a, bool b, char c){
    t->supersetter(p,a,b,c);
};
void Node::setoldTower(){
    oldTower->supersetter(t->getposition(),t->getalive(),t->getfriend(),t->gettype());
};
void Node::reverttower(){
    t->supersetter(oldTower->getposition(),oldTower->getalive(),oldTower->getfriend(),oldTower->gettype());
};
void Node::setdistance(int a){
    distance = a;
};
void Node::setvisit(bool v){
    visit = v;
};
void Node::isvisit(){
    visit = true;
};
void Node::notvisit(){
    visit = false;
};
void Node::setseq(int s){
    seq = s;
};
void Node::setmv(bool m){
    mv = m;
};
void Node::ismv(){
    mv = true;
};
void Node::notmv(){
    mv = false;
};
void Node::settarget(bool t){
    target = t;
};
void Node::istarget(){
    target = true;
};
void Node::nottarget(){
    target = false;
};
void Node::setenemyaom(bool e){
    enemyaom = e;
};
void Node::isenemyaom(){
    enemyaom = true;
};
void Node::notenemyaom(){
    enemyaom = false;
};
void Node::setup(Node* u){
    up = u;
};
void Node::setright(Node* r){
    right = r;
};
void Node::setleft(Node* l){
    left = l;
};
void Node::setdown(Node* d){
    down = d;
};


//functionality
int Node::getmoves(){
  //Amount of POSSIBLE paths that the tower can make- pawn 3, bishop 4, etc...
    char funky = t->gettype();
    if(funky == 'P'){
        return 3;
    }
    else if(funky == 'B'){
        return 4;
    }
    else if(funky == 'H'){
        return 8;
    }
    else if(funky == 'R'){
        return 4;
    }
    else if(funky == 'Q'){
        return 8;
    }
    else if(funky == 'K'){
        return 8;
    }
    else{
        //base case that it isnt any actual usable tower
        return 0;
    }
};
Node* Node::path(int p,int d){
    //check if its alive
    if(t->getalive() == false){
      //failsafe in case not caught with the p
      return NULL;
    }
    //if the path exceeds the amount of possible paths, NULL
    if(p >= getmoves()){
        return NULL;
    }
    //the distance from the current state to the next state is less than 1, NULL
    if(d < 1){
      return NULL;
    }

    //redirect the path to the tower's given path
    else{
        char funky = t->gettype();
        if(funky == 'P'){
            return pawnpath(p,d);
        }
        else if(funky == 'B'){
            return bishoppath(p,d);
        }
        else if(funky == 'H'){
            return knightpath(p,d);
        }
        else if(funky == 'R'){
            return rookpath(p,d);
        }
        else if(funky == 'Q'){
            return queenpath(p,d);
        }
        else if(funky == 'K'){
            return kingpath(p,d);
        }
        else{
            //base case that it isnt any actual usable tower
            return NULL;
        }
    }
};
Node* Node::pawnpath(int p,int d){
    if(d != 1){
      //failsafe
        return NULL;
    }
    //it is the pawn we are looking for
    if(t->getfriend()){
        Node* sel = getup();
        if(sel != NULL){
            if(p == 0){
                //can move up
                if(sel->enempresent()){
                  //enemy there, no go on the going
                  return NULL;
                }
                //can go, therefore we say it can
                return sel;
            }
            else if(p == 1){
              //upright
                sel = sel->getright();
                if(sel != NULL){ //if the tower is alive and it is an enemy
                    if(sel->enempresent()){
                        return sel;
                    }
                }
            }
            else if(p == 2){
              //upleft
                sel = sel->getleft();
                if(sel != NULL){ //if the tower is alive and it is an enemy
                    if(sel->enempresent()){
                        return sel;
                    }
                }
            }
        }
    }
    else{
      //the tower is an enemy
        Node* sel = getdown();
        if(sel != NULL){
          //WE ARE ONLY CONCERNED WITH ITS AREA OF ATTACK, not movement
            if(p == 0 || p == 1){
              //possible move is downleft
                if(sel->getleft() != NULL){
                    return sel->getleft();
                }
            }
            else{
              //and downright
                if(sel->getright() != NULL){
                    return sel->getright();
                }
            }
        }
    }
    return NULL;
};
Node* Node::bishoppath(int p,int d){
    Node* sel = this;
    if(d < 1){
      return NULL;
    }
    //loop through until we get to the distance set
    for(int i = 0; i < d; i++){
        //if the previous space has an enemy tower we say NO
        if(sel->enempresent() && sel != this){
            return NULL;
        }
        else if(p == 0){
            //UP LEFT
            sel = sel->getup();
            if(sel != NULL){
                sel = sel->getleft();
            }
            if(sel == NULL){
                return NULL;
            }
        }
        else if(p == 1){
            //UP RIGHT
            sel = sel->getup();
            if(sel != NULL){
                sel = sel->getright();
            }
            if(sel == NULL){
                return NULL;
            }
        }
        else if(p == 2){
            //DOWN RIGHT
            sel = sel->getdown();
            if(sel != NULL){
                sel = sel->getright();
            }
            if(sel == NULL){
                return NULL;
            }
        }
        else if(p == 3){
            //DOWN left
            sel = sel->getdown();
            if(sel != NULL){
                sel = sel->getleft();
            }
            if(sel == NULL){
                return NULL;
            }
        }
        else{
            return NULL;
        }
    }
    return sel;
};
Node* Node::queenpath(int p,int d){
    if(d < 1){
      return NULL;
    }
    //a queen is simply a combo of a rook and a bishop
    if(p < 4){
      return rookpath(p,d);
    }
    else{
      return bishoppath(p - 4, d);
    }
};
Node* Node::kingpath(int p,int d){
    if(d != 1){
      return NULL;
    }

    Node* sel = this;
    if(p == 0){
      //UP
      sel = sel->getup();
    }
    else if(p == 1){
      //up right
      sel = sel->getup();
      if(sel != NULL){
        sel = sel->getright();
      }
    }
    else if(p == 2){
      //right
      sel = sel->getright();
    }
    else if(p == 3){
      //down right
      sel = sel->getdown();
      if(sel != NULL){
        sel = sel->getright();
      }
    }
    else if(p == 4){
      //down
      sel = sel->getdown();
    }
    else if(p == 5){
      //down left
      sel = sel->getdown();
      if(sel != NULL){
        sel = sel->getleft();
      }
    }
    else if(p == 6){
      //left
      sel = sel->getleft();
    }
    else if(p == 7){
      //up left
      sel = sel->getup();
      if(sel != NULL){
        sel = sel->getleft();
      }
    }
    else{
      sel = NULL;
    }

    return sel;

};
Node* Node::knightpath(int p,int d){
    Node* sel = this;
    if(d != 1){
      return NULL;
    }
    if(p == 0 || p == 7){
      //uppers
      sel = sel->getup();
      if(sel != NULL){
        sel = sel->getup();
        if(sel !=NULL){
          if(p == 0){
            //right
            sel = sel->getright();
          }
          else{
            //left
            sel = sel->getleft();
          }
        }
      }
    }
    else if(p == 1 || p == 2){
      //righters
      sel = sel->getright();
      if(sel != NULL){
        sel = sel->getright();
        if(sel !=NULL){
          if(p == 1){
            //up
            sel = sel->getup();
          }
          else{
            //down
            sel = sel->getdown();
          }
        }
      }
    }
    else if(p == 3 || p == 4){
      //downers
      sel = sel->getdown();
      if(sel != NULL){
        sel = sel->getdown();
        if(sel !=NULL){
          if(p == 3){
            //right
            sel = sel->getright();
          }
          else{
            //left
            sel = sel->getleft();
          }
        }
      }
    }
    else if(p == 5 || p == 6){
      //lefters
      sel = sel->getleft();
      if(sel != NULL){
        sel = sel->getleft();
        if(sel !=NULL){
          if(p == 5){
            //down
            sel = sel->getdown();
          }
          else{
            //up
            sel = sel->getup();
          }
        }
      }
    }
    else{
      sel = NULL;
    }

    return sel;
};
Node* Node::rookpath(int p,int d){
    Node* sel = this;
    if(d < 1){
      //failsafe
      return NULL;
    }
    //loop until we reach the given distance
    for(int i = 0; i < d; i++){
      //enemy is present in the previous one in the loop, we say oh hell no to going forward
      if(sel->enempresent() && sel != this){
        //std::cout<<"Pos: "<<sel->getpos()<<std::endl;
        //std::cin.ignore();
        //previous one has an enemy in it- we say OH NO NO to going forward
        return NULL;
      }

      else if(p == 0){
        //UP
        sel = sel->getup();
      }
      else if(p == 1){
        //RIGHT
        sel = sel->getright();
      }
      else if(p == 2){
        //DOWN
        sel = sel->getdown();
      }
      else if(p == 3){
        //LEFT
        sel = sel->getleft();
      }
      else{
        //failsafe
        return NULL;
      }

      if(sel == NULL){
        return NULL;
      }

    }
    return sel;
};

Node* Node::backpawnpath(int p, int d){
  //backtracking the pawn path for later use in the pawn
      if(d != 1){
        //failsafe
          return NULL;
      }
      //it is the pawn we are looking for
      if(t->getfriend()){
          Node* sel = getdown();
          Tower* ot = getOldTower();
          if(sel != NULL){
              if(p==0){
                //no enemy is present in the current position, therefore we return the downward one
                  if(ot->getalive() == false || ot->getfriend()){
                    return sel;
                  }
              }
          else{
            //an enemy is present in the current node
            if(ot->getalive() && ot->getfriend() == false){
              //He can go right
              if(p==1){
                sel = sel->getright();
                if(sel != NULL){
                  return sel;
                }
              }//or left
              else if(p==2){
                sel = sel->getleft();
                if(sel != NULL){
                  return sel;
                }
              }
            }
          }
        }
      }
    return NULL;
};


//KNIGHTS PATH
void Node::setPM(){
  setoldTower();
  //set the tower to a friendly knight
  getTower()->makealive();
  getTower()->settype('H');
  getTower()->makefriend();
  pm = 0;
  //loop through each possible move
  for(int i = 0; i < getmoves(); i++){
    //check for a null
    if(path(i,1) != NULL){
      //check if unvisited
      if(path(i,1)->getvisit() == false){
        pm++;
      }
    }
  }//end for
  //std::cout<<getposition()<<":"<<pm<<std::endl;
  //revert to the original tower
  reverttower();
};
void Node::setPM(int a){
  pm = a;
};
int Node::getPM(){
  return pm;
};
