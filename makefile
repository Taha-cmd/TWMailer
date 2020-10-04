# $@: target, $^ dependencies, % pattern

COMPILER=g++
FLAGS=-Wall -pthread -std=c++11

all: client server

client: client.o client.class.o functions.o
	$(COMPILER) $(FLAGS) $^ -o $@

server: fileSystem.o server.o server.class.o functions.o
	$(COMPILER) $(FLAGS) $^ -o $@

%.o: %.cpp 
	$(COMPILER) $(FLAGS) -c $^ 

clean:
	rm *.o client server
