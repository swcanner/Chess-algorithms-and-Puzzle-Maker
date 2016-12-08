//Board Class

#ifndef BOARD_H_EXISTS
#define BOARD_H_EXISTS

#include "Node.h" //includes tower and string

class Board{
    protected:
        Node* head;
        std::string target;
        int row;
        int col;
        std::string COLS; //columns names of the baby
        int MAX;
    public:
        //construction and demolition
        Board();
        Board(int,int);
        ~Board();

        void setup();
        void reconfig();

        //Getters
        int getrow();
        int getcol();
        Node* gethead();
        std::string gettarget();
        std::string getcolsstr(int);
        char getcolsch(int);
        std::string longname(char c);

        //checker
        std::string checkcoor(std::string);
        std::string checktype(std::string);
        std::string checkyes(std::string);

        //Setters
        void setrow(int);
        void setcol(int);
        void settarget(std::string);


        //FOR EACH NODE algorithm
        //only to be used for the purpose of copy and paste
        void foreach();

        //prints
        void printch();
        void printdash();
        void printBoard();
        void printaoms();
        void printpath();
        void debuggery();
        void showpath(std::string);

        //finds
        Node* find(std::string);
        Node* findseq(int); //can only be called at the beginning of a dijkstra
        Node* findstart();


        //movement
        void copy(std::string,std::string);
        void copy(Node*,Node*);
        void move(Node*,Node*);
        void move(std::string,std::string);


        //clean up
        void clearaom();
        void updateaom();
        void reset();
        void reverttowers();
        void clean();
        void setoldtowers();


        //dijkstra
        std::string pathquick();
        std::string pathquickmiss();
        std::string pathquickattack();
        std::string pathquickaround();
        std::string mindistance();
        std::string path(int);
        std::string pawnpath(int);

        //Knights TOUR
        std::string kpath(Node*);
        void updatePM();
        bool checkPM(); //checks if the knights tour worked
};


#endif
