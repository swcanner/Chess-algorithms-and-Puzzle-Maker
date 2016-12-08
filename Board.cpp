#include "Board.h" //includes tower and string
#include <iostream>
#include <sstream>
#include <locale>
#include <limits> //shamelessly stolen from Stack Overflow
#include <algorithm> //stolen from Stack Overflow for uppercasing the string

//construct and destruct
Board::Board(){
  Board(8,8); //default board size
};
Board::Board(int r,int c){
  MAX = std::numeric_limits<int>::max(); //shameleslly stolen from Stack Overflow
  COLS = "!ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //is treated as a constant
  row = r;
  col = c;
  head = new Node();

  //std::cout<<"A"<<std::endl;

  std::string ro = "";
  std::stringstream convert;
  //converts the int to a string
  convert.clear();
  convert.str("");
  convert<<row;
  convert>>ro;

  Node* rsel = new Node(getcolsstr(1) + ro, head, NULL);
  Node* csel = rsel;
  //create first row
  for(int i = 2; i <= col; i++){
    csel = new Node(getcolsstr(i) + ro, csel, NULL);
  }

  //std::cout<<"A"<<std::endl;

  //create remaining rows
  for(int i = row - 1; i > 0; i--){
    //stringify the row we are in
    convert.clear();
    convert.str("");
    convert<<i;
    convert>>ro;

    //std::cout<<ro<<"-"<<i<<std::endl;

    rsel = new Node(getcolsstr(1) + ro, NULL, rsel);
    csel = rsel;

    //get previous row string
    int pr = i + 1;
    std::string prevrow;
    convert.clear();
    convert.str("");
    convert<<pr;
    convert>>prevrow;


    for(int j = 2; j <= col; j++){

      //std::cout<<"FSD:  "<<j<<std::endl;

      //std::cout<<"NEXT POSITION: "<<getcolsstr(j) + ro<<std::endl;
      //std::cout<<"Curr Position: "<<csel->getposition()<<std::endl;
      //std::cout<<"Up\'s Position: "<<find(getcolsstr(j) + prevrow)->getposition()<<std::endl;
      //create a node that uses the previous's as the left and the previous row as the upper
      csel = new Node(getcolsstr(j) + ro, csel, find(getcolsstr(j) + prevrow));

      //std::cout<<"NUDI: "<<j<<std::endl;
    }
  }
  //clean it out for goodness sake
  clean();
  //std::cout<<"A"<<std::endl;

};
Board::~Board(){
  //Deletes every single one of the nodes
  Node* rsel = head->getright();
  Node* csel = rsel;
  Node* prev = csel;
  //Modified for each loop
  while(rsel != NULL){
    rsel = rsel->getdown();
    while(csel != NULL){
      //go through each column of the row until we reach the end
      csel = csel->getright();
      delete prev;
      prev = csel;
    }
    //Down
    csel = rsel;
    prev = csel;
  }

  delete head;
};

