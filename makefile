COMPILER=g++




client: client.o client.class.o
	$(COMPILER) client.o client.class.o -o client

server:

client.o: client.cpp
	$(COMPILER) -c client.cpp

client.class.o: client.class.cpp
	$(COMPILER) -c client.class.cpp

clean:
	rm *.o client server
