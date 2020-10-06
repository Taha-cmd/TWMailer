# $@: target, $^ dependencies, % pattern

COMPILER=g++
FLAGS=-Wall -pthread -std=c++11
INFRASTRUCTURE=configReader.o exceptionBase.o configReaderException.o
DATEBASE=messageRepositoryException.o messageRepository.o idGeneratorException.o idGenerator.o

all: client server

client: client.o client.class.o functions.o message.o $(INFRASTRUCTURE)
	$(COMPILER) $(FLAGS) $^ -o $@

server: fileSystem.o server.o server.class.o functions.o $(INFRASTRUCTURE) $(DATEBASE)
	$(COMPILER) $(FLAGS) $^ -o $@

%.o: %.cpp 
	$(COMPILER) $(FLAGS) -c $^ 

%.o: Infrastructure/%.cpp 
	$(COMPILER) $(FLAGS) -c $^ 

%.o: Database/%.cpp 
	$(COMPILER) $(FLAGS) -c $^ 

clean:
	rm *.o client server
