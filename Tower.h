//Tower Class- chess piece

#ifndef TOWER_H_EXISTS
#define TOWER_H_EXISTS


#include <string>

class Tower{
    private:
        std::string pos; //position that the Chess piece is in- failsafe
        bool alive; //whether the piece is active or not
        bool buddy; //whether the piece is friendly or not
        char type; //the type the chess piece is
    public:
        Tower(); //constructor
        Tower(std::string); //overloaded constructor
        Tower(std::string, bool, char); //overloaded constructor
        ~Tower(); //destructor

        //GET STATEMENTS
        std::string getposition();
        bool getalive();
        bool getfriend();
        char gettype();

        //SET STATEMENTS
        void makealive();
        void makedead();
        void kill();
        void setalive(bool);
        void makefriend();
        void makeenemy();
        void setfriend(bool);
        void changetype(char);
        void settype(char);
        void setposition(std::string);

        //Super Setter
        void supersetter(std::string, bool, bool, char);

};


#endif