void Board::setup(){
  std::stringstream convert;

  printBoard();
  printch();
  //foreach();
  //get the Chess Piece / Tower we are concerned with
  std::cout<<"Enter your piece using it\'s cooresponding character: ";
  char ty;
  std::string tt;
  std::getline(std::cin,tt);

  while(checktype(tt) == "NULL"){
    std::cout<<std::endl;
    printch();
    std::cout<<"Could not process your request...\nPlease re-enter your type value: ";
    std::getline(std::cin,tt);
  }
  //turn it into a char
  convert.clear();
  convert.str("");
  convert<<checktype(tt);
  convert>>ty;

  //get position of the tower
  std::cout<<"What position (Column Letter first, Row second- ex. A1): ";

  std::string coor;
  std::getline(std::cin,coor);

  while(checkcoor(coor) == "NULL"){
    std::cout<<std::endl;
    std::cout<<"Could not process your request...\nPlease re-enter your Position value (Col first, Row Second): ";
    std::getline(std::cin,coor);
  }


  find(checkcoor(coor))->getTower()->supersetter(checkcoor(coor),true,true,ty);

  //get if enemies are presnt
  std::cout<<"Are there enemies present (Y)es or (N)o: ";
  std::string e;

  std::getline(std::cin,e);

  while(checkyes(e) == "NULL"){
    std::cout<<std::endl;
    std::cout<<"Could not process your request...\nAre there enemies present (Y)es or (N)o: ";
    std::getline(std::cin,e);
  }

  char echo;
  //turn it into a char
  convert.clear();
  convert.str("");
  convert<<checkyes(e);
  convert>>echo;

  std::string dude = "";
  while(echo == 'Y' && dude != "-1"){
    //enemy is here
    printBoard();
    printch();
    //get the enemy that is present
    std::cout<<"Which enemy is present (Use character) (-1 to exit): ";

    std::getline(std::cin,dude);

    while(checktype(dude) == "NULL" && dude != "-1"){
      std::cout<<std::endl;
      printch();
      std::cout<<"Could not process your request...\nPlease re-enter the enemy type (-1 to exit): ";
      std::getline(std::cin,dude);
    }

    //turn type into a char
    char d;

    convert.clear();
    convert.str("");
    convert<<checktype(dude);
    convert>>d;

    if(dude != "-1"){
      //get that position of the enemy
      std::cout<<"What position (Column Letter first, Row second- ex. A1) (-1 to cancel): ";

      std::string poser;
      std::getline(std::cin,poser);
      //funyon = enemy presence, we say true until proven false
      bool funyon = true;
      //check if an enemy is in that position
      if(checkcoor(poser) != "NULL"){
        //std::cout<<"CUNT"<<std::endl;
        if(find(checkcoor(poser))->getTower()->getalive()){
          funyon = true;
        }
        else{
          funyon = false;
        }
      }
      while((checkcoor(poser) == "NULL" && poser != "-1") || (funyon && poser != "-1")){
        std::cout<<std::endl;
        if(checkcoor(poser) == "NULL"){
          std::cout<<"Could not process your request..."<<std::endl;
        }
        else{
          std::cout<<"There is an piece in such position. Unable to move the chess piece there."<<std::endl;
        }
        std::cout<<"Please re-enter your Position value (Col first, Row Second): ";
        std::getline(std::cin,poser);
        //get if an enemy is present
        if(checkcoor(poser) != "NULL"){
          if(find(checkcoor(poser))->getTower()->getalive()){
            funyon = true;
          }
          else{
            funyon = false;
          }
        }
      }
      if(poser != "-1"){
        find(checkcoor(poser))->getTower()->supersetter(checkcoor(poser),true,false,d);
      }
    }
  }

  printBoard();
  //get that final destination of the tower
  std::cout<<"What is the final destination (Col first, Row Second- ex. A1): ";

  std::string dest;
  std::getline(std::cin,dest);

  while(checkcoor(dest) == "NULL"){
    std::cout<<std::endl;
    std::cout<<"Could not process your request...\nPlease re-enter Destination Position (Col first, Row Second): ";
    std::getline(std::cin,dest);
  }
  //set the target to the destination we got
  settarget(checkcoor(dest));
  //set all the old towers now
  setoldtowers();
  std::cout<<"Successfully exited the setup"<<std::endl;
}
void Board::reconfig(){
  //clean it all up
  clean();
  //loop until they say to exit
  while(true){
    printBoard();
    std::stringstream convert;

    std::cout<<"What would you wish to recofigure:"<<std::endl;
    std::cout<<"\t1: Main Chess Piece"<<std::endl;
    std::cout<<"\t2: Enemy Chess Pieces"<<std::endl;
    std::cout<<"\t3: Destination"<<std::endl;
    std::cout<<"\t4: End Reconfiguration"<<std::endl;
    std::cout<<">";
    std::string inp;
    int in;
    std::getline(std::cin,inp);
    //convert the response to an int because I hate my life and try to make it difficult
    convert.clear();
    convert.str("");
    convert<<inp;
    convert>>in;
    //woo, the user decided that we do 1
    if(in == 1){
      std::cout<<"What would you like to change about the Main Chess Piece:"<<std::endl;
      std::cout<<"\t1: Position"<<std::endl;
      std::cout<<"\t2: Type of Piece"<<std::endl;
      std::string mc;
      int mci;
      //get the choice of the user and turn it into an int
      //                                            why an int? because I SAID SO GOD DAMMIT
      std::getline(std::cin,mc);
      convert.clear();
      convert.str("");
      convert<<mc;
      convert>>mci;
      //LOokie here,
      if(mci == 1){
        std::cout<<"Current Position: "<<findstart()->getposition()<<std::endl;
        std::cout<<"What Position should the chess piece move: ";
        std::string poser;
        std::getline(std::cin,poser);
        bool funyon = true;
        if(checkcoor(poser) != "NULL"){
          //std::cout<<"CUNT"<<std::endl;
          if(find(checkcoor(poser))->getTower()->getalive()){
            funyon = true;
          }
          else{
            funyon = false;
          }
        }
        //dude that friggin user is stupid
        if(checkcoor(poser) == "NULL" || funyon){
          std::cout<<"Could not process your request, returning to the recofiguration menu"<<std::endl;
        }
        else{
          //move that
          move(findstart(),find(checkcoor(poser)));
        }
      }
      else if(mci == 2){
        //get the type that we want the user to change it to
        printch();
        std::cout<<"Current type: "<<findstart()->getTower()->gettype()<<std::endl;
        std::cout<<"What Type do you wish to change your main Chess Piece to: ";
        std::string tt;

        std::getline(std::cin,tt);

        while(checktype(tt) == "NULL"){
          std::cout<<std::endl;
          printch();
          std::cout<<"Could not process your request...\nPlease re-enter your type value: ";
          std::getline(std::cin,tt);
        }
        convert.clear();
        convert.str("");
        //set it
        char t;
        convert<<checktype(tt);
        convert>>t;
        findstart()->getTower()->settype(t);
      }
      else{
        std::cout<<"Could not process your request, exiting to basic reconfiguration"<<std::endl;
      }
    }
    else if(in == 2){
      //get what they want to be done with th eenemy chess piece
      std::string duder;
      std::cout<<"1: Add an Enemy Chess Piece"<<std::endl;
      std::cout<<"2: Delete an Enemy Chess Piece"<<std::endl;
      std::cout<<"3: Exit"<<std::endl;
      std::cout<<">";
      std::getline(std::cin,duder);
      if(duder == "1"){
        printch();
        std::cout<<"Which piece type would you like to add (-1 to exit): ";
        std::string tt;
        std::getline(std::cin,tt);

        while(checktype(tt) == "NULL" || tt != "-1"){
          std::cout<<std::endl;
          printch();
          std::cout<<"Could not process your request...\nPlease re-enter your type value: ";
          std::getline(std::cin,tt);
        }
        convert.clear();
        convert.str("");
        if(tt != "-1"){
          std::cout<<"What position (Col First, Row Second) (-1 to exit): ";
          std::string poser;
          std::getline(std::cin,poser);
          //check if an enemy is in the position selected
          bool funyon = true;
          if(checkcoor(poser) != "NULL"){
            if(find(checkcoor(poser))->getTower()->getalive()){
              funyon = true;
            }
            else{
              funyon = false;
            }
          }
          while((checkcoor(poser) == "NULL" && poser != "-1") || (funyon && poser != "-1")){
            std::cout<<std::endl;
            if(checkcoor(poser) == "NULL"){
              std::cout<<"Could not process your request..."<<std::endl;
            }
            else{
              std::cout<<"There is an piece in such position. Unable to move the chess piece there."<<std::endl;
            }
            std::cout<<"Please re-enter your Position value (Col first, Row Second): ";
            std::getline(std::cin,poser);
            if(checkcoor(poser) != "NULL"){
              if(find(checkcoor(poser))->getTower()->getalive()){
                funyon = true;
              }
              else{
                funyon = false;
              }
            }
          }
          if(poser != "-1"){
            char t;
            convert<<checktype(tt);
            convert>>t;
            find(checkcoor(poser))->getTower()->settype(t);
            find(checkcoor(poser))->getTower()->makealive();
          }
        }
      }
      else if(duder == "2"){
        std::cout<<"What position is the enemy chess piece you would like to remove (-1 to exit): ";
        std::string fun;
        std::getline(std::cin,fun);
        if(checkcoor(fun) == "NULL"){
          std::cout<<"Could not process your request. Exiting to reconfiguration"<<std::endl;
        }
        else if(find(checkcoor(fun))->getTower()->getfriend()){
          std::cout<<"Unable to delete such tower, it is the friendly tower"<<std::endl;
        }
        else if(find(checkcoor(fun))->getTower()->getalive() == false){
          std::cout<<"No tower is in such position"<<std::endl;
        }
        else{
          find(checkcoor(fun))->getTower()->kill();
          std::cout<<"Enemy Chess piece sucessfully removed"<<std::endl;
        }
      }
      else if(duder == "3"){

      }
      else{
        std::cout<<"Could not process your request- exiting to the basic reconfiguration page"<<std::endl;
      }
    }
    else if(in == 3){
      //changing the final position
      std::cout<<"Current Destintation: "<<target<<std::endl;
      std::cout<<"Where do you wish to move the destination to: ";
      std::string bollocks;
      std::getline(std::cin,bollocks);
      while(checkcoor(bollocks) == "NULL"){
        std::cout<<std::endl;
        std::cout<<"Could not process your request...\nPlease re-enter your Position value (Col first, Row Second): ";
        std::getline(std::cin,bollocks);
      }
      //set the old one as not a target, set the new target in node form and in board form
      find(target)->nottarget();
      target = checkcoor(bollocks);
      find(target)->istarget();
    }
    else if(in == 4){
      setoldtowers();
      clean();
      return;
    }
    else{
      std::cout<<"Could not process your request"<<std::endl;
      std::cout<<"Please enter an integer value"<<std::endl;
    }
  }
}

