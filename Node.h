//Tower Class- chess piece

#ifndef NODE_H_EXISTS
#define NODE_H_EXISTS


#include "Tower.h"

class Node{
    protected:
        std::string pos; //position
        Tower* t; //Tower that is on the node
        Tower* oldTower; //Tower for reverting once dijstra has had his way with my code
        int distance; //used for dijkstra
        bool visit;
        int seq;
        bool mv;
        bool target;
        bool enemyaom;
        Node * up;
        Node * right;
        Node * left;
        Node * down;
        int pm; //possible moves for the Knights tour
    public:
        //IM SOMETHING FROM NOTHING
        //YOU ARE MY FUSE: IT GOES ON ON ON
        Node();
        Node(std::string, Node*, Node*);
        ~Node();

        //Getters
        Tower* getTower();
        Tower* getOldTower();
        Node* getup();
        Node* getright();
        Node* getleft();
        Node* getdown();
        int getdistance();
        int getseq();
        bool getvisit();
        bool getmv();
        bool gettarget();
        bool getenemyaom();
        bool enempresent();
        std::string getposition();
        std::string getpos();
        std::string getcol();
        std::string getrow();


        //Setters
        void killtower();
        void setposition(std::string);
        void setTower(std::string, bool, bool, char);
        void setoldTower();
        void reverttower();
        void setdistance(int);
        void setvisit(bool);
        void isvisit();
        void notvisit();
        void setseq(int);
        void setmv(bool);
        void ismv();
        void notmv();
        void settarget(bool);
        void istarget();
        void nottarget();
        void setenemyaom(bool);
        void isenemyaom();
        void notenemyaom();
        void setup(Node*);
        void setright(Node*);
        void setleft(Node*);
        void setdown(Node*);


        //functionality
        int getmoves();
        Node* path(int,int);
        Node* pawnpath(int,int);
        Node* bishoppath(int,int);
        Node* queenpath(int,int);
        Node* kingpath(int,int);
        Node* knightpath(int,int);
        Node* rookpath(int,int);

        Node* backpawnpath(int,int);


        //KNIGHTS TOUR
        void setPM();
        void setPM(int);
        int getPM();
};


#endif
