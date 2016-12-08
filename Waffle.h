//God Class- controller of everything

#ifndef WAFFLE_H_EXISTS
#define WAFFLE_H_EXISTS

#include "God.h"
#include "Pboard.h"
#include "Ni.h"

class Waffle{
  protected:
        God* paths;
        Pboard* pb;
        Ni* ni;
  public:
        //constructor
        Waffle();
        ~Waffle();
        void login();
        void looping();
};


#endif