//Getters
int Board::getrow(){
  return row;
};
int Board::getcol(){
  return col;
};
Node* Board::gethead(){
  return head;
};
std::string Board::gettarget(){
  return target;
};
std::string Board::getcolsstr(int num){
  return COLS.substr(num,1);
};
char Board::getcolsch(int num){
  //treat the ABC... as an array and select it for ability in creating the board
  std::stringstream convert;
  convert.clear();
  convert.str("");
  char target = ' ';
  convert<<getcolsstr(num);
  convert>>target;
  return target;
};
std::string longname(char c){
  //returns the long name of the piece given the char of the tower
  if(c == 'K'){
    return "King";
  }
  else if(c == 'Q'){
    return "Queen";
  }
  else if(c == 'H'){
    return "Knight";
  }
  else if(c == 'B'){
    return "Bishop";
  }
  else if(c == 'R'){
    return "Rook";
  }
  else if(c == 'P'){
    return "Pawn";
  }
  else{
    return "";
  }
}


//checker
std::string Board::checkcoor(std::string coor){
  //checks if the position/coordinates are valid or not
  //make it all uppercase
  std::transform(coor.begin(), coor.end(),coor.begin(), ::toupper); //happily stolen from the internet
  //std::cout<<"COORDINATES: "<<coor<<std::endl;
  //std::cout<<"coor length: "<<coor.length()<<std::endl;
  if(coor.length() > 1 && find(coor) == NULL){
    //check if the backwards is actually good
    std::string temp1, temp2, temp3;
    temp1 = coor.substr(coor.length() - 1,1);
    //std::cout<<"TEMP1: "<<temp1<<std::endl;
    temp2 = coor.substr(0,coor.length() - 1);
    //std::cout<<"temp2: "<<temp2<<std::endl;
    temp3 = temp1 + temp2;
    //std::cout<<"Temp3: "<<temp1<<temp2<<"|"<<temp3<<std::endl;
    if(find(temp3) != NULL){
      return temp3;
    }
  }
  if(find(coor) != NULL){
    //what we found is all good
    //std::cout<<"coor"<<coor<<std::endl;
    return coor;
  }
  return "NULL";
};
std::string Board::checktype(std::string t){
  //make it uppercase first so easier for checking
  std::transform(t.begin(), t.end(),t.begin(), ::toupper);
  if(t.length() == 1){
    if(t == "K" || t == "Q" || t == "H" || t == "P" || t == "R" || t == "B"){
      return t;
    }
  }
  else{
    //I got bored...
    if(t == "BUSH DID 911"){
      std::cout<<"Harambe can\'t melt steel beams"<<std::endl;
    }
    if(t == "HARAMBE"){
      std::cout<<"Our lord and saviour"<<std::endl;
    }

    if(t == "KING" || t == "ANDY" || t == "SCHMOOPLEZ"){
      return "K";
    }
    else if(t == "QUEEN" || t == "JUSTIN" || t == "POOPLEZ"){
      return "Q";
    }
    else if(t == "KNIGHT" || t == "HORSE" || t == "HORSEY" || t == "SAM"){
      return "H";
    }
    else if(t == "PAWN" || t == "PEASANT" || t == "DOM"){
      return "P";
    }
    else if(t == "ROOK" || t == "CASTLE" || t == "TOWER" || t == "BUSH DID 911"){
      return "R";
    }
    else if(t == "BISHOP" || t == "POPE" || t == "HARAMBE"){
      return "B";
    }
    else{
      return "NULL";
    }
  }
  return "NULL";
}
std::string Board::checkyes(std::string yeah){
  std::transform(yeah.begin(), yeah.end(),yeah.begin(), ::toupper);
  if(yeah.length() == 1){
    if(yeah == "Y" || yeah == "1"){
      return yeah;
    }
    else if(yeah == "N" || yeah == "0"){
      return yeah;
    }
  }
  else{
    if(yeah == "YES" || yeah == "YEAH" || yeah == "SURE" || yeah == "WHY NOT" || yeah == "YOLO" || yeah == "TRIANGLE" || yeah == "FO SHIZZLE MY NIZZLE" || yeah == "FO SHIZZLE"){
      return "Y";
    } //                                                               my safe word
    else if(yeah == "NO" || yeah == "NAH" || yeah == "NAY" || yeah == "PINEAPPLE"){
      return "N";
    }
  }
  return "NULL";
}

