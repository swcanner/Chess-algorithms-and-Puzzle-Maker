//God Class- controller of everything

#ifndef GOD_H_EXISTS
#define GOD_H_EXISTS


#include "Board.h"

class God{
    private:
        Board* base;
        std::string pq;
        std::string pqm;
        std::string pqa;
        std::string pqr;
    public:
        //constructor
        God();
        ~God();

        void start();
        void pathe();
        void displaypaths();
        void looper();
};


#endif
