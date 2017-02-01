C_FLAGS=-Wall -Wextra -DDEBUG -g -pedantic -std=c++14
SOURCES = hamza_p1.cpp 

all: hamza_p1

hamza_p1: hamza_p1.o
		g++ $(C_FLAGS) hamza_p1.o -o hamza_p1

hamza_p1.o: hamza_p1.cpp 
		g++ -c $(C_FLAGS) hamza_p1.cpp -o hamza_p1.o

run: all
		./hamza_p1


clean:
		rm -f *.o hamza_p1