//Setters
void Board::setrow(int r){
  row = r;
};
void Board::setcol(int c){
  col = c;
};
void Board::settarget(std::string t){
  target = t;
  find(t)->istarget();
};

//FOR EACH
void Board::foreach(){
  //never to be actually used, just copied and pasted where necessary

  Node* rsel = head->getright();
  Node* csel = rsel;
  while(rsel != NULL){
    while(csel != NULL){
      std::cout<<csel->getposition()<<",";
      csel = csel->getright();
    }
    std::cout<<std::endl;
    rsel = rsel->getdown();
    csel = rsel;
  }
}


//prints
void Board::printch(){
  std::cout<<"K: King"<<std::endl<<"Q: Queen"<<std::endl<<"H: Knight"<<std::endl;
  std::cout<<"B: Bishop"<<std::endl<<"R: Rook"<<std::endl<<"P: Pawn"<<std::endl;
}
void Board::printdash(){
  std::cout<<"     ";
  for(int i = 0; i < col; i++){
    std::cout<<"----";
  }
  std::cout<<std::endl;
}
void Board::printBoard(){
  Node* rsel = head->getright();
  Node* csel = rsel;

  int cnt = row;

  std::cout<<"      ";
  //print the A   B   C   D....
  for(int i = 1; i <= col; i++){
    std::cout<<getcolsstr(i)<<"   ";
  }
  std::cout<<std::endl;
  printdash();

  while(rsel != NULL){
    std::cout<<cnt<<"   |";
    while(csel != NULL){
      std::string ender;
      ender = " ";

      if(csel->getTower()->getalive()){
        if(csel->getTower()->getfriend()){
          std::cout<<"*"<<csel->getTower()->gettype();
          ender = "*";
        }
        else{
          std::cout<<" "<<csel->getTower()->gettype();
        }
      }
      else{
        std::cout<<"  ";
      }

      if(csel->gettarget()){
        //destination
        ender = "#";
      }

      std::cout<<ender<<"|";

      csel = csel->getright();
    }
    std::cout<<std::endl;
    printdash();
    rsel = rsel->getdown();
    csel = rsel;
    cnt--;
  }
};
void Board::printaoms(){
  //prints the areas of attack of the enemies
  //and the areas of movement of the friendly
  Node* rsel = head->getright();
  Node* csel = rsel;

  int cnt = row;

  std::cout<<"\t";
  //print the A   B   C   D....
  for(int i = 1; i <= col; i++){
    std::cout<<getcolsstr(i)<<"   ";
  }
  std::cout<<std::endl;

  while(rsel != NULL){
    std::cout<<cnt<<"   |";
    while(csel != NULL){
      std::string ender;
      ender = "";

      if(csel->getTower()->getalive()){
        if(csel->getTower()->getfriend()){
          std::cout<<"*"<<csel->getTower()->gettype();
          ender = "*";
        }
        else{
          std::cout<<" "<<csel->getTower()->gettype();
        }
      }
      else{
        std::cout<<"  ";
      }

      std::cout<<ender;

      if(csel->getenemyaom()){
        ender = ender + "X";
      }
      if(csel->getmv()){
        ender = ender + "O";
      }

      if(ender == ""){
        ender = " ";
      }

      std::cout<<ender<<"|";
      csel = csel->getright();
    }
    std::cout<<std::endl;
    rsel = rsel->getdown();
    csel = rsel;
    cnt--;
  }
};
void Board::printpath(){
  Node* rsel = head->getright();
  Node* csel = rsel;

  int cnt = row;

  std::cout<<"\t";
  //print the A   B   C   D....
  for(int i = 1; i <= col; i++){
    std::cout<<getcolsstr(i)<<"   ";
  }
  std::cout<<std::endl;

  while(rsel != NULL){
    std::cout<<cnt<<"   |";
    while(csel != NULL){
      std::cout<<" "<<csel->getseq()<<" |";
      csel = csel->getright();
    }
    std::cout<<std::endl;
    rsel = rsel->getdown();
    csel = rsel;
    cnt--;
  }
};
void Board::debuggery(){
  printBoard();
  std::cout<<"AOMS"<<std::endl;
  printaoms();
  std::cout<<"paths"<<std::endl;
  printpath();
};
void Board::showpath(std::string p){
  Node* prev = findstart();
  char type = prev->getTower()->gettype();
  Node* next = prev;
  std::cout<<"Start position: "<<prev->getposition()<<std::endl;
  std::cout<<"Destination:    "<<target<<std::endl;
  std::cout<<"Path is:        "<<p<<std::endl;
  std::stringstream ss;
  ss.clear();
  ss.str("");
  ss.str(p);
  std::string lol;
  //loop through each position value and start it
  while(getline(ss,lol,',')){
    //move the previous tower to the next tower
    next = find(lol);
    next->getTower()->makealive();
    next->getTower()->makefriend();
    next->getTower()->settype(type);
    if(next != prev){
      prev->getTower()->kill();
    }
    prev = next;
    printBoard();
    std::cout<<"Current position: "<<lol<<std::endl;
    std::cout<<"Press Enter to continue"<<std::endl;
    std::cin.ignore();
  }
  std::cout<<"Destination has been reached"<<std::endl;
  std::cout<<"Path was: "<<p<<std::endl;
};


