COMPILER=g++
FLAGS=-Wall


all: client server

client: client.o client.class.o functions.o
	$(COMPILER) $(FLAGS) functions.o client.o client.class.o -o client

server: server.o server.class.o functions.o
	$(COMPILER) $(FLAGS) functions.o server.o -o server

client.o: client.cpp
	$(COMPILER) $(FLAGS) -c client.cpp

client.class.o: client.class.cpp
	$(COMPILER) $(FLAGS) -c client.class.cpp

server.o: server.cpp
	$(COMPILER) $(FLAGS) -c server.cpp

server.class.o: server.class.cpp
	$(COMPILER) $(FLAGS) -c server.class.cpp

functions.o: functions.cpp
	$(COMPILER) $(FLAGS) -c functions.cpp

clean:
	rm *.o client server
