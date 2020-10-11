# $@: target, $^ dependencies, % pattern

COMPILER=g++
FLAGS=-Wall -pthread -std=c++11
OBJDIR= obj
INFRASTRUCTURE= $(addprefix $(OBJDIR)/, exceptionBase.o functions.o message.o)
DATEBASE= $(addprefix $(OBJDIR)/, messageRepositoryException.o messageRepository.o idGeneratorException.o idGenerator.o)
SERVERDEPENDENCIES= $(addprefix $(OBJDIR)/, server.class.o messageHandler.o messageHandlerException.o fileSystem.o)
CLIENTDEPENDENCIES= $(addprefix $(OBJDIR)/, client.class.o configReader.o configReaderException.o)

all: client server

client: obj/client.o $(CLIENTDEPENDENCIES) $(INFRASTRUCTURE)
	$(COMPILER) $(FLAGS) $^ -o $@

server: obj/server.o $(SERVERDEPENDENCIES) $(INFRASTRUCTURE) $(DATEBASE)
	$(COMPILER) $(FLAGS) $^ -o $@

obj/%.o: %.cpp 
	$(COMPILER) $(FLAGS) -c $^ -o $@

obj/%.o: Infrastructure/%.cpp 
	$(COMPILER) $(FLAGS) -c $^ -o $@

obj/%.o: Database/%.cpp 
	$(COMPILER) $(FLAGS) -c $^ -o $@

obj/%.o: ServerDependencies/%.cpp
	$(COMPILER) $(FLAGS) -c $^ -o $@

obj/%.o: ClientDependencies/%.cpp
	$(COMPILER) $(FLAGS) -c $^ -o $@

clean:
	rm *.o client server obj/*.o