//finds
Node* Board::find(std::string p){
  Node* rsel = head->getright();
  std::string cp = p.substr(0,1); //col name
  std::string rp = p.substr(1); //row names
  //std::cout<<"Looking for: "<<p<<"|"<<cp<<rp<<std::endl;
  //go to the right until we find it
  while(rsel != NULL && rsel->getcol() != cp){
    //std::cout<<"Poop"<<std::endl;
    rsel = rsel->getright();
  }
  //go down until found
  while(rsel != NULL && rsel->getrow() != rp){
    //std::cout<<"Scoop"<<std::endl;
    rsel = rsel->getdown();
  }
  //if(rsel == NULL){
    //std::cout<<"SFDLKJ"<<std::endl;
  //}
  return rsel;
};
Node* Board::findseq(int s){
  Node* rsel = head->getright();
  Node* csel = rsel;
  while(rsel != NULL){
    while(csel != NULL){
      if(csel->getseq() == s){
        return csel;
      }
      csel = csel->getright();
    }
    rsel = rsel->getdown();
    csel = rsel;
  }
  return NULL;
};
Node* Board::findstart(){
  Node* rsel = head->getright();
  Node* csel = rsel;
  while(rsel != NULL){
    while(csel != NULL){
      if(csel->getTower()->getfriend() && csel->getTower()->getalive()){
        return csel;
      }
      csel = csel->getright();
    }
    rsel = rsel->getdown();
    csel = rsel;
  }
  return NULL;
};


//movement
void Board::copy(std::string a,std::string b){
  copy(find(a),find(b));
};
void Board::copy(Node* a ,Node* b){
  //copies the tower from the first tower to the second tower
  Tower* tow = a->getTower();
  b->getTower()->supersetter(tow->getposition(),tow->getalive(),tow->getfriend(),tow->gettype());
};
void Board::move(Node* a,Node* b){
  copy(a,b);
  //copy and kill
  a->getTower()->kill();
};
void Board::move(std::string a,std::string b){
  move(find(a),find(b));
};


