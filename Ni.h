//Ni class
//WE ARE THE KNIGHTS WHO SAY NI!
//handles the knights path

#ifndef NI_H_EXISTS
#define NI_H_EXISTS

#include "Board.h"

class Ni{
  protected:
        Board* b;
        std::string path;
        std::string start;
  public:
        //constructor
        Ni();
        ~Ni();

        //Handler
        void setup();
        void reconfig();
        void compute(); //because i want it to look professional like
        void looper();
};


#endif
