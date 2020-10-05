# $@: target, $^ dependencies, % pattern

COMPILER=g++
FLAGS=-Wall -pthread -std=c++11

all: client server

client: client.o client.class.o functions.o message.o configReader.o exceptionBase.o configReaderException.o
	$(COMPILER) $(FLAGS) $^ -o $@

server: fileSystem.o server.o server.class.o functions.o
	$(COMPILER) $(FLAGS) $^ -o $@

%.o: %.cpp 
	$(COMPILER) $(FLAGS) -c $^ 

message.o: message.cpp
	$(COMPILER) $(FLAGS) -c message.cpp

configReader.o: Infrastructure/configReader.cpp
	$(COMPILER) $(FLAGS) -c Infrastructure/configReader.cpp

exceptionBase.o: Infrastructure/exceptionBase.cpp
	$(COMPILER) $(FLAGS) -c Infrastructure/exceptionBase.cpp

configReaderException.o: Infrastructure/configReaderException.cpp
	$(COMPILER) $(FLAGS) -c Infrastructure/configReaderException.cpp

clean:
	rm *.o client server
