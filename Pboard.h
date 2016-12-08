//PBoard Class

#ifndef PBOARD_H_EXISTS
#define PBOARD_H_EXISTS


#include "Board.h" //includes tower and string

class Pboard{
  protected:
    Board* b;
    int mvs; // moves it takes to get to the final destination
  public:
    //Constructor
    Pboard();
    ~Pboard();

    //handler
    void looper();

    char intToType(int);

    //randomization of the board
    void baseRand(int,int);
    void randEasy();
    void enemRand(int,int,int);
    void randMed();
    void randHard();

    //is the space movable into?
    bool movableEasy(std::string);
    bool movableMed(std::string);
    bool movableHard(std::string);
};

#endif
