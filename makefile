# $@: target, $^ dependencies, % pattern

COMPILER=g++
FLAGS=-Wall -pthread -std=c++11
INFRASTRUCTURE=configReader.o exceptionBase.o configReaderException.o functions.o message.o
DATEBASE=messageRepositoryException.o messageRepository.o idGeneratorException.o idGenerator.o
SERVERDEPENDENCIES=server.class.o messageHandler.o messageHandlerException.o fileSystem.o
CLIENTDEPENDENCIES=client.class.o

all: client server

client: client.o $(CLIENTDEPENDENCIES) $(INFRASTRUCTURE)
	$(COMPILER) $(FLAGS) $^ -o $@

server: server.o $(SERVERDEPENDENCIES) $(INFRASTRUCTURE) $(DATEBASE)
	$(COMPILER) $(FLAGS) $^ -o $@

%.o: %.cpp 
	$(COMPILER) $(FLAGS) -c $^ 

%.o: Infrastructure/%.cpp 
	$(COMPILER) $(FLAGS) -c $^ 

%.o: Database/%.cpp 
	$(COMPILER) $(FLAGS) -c $^ 

clean:
	rm *.o client server