//clean up
void Board::clearaom(){
  Node* rsel = head->getright();
  Node* csel = rsel;
  while(rsel != NULL){
    while(csel != NULL){
      csel->notenemyaom();
      csel->notmv();
      csel = csel->getright();
    }
    rsel = rsel->getdown();
    csel = rsel;
  }
};
void Board::updateaom(){
  clearaom();
  Node* rsel = head->getright();
  Node* csel = rsel;
  while(rsel != NULL){
    while(csel != NULL){
      if(csel->getTower()->getalive()){

        //enemy
        if(csel->enempresent()){
          for(int i = 0; i < csel->getmoves(); i++){
            int j = 1;
            while(csel->path(i,j) != NULL){
              csel->path(i,j)->isenemyaom();
              //csel->path(i,j)->setenemyaom(true);
              j++;
            }
          }
        }

        //OUR HERO
        if(csel->getTower()->getfriend()){
          for(int i = 0; i < csel->getmoves(); i++){
            int j = 1;
            while(csel->path(i,j) != NULL){
              csel->path(i,j)->ismv();
              j++;
            }
          }
        }

      }
      csel = csel->getright();
    }
    rsel = rsel->getdown();
    csel = rsel;
  }
};
void Board::reset(){
  //clears almost everything possible
  Node* rsel = head->getright();
  Node* csel = rsel;
  while(rsel != NULL){
    while(csel != NULL){
      csel->getTower()->supersetter(csel->getposition(),false,false,'A');
      csel->nottarget();
      csel->notmv();
      csel->notenemyaom();
      csel->setdistance(MAX);
      csel->notvisit();
      csel->setseq(-1);
      csel->setoldTower();
      csel = csel->getright();
    }
    rsel = rsel->getdown();
    csel = rsel;
  }
};
void Board::reverttowers(){
  //change the current tower to the old tower
  Node* rsel = head->getright();
  Node* csel = rsel;
  while(rsel != NULL){
    while(csel != NULL){
      csel->reverttower();
      csel = csel->getright();
    }
    rsel = rsel->getdown();
    csel = rsel;
  }
};
void Board::clean(){
  //resets what we need for the path to be found
  //sets distance to max, all unvisited, sequence is undefined- and is -2 so there is no reason for it to be ever seen
  head->setdistance(MAX);
  head->notvisit();
  head->setseq(-2);
  Node* rsel = head->getright();
  Node* csel = rsel;
  //for each node
  while(rsel != NULL){
    while(csel != NULL){
      //do what we did to the head
      csel->setdistance(MAX);
      csel->notvisit();
      csel->setseq(-1);
      csel = csel->getright();
    }
    rsel = rsel->getdown();
    csel = rsel;
  }
};
void Board::setoldtowers(){
  //make the current tower to the new tower
  Node* rsel = head->getright();
  Node* csel = rsel;
  while(rsel != NULL){
    while(csel != NULL){
      csel->setoldTower();
      csel = csel->getright();
    }
    rsel = rsel->getdown();
    csel = rsel;
  }
};


