//Implementation of the Tower header
#include "Tower.h"

#include <iostream>

//set the contructor to a bunch of bs values
Tower::Tower(){
    alive = false;
    buddy = false;
    pos = "Z26";
    type = 'A';
}

Tower::Tower(std::string p){
    alive = false;
    buddy = false;
    pos = p;
    type = 'A';
}

Tower::Tower(std::string p, bool f, char t){
    alive = true;
    buddy = f;
    pos = p;
    type = t;
}

Tower::~Tower(){
    //Nothing on the heap, nothing to destruct
}


//GETTERS
std::string Tower::getposition(){
    return pos;
}
bool Tower::getalive(){
    return alive;
}
bool Tower::getfriend(){
    return buddy;
}

char Tower::gettype(){
    return type;
}


//SETTERS
void Tower::makealive(){
    alive = true;
};
void Tower::makedead(){
    alive = false;
};
void Tower::kill(){
    makedead();
}
void Tower::setalive(bool a){
    alive = a;
};
void Tower::makefriend(){
    buddy = true;
};
void Tower::makeenemy(){
    buddy = false;
};
void Tower::setfriend(bool f){
    buddy = f;
}
void Tower::changetype(char t){
    type = t;
};
void Tower::settype(char t){
    type = t;
}
void Tower::setposition(std::string lol){
    pos = lol;
}

//Super Setter
void Tower::supersetter(std::string p, bool a, bool f, char t){
    pos = p;
    alive = a;
    buddy = f;
    type = t;
};
