CC=g++
CFLAGS= -g -Wall

final: Tower.o Node.o Board.o God.o Pboard.o Ni.o Waffle.o main.o
	$(CC) $(CFLAGS) Tower.o Node.o Board.o God.o Pboard.o Ni.o Waffle.o main.o -o final
Tower.o: Tower.cpp Tower.h
	$(CC) $(CFLAGS) -c Tower.cpp
Node.o: Node.cpp Node.h  Tower.h
	$(CC) $(CFLAGS) -c Node.cpp
Board.o: Board.cpp Board.h  Node.h
	$(CC) $(CFLAGS) -c Board.cpp
God.o: God.cpp God.h  Board.h
	$(CC) $(CFLAGS) -c God.cpp
Pboard.o: Pboard.cpp Pboard.h  Board.h
	$(CC) $(CFLAGS) -c Pboard.cpp
Ni.o: Ni.h Ni.cpp Board.h
	$(CC) $(CFLAGS) -c Ni.cpp
Waffle.o: God.h Pboard.h Ni.h Waffle.h Waffle.cpp
	$(CC) $(CFLAGS) -c Waffle.cpp
main.o: main.cpp  Waffle.h
	$(CC) $(CFLAGS) -c main.cpp
clean:
	rm -f *.o
	rm final
run: final
	./final
mem: final
	valgrind --leak-check=full ./final