//dijkstra
std::string Board::pathquick(){
  //std::cout<<"Quick Path entered"<<std::endl;
  clean();
  //std::cout<<"Fun"<<std::endl;
  int nodecnt = row * col;
  //std::cout<<"Cumload"<<std::endl;
  //get the start and make it so it is the 0 of everything
  findstart()->setdistance(0);
  findstart()->setseq(0);
  //std::cout<<"Yoho"<<std::endl;
  //stores the path
  std::string p = "";
  for(int i = 0; i < nodecnt; i++){
    //printpath();
    //std::cin.ignore();
    //get the minimum distance and check if it is null
    std::string j = mindistance();
    Node* curr = NULL;
    if(j != ""){
      curr = find(j);
    }
    if(curr != NULL){
      //std::cout<<"Curr is not null"<<std::endl;
      curr->isvisit();
      if(curr->gettarget()){
        //std::cout<<"Path reached"<<std::endl;
        i = nodecnt;
        p = path(curr->getseq());
        return p;
      }
      else{
        //for each possible move
        for(int k = 0; k < curr->getmoves(); k++){
          //set the distance to the largest possible and work backwards until it is 0
          int u = 1;
          //std::cout<<"K: "<<k<<std::endl;

            //std::cout<<"U:"<<u<<std::endl;
            //std::cout<<"PATH:"<<curr->path(k,u)->getpos()<<std::endl;
            //if the position exists
            while(curr->path(k,u) != NULL){
              //if the position in question is greater than what we have now +1, we set it as next
              if(curr->getdistance() + 1 < curr->path(k,u)->getdistance()){
                Node* mover = curr->path(k,u);
                mover->setdistance(curr->getdistance() + 1);
                copy(curr,mover);
                mover->setseq(curr->getseq() + 1);
              }
              u++;
            }

        }
      }
    }
  }
  //std::cout<<"Path not reached by quick"<<std::endl;
  //base case, doesnt exist
  return p;
};
std::string Board::pathquickmiss(){
  //std::cout<<"Path miss entered"<<std::endl;
  //same as above, BUT-- commented below why
  clean();
  updateaom();
  //st
  //debuggery();
  int nodecnt = row * col;
  findstart()->setdistance(0);
  findstart()->setseq(0);
  std::string p = "";
  for(int i = 0; i < nodecnt; i++){
    updateaom();
    //debuggery();
    std::string j = mindistance();
    Node* curr = NULL;
    if(j != ""){
      curr = find(j);
    }
    if(curr != NULL){
      updateaom();
      //printaoms();
      //std::cin.ignore();
      curr->isvisit();
      if(curr->gettarget()){
        i = nodecnt;
        //printpath();
        p = path(curr->getseq());
        return p;
      }
      else{
        updateaom();
        for(int k = 0; k < curr->getmoves(); k++){
          //printaoms();
          int u = 1;

            while(curr->path(k,u) != NULL){
              //check if it is a point of enemy attack, and if an enemy is there
              //if either of the above is true; say oh no no to going
              if(curr->getdistance() + 1 < curr->path(k,u)->getdistance() && curr->path(k,u)->enempresent() == false){
                if(curr->path(k,u)->getenemyaom() == false){
                  if(curr->path(k,u)->enempresent() == false){
                    Node* mover = curr->path(k,u);
                    mover->setdistance(curr->getdistance() + 1);
                    copy(curr,mover);
                    mover->setseq(curr->getseq() + 1);
                  }
                }
              }
              u++;
            }

        }
      }
    }
  }
  return p;
};
std::string Board::pathquickattack(){
  //std::cout<<"Path attack entered"<<std::endl;
  clean();
  int nodecnt = row * col;
  findstart()->setdistance(0);
  findstart()->setseq(0);
  Node* start = findstart();
  std::string p = "";
  //debuggery();
  //std::cout<<"FSD"<<std::endl;
  for(int i = 0; i < nodecnt; i++){
    std::string j = mindistance();
    Node* curr = NULL;
    //std::cout<<"Dude"<<std::endl;
    if(j != ""){
      curr = find(j);
    }
    if(curr != NULL){
      //std::cout<<"Jumbo lover"<<std::endl;
      curr->isvisit();
      if(curr->gettarget()){
        //debuggery();
        i = nodecnt;
        //std::cout<<"SEQ: "<<curr->getseq()<<std::endl;
        p = path(curr->getseq());
        return p;
      }
      else{
        //revert the towers to the orginal way
        reverttowers();
        updateaom();
        //std::cout<<"Yolo"<<std::endl;
        copy(start,curr);
        Node* sel = curr;
        //std::cout<<"Gotten seq: "<<curr->getseq()<<std::endl;
        //loop through the previous moves so we get the board situation that we want

        //BACK TRACKING



        int tot = curr->getseq();
          for(int k = 0; k < sel->getmoves(); k++){
            //find if an enemy is present or not in the paths
            bool ep = false;
            for(int u = curr->getdistance(); u > 0; u--){
              for(int i = 0; i < curr->getmoves(); i++){
                int j = 1;
                while(curr->path(i,j) != NULL){
                  if(curr->path(i,j)->getseq() == tot){
                    if(curr->path(i,j)->enempresent()){
                      ep = true;
                    }
                  }
                  j++;
                }
              }
            //std::cout<<"\tK: "<<k<<std::endl;
            int z = 1;
            //std::cout<<"Money"<<std::endl;

              //std::cout<<"Z: "<<z<<std::endl;
              if(sel->path(k,z) != NULL){
                if(sel->path(k,z)->getdistance() == sel->getdistance() - 1){
                  if(curr->path(k,z)->enempresent() && ep == true){ //if the enemy is in the position and we are wanting that
                    //copy over when we found the previous cell
                    copy(curr, sel->path(k,z));
                    sel = sel->path(k,z);
                    k = curr->getmoves() + 1;
                    z = 0;
                    //std::cout<<"\t\tDick"<<std::endl;
                  }
                  else if(ep == false){
                    //copy over when we found the previous cell
                    copy(curr, sel->path(k,z));
                    sel = sel->path(k,z);
                    k = curr->getmoves() + 1;
                    z = 0;
                    //std::cout<<"\t\tDick"<<std::endl;
                  }
                }
                z++;
              }


            //std::cout<<"moneY"<<std::endl;
          }
        }
        //FORWARDS
        updateaom();
        //printaoms();
        for(int k = 0; k < curr->getmoves(); k++){
          //std::cout<<"\tK:"<<k<<std::endl;
          int u = 1;

            //std::cout<<"U: "<<u<<std::endl;
            while(curr->path(k,u) != NULL){
              //similar to above but only check if enemy aom
              if(curr->getdistance() + 1 < curr->path(k,u)->getdistance() && curr->path(k,u)->getenemyaom() == false){
                  Node* mover = curr->path(k,u);
                  mover->setdistance(curr->getdistance() + 1);
                  copy(curr,mover);
                  mover->setseq(curr->getseq() + 1);
              }
              u++;
            }

        }
      }
    }
    reverttowers();
    updateaom();
  }
  return p;
};
std::string Board::pathquickaround(){
  //std::cout<<"Path miss entered"<<std::endl;
  //same as above, BUT-- commented below why
  clean();
  updateaom();
  //st
  //debuggery();
  int nodecnt = row * col;
  findstart()->setdistance(0);
  findstart()->setseq(0);
  std::string p = "";
  for(int i = 0; i < nodecnt; i++){
    //updateaom();
    //debuggery();
    std::string j = mindistance();
    Node* curr = NULL;
    if(j != ""){
      curr = find(j);
    }
    if(curr != NULL){
      //updateaom();
      //printaoms();
      //std::cin.ignore();
      curr->isvisit();
      if(curr->gettarget()){
        i = nodecnt;
        //printpath();
        p = path(curr->getseq());
        return p;
      }
      else{
        for(int k = 0; k < curr->getmoves(); k++){
          //printaoms();
          int u = 1;
            while(curr->path(k,u) != NULL){
              //check if it is a point of enemy attack, and if an enemy is there
              //if either of the above is true; say oh no no to going
              if(curr->getdistance() + 1 < curr->path(k,u)->getdistance() && curr->path(k,u)->enempresent() == false){

                  Node* mover = curr->path(k,u);
                  mover->setdistance(curr->getdistance() + 1);
                  copy(curr,mover);
                  mover->setseq(curr->getseq() + 1);

              }
              u++;
            }
        }
      }
    }
  }
  return p;
};
std::string Board::mindistance(){
  //set some base cases
  int min = MAX;
  std::string minindex = "";
  //std::cout<<"Enter mindistance"<<std::endl;
  Node* rsel = head->getright();
  Node* csel = rsel;
  //for each node
  while(rsel != NULL){
    while(csel != NULL){
      //if the place is not visited and the distance smaller than MAX, set it
      if(csel->getvisit() == false && csel->getdistance() < min){
        min = csel->getdistance();
        minindex = csel->getposition();
      }
      csel = csel->getright();
    }
    rsel = rsel->getdown();
    csel = rsel;
  }
  //found minimum distance or nothing, either way return value
  return minindex;
};
std::string Board::path(int tot){
  reverttowers();
  //std::cout<<"Path figurer entered"<<std::endl;
  Node* curr = find(target);
  //char type = findstart()->getTower()->gettype();
  Node* start = findstart();
  //if the tower is the pawn, go to the pawn path, else stay here
  if(start->getTower()->gettype() == 'P'){
    return pawnpath(tot);
  }

  //std::cout<<"TYPE: "<<type<<std::endl;
  //first position is the last one
  std::string p = "";
  p = curr->getposition();
  //std::cout<<p<<std::endl;
  tot--;

  while(tot >= 0){
    copy(start,curr);
    //gets whether or not a position has an enemy present
    bool ep = false;
    for(int i = 0; i < curr->getmoves(); i++){

      int j = 1;
      //std::cout<<i<<","<<j<<std::endl;
      while(curr->path(i,j) != NULL){
        //std::cout<<i<<","<<j<<std::endl;
        if(curr->path(i,j)->getseq() == tot){
          if(curr->path(i,j)->enempresent()){
            ep = true;
          }
        }
        j++;
      }
    }

      for(int i = 0; i < curr->getmoves(); i++){

        int j = 1;
        //std::cout<<i<<","<<j<<std::endl;
        while(curr->path(i,j) != NULL){
          //std::cout<<i<<","<<j<<std::endl;
          if(curr->path(i,j)->getseq() == tot){
            //std::cout<<"found the thingy"<<std::endl;
            //move(curr, curr->path(i,j));
            if(curr->path(i,j)->enempresent() && ep == true){ //if the enemy is in the position and we are wanting that
              //then we go there
              curr = curr->path(i,j);
              p = curr->getposition() + "," + p;
              j = MAX - 100;
              i = start->getmoves();
            }
            else if(ep == false){
              //if there are none that were set in the path making, then we go forward and return this
              curr = curr->path(i,j);
              p = curr->getposition() + "," + p;
              j = MAX - 100;
              i = start->getmoves();
            }
          }
          j++;
        }


    }
    //std::cin.ignore();
    tot--;
  }
  //std::cout<<"path finalized"<<std::endl;
  return p;
};
std::string Board::pawnpath(int tot){
  //pawn is not revertible
  //same as above, but we use backpawnpath to do the reversiblilty
  //reverttowers();
  //std::cout<<"Path figurer entered"<<std::endl;
  Node* curr = find(target);
  //char type = findstart()->getTower()->gettype();
  Node* start = findstart();

  //std::cout<<"TYPE: "<<type<<std::endl;

  std::string p = "";
  p = curr->getposition();
  //std::cout<<p<<std::endl;
  tot--;

  while(tot >= 0){
    copy(start,curr);

    for(int i = 0; i < curr->getmoves(); i++){

      int j = 1;
      //std::cout<<i<<","<<j<<std::endl;
      while(curr->backpawnpath(i,j) != NULL){
        //std::cout<<i<<","<<j<<std::endl;
        if(curr->backpawnpath(i,j)->getseq() == tot){
          //std::cout<<"found the thingy"<<std::endl;
          //move(curr, curr->path(i,j));
          curr = curr->backpawnpath(i,j);
          p = curr->getposition() + "," + p;
          j = MAX - 100;
          i = curr->getmoves();
        }
        j++;
      }
    }
    //std::cin.ignore();
    tot--;
  }
  //std::cout<<"path finalized"<<std::endl;
  return p;
};

