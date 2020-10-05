COMPILER=g++
FLAGS=-Wall -pthread
INFRASTRUCTURE= configReader.o exceptionBase.o configReaderException.o


all: client server

client: client.o client.class.o functions.o message.o $(INFRASTRUCTURE)
	$(COMPILER) $(FLAGS) functions.o client.o client.class.o message.o $(INFRASTRUCTURE) -o client

server: fileSystem.o server.o server.class.o functions.o
	$(COMPILER) $(FLAGS) fileSystem.o functions.o server.o server.class.o -o server

client.o: client.cpp
	$(COMPILER) $(FLAGS) -c client.cpp

client.class.o:	client.class.cpp
	$(COMPILER) $(FLAGS) -c client.class.cpp

server.o: server.cpp
	$(COMPILER) $(FLAGS) -c server.cpp

server.class.o: server.class.cpp
	$(COMPILER) $(FLAGS) -c server.class.cpp

fileSystem.o: fileSystem.cpp
	$(COMPILER) $(FLAGS) -c fileSystem.cpp

functions.o: functions.cpp
	$(COMPILER) $(FLAGS) -c functions.cpp

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