//KNIGHTS TOUR stuff
std::string Board::kpath(Node* sel){
  updatePM();
  Node* next = NULL;
  int min = 10;
  //find the lowest pm
  for(int i = 0; i < sel->getmoves(); i++){
    if(sel->path(i,1) != NULL){
      Node* pather = sel->path(i,1);
      //check if has been visited
      if(pather->getvisit() == false){
        //check if position has lower possible movement areas than current
        if(pather->getPM() < min){
          //if it is the head then NO NO NO
          if(pather != head){
            next = pather;
            min = pather->getPM();
          }
        }
      }
    }
  }
  //set the current as visited and send the knight to the next position
  sel->isvisit();
  //if it is the last, the above will have next be null
  if(next == NULL){
    return sel->getposition();
  }
  else{
    //otherwise we continue on
    move(sel,next);
    return sel->getposition() + "," + kpath(next);
  }
}
void Board::updatePM(){
  Node* rsel = head->getright();
  Node* csel = rsel;
  while(rsel != NULL){
    while(csel != NULL){
      csel->setPM();
      csel= csel->getright();
    }
    rsel = rsel->getdown();
    csel = rsel;
  }
  //std::cout<<"PM Updated"<<std::endl;
}
bool Board::checkPM(){
  Node* rsel = head->getright();
  Node* csel = rsel;
  while(rsel != NULL){
    while(csel != NULL){
      if(csel->getvisit() == false){
        return false;
      }
      csel = csel->getright();
    }
    rsel = rsel->getdown();
    csel = rsel;
  }
  //all were visited, therefore return true
  return true;
}
